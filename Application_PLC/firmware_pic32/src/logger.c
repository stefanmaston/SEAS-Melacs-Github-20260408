#include "logger.h"

#include "image_lock.h"

#include <stdio.h>
#include <string.h>

#define SAF_Q 32u

static char g_path[256];
static char g_bak[256];
static char g_saf[256];
static char g_last[1024];
static uint32_t g_sample_ord;
static uint32_t g_backup_ord;
static bool g_have_sample;
static bool g_backup_have;
static bool g_header_done;
static bool g_bak_header;
static bool g_saf_header;
static bool g_sealed;
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

static uint16_t g_seq;
static uint8_t g_qh;
static uint8_t g_qn;
static int g_ovf;
static int g_watch_ready;
static int g_prev_ok;
static int g_prev_fault;
static int g_prev_master;
static uint16_t g_prev_safe;
static uint16_t g_prev_inh;
static uint16_t g_prev_trip;

typedef struct {
    uint16_t seq;
    uint16_t code;
    uint16_t detail;
    RtcClock clk;
} SafEv;

static SafEv g_q[SAF_Q];

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

static const char *saf_header = "TimeStamp,Seq,Code,Detail\n";

static void sibling(char *dst, size_t n, const char *path, const char *name)
{
    const char *slash = NULL;
    const char *scan;

    dst[0] = '\0';
    if (path == NULL || name == NULL || n == 0) {
        return;
    }
    for (scan = path; *scan != '\0'; scan++) {
        if (*scan == '/' || *scan == '\\') {
            slash = scan;
        }
    }
    if (slash == NULL) {
        snprintf(dst, n, "%s", name);
        return;
    }
    snprintf(dst, n, "%.*s/%s", (int)(slash - path), path, name);
}

const char *logger_path(void)
{
    return g_path;
}

void logger_init(const char *path)
{
    g_path[0] = '\0';
    g_bak[0] = '\0';
    g_saf[0] = '\0';
    g_last[0] = '\0';
    g_have_sample = false;
    g_backup_have = false;
    g_header_done = false;
    g_bak_header = false;
    g_saf_header = false;
    g_sealed = false;
    g_fail = false;
    g_n = 0;
    g_seq = 0;
    g_qh = 0;
    g_qn = 0;
    g_ovf = 0;
    g_watch_ready = 0;
    if (path != NULL) {
        snprintf(g_path, sizeof(g_path), "%s", path);
        sibling(g_bak, sizeof(g_bak), path, "MELACS.BAK");
        sibling(g_saf, sizeof(g_saf), path, "MELACS.SAF");
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

static void seal_logs(void)
{
    if (g_sealed || g_path[0] == '\0') {
        return;
    }
    if (!plat_log_repair(g_path)) {
        return;
    }
    if (g_bak[0] != '\0' && !plat_log_repair(g_bak)) {
        return;
    }
    if (g_saf[0] != '\0' && !plat_log_repair(g_saf)) {
        return;
    }
    g_sealed = true;
}

/* Rubriken skrivs bara när filen är tom, så en omstart inte lägger en ny rubrik mitt i serien. */
static int ensure_header(const char *path, bool *done, const char *text)
{
    uint32_t size = 0;

    if (*done) {
        return 1;
    }
    if (!plat_log_size(path, &size)) {
        return 0;
    }
    if (size > 0) {
        *done = true;
        return 1;
    }
    if (!plat_log_append(path, text)) {
        return 0;
    }
    *done = true;
    return 1;
}

static void queue_push(const RtcClock *clk, uint16_t seq, uint16_t code, uint16_t detail)
{
    SafEv *ev;

    image_lock();
    if (g_qn >= SAF_Q) {
        g_ovf = 1;
        image_unlock();
        return;
    }
    ev = &g_q[(uint8_t)((g_qh + g_qn) % SAF_Q)];
    ev->seq = seq;
    ev->code = code;
    ev->detail = detail;
    ev->clk = *clk;
    g_qn++;
    image_unlock();
}

static void logger_event(const RtcClock *clk, uint16_t code, uint16_t detail)
{
    char ts[32];
    char line[96];
    uint16_t seq;
    int n;

    if (g_saf[0] == '\0' || clk == NULL) {
        return;
    }
    seal_logs();
    image_lock();
    g_seq++;
    if (g_seq == 0) {
        g_seq = 1;
    }
    seq = g_seq;
    image_unlock();

    rtc_format(clk, ts, sizeof(ts));
    n = snprintf(line, sizeof(line), "%s,%u,%u,%u\n", ts, (unsigned)seq, (unsigned)code, (unsigned)detail);
    if (n > 0 && (size_t)n < sizeof(line)) {
        if (ensure_header(g_saf, &g_saf_header, saf_header)) {
            (void)plat_log_append(g_saf, line);
        }
    }
    queue_push(clk, seq, code, detail);
}

void logger_watch(const RtcClock *clk, int image_ok, int image_fault,
                  int master, uint16_t safe_mode, uint16_t inhibit, uint16_t trip)
{
    if (!g_watch_ready) {
        logger_event(clk, SAF_BOOT, 0);
        if (image_fault) {
            logger_event(clk, SAF_IMAGE_FAULT, 0);
        } else if (!image_ok) {
            logger_event(clk, SAF_IMAGE_MISSING, 0);
        } else {
            logger_event(clk, SAF_IMAGE_OK, 0);
        }
        g_watch_ready = 1;
        g_prev_ok = image_ok;
        g_prev_fault = image_fault;
        g_prev_master = master;
        g_prev_safe = safe_mode;
        g_prev_inh = inhibit;
        g_prev_trip = trip;
        return;
    }
    if (image_fault != g_prev_fault || image_ok != g_prev_ok) {
        if (image_fault) {
            logger_event(clk, SAF_IMAGE_FAULT, 0);
        } else if (!image_ok) {
            logger_event(clk, SAF_IMAGE_MISSING, 0);
        } else {
            logger_event(clk, SAF_IMAGE_OK, 0);
        }
    }
    if (master != g_prev_master) {
        logger_event(clk, master ? SAF_MASTER_OK : SAF_MASTER_LOST, 0);
    }
    if (safe_mode != g_prev_safe) {
        logger_event(clk, SAF_SAFE_MODE, safe_mode);
    }
    if (inhibit != g_prev_inh) {
        logger_event(clk, SAF_INHIBIT, inhibit);
    }
    if (trip != g_prev_trip) {
        logger_event(clk, SAF_INTERLOCK, trip);
    }
    g_prev_ok = image_ok;
    g_prev_fault = image_fault;
    g_prev_master = master;
    g_prev_safe = safe_mode;
    g_prev_inh = inhibit;
    g_prev_trip = trip;
}

bool logger_safety_is_input(uint16_t addr)
{
    return addr >= SAF_IN_SEQ && addr <= SAF_IN_SECOND;
}

uint16_t logger_safety_input(uint16_t addr)
{
    const SafEv *ev = g_qn > 0 ? &g_q[g_qh] : NULL;

    switch (addr) {
    case SAF_IN_SEQ: return ev != NULL ? ev->seq : 0;
    case SAF_IN_CODE: return ev != NULL ? ev->code : 0;
    case SAF_IN_DETAIL: return ev != NULL ? ev->detail : 0;
    case SAF_IN_COUNT: return g_qn;
    case SAF_IN_OVF: return g_ovf ? 1u : 0u;
    case SAF_IN_YEAR: return ev != NULL ? ev->clk.year : 0;
    case SAF_IN_MONTH: return ev != NULL ? ev->clk.month : 0;
    case SAF_IN_DAY: return ev != NULL ? ev->clk.day : 0;
    case SAF_IN_HOUR: return ev != NULL ? ev->clk.hour : 0;
    case SAF_IN_MINUTE: return ev != NULL ? ev->clk.minute : 0;
    case SAF_IN_SECOND: return ev != NULL ? ev->clk.second : 0;
    default: return 0;
    }
}

bool logger_safety_is_ack(uint16_t addr)
{
    return addr == SAF_ACK;
}

void logger_safety_ack(uint16_t seq)
{
    if (g_qn == 0 || g_q[g_qh].seq != seq) {
        return;
    }
    g_qh = (uint8_t)((g_qh + 1u) % SAF_Q);
    g_qn--;
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

    seal_logs();
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
    if (!ensure_header(g_path, &g_header_done, header)) {
        g_fail = true;
        acc_clear();
        return false;
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

    if (g_bak[0] != '\0' && (!g_backup_have || (uint32_t)(ord - g_backup_ord) >= MELACS_BACKUP_PERIOD_S)) {
        if (ensure_header(g_bak, &g_bak_header, header) && plat_log_append(g_bak, line)) {
            g_backup_ord = ord;
            g_backup_have = true;
        }
    }

    snprintf(g_last, sizeof(g_last), "%s", line);
    acc_clear();
#ifndef __PIC32MX__
    printf("log %s", line);
#endif
    return true;
}
