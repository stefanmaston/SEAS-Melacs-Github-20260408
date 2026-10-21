#include "fast_ctrl.h"

#include <string.h>

typedef struct {
    uint16_t enable;
    uint16_t feedback;
    uint16_t output;
    uint16_t setpoint;
    int16_t kp;
    int16_t ki;
    int16_t kd;
    uint16_t period_ms;
    uint16_t out_min;
    uint16_t out_max;
} PidCfg;

typedef struct {
    uint16_t ilk[FAST_N_ILK];
    PidCfg pid[FAST_N_PID];
} FastCfg;

typedef struct {
    int64_t integ;      /* Q8.8 utsignalsenheter gånger ms, så små ki inte avrundas bort */
    int32_t prev_fb;
    uint16_t count;
    uint16_t out;
    int16_t err;
    uint16_t fb;
    bool primed;
} PidState;

/* Skrivs av Modbus under fast_lock. Läses av avbrottet när g_dirty är satt. */
static FastCfg g_shadow;
static volatile bool g_dirty;
static volatile bool g_reset_req;
static volatile bool g_run;

/* Ägs av avbrottet. */
static FastCfg g_cfg;
static PidState g_pid[FAST_N_PID];
static uint8_t g_tripped;

/* Speglas ut till huvudloopen. 8- och 16-bitars läsningar är odelbara på PIC32. */
static volatile uint8_t g_owned;
static volatile uint8_t g_block_mask;
static volatile uint8_t g_status_tripped;
static volatile uint8_t g_cfg_error;
static volatile uint16_t g_ticks;
static volatile uint16_t g_isr_max_us;
static volatile uint16_t g_status_out[FAST_N_PID];
static volatile uint16_t g_status_fb[FAST_N_PID];
static volatile int16_t g_status_err[FAST_N_PID];
static volatile uint8_t g_guard;
static volatile uint32_t g_now_ms;
static volatile uint32_t g_sweep_ms;

#if !defined(__PIC32MX__)
#include <pthread.h>

static pthread_mutex_t g_fast_mutex = PTHREAD_MUTEX_INITIALIZER;

void fast_lock(void)
{
    pthread_mutex_lock(&g_fast_mutex);
}

void fast_unlock(void)
{
    pthread_mutex_unlock(&g_fast_mutex);
}
#endif

static void pid_defaults(PidCfg *cfg)
{
    memset(cfg, 0, sizeof(*cfg));
    cfg->period_ms = 10;
}

void fast_ctrl_init(void)
{
    int c;

    fast_lock();
    memset(&g_shadow, 0, sizeof(g_shadow));
    for (c = 0; c < FAST_N_PID; c++) {
        pid_defaults(&g_shadow.pid[c]);
    }
    g_cfg = g_shadow;
    memset(g_pid, 0, sizeof(g_pid));
    g_tripped = 0;
    g_dirty = false;
    g_reset_req = false;
    g_run = false;
    g_owned = 0;
    g_block_mask = 0;
    g_status_tripped = 0;
    g_cfg_error = 0;
    g_ticks = 0;
    g_isr_max_us = 0;
    g_guard = 0;
    g_now_ms = 0;
    g_sweep_ms = 0;
    for (c = 0; c < FAST_N_PID; c++) {
        g_status_out[c] = 0;
        g_status_fb[c] = 0;
        g_status_err[c] = 0;
    }
    fast_unlock();
}

void fast_ctrl_set_run(bool running)
{
    g_run = running;
}

void fast_ctrl_set_guard(bool h1, bool h2)
{
    g_guard = (uint8_t)((h1 ? 1u : 0u) | (h2 ? 2u : 0u));
}

void fast_ctrl_note_time(uint32_t now_ms)
{
    g_now_ms = now_ms;
}

void fast_ctrl_sweep_kick(uint32_t now_ms)
{
    g_sweep_ms = now_ms;
}

static int bridge_of(uint16_t pwm)
{
    return pwm < 2u ? 0 : 1;
}

static uint16_t pid_period(const PidCfg *cfg)
{
    if (cfg->period_ms == 0) {
        return 10;
    }
    if (cfg->period_ms > 1000u) {
        return 1000;
    }
    return cfg->period_ms;
}

static bool pid_valid(const FastCfg *cfg, int c)
{
    const PidCfg *p = &cfg->pid[c];
    int other;

    if (p->feedback > 5u || p->output >= FAST_N_PWM || p->out_min > p->out_max) {
        return false;
    }
    for (other = 0; other < c; other++) {
        const PidCfg *q = &cfg->pid[other];
        if (q->enable && q->output == p->output) {
            return false;
        }
    }
    return true;
}

static void take_config(void)
{
    FastCfg next = g_shadow;
    int c;

    for (c = 0; c < FAST_N_PID; c++) {
        if (memcmp(&next.pid[c], &g_cfg.pid[c], sizeof(PidCfg)) != 0) {
            memset(&g_pid[c], 0, sizeof(g_pid[c]));
        }
    }
    g_cfg = next;
}

static void step_interlocks(const FastIn *in, uint8_t *block)
{
    uint8_t active = 0;
    int i;

    for (i = 0; i < FAST_N_ILK; i++) {
        uint16_t cfg = g_cfg.ilk[i];
        bool level;
        bool trip;

        if ((cfg & FAST_ILK_ENABLE) == 0) {
            g_tripped &= (uint8_t)~(1u << i);
            continue;
        }
        level = in->dio_in[cfg & FAST_ILK_INPUT_MASK];
        trip = (cfg & FAST_ILK_TRIP_HIGH) ? level : !level;
        if (trip) {
            active |= (uint8_t)(1u << i);
        }
    }
    if (g_reset_req) {
        /* Kvittering släpper bara förreglingar vars ingång har återgått. */
        g_tripped &= active;
        g_reset_req = false;
    }
    g_tripped |= active;

    *block = 0;
    for (i = 0; i < FAST_N_ILK; i++) {
        if (g_tripped & (1u << i)) {
            if (g_cfg.ilk[i] & FAST_ILK_BLOCK_H1) {
                *block |= 1u;
            }
            if (g_cfg.ilk[i] & FAST_ILK_BLOCK_H2) {
                *block |= 2u;
            }
        }
    }
}

static uint16_t clamp_u16(int64_t value, uint16_t lo, uint16_t hi)
{
    if (value < (int64_t)lo) {
        return lo;
    }
    if (value > (int64_t)hi) {
        return hi;
    }
    return (uint16_t)value;
}

static void step_pid(int c, const FastIn *in, bool may_run)
{
    const PidCfg *cfg = &g_cfg.pid[c];
    PidState *st = &g_pid[c];
    uint16_t period = pid_period(cfg);
    int32_t fb = (int32_t)in->ai[cfg->feedback];
    int32_t err;
    int64_t p;
    int64_t i_add;
    int64_t d;
    int64_t u;

    st->fb = (uint16_t)fb;
    if (!may_run) {
        st->integ = 0;
        st->count = 0;
        st->out = 0;
        st->err = 0;
        st->prev_fb = fb;
        st->primed = false;
        return;
    }
    if (!st->primed) {
        st->prev_fb = fb;
        st->primed = true;
        st->count = period; /* räkna direkt vid start */
    }
    if (++st->count < period) {
        return;
    }
    st->count = 0;

    err = (int32_t)cfg->setpoint - fb;
    p = (int64_t)cfg->kp * err;
    i_add = (int64_t)cfg->ki * err * period;
    d = -(int64_t)cfg->kd * (fb - st->prev_fb) * 1000 / period;
    st->prev_fb = fb;

    u = (p + (st->integ + i_add) / 1000 + d) / 256;
    /* Villkorlig integrering: integrera inte vidare in i mättnad. */
    if (!((u > (int64_t)cfg->out_max && i_add > 0) ||
          (u < (int64_t)cfg->out_min && i_add < 0))) {
        st->integ += i_add;
        u = (p + st->integ / 1000 + d) / 256;
    }
    st->out = clamp_u16(u, cfg->out_min, cfg->out_max);
    st->err = (int16_t)(err > 32767 ? 32767 : (err < -32768 ? -32768 : err));
}

void fast_ctrl_step(const FastIn *in, FastOut *out)
{
    uint8_t block = 0;
    uint8_t owned = 0;
    uint8_t cfg_error = 0;
    int c;

#if !defined(__PIC32MX__)
    fast_lock();
#endif
    if (g_dirty) {
        take_config();
        g_dirty = false;
    }

    step_interlocks(in, &block);
    block |= g_guard;
    if (g_now_ms != 0 && (uint32_t)(g_now_ms - g_sweep_ms) > FAST_SWEEP_LATE_MS) {
        block |= 3u;
    }

    memset(out, 0, sizeof(*out));
    for (c = 0; c < FAST_N_PID; c++) {
        const PidCfg *cfg = &g_cfg.pid[c];
        bool valid = pid_valid(&g_cfg, c);
        bool enabled = cfg->enable != 0;
        bool may_run;

        if (enabled && !valid) {
            cfg_error |= (uint8_t)(1u << c);
        }
        if (!enabled || !valid) {
            step_pid(c, in, false);
            continue;
        }
        owned |= (uint8_t)(1u << cfg->output);
        may_run = g_run && (block & (1u << bridge_of(cfg->output))) == 0;
        step_pid(c, in, may_run);
        out->pwm[cfg->output] = g_pid[c].out;
    }
    out->pwm_owned = owned;
    out->block[0] = (block & 1u) != 0;
    out->block[1] = (block & 2u) != 0;

    g_owned = owned;
    g_block_mask = block;
    g_status_tripped = g_tripped;
    g_cfg_error = cfg_error;
    for (c = 0; c < FAST_N_PID; c++) {
        g_status_out[c] = g_pid[c].out;
        g_status_fb[c] = g_pid[c].fb;
        g_status_err[c] = g_pid[c].err;
    }
    g_ticks++;
#if !defined(__PIC32MX__)
    fast_unlock();
#endif
}

uint8_t fast_ctrl_owned_pwm(void)
{
    return g_owned;
}

bool fast_ctrl_blocked(int bridge)
{
    return (g_block_mask & (1u << (bridge & 1))) != 0;
}

void fast_ctrl_note_isr_us(uint16_t us)
{
    if (us > g_isr_max_us) {
        g_isr_max_us = us;
    }
}

bool fast_ctrl_is_reg(uint16_t addr)
{
    return addr >= FAST_REG_FIRST && addr <= FAST_REG_LAST;
}

static uint16_t *pid_field(PidCfg *cfg, uint16_t field)
{
    switch (field) {
    case 0: return &cfg->enable;
    case 1: return &cfg->feedback;
    case 2: return &cfg->output;
    case 3: return &cfg->setpoint;
    case 4: return (uint16_t *)&cfg->kp;
    case 5: return (uint16_t *)&cfg->ki;
    case 6: return (uint16_t *)&cfg->kd;
    case 7: return &cfg->period_ms;
    case 8: return &cfg->out_min;
    case 9: return &cfg->out_max;
    default: return 0;
    }
}

static uint16_t *shadow_slot(uint16_t addr)
{
    if (addr >= FAST_REG_ILK_CFG && addr < FAST_REG_ILK_CFG + FAST_N_ILK) {
        return &g_shadow.ilk[addr - FAST_REG_ILK_CFG];
    }
    if (addr >= FAST_REG_PID && addr < FAST_REG_PID + FAST_N_PID * FAST_REG_PID_STRIDE) {
        uint16_t rel = (uint16_t)(addr - FAST_REG_PID);
        return pid_field(&g_shadow.pid[rel / FAST_REG_PID_STRIDE], rel % FAST_REG_PID_STRIDE);
    }
    return 0;
}

bool fast_ctrl_writable(uint16_t addr)
{
    return addr == FAST_REG_ILK_RESET || shadow_slot(addr) != 0;
}

/* Anroparen håller fast_lock, så ett helt FC16-svep blir synligt på en gång. */
bool fast_ctrl_write_reg(uint16_t addr, uint16_t value)
{
    uint16_t *slot;

    if (!fast_ctrl_is_reg(addr)) {
        return false;
    }
    if (addr == FAST_REG_ILK_RESET) {
        if (value != 0) {
            g_reset_req = true;
        }
        return true;
    }
    slot = shadow_slot(addr);
    if (slot != 0) {
        *slot = value;
        g_dirty = true;
    }
    return true;
}

bool fast_ctrl_read_holding(uint16_t addr, uint16_t *value)
{
    uint16_t *slot;

    if (!fast_ctrl_is_reg(addr)) {
        return false;
    }
    slot = shadow_slot(addr);
    *value = slot != 0 ? *slot : 0;
    return true;
}

bool fast_ctrl_read_input(uint16_t addr, uint16_t *value)
{
    if (!fast_ctrl_is_reg(addr)) {
        return false;
    }
    *value = 0;
    if (addr == 300u) {
        *value = (uint16_t)(g_status_tripped | ((uint16_t)g_block_mask << 8));
    } else if (addr == 301u) {
        *value = g_ticks;
    } else if (addr == 302u) {
        *value = g_isr_max_us;
    } else if (addr == 303u) {
        *value = g_cfg_error;
    } else if (addr >= FAST_REG_PID && addr < FAST_REG_PID + FAST_N_PID * FAST_REG_PID_STRIDE) {
        uint16_t rel = (uint16_t)(addr - FAST_REG_PID);
        int c = rel / FAST_REG_PID_STRIDE;

        switch (rel % FAST_REG_PID_STRIDE) {
        case 0: *value = g_status_out[c]; break;
        case 1: *value = g_status_fb[c]; break;
        case 2: *value = (uint16_t)g_status_err[c]; break;
        default: break;
        }
    }
    return true;
}
