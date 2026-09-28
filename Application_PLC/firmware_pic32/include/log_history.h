#ifndef LOG_HISTORY_H
#define LOG_HISTORY_H

#include "rtc.h"

#include <stdint.h>

#define LOG_HIST_ARM 220u
#define LOG_HIST_STATUS 500u
#define LOG_HIST_COUNT 501u
#define LOG_HIST_BASE 510u
#define LOG_HIST_STRIDE 9u

void log_history_arm(uint16_t minutes, const RtcClock *now);
void log_history_poll(const RtcClock *now);
void log_history_accept(const char *line);
void log_history_ready(void);
void log_history_fail(void);
uint16_t log_history_status(void);
uint16_t log_history_count(void);
uint16_t log_history_minutes(void);
uint16_t log_history_reg(uint16_t addr);

#endif
