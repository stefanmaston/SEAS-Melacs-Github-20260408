#include "rtc.h"

#include <stdio.h>

static RtcClock g_clk;

static int days_in_month(uint16_t year, uint8_t month)
{
    static const uint8_t mdays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dim = mdays[month];

    if (month == 2 && (year % 4u) == 0) {
        dim = 29;
    }
    return dim;
}

bool rtc_valid(const RtcClock *clk)
{
    if (clk->year < 2000 || clk->year > 2099) {
        return false;
    }
    if (clk->month < 1 || clk->month > 12) {
        return false;
    }
    if (clk->day < 1 || clk->day > days_in_month(clk->year, clk->month)) {
        return false;
    }
    if (clk->hour > 23 || clk->minute > 59 || clk->second > 59 || clk->weekday > 6) {
        return false;
    }
    return true;
}

void rtc_add_second(RtcClock *clk)
{
    clk->second++;
    if (clk->second < 60) {
        return;
    }
    clk->second = 0;
    clk->minute++;
    if (clk->minute < 60) {
        return;
    }
    clk->minute = 0;
    clk->hour++;
    if (clk->hour < 24) {
        return;
    }
    clk->hour = 0;
    clk->weekday = (uint8_t)((clk->weekday + 1u) % 7u);
    clk->day++;
    if (clk->day <= days_in_month(clk->year, clk->month)) {
        return;
    }
    clk->day = 1;
    clk->month++;
    if (clk->month <= 12) {
        return;
    }
    clk->month = 1;
    if (clk->year < 2099) {
        clk->year++;
    }
}

void rtc_init(void)
{
    g_clk.year = 2000;
    g_clk.month = 1;
    g_clk.day = 1;
    g_clk.hour = 0;
    g_clk.minute = 0;
    g_clk.second = 0;
    g_clk.weekday = 6;
}

void rtc_poll(void)
{
    plat_read_rtc(&g_clk);
}

void rtc_get(RtcClock *out)
{
    *out = g_clk;
}

bool rtc_set(const RtcClock *clk)
{
    if (!rtc_valid(clk)) {
        return false;
    }
    g_clk = *clk;
    plat_write_rtc(clk);
    return true;
}

void rtc_format(const RtcClock *clk, char *buf, size_t n)
{
    snprintf(buf, n, "%04u-%02u-%02u %02u:%02u:%02u",
             (unsigned)clk->year, (unsigned)clk->month, (unsigned)clk->day,
             (unsigned)clk->hour, (unsigned)clk->minute, (unsigned)clk->second);
}

uint32_t rtc_ordinal(const RtcClock *clk)
{
    return (uint32_t)clk->second
        + (uint32_t)clk->minute * 60u
        + (uint32_t)clk->hour * 3600u
        + (uint32_t)clk->day * 86400u
        + (uint32_t)clk->month * 2678400u
        + (uint32_t)clk->year * 32140800u;
}
