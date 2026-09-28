#include "logger.h"

#include <stdio.h>
#include <string.h>

static char g_path[256];
static char g_last[1024];
static uint32_t g_sample_ord;
static bool g_have_sample;
static bool g_header_done;
static bool g_fail;
static uint16_t g_n;
static uint64_t g_ad[8];
static uint64_t g_ai[6];
static uint64_t g_t_board;
static uint64_t g_p;
static uint64_t g_t1;
static uint64_t g_t2;
static uint64_t g_value;
static uint16_t g_dio_in[4];
static uint16_t g_error;
static bool g_sd_ok;
static bool g_loaded;
static bool g_running;
static PlcOutputs g_snap;

static const char *header =
    "TimeStamp,AD0,AD1,AD2,AD3,AD4,AD5,AD6,AD7,"
    "DIO0,DIO1,DIO2,DIO3,"
    "AI10,AI11,AI12,AI13,AI14,AI15,"
    "sd_ok,logger_ok,plc_loaded,plc_running,error_code,"
    "DIO4,DIO5,DIO6,DIO7,AO0,AO1,AO2,"
    "SIP0,SIP1,SIP2,SIP3,SIP4,SIP5,SIP6,SIP7,"
    "H1_DIS,H1_ALI,H1_BLI,H1_AHI,H1_BHI,"
    "H2_DIS,H2_ALI,H2_BLI,H2_AHI,H2_BHI,"
    "T_BOARD,P,T1,T2,VALUE,NOTE\n";

const char *logger_path(void)
{
    return g_path;
}

void logger_init(const char *path)
{
    g_path[0] = '\0';
    g_last[0] = '\0';
    g_have_sample = false;
    g_header_done = false;
    g_fail = false;
    g_n = 0;
    if (path != NULL) {
        snprintf(g_path, sizeof(g_path), "%s", path);
    }
}

const char *logger_last_line(void)
{
    return g_last;
}

bool logger_failed(void)
{
    return g_fail;
}

static void acc_clear(void)
{
    memset(g_ad, 0, sizeof(g_ad));
    memset(g_ai, 0, sizeof(g_ai));
    memset(g_dio_in, 0, sizeof(g_dio_in));
    g_t_board = 0;
    g_p = 0;
    g_t1 = 0;
    g_t2 = 0;
    g_value = 0;
    g_error = 0;
    g_n = 0;
}

static uint16_t mean_u16(uint64_t sum, uint16_t n)
{
    return (uint16_t)((sum + (uint64_t)n / 2u) / n);
}

static int mean_bit(uint16_t sum, uint16_t n)
{
    return sum * 2u >= n;
}

bool logger_tick(const RtcClock *clk, uint16_t period_s,
                 const PlcInputs *in, const PlcOutputs *out, const PlcStatus *st)
{
    uint32_t ord;
    char ts[32];
    char line[1024];
    int n;
    int i;
    const PlcOutputs *snap;

    if (g_path[0] == '\0') {
        return false;
    }
    if (period_s == 0) {
        period_s = MELACS_LOG_PERIOD_S;
    }

    ord = rtc_ordinal(clk);
    if (g_have_sample && ord == g_sample_ord) {
        return false;
    }
    if (g_have_sample && ord != g_sample_ord + 1u) {
        acc_clear();
    }

    g_n++;
    for (i = 0; i < 8; i++) {
        g_ad[i] += in->ad[i];
    }
    for (i = 0; i < 6; i++) {
        g_ai[i] += in->ai[i];
    }
    for (i = 0; i < 4; i++) {
        g_dio_in[i] = (uint16_t)(g_dio_in[i] + (in->dio_in[i] ? 1u : 0u));
    }
    g_t_board += in->t_board;
    g_p += in->p;
    g_t1 += in->t1;
    g_t2 += in->t2;
    g_value += in->value;
    g_error = (uint16_t)(g_error | in->error_code);
    g_sd_ok = in->sd_ok;
    g_loaded = st->plc_loaded;
    g_running = st->plc_running;
    g_snap = *out;
    g_sample_ord = ord;
    g_have_sample = true;
    plat_sample_mark();
    if (g_n < period_s) {
        return false;
    }

    snap = &g_snap;
    if (!g_header_done) {
        if (!plat_log_append(g_path, header)) {
            g_fail = true;
            acc_clear();
            return false;
        }
        g_header_done = true;
    }

    rtc_format(clk, ts, sizeof(ts));
    n = snprintf(line, sizeof(line),
                 "%s,%u,%u,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d,%u,%u,%u,%u,%u,%u,%d,%d,%d,%d,%u,%d,%d,%d,%d,%u,%u,%u,"
                 "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%d,%d,%d,%u,%u,%u,%u,%u,%u,%u,%u\n",
                 ts,
                 (unsigned)mean_u16(g_ad[0], g_n), (unsigned)mean_u16(g_ad[1], g_n),
                 (unsigned)mean_u16(g_ad[2], g_n), (unsigned)mean_u16(g_ad[3], g_n),
                 (unsigned)mean_u16(g_ad[4], g_n), (unsigned)mean_u16(g_ad[5], g_n),
                 (unsigned)mean_u16(g_ad[6], g_n), (unsigned)mean_u16(g_ad[7], g_n),
                 mean_bit(g_dio_in[0], g_n), mean_bit(g_dio_in[1], g_n),
                 mean_bit(g_dio_in[2], g_n), mean_bit(g_dio_in[3], g_n),
                 (unsigned)mean_u16(g_ai[0], g_n), (unsigned)mean_u16(g_ai[1], g_n),
                 (unsigned)mean_u16(g_ai[2], g_n), (unsigned)mean_u16(g_ai[3], g_n),
                 (unsigned)mean_u16(g_ai[4], g_n), (unsigned)mean_u16(g_ai[5], g_n),
                 g_sd_ok ? 1 : 0, 1,
                 g_loaded ? 1 : 0, g_running ? 1 : 0,
                 (unsigned)g_error,
                 snap->dio_out[0] ? 1 : 0, snap->dio_out[1] ? 1 : 0,
                 snap->dio_out[2] ? 1 : 0, snap->dio_out[3] ? 1 : 0,
                 (unsigned)snap->ao[0], (unsigned)snap->ao[1],
                 (unsigned)snap->ao[2],
                 snap->sip[0] ? 1 : 0, snap->sip[1] ? 1 : 0,
                 snap->sip[2] ? 1 : 0, snap->sip[3] ? 1 : 0,
                 snap->sip[4] ? 1 : 0, snap->sip[5] ? 1 : 0,
                 snap->sip[6] ? 1 : 0, snap->sip[7] ? 1 : 0,
                 snap->h1_dis ? 1 : 0, snap->h1_ali ? 1 : 0, snap->h1_bli ? 1 : 0,
                 (unsigned)snap->h1_ahi, (unsigned)snap->h1_bhi,
                 snap->h2_dis ? 1 : 0, snap->h2_ali ? 1 : 0, snap->h2_bli ? 1 : 0,
                 (unsigned)snap->h2_ahi, (unsigned)snap->h2_bhi,
                 (unsigned)mean_u16(g_t_board, g_n), (unsigned)mean_u16(g_p, g_n),
                 (unsigned)mean_u16(g_t1, g_n), (unsigned)mean_u16(g_t2, g_n),
                 (unsigned)mean_u16(g_value, g_n), (unsigned)snap->note);
    if (n < 0 || (size_t)n >= sizeof(line)) {
        acc_clear();
        return false;
    }
    if (!plat_log_append(g_path, line)) {
        g_fail = true;
        acc_clear();
        return false;
    }
    g_fail = false;

    snprintf(g_last, sizeof(g_last), "%s", line);
    acc_clear();
#ifndef __PIC32MX__
    printf("log %s", line);
#endif
    return true;
}
