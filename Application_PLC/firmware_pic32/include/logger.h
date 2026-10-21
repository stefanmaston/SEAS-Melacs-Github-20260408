#ifndef LOGGER_H
#define LOGGER_H

#include "plc_runtime.h"
#include "rtc.h"

#include <stdbool.h>
#include <stdint.h>

/* 0 i log_period_s betyder det här värdet. */
#define MELACS_LOG_PERIOD_S 6u
/* MELACS.BAK får samma slags rad, högst så här ofta. */
#define MELACS_BACKUP_PERIOD_S 3600u

/*
 * MELACS.SAF. Koderna är händelser, inte mätvärden.
 * Input 350 är äldsta okvitterade händelsen. Holding 381 kvitterar dess seq.
 */
#define SAF_BOOT 1u
#define SAF_IMAGE_OK 2u
#define SAF_IMAGE_MISSING 3u
#define SAF_IMAGE_FAULT 4u
#define SAF_MASTER_LOST 5u
#define SAF_MASTER_OK 6u
#define SAF_SAFE_MODE 7u
#define SAF_INHIBIT 9u
#define SAF_INTERLOCK 10u

#define SAF_IN_SEQ 350u
#define SAF_IN_CODE 351u
#define SAF_IN_DETAIL 352u
#define SAF_IN_COUNT 353u
#define SAF_IN_OVF 354u
#define SAF_IN_YEAR 355u
#define SAF_IN_MONTH 356u
#define SAF_IN_DAY 357u
#define SAF_IN_HOUR 358u
#define SAF_IN_MINUTE 359u
#define SAF_IN_SECOND 360u
#define SAF_ACK 381u

void logger_init(const char *path);
const char *logger_path(void);
void plat_sample_mark(void);
bool logger_tick(const RtcClock *clk, uint16_t period_s,
                 const PlcInputs *in, const PlcOutputs *out, const PlcStatus *st);
void logger_watch(const RtcClock *clk, int image_ok, int image_fault,
                  int master, uint16_t safe_mode, uint16_t inhibit, uint16_t trip);
bool logger_failed(void);
const char *logger_last_line(void);

bool logger_safety_is_input(uint16_t addr);
uint16_t logger_safety_input(uint16_t addr);
bool logger_safety_is_ack(uint16_t addr);
void logger_safety_ack(uint16_t seq);

/* Append-only. size är 0 när filen saknas. repair tar bara bort en avbruten sista rad. */
bool plat_log_append(const char *path, const char *text);
bool plat_log_size(const char *path, uint32_t *size);
bool plat_log_repair(const char *path);

#endif
