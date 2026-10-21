#include "protect.h"

#include "image_lock.h"

#include <string.h>

#define PROT_N_STACK 8
#define PROT_N_LOCAL 16
#define PROT_N_TIMER 8
#define PROT_N_EDGE 8

static uint8_t g_stage[PROT_MAX_IMAGE];
static uint16_t g_expect;
static uint16_t g_high;
static uint16_t g_off;
static bool g_open;
static bool g_stage_error;

static uint8_t g_active[PROT_MAX_IMAGE];
static uint16_t g_active_len;
static bool g_fault;
static uint8_t g_kick;

static uint16_t g_local[PROT_N_LOCAL];
static uint16_t g_timer[PROT_N_TIMER];
static uint8_t g_edge[PROT_N_EDGE];

static void reset_vm(void)
{
    memset(g_local, 0, sizeof(g_local));
    memset(g_timer, 0, sizeof(g_timer));
    memset(g_edge, 0, sizeof(g_edge));
}

static void fail_image(void)
{
    g_active_len = 0;
    g_fault = true;
    g_open = false;
    reset_vm();
}

uint32_t protect_crc32(const uint8_t *data, uint16_t len)
{
    uint32_t crc = 0xFFFFFFFFu;
    uint16_t i;
    int bit;

    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++) {
            uint32_t mask = (uint32_t)-(int32_t)(crc & 1u);
            crc = (crc >> 1) ^ (0xEDB88320u & mask);
        }
    }
    return ~crc;
}

static int image_valid(const uint8_t *img, uint16_t len)
{
    uint16_t version;
    uint16_t body;
    uint32_t crc;

    if (len < PROT_HEADER_LEN + 1u || len > PROT_MAX_IMAGE) {
        return 0;
    }
    if (img[0] != 'M' || img[1] != 'P' || img[2] != 'I' || img[3] != '1') {
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
    if ((uint32_t)body + PROT_HEADER_LEN != len) {
        return 0;
    }
    return protect_crc32(img + PROT_HEADER_LEN, body) == crc;
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
    if (!g_open || g_stage_error || g_expect == 0 || g_expect > PROT_MAX_IMAGE
        || g_high < g_expect || !image_valid(g_stage, g_expect)) {
        fail_image();
        return;
    }
    memcpy(g_active, g_stage, g_expect);
    g_active_len = g_expect;
    g_fault = false;
    g_open = false;
    reset_vm();
}

void protect_init(void)
{
    memset(g_stage, 0, sizeof(g_stage));
    g_expect = 0;
    g_high = 0;
    g_off = 0;
    g_open = false;
    g_stage_error = false;
    g_active_len = 0;
    g_fault = false;
    g_kick = 0;
    reset_vm();
}

bool protect_ok(void)
{
    bool ok;

    image_lock();
    ok = g_active_len != 0 && !g_fault;
    image_unlock();
    return ok;
}

bool protect_fault(void)
{
    bool fault;

    image_lock();
    fault = g_fault;
    image_unlock();
    return fault;
}

static uint16_t load_src(const ProtectIn *in, uint8_t src, int *bad)
{
    if (src < 4u) {
        return in->dio[src] ? 1u : 0u;
    }
    if (src < 10u) {
        return in->ai[src - 4u];
    }
    *bad = 1;
    return 0;
}

void protect_step(const ProtectIn *in, ProtectOut *out)
{
    uint16_t stack[PROT_N_STACK];
    int sp = 0;
    int steps = 0;
    int bad = 0;
    int ended = 0;
    uint16_t mask = 0;
    const uint8_t *p;
    const uint8_t *end;

    image_lock();
    out->mask = 0;
    out->fault = g_fault || g_active_len == 0;
    if (g_fault || g_active_len == 0) {
        image_unlock();
        return;
    }

    p = g_active + PROT_HEADER_LEN;
    end = g_active + g_active_len;
    while (p < end && steps < (int)PROT_MAX_STEPS && !bad) {
        uint8_t op = *p++;
        uint16_t a;
        uint16_t b;
        uint8_t id;
        uint16_t pt;

        steps++;
        switch (op) {
        case PROT_OP_END:
            ended = 1;
            p = end;
            break;
        case PROT_OP_LD_BOOL:
        case PROT_OP_LD_WORD:
            if (p >= end) {
                bad = 1;
                break;
            }
            a = load_src(in, *p++, &bad);
            if (sp >= PROT_N_STACK) {
                bad = 1;
            } else {
                stack[sp++] = a;
            }
            break;
        case PROT_OP_LDC:
            if (p + 2 > end || sp >= PROT_N_STACK) {
                bad = 1;
                break;
            }
            a = (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
            p += 2;
            stack[sp++] = a;
            break;
        case PROT_OP_NOT:
            if (sp < 1) {
                bad = 1;
                break;
            }
            stack[sp - 1] = stack[sp - 1] == 0 ? 1u : 0u;
            break;
        case PROT_OP_AND:
        case PROT_OP_OR:
        case PROT_OP_XOR:
        case PROT_OP_EQ:
        case PROT_OP_NE:
        case PROT_OP_LT:
        case PROT_OP_GT:
        case PROT_OP_LE:
        case PROT_OP_GE:
            if (sp < 2) {
                bad = 1;
                break;
            }
            b = stack[--sp];
            a = stack[--sp];
            if (op == PROT_OP_AND) {
                a = (a != 0 && b != 0) ? 1u : 0u;
            } else if (op == PROT_OP_OR) {
                a = (a != 0 || b != 0) ? 1u : 0u;
            } else if (op == PROT_OP_XOR) {
                a = ((a != 0) != (b != 0)) ? 1u : 0u;
            } else if (op == PROT_OP_EQ) {
                a = a == b ? 1u : 0u;
            } else if (op == PROT_OP_NE) {
                a = a != b ? 1u : 0u;
            } else if (op == PROT_OP_LT) {
                a = a < b ? 1u : 0u;
            } else if (op == PROT_OP_GT) {
                a = a > b ? 1u : 0u;
            } else if (op == PROT_OP_LE) {
                a = a <= b ? 1u : 0u;
            } else {
                a = a >= b ? 1u : 0u;
            }
            stack[sp++] = a;
            break;
        case PROT_OP_TON:
            if (p + 3 > end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            pt = (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
            p += 2;
            if (id >= PROT_N_TIMER) {
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
        case PROT_OP_RTRIG:
        case PROT_OP_FTRIG:
            if (p >= end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= PROT_N_EDGE) {
                bad = 1;
                break;
            }
            a = stack[--sp] != 0 ? 1u : 0u;
            if (op == PROT_OP_RTRIG) {
                b = (a != 0 && g_edge[id] == 0) ? 1u : 0u;
            } else {
                b = (a == 0 && g_edge[id] != 0) ? 1u : 0u;
            }
            g_edge[id] = (uint8_t)a;
            stack[sp++] = b;
            break;
        case PROT_OP_INHIBIT:
            if (p + 2 > end || sp < 1) {
                bad = 1;
                break;
            }
            a = (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
            p += 2;
            if (stack[--sp] != 0) {
                mask = (uint16_t)(mask | a);
            }
            break;
        case PROT_OP_ST_LOCAL:
            if (p >= end || sp < 1) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= PROT_N_LOCAL) {
                bad = 1;
                break;
            }
            g_local[id] = stack[--sp];
            break;
        case PROT_OP_LD_LOCAL:
            if (p >= end || sp >= PROT_N_STACK) {
                bad = 1;
                break;
            }
            id = *p++;
            if (id >= PROT_N_LOCAL) {
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

    if (!ended || bad || sp != 0) {
        g_fault = true;
        g_active_len = 0;
        reset_vm();
        out->mask = 0;
        out->fault = true;
    } else {
        out->mask = mask;
        out->fault = false;
    }
    image_unlock();
}

void protect_apply(uint16_t mask, PlcOutputs *out)
{
    if (mask & PROT_INH_H1) {
        out->h1_dis = true;
        out->h1_ali = false;
        out->h1_bli = false;
        out->h1_ahi = 0;
        out->h1_bhi = 0;
    }
    if (mask & PROT_INH_H2) {
        out->h2_dis = true;
        out->h2_ali = false;
        out->h2_bli = false;
        out->h2_ahi = 0;
        out->h2_bhi = 0;
    }
    if (mask & PROT_INH_DIO) {
        memset(out->dio_out, 0, sizeof(out->dio_out));
    }
    if (mask & PROT_INH_SIP) {
        memset(out->sip, 0, sizeof(out->sip));
    }
    if (mask & PROT_INH_AO) {
        out->ao[0] = 0;
        out->ao[1] = 0;
        out->ao[2] = 0;
    }
    if (mask & PROT_INH_PWM) {
        out->h1_ahi = 0;
        out->h1_bhi = 0;
        out->h2_ahi = 0;
        out->h2_bhi = 0;
    }
}

void protect_kick_tick(void)
{
    g_kick ^= 1u;
}

static void store_word(uint16_t index, uint16_t value)
{
    uint32_t pos;

    if (!g_open) {
        return;
    }
    pos = (uint32_t)g_off + (uint32_t)index * 2u;
    if (pos + 1u >= PROT_MAX_IMAGE) {
        g_stage_error = true;
        return;
    }
    g_stage[pos] = (uint8_t)(value >> 8);
    g_stage[pos + 1u] = (uint8_t)value;
    if (pos + 2u > g_high) {
        g_high = (uint16_t)(pos + 2u);
    }
}

bool protect_is_holding(uint16_t addr)
{
    return addr >= PROT_REG_CTRL && addr <= PROT_REG_LAST;
}

bool protect_holding_writable(uint16_t addr)
{
    return protect_is_holding(addr);
}

bool protect_write_reg(uint16_t addr, uint16_t value)
{
    if (!protect_is_holding(addr)) {
        return false;
    }
    if (addr == PROT_REG_CTRL) {
        if (value == 1u) {
            begin_stage();
        } else if (value == 2u) {
            commit_stage();
        } else if (value == 3u) {
            g_open = false;
        }
        return true;
    }
    if (addr == PROT_REG_LEN) {
        if (g_open) {
            g_expect = value;
            if (value == 0 || value > PROT_MAX_IMAGE) {
                g_stage_error = true;
            }
        }
        return true;
    }
    if (addr == PROT_REG_OFF) {
        g_off = value;
        return true;
    }
    if (addr >= PROT_REG_DATA && addr < PROT_REG_DATA + PROT_REG_DATA_N) {
        store_word((uint16_t)(addr - PROT_REG_DATA), value);
        return true;
    }
    return true;
}

bool protect_read_holding(uint16_t addr, uint16_t *value)
{
    uint32_t crc;

    if (!protect_is_holding(addr)) {
        return false;
    }
    *value = 0;
    if (addr == PROT_REG_LEN) {
        *value = g_expect;
    } else if (addr == PROT_REG_OFF) {
        *value = g_off;
    } else if (addr == PROT_REG_CRC_LO || addr == PROT_REG_CRC_HI) {
        if (g_active_len > PROT_HEADER_LEN) {
            crc = protect_crc32(g_active + PROT_HEADER_LEN,
                                (uint16_t)(g_active_len - PROT_HEADER_LEN));
            *value = addr == PROT_REG_CRC_LO ? (uint16_t)crc : (uint16_t)(crc >> 16);
        }
    } else if (addr >= PROT_REG_DATA && addr < PROT_REG_DATA + PROT_REG_DATA_N) {
        uint32_t pos = (uint32_t)g_off + (uint32_t)(addr - PROT_REG_DATA) * 2u;
        if (pos + 1u < PROT_MAX_IMAGE) {
            *value = (uint16_t)(((uint16_t)g_stage[pos] << 8) | g_stage[pos + 1u]);
        }
    }
    return true;
}

bool protect_is_input(uint16_t addr)
{
    return addr == PROT_IN_STATUS;
}

uint16_t protect_read_input(uint16_t addr)
{
    uint16_t status = 0;

    if (addr != PROT_IN_STATUS) {
        return 0;
    }
    if (g_active_len != 0 && !g_fault) {
        status |= 1u;
    }
    if (g_fault) {
        status |= 2u;
    }
    if (g_kick) {
        status |= 4u;
    }
    if (g_open) {
        status |= 8u;
    }
    return status;
}
