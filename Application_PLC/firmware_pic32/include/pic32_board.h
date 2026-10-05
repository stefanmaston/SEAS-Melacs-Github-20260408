#ifndef PIC32_BOARD_H
#define PIC32_BOARD_H

#include <xc.h>
#include "plc_runtime.h"
#include "rtc.h"

#include <stdbool.h>
#include <stdint.h>

void board_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
uint32_t board_millis(void);

void spi_bus_init(void);
void spi_hw_on(int slow);
void spi_hw_off(void);
uint8_t spi_xfer(uint8_t value);
uint8_t bb_xfer(uint8_t value);

void memled_init(void);
void memled_pulse(void);
void memled_sd(int on);
void memled_poll(void);

void buzzer_pulse(void);
void buzzer_poll(void);

void io_init(void);
void io_read(PlcInputs *in);
void io_write(const PlcOutputs *out);

bool rtc_chip_read(RtcClock *clk);
bool rtc_chip_write(const RtcClock *clk);
bool rtc_chip_ok(void);

bool sd_start(void);
bool sd_ok(void);
bool sd_append_line(const char *path, const char *text);
bool sd_seed_pack(void);
void sd_hist_start(uint32_t budget_bytes);
void sd_hist_step(void);

bool enc_start(uint8_t mac[6]);
bool enc_link(void);
void enc_apply_duplex(void);
bool enc_rx(uint8_t *frame, int *len, int max_len);
bool enc_take_rx(void);
bool enc_tx(const uint8_t *frame, int len);
bool enc_ok(void);

void net_init(const uint8_t mac[6]);
void net_poll(void);
bool net_up(void);

#endif
