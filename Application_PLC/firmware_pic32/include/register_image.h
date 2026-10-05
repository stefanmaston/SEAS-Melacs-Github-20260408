#ifndef REGISTER_IMAGE_H
#define REGISTER_IMAGE_H

#include "plc_runtime.h"
#include "rtc.h"

#include <stdbool.h>
#include <stdint.h>

void register_image_init(void);

void register_image_publish(const PlcInputs *in, const PlcOutputs *physical,
                            const PlcStatus *st, const RtcClock *clk);

void register_image_commands(PlcOutputs *cmd, uint16_t *safe_mode,
                             uint16_t *log_period_s, bool *master);

/* Tar emot en klockskrivning (stigande kant på rtc_set). */
bool register_image_take_clock(RtcClock *clk);

/* Tar emot en begäran om en kort summersignal. */
bool register_image_take_beep(void);

int register_image_read_bits(bool coils, uint16_t addr, uint16_t count,
                             uint8_t *dest);
int register_image_read_regs(bool holding, uint16_t addr, uint16_t count,
                             uint16_t *dest);
int register_image_write_coils(uint16_t addr, uint16_t count, const uint8_t *src);
int register_image_write_regs(uint16_t addr, uint16_t count, const uint16_t *src);

#endif
