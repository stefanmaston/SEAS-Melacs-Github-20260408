#include "register_image.h"

#include "image_lock.h"
#include "log_history.h"
#include "logger.h"

#include <string.h>

#if !defined(__PIC32MX__)
#include <pthread.h>

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void image_lock(void)
{
    pthread_mutex_lock(&g_lock);
}

void image_unlock(void)
{
    pthread_mutex_unlock(&g_lock);
}
#endif

enum {
    COIL_DIO4 = 16,
    COIL_SIP = 32,
    COIL_H1_DIS = 40,
    COIL_H2_DIS = 43,
    REG_AO = 100,
    REG_H_PWM = 110,
    REG_NOTE = 114,
    REG_MEAS = 30,
    REG_SAFE = 200,
    REG_LOG_PERIOD = 201,
    REG_RTC_YEAR = 202,
    REG_RTC_SET = 209,
    REG_HIST_ARM = 220
};

static PlcInputs g_in;
static PlcStatus g_st;
static RtcClock g_clk;
static PlcOutputs g_cmd;
static uint16_t g_safe_mode;
static uint16_t g_log_period;
static bool g_master;
static bool g_set_level;
static bool g_clock_pending;
static RtcClock g_clock_req;
static uint16_t g_setbuf[7];

static int bit_get(const uint8_t *src, uint16_t index)
{
    return (src[index / 8u] >> (index % 8u)) & 1;
}

static void bit_put(uint8_t *dest, uint16_t index, int on)
{
    uint8_t mask = (uint8_t)(1u << (index % 8u));

    if (on) {
        dest[index / 8u] |= mask;
    } else {
        dest[index / 8u] &= (uint8_t)~mask;
    }
}

static int read_discrete(uint16_t addr)
{
    switch (addr) {
    case 0: return g_in.dio_in[0];
    case 1: return g_in.dio_in[1];
    case 2: return g_in.dio_in[2];
    case 3: return g_in.dio_in[3];
    case 8: return g_in.sd_ok;
    case 9: return g_st.logger_ok;
    case 10: return g_st.plc_loaded;
    case 11: return g_st.plc_running;
    default: return 0;
    }
}

static bool *coil_slot(uint16_t addr)
{
    if (addr >= COIL_DIO4 && addr < COIL_DIO4 + 4) {
        return &g_cmd.dio_out[addr - COIL_DIO4];
    }
    if (addr >= COIL_SIP && addr < COIL_SIP + 8) {
        return &g_cmd.sip[addr - COIL_SIP];
    }
    switch (addr) {
    case COIL_H1_DIS: return &g_cmd.h1_dis;
    case COIL_H1_DIS + 1: return &g_cmd.h1_ali;
    case COIL_H1_DIS + 2: return &g_cmd.h1_bli;
    case COIL_H2_DIS: return &g_cmd.h2_dis;
    case COIL_H2_DIS + 1: return &g_cmd.h2_ali;
    case COIL_H2_DIS + 2: return &g_cmd.h2_bli;
    default: return NULL;
    }
}

static int read_coil(uint16_t addr)
{
    bool *slot = coil_slot(addr);
    return slot != NULL && *slot;
}

static uint16_t read_input_reg(uint16_t addr)
{
    if (addr < 8) {
        return g_in.ad[addr];
    }
    if (addr >= 10 && addr <= 15) {
        return g_in.ai[addr - 10];
    }
    if (addr >= REG_MEAS && addr < REG_MEAS + 5) {
        const uint16_t meas[] = {
            g_in.t_board, g_in.p, g_in.t1, g_in.t2, g_in.value
        };
        return meas[addr - REG_MEAS];
    }
    if (addr == 20) {
        return g_in.error_code;
    }
    if (addr >= LOG_HIST_STATUS) {
        return log_history_reg(addr);
    }
    return 0;
}

static uint16_t read_holding_reg(uint16_t addr)
{
    switch (addr) {
    case REG_AO: return g_cmd.ao[0];
    case REG_AO + 1: return g_cmd.ao[1];
    case REG_AO + 2: return g_cmd.ao[2];
    case REG_H_PWM: return g_cmd.h1_ahi;
    case REG_H_PWM + 1: return g_cmd.h1_bhi;
    case REG_H_PWM + 2: return g_cmd.h2_ahi;
    case REG_H_PWM + 3: return g_cmd.h2_bhi;
    case REG_NOTE: return g_cmd.note;
    case REG_SAFE: return g_safe_mode;
    case REG_LOG_PERIOD: return g_log_period;
    case REG_RTC_YEAR: return g_clk.year;
    case REG_RTC_YEAR + 1: return g_clk.month;
    case REG_RTC_YEAR + 2: return g_clk.day;
    case REG_RTC_YEAR + 3: return g_clk.hour;
    case REG_RTC_YEAR + 4: return g_clk.minute;
    case REG_RTC_YEAR + 5: return g_clk.second;
    case REG_RTC_YEAR + 6: return g_clk.weekday;
    case REG_RTC_SET: return 0;
    case REG_HIST_ARM: return log_history_minutes();
    default: return 0;
    }
}

static bool holding_writable(uint16_t addr)
{
    return (addr >= REG_AO && addr <= REG_AO + 2)
        || (addr >= REG_H_PWM && addr <= REG_NOTE)
        || (addr >= REG_SAFE && addr <= REG_RTC_SET)
        || addr == REG_HIST_ARM;
}

static bool clock_from_buf(RtcClock *clk)
{
    clk->year = g_setbuf[0];
    clk->month = (uint8_t)g_setbuf[1];
    clk->day = (uint8_t)g_setbuf[2];
    clk->hour = (uint8_t)g_setbuf[3];
    clk->minute = (uint8_t)g_setbuf[4];
    clk->second = (uint8_t)g_setbuf[5];
    clk->weekday = (uint8_t)g_setbuf[6];
    return rtc_valid(clk);
}

static void seed_setbuf(void)
{
    g_setbuf[0] = g_clk.year;
    g_setbuf[1] = g_clk.month;
    g_setbuf[2] = g_clk.day;
    g_setbuf[3] = g_clk.hour;
    g_setbuf[4] = g_clk.minute;
    g_setbuf[5] = g_clk.second;
    g_setbuf[6] = g_clk.weekday;
}

static void note_output_write(void)
{
    g_master = true;
}

static void write_one_holding(uint16_t addr, uint16_t value, bool *rising)
{
    if (addr >= REG_RTC_YEAR && addr < REG_RTC_SET) {
        g_setbuf[addr - REG_RTC_YEAR] = value;
        return;
    }
    if (addr == REG_RTC_SET) {
        bool on = value != 0;
        if (on && !g_set_level) {
            *rising = true;
        }
        g_set_level = on;
        return;
    }
    if (addr == REG_SAFE) {
        g_safe_mode = value;
        return;
    }
    if (addr == REG_LOG_PERIOD) {
        g_log_period = value == 0 ? MELACS_LOG_PERIOD_S : value;
        return;
    }
    if (addr >= REG_AO && addr < REG_AO + 3) {
        g_cmd.ao[addr - REG_AO] = value;
        note_output_write();
        return;
    }
    if (addr >= REG_H_PWM && addr < REG_H_PWM + 4) {
        uint16_t *pwm[] = { &g_cmd.h1_ahi, &g_cmd.h1_bhi, &g_cmd.h2_ahi, &g_cmd.h2_bhi };
        *pwm[addr - REG_H_PWM] = value;
        note_output_write();
        return;
    }
    if (addr == REG_NOTE) {
        g_cmd.note = value;
        note_output_write();
        return;
    }
    if (addr == REG_HIST_ARM) {
        log_history_arm(value, &g_clk);
    }
}

void register_image_init(void)
{
    image_lock();
    memset(&g_in, 0, sizeof(g_in));
    memset(&g_st, 0, sizeof(g_st));
    memset(&g_clk, 0, sizeof(g_clk));
    memset(&g_cmd, 0, sizeof(g_cmd));
    g_cmd.h1_dis = true;
    g_cmd.h2_dis = true;
    g_safe_mode = 0;
    g_log_period = MELACS_LOG_PERIOD_S;
    g_master = false;
    g_set_level = false;
    g_clock_pending = false;
    seed_setbuf();
    image_unlock();
}

void register_image_publish(const PlcInputs *in, const PlcOutputs *physical,
                            const PlcStatus *st, const RtcClock *clk)
{
    (void)physical;
    image_lock();
    g_in = *in;
    g_st = *st;
    g_clk = *clk;
    image_unlock();
}

void register_image_commands(PlcOutputs *cmd, uint16_t *safe_mode,
                             uint16_t *log_period_s, bool *master)
{
    image_lock();
    *cmd = g_cmd;
    *safe_mode = g_safe_mode;
    *log_period_s = g_log_period;
    *master = g_master;
    image_unlock();
}

bool register_image_take_clock(RtcClock *clk)
{
    bool pending;

    image_lock();
    pending = g_clock_pending;
    if (pending) {
        *clk = g_clock_req;
        g_clock_pending = false;
    }
    image_unlock();
    return pending;
}

int register_image_read_bits(bool coils, uint16_t addr, uint16_t count, uint8_t *dest)
{
    uint16_t i;
    uint16_t nbytes;

    if (count == 0 || count > 2000) {
        return 3;
    }
    if ((uint32_t)addr + count > 65536u) {
        return 2;
    }
    nbytes = (uint16_t)((count + 7u) / 8u);
    memset(dest, 0, nbytes);

    image_lock();
    for (i = 0; i < count; i++) {
        int on = coils ? read_coil((uint16_t)(addr + i))
                       : read_discrete((uint16_t)(addr + i));
        bit_put(dest, i, on);
    }
    image_unlock();
    return 0;
}

int register_image_read_regs(bool holding, uint16_t addr, uint16_t count, uint16_t *dest)
{
    uint16_t i;

    if (count == 0 || count > 125) {
        return 3;
    }
    if ((uint32_t)addr + count > 65536u) {
        return 2;
    }

    image_lock();
    for (i = 0; i < count; i++) {
        uint16_t a = (uint16_t)(addr + i);
        dest[i] = holding ? read_holding_reg(a) : read_input_reg(a);
    }
    image_unlock();
    return 0;
}

int register_image_write_coils(uint16_t addr, uint16_t count, const uint8_t *src)
{
    uint16_t i;

    if (count == 0 || count > 2000) {
        return 3;
    }
    if ((uint32_t)addr + count > 65536u) {
        return 2;
    }
    for (i = 0; i < count; i++) {
        if (coil_slot((uint16_t)(addr + i)) == NULL) {
            return 2;
        }
    }

    image_lock();
    for (i = 0; i < count; i++) {
        *coil_slot((uint16_t)(addr + i)) = bit_get(src, i) != 0;
    }
    note_output_write();
    image_unlock();
    return 0;
}

int register_image_write_regs(uint16_t addr, uint16_t count, const uint16_t *src)
{
    uint16_t i;
    bool rising = false;
    RtcClock requested;

    if (count == 0 || count > 123) {
        return 3;
    }
    if ((uint32_t)addr + count > 65536u) {
        return 2;
    }
    for (i = 0; i < count; i++) {
        if (!holding_writable((uint16_t)(addr + i))) {
            return 2;
        }
    }

    image_lock();
    for (i = 0; i < count; i++) {
        write_one_holding((uint16_t)(addr + i), src[i], &rising);
    }
    if (rising && clock_from_buf(&requested)) {
        g_clock_req = requested;
        g_clock_pending = true;
    }
    image_unlock();
    return 0;
}
