#include "log_history.h"

#include "logger.h"

#include <string.h>

#if defined(__PIC32MX__)
#include "pic32_board.h"
#else
#include <stdio.h>
#endif

enum {
    HIST_IDLE = 0,
    HIST_BUSY = 1,
    HIST_READY = 2,
    HIST_FAIL = 3,
    HIST_MAX = 800
};

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint16_t t_board;
    uint16_t t1;
    uint16_t t2;
} HistPoint;

static HistPoint g_pts[HIST_MAX];
static uint16_t g_count;
static uint16_t g_status;
static uint16_t g_minutes;
static uint32_t g_now_sec;

static uint32_t stamp_sec(uint16_t year, unsigned month, unsigned day,
                          unsigned hour, unsigned minute, unsigned second)
{
    return (((uint32_t)year * 372u + month * 31u + day) * 86400u)
        + hour * 3600u + minute * 60u + second;
}

static uint32_t clock_sec(const RtcClock *clk)
{
    return stamp_sec(clk->year, clk->month, clk->day, clk->hour, clk->minute, clk->second);
}

static int parse_fixed(const char **p, int digits)
{
    int value = 0;
    int i;

    for (i = 0; i < digits; i++) {
        if (**p < '0' || **p > '9') {
            return -1;
        }
        value = value * 10 + (*(*p)++ - '0');
    }
    return value;
}

static int take_field(const char **p, char *out, int cap)
{
    int n = 0;

    if (**p == '\0') {
        return 0;
    }
    while (**p && **p != ',' && **p != '\n' && n + 1 < cap) {
        out[n++] = *(*p)++;
    }
    out[n] = '\0';
    if (**p == ',') {
        (*p)++;
    }
    return 1;
}

static int parse_u16(const char *text, uint16_t *out)
{
    unsigned value = 0;
    const char *p = text;

    if (*p == '\0') {
        return 0;
    }
    while (*p >= '0' && *p <= '9') {
        value = value * 10u + (unsigned)(*p - '0');
        if (value > 65535u) {
            return 0;
        }
        p++;
    }
    if (*p != '\0') {
        return 0;
    }
    *out = (uint16_t)value;
    return 1;
}

static void store_point(const HistPoint *point)
{
    if (g_count == HIST_MAX) {
        memmove(g_pts, g_pts + 1, (HIST_MAX - 1) * sizeof(g_pts[0]));
        g_count = HIST_MAX - 1;
    }
    g_pts[g_count++] = *point;
}

void log_history_accept(const char *line)
{
    const char *p = line;
    char field[24];
    int index = 0;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    uint16_t t_board = 0;
    uint16_t t1 = 0;
    uint16_t t2 = 0;
    uint32_t when;
    uint32_t start;
    HistPoint point;

    year = parse_fixed(&p, 4);
    if (year < 2000 || *p != '-') {
        return;
    }
    p++;
    month = parse_fixed(&p, 2);
    if (month < 1 || *p != '-') {
        return;
    }
    p++;
    day = parse_fixed(&p, 2);
    if (day < 1 || *p != ' ') {
        return;
    }
    p++;
    hour = parse_fixed(&p, 2);
    if (hour < 0 || *p != ':') {
        return;
    }
    p++;
    minute = parse_fixed(&p, 2);
    if (minute < 0 || *p != ':') {
        return;
    }
    p++;
    second = parse_fixed(&p, 2);
    if (second < 0) {
        return;
    }
    if (*p == ',') {
        p++;
    }
    index = 1;
    while (index <= 52 && take_field(&p, field, (int)sizeof(field))) {
        if (index == 49) {
            parse_u16(field, &t_board);
        } else if (index == 51) {
            parse_u16(field, &t1);
        } else if (index == 52) {
            parse_u16(field, &t2);
        }
        index++;
    }
    when = stamp_sec((uint16_t)year, (unsigned)month, (unsigned)day,
                      (unsigned)hour, (unsigned)minute, (unsigned)second);
    start = g_now_sec > (uint32_t)g_minutes * 60u
        ? g_now_sec - (uint32_t)g_minutes * 60u
        : 0;
    if (when < start || when > g_now_sec + 5u) {
        return;
    }
    point.year = (uint16_t)year;
    point.month = (uint8_t)month;
    point.day = (uint8_t)day;
    point.hour = (uint8_t)hour;
    point.minute = (uint8_t)minute;
    point.second = (uint8_t)second;
    point.t_board = t_board;
    point.t1 = t1;
    point.t2 = t2;
    store_point(&point);
}

static void begin_scan(uint16_t minutes, const RtcClock *now)
{
    if (minutes < 1) {
        minutes = 1;
    }
    if (minutes > 360) {
        minutes = 360;
    }
    g_minutes = minutes;
    g_now_sec = clock_sec(now);
    g_count = 0;
    g_status = HIST_BUSY;
}

void log_history_ready(void)
{
    g_status = HIST_READY;
}

void log_history_fail(void)
{
    g_status = HIST_FAIL;
}

#if !defined(__PIC32MX__)
static void read_file(void)
{
    FILE *file;
    char line[640];
    const char *path = logger_path();

    if (path == NULL || path[0] == '\0') {
        log_history_fail();
        return;
    }
    file = fopen(path, "r");
    if (file == NULL) {
        log_history_fail();
        return;
    }
    while (fgets(line, (int)sizeof(line), file) != NULL) {
        log_history_accept(line);
    }
    fclose(file);
    log_history_ready();
}
#endif

void log_history_arm(uint16_t minutes, const RtcClock *now)
{
    begin_scan(minutes, now);
#if defined(__PIC32MX__)
    sd_hist_start((uint32_t)g_minutes * 60u * 512u);
#else
    read_file();
#endif
}

void log_history_poll(const RtcClock *now)
{
    if (now != NULL) {
        g_now_sec = clock_sec(now);
    }
#if defined(__PIC32MX__)
    if (g_status == HIST_BUSY) {
        sd_hist_step();
    }
#else
    (void)now;
#endif
}

uint16_t log_history_status(void)
{
    return g_status;
}

uint16_t log_history_count(void)
{
    return g_count;
}

uint16_t log_history_minutes(void)
{
    return g_minutes;
}

uint16_t log_history_reg(uint16_t addr)
{
    uint32_t rel;
    uint16_t index;
    uint16_t field;
    const HistPoint *point;

    if (addr == LOG_HIST_STATUS) {
        return g_status;
    }
    if (addr == LOG_HIST_COUNT) {
        return g_count;
    }
    if (addr < LOG_HIST_BASE) {
        return 0;
    }
    rel = (uint32_t)(addr - LOG_HIST_BASE);
    index = (uint16_t)(rel / LOG_HIST_STRIDE);
    field = (uint16_t)(rel % LOG_HIST_STRIDE);
    if (index >= g_count) {
        return 0;
    }
    point = &g_pts[index];
    switch (field) {
    case 0: return point->year;
    case 1: return point->month;
    case 2: return point->day;
    case 3: return point->hour;
    case 4: return point->minute;
    case 5: return point->second;
    case 6: return point->t_board;
    case 7: return point->t1;
    case 8: return point->t2;
    default: return 0;
    }
}
