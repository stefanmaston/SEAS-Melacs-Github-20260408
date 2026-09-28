#ifndef RTC_H
#define RTC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Samma fält som OEM RTCclk, med årtal som 2000–2099. */
typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t weekday; /* 0 = söndag … 6 = lördag */
} RtcClock;

void rtc_init(void);
void rtc_poll(void);
void rtc_get(RtcClock *out);
bool rtc_valid(const RtcClock *clk);
bool rtc_set(const RtcClock *clk);
void rtc_format(const RtcClock *clk, char *buf, size_t n);
uint32_t rtc_ordinal(const RtcClock *clk);
void rtc_add_second(RtcClock *clk);

void plat_read_rtc(RtcClock *clk);
void plat_write_rtc(const RtcClock *clk);

#endif
