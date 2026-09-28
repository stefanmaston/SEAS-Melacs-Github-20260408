#ifndef LOGGER_H
#define LOGGER_H

#include "plc_runtime.h"
#include "rtc.h"

#include <stdbool.h>
#include <stdint.h>

/* 0 i log_period_s betyder det här värdet. */
#define MELACS_LOG_PERIOD_S 6u

void logger_init(const char *path);
const char *logger_path(void);
void plat_sample_mark(void);
bool logger_tick(const RtcClock *clk, uint16_t period_s,
                 const PlcInputs *in, const PlcOutputs *out, const PlcStatus *st);
bool logger_failed(void);
const char *logger_last_line(void);

bool plat_log_append(const char *path, const char *text);

#endif
