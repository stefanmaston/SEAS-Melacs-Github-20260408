#ifndef MODBUS_RTU_H
#define MODBUS_RTU_H

#include <stdint.h>

uint16_t modbus_crc(const uint8_t *data, int len);

/* Bygger en läsbegäran (funktion 3 eller 4). Returnerar längden, eller 0. */
int modbus_rtu_read_req(uint8_t *dst, int cap, uint8_t slave, uint8_t func,
                        uint16_t addr, uint16_t count);

/*
 * Tolkar ett svar på funktion 3 eller 4.
 * Returnerar antalet register, 0 om ramen inte är hel eller adressen inte
 * stämmer, och -1 om CRC eller funktionen är fel.
 */
int modbus_rtu_parse_read(const uint8_t *frame, int len, uint8_t slave,
                          uint16_t *regs, int max_regs);

typedef uint16_t (*modbus_read_fn)(void *ctx, int holding, uint16_t addr, int *ok);
typedef int (*modbus_write_fn)(void *ctx, uint16_t addr, uint16_t value);

/*
 * Slavsvar på en hel RTU-ram. Returnerar svarslängden, 0 om ramen inte är
 * till den här slaven, och -1 om CRC saknas.
 * write_fn returnerar 0 vid ok, 2 vid ogiltig adress och 3 vid ogiltigt värde.
 */
int modbus_rtu_slave(const uint8_t *frame, int len, uint8_t slave,
                     modbus_read_fn read_reg, modbus_write_fn write_reg,
                     void *ctx, uint8_t *rsp, int rsp_cap);

#endif
