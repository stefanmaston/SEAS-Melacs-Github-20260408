#include "loc_runtime.h"

#include "image_lock.h"
#include "protect.h"

#include <string.h>

#define LOC_N_STACK 16
#define LOC_N_LOCAL 32
#define LOC_N_TIMER 16
#define LOC_N_EDGE 16

static uint8_t g_stage[LOC_MAX_IMAGE];
static uint16_t g_expect;
static uint16_t g_high;
static uint16_t g_off;
static bool g_open;
static bool g_stage_error;

static uint8_t g_active[LOC_MAX_IMAGE];
static uint16_t g_active_len;
static bool g_fault;
static uint16_t g_fault_code;
static uint16_t g_last_steps;
static bool g_save_pending;

static uint16_t g_local[LOC_N_LOCAL];
static uint16_t g_timer[LOC_N_TIMER];
static uint8_t g_edge[LOC_N_EDGE];

static void reset_vm(void)
{
    memset(g_local, 0, sizeof(g_local));
    memset(g_timer, 0, sizeof(g_timer));
    memset(g_edge, 0, sizeof(g_edge));
    g_last_steps = 0;
}

static void fail_image(uint16_t code)
{
    g_active_len = 0;
    g_fault = true;
    g_fault_code = code;
    g_open = false;
    reset_vm();
}

static int image_valid(const uint8_t *img, uint16_t len)
{
    uint16_t version;
    uint16_t body;
    uint32_t crc;

    if (len < LOC_HEADER_LEN + LOC_MASK_LEN + 1u || len > LOC_MAX_IMAGE) {
        return 0;
    }
    if (img[0] != 'M' || img[1] != 'P' || img[2] != 'L' || img[3] != '1') {
        return 0;
    }
    version = (uint16_t)(img[4] | ((uint16_t)img[5] << 8));
    body = (uint16_t)(img[6] | ((uint16_t)img[7] << 8));
    crc = (uint32_t)img[8]
        | ((uint32_t)img[9] << 8)
        | ((uint32_t)img[10] << 16)
        | ((uint32_t)img[11] << 24);
    if (version != 1u) {
        return 0;
    }
    if ((uint32_t)body + LOC_HEADER_LEN != len) {
        return 0;
    }
    return protect_crc32(img + LOC_HEADER_LEN, body) == crc;
}

static uint32_t active_mask(void)
{
    const uint8_t *p;

    if (g_active_len < LOC_HEADER_LEN + LOC_MASK_LEN) {
        return 0;
    }
    p = g_active + LOC_HEADER_LEN;
    return (uint32_t)p[0]
        | ((uint32_t)p[1] << 8)
        | ((uint32_t)p[2] << 16)
        | ((uint32_t)p[3] << 24);
}

static void begin_stage(void)
{
    memset(g_stage, 0, sizeof(g_stage));
    g_expect = 0;
    g_high = 0;
    g_off = 0;
    g_open = true;
    g_stage_error = false;
}

static void commit_stage(void)
{
    if (!g_open || g_stage_error || g_expect == 0 || g_expect > LOC_MAX_IMAGE
        || g_high < g_expect || !image_valid(g_stage, g_expect)) {
        fail_image(1);
        return;
    }
    memcpy(g_active, g_stage, g_expect);
    g_active_len = g_expect;
    g_fault = false;
    g_fault_code = 0;
    g_open = false;
    reset_vm();
}

static void store_word(uint16_t index, uint16_t value)
{
    uint32_t pos;

    if (!g_open) {
        return;
    }
    pos = (uint32_t)g_off + (uint32_t)index * 2u;
    if (pos + 1u >= LOC_MAX_IMAGE) {
        g_stage_error = true;
        return;
    }
    g_stage[pos] = (uint8_t)(value >> 8);
    g_stage[pos + 1u] = (uint8_t)value;
    if (pos + 2u > g_high) {
        g_high = (uint16_t)(pos + 2u);
    }
}

void loc_init(void)
{
    memset(g_stage, 0, sizeof(g_stage));
    g_expect = 0;
    g_high = 0;
    g_off = 0;
    g_open = false;
    g_stage_error = false;
    g_active_len = 0;
    g_fault = false;
    g_fault_code = 0;
    g_save_pending = false;
    reset_vm();
}

bool loc_ok(void)
{
    bool ok;

    image_lock();
    ok = g_active_len != 0 && !g_fault;
    image_unlock();
    return ok;
}

bool loc_fault(void)
{
    bool fault;

    image_lock();
    fault = g_fault;
    image_unlock();
    return fault;
}

uint32_t loc_own_mask(void)
{
    uint32_t mask;

    image_lock();
    mask = g_active_len != 0 && !g_fault ? active_mask() : 0u;
    image_unlock();
    return mask;
}

uint16_t loc_steps(void)
{
    return g_last_steps;
}

uint16_t loc_fault_code(void)
{
    return g_fault_code;
}

static uint16_t load_src(const PlcInputs *in, uint8_t src, int *bad)
{
    if (src < 4u) {
        return in->dio_in[src] ? 1u : 0u;
    }
    if (src < 10u) {
        return in->ai[src - 4u];
    }
    if (src < 18u) {
        return in->ad[src - 10u];
    }
    *bad = 1;
    return 0;
}

static void store_q_bool(PlcOutputs *out, uint8_t ch, uint16_t value, int *bad)
{
    bool on = value != 0;

    switch (ch) {
    case 0: case 1: case 2: case 3:
        out->dio_out[ch] = on;
        break;
    case 4: case 5: case 6: case 7:
    case 8: case 9: case 10: case 11:
        out->sip[ch - 4u] = on;
        break;
    case 12: out->h1_dis = on; break;
    case 13: out->h1_ali = on; break;
    case 14: out->h1_bli = on; break;
    case 15: out->h2_dis = on; break;
    case 16: out->h2_ali = on; break;
    case 17: out->h2_bli = on; break;
    default:
        *bad = 1;
        break;
    }
}

static void store_q_word(PlcOutputs *out, uint8_t ch, uint16_t value, int *bad)
{
    switch (ch) {
    case 0: case 1: case 2:
        out->ao[ch] = value;
        break;
    case 3: out->h1_ahi = value; break;
    case 4: out->h1_bhi = value; break;
    case 5: out->h2_ahi = value; break;
    case 6: out->h2_bhi = value; break;
    default:
        *bad = 1;
        break;
    }
}

void loc_step(const PlcInputs *in, PlcOutputs *out)
{
    uint16_t stack[LOC_N_STACK];
    int sp = 0;
    int steps = 0;
    int bad = 0;
    int ended = 0;
    const uint8_t *p;
    const uint8_t *end;

    memset(out, 0, sizeof(*out));
    out->h1_dis = true;
    out->h2_dis = true;

    image_lock();
    g_last_steps = 0;
    if (g_fault || g_active_len == 0) {
        image_unlock();
        return;
    }

    p = g_active + LOC_HEADER_LEN + LOC_MASK_LEN;
    end = g_active + g_active_len;
    while (p < end && steps < (int)LOC_MAX_STEPS && !bad) {
        uint8_t op = *p++;
        uint16_t a;
        uint16_t b;
        uint8_t id;
        uint16_t pt;

        steps++;
        switch (op) {
        case LOC_OP_END:
            ended = 1;
            p = end;
            break;
        case LOC_OP_LD_BOOL:
        case LOC_OP_LD_WORD:
            if (p >= end) {
                bad = 1;
                break;
            }
            a = load_src(in, *p++, &bad);
            if (sp >= LOC_N_STACK) {
                bad = 1;
            } else {
                stack[sp++] = a;
            }
            break;
        case LOC_OP_LDC:
            if (p + 2 > end || sp >= LOC_N_STACK) {
                bad = 1;
                break;
            }
            a = (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
            p += 2;
            stack[sp++] = a;
            break;
        case LOC_OP_NOT:
            if (sp < 1) {
                bad = 1;
                break;
            }
            stack[sp - 1] = stack[sp - 1] == 0 ? 1u : 0u;
            break;
        case LOC_OP_AND:
        case LOC_OP_OR:
        case LOC_OP_XOR:
        case LOC_OP_EQ:
        case LOC_OP_NE:
        case LOC_OP_LT:
        case LOC_OP_GT:
        case LOC_OP_LE:
        case LOC_OP_GE:
            if (sp < 2) {
                bad = 1;
                break;
            }
            b = stack[--sp];
            a = stack[--sp];
            if (op == LOC_OP_AND) {
                a = (a != 0 && b != 0) ? 1u : 0u;
            } else if (op == LOC_OP_OR) {
                a = (a != 0 || b != 0) ? 1u : 0u;
            } else if (op == LOC_OP_XOR) {
                a = ((a != 0) != (b != 0)) ? 1u : 0u;
            } else if (op == LOC_OP_EQ) {
                a = a == b ? 1u : 0u;
            } else if (op == LOC_OP_NE) {
                a = a != b ? 1u : 0u;
            } else if (op == LOC_OP_LT) {
                a = a < b ? 1u : 0u;
            } else if (op == LOC_OP_GT) {
                a = a > b ? 1u : 0u;
            } else if (op == LOC_OP_LE) {
                a = a <= b ? 1u : 0u;
            } else {
                a = a >= b ? 1u : 0u;
            }
            stack[sp++] = a;
            break;
        case LOC_OP_TON:
            if (p + 3 > end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            pt = (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
            p += 2;
            if (id >= LOC_N_TIMER) {
                bad = 1;
                break;
            }
            a = stack[--sp];
            if (a != 0) {
                if (g_timer[id] < 0xFFFFu) {
                    g_timer[id]++;
                }
            } else {
                g_timer[id] = 0;
            }
            if (pt == 0) {
                b = a != 0 ? 1u : 0u;
            } else {
                b = g_timer[id] >= pt ? 1u : 0u;
            }
            stack[sp++] = b;
            break;
        case LOC_OP_RTRIG:
        case LOC_OP_FTRIG:
            if (p >= end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= LOC_N_EDGE) {
                bad = 1;
                break;
            }
            a = stack[--sp] != 0 ? 1u : 0u;
            if (op == LOC_OP_RTRIG) {
                b = (a != 0 && g_edge[id] == 0) ? 1u : 0u;
            } else {
                b = (a == 0 && g_edge[id] != 0) ? 1u : 0u;
            }
            g_edge[id] = (uint8_t)a;
            stack[sp++] = b;
            break;
        case LOC_OP_ST_Q_BOOL:
        case LOC_OP_ST_Q_WORD:
            if (p >= end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            a = stack[--sp];
            if (op == LOC_OP_ST_Q_BOOL) {
                store_q_bool(out, id, a, &bad);
            } else {
                store_q_word(out, id, a, &bad);
            }
            break;
        case LOC_OP_ST_LOCAL:
            if (p >= end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= LOC_N_LOCAL) {
                bad = 1;
                break;
            }
            g_local[id] = stack[--sp];
            break;
        case LOC_OP_LD_LOCAL:
            if (p >= end || sp >= LOC_N_STACK) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= LOC_N_LOCAL) {
                bad = 1;
                break;
            }
            stack[sp++] = g_local[id];
            break;
        default:
            bad = 1;
            break;
        }
    }

    g_last_steps = (uint16_t)steps;
    if (!ended || bad || sp != 0) {
        fail_image(bad ? 4u : (sp != 0 ? 3u : 2u));
        memset(out, 0, sizeof(*out));
        out->h1_dis = true;
        out->h2_dis = true;
    }
    image_unlock();
}

void loc_apply(uint32_t mask, const PlcOutputs *local, PlcOutputs *out)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (mask & (1u << i)) {
            out->dio_out[i] = local->dio_out[i];
        }
    }
    for (i = 0; i < 8; i++) {
        if (mask & (1u << (4 + i))) {
            out->sip[i] = local->sip[i];
        }
    }
    if (mask & (1u << 12)) {
        out->h1_dis = local->h1_dis;
    }
    if (mask & (1u << 13)) {
        out->h1_ali = local->h1_ali;
    }
    if (mask & (1u << 14)) {
        out->h1_bli = local->h1_bli;
    }
    if (mask & (1u << 15)) {
        out->h2_dis = local->h2_dis;
    }
    if (mask & (1u << 16)) {
        out->h2_ali = local->h2_ali;
    }
    if (mask & (1u << 17)) {
        out->h2_bli = local->h2_bli;
    }
    for (i = 0; i < 3; i++) {
        if (mask & (1u << (18 + i))) {
            out->ao[i] = local->ao[i];
        }
    }
    if (mask & (1u << 21)) {
        out->h1_ahi = local->h1_ahi;
    }
    if (mask & (1u << 22)) {
        out->h1_bhi = local->h1_bhi;
    }
    if (mask & (1u << 23)) {
        out->h2_ahi = local->h2_ahi;
    }
    if (mask & (1u << 24)) {
        out->h2_bhi = local->h2_bhi;
    }
}

bool loc_is_holding(uint16_t addr)
{
    return (addr >= LOC_REG_CTRL && addr <= LOC_REG_DATA + LOC_REG_DATA_N - 1u)
        || addr == LOC_REG_OWN_LO || addr == LOC_REG_OWN_HI;
}

bool loc_holding_writable(uint16_t addr)
{
    return loc_is_holding(addr);
}

bool loc_write_reg(uint16_t addr, uint16_t value)
{
    if (!loc_is_holding(addr)) {
        return false;
    }
    if (addr == LOC_REG_CTRL) {
        if (value == 1u) {
            begin_stage();
        } else if (value == 2u) {
            commit_stage();
        } else if (value == 3u) {
            g_open = false;
        } else if (value == 4u) {
            g_save_pending = true;
        }
        return true;
    }
    if (addr == LOC_REG_LEN) {
        if (g_open) {
            g_expect = value;
            if (value == 0 || value > LOC_MAX_IMAGE) {
                g_stage_error = true;
            }
        }
        return true;
    }
    if (addr == LOC_REG_OFF) {
        g_off = value;
        return true;
    }
    if (addr >= LOC_REG_DATA && addr < LOC_REG_DATA + LOC_REG_DATA_N) {
        store_word((uint16_t)(addr - LOC_REG_DATA), value);
        return true;
    }
    return true;
}

bool loc_read_holding(uint16_t addr, uint16_t *value)
{
    uint32_t crc;
    uint32_t mask;

    if (!loc_is_holding(addr)) {
        return false;
    }
    *value = 0;
    if (addr == LOC_REG_LEN) {
        *value = g_expect;
    } else if (addr == LOC_REG_OFF) {
        *value = g_off;
    } else if (addr == LOC_REG_CRC_LO || addr == LOC_REG_CRC_HI) {
        if (g_active_len > LOC_HEADER_LEN) {
            crc = protect_crc32(g_active + LOC_HEADER_LEN,
                                (uint16_t)(g_active_len - LOC_HEADER_LEN));
            *value = addr == LOC_REG_CRC_LO ? (uint16_t)crc : (uint16_t)(crc >> 16);
        }
    } else if (addr == LOC_REG_OWN_LO || addr == LOC_REG_OWN_HI) {
        mask = g_active_len != 0 && !g_fault ? active_mask() : 0u;
        *value = addr == LOC_REG_OWN_LO ? (uint16_t)mask : (uint16_t)(mask >> 16);
    } else if (addr >= LOC_REG_DATA && addr < LOC_REG_DATA + LOC_REG_DATA_N) {
        uint32_t pos = (uint32_t)g_off + (uint32_t)(addr - LOC_REG_DATA) * 2u;
        if (pos + 1u < LOC_MAX_IMAGE) {
            *value = (uint16_t)(((uint16_t)g_stage[pos] << 8) | g_stage[pos + 1u]);
        }
    }
    return true;
}

bool loc_is_input(uint16_t addr)
{
    return addr >= LOC_IN_STATUS && addr <= LOC_IN_FAULT;
}

uint16_t loc_read_input(uint16_t addr)
{
    uint16_t status = 0;
    uint32_t crc;

    if (addr == LOC_IN_STEPS) {
        return g_last_steps;
    }
    if (addr == LOC_IN_FAULT) {
        return g_fault_code;
    }
    if (addr == LOC_IN_CRC_LO || addr == LOC_IN_CRC_HI) {
        if (g_active_len > LOC_HEADER_LEN) {
            crc = protect_crc32(g_active + LOC_HEADER_LEN,
                                (uint16_t)(g_active_len - LOC_HEADER_LEN));
            return addr == LOC_IN_CRC_LO ? (uint16_t)crc : (uint16_t)(crc >> 16);
        }
        return 0;
    }
    if (addr != LOC_IN_STATUS) {
        return 0;
    }
    if (g_active_len != 0 && !g_fault) {
        status |= 1u;
        status |= 16u;
    }
    if (g_fault) {
        status |= 2u;
    }
    if (g_open) {
        status |= 8u;
    }
    return status;
}

bool loc_take_save(void)
{
    bool pending;

    image_lock();
    pending = g_save_pending;
    g_save_pending = false;
    image_unlock();
    return pending;
}

void loc_load_sd(void)
{
    uint8_t buf[LOC_MAX_IMAGE];
    uint16_t len = 0;

    if (!plat_blob_read(LOC_FILE_NAME, buf, LOC_MAX_IMAGE, &len)) {
        return;
    }
    image_lock();
    if (!image_valid(buf, len)) {
        image_unlock();
        return;
    }
    memcpy(g_active, buf, len);
    g_active_len = len;
    g_fault = false;
    g_fault_code = 0;
    reset_vm();
    image_unlock();
}

void loc_save_sd(void)
{
    uint8_t buf[LOC_MAX_IMAGE];
    uint16_t len;

    image_lock();
    if (g_active_len == 0 || g_fault) {
        image_unlock();
        return;
    }
    len = g_active_len;
    memcpy(buf, g_active, len);
    image_unlock();
    (void)plat_blob_write(LOC_FILE_NAME, buf, len);
}
