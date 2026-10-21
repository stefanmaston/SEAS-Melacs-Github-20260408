#ifndef PROTECT_H
#define PROTECT_H

/*
 * Skyddsbild från POU:er som märkts säkerhetsrelaterade.
 * Bilden kan bara spärra utgångar. Ogiltig, saknad eller för lång bild
 * gör protect_ok() falsk, och plc_runtime lägger då safe_outputs().
 *
 * Bild, little-endian:
 *   0..3   'M','P','I','1'
 *   4..5   version 1
 *   6..7   kroppslängd
 *   8..11  CRC-32 (IEEE) av kroppen
 *   12..   kropp
 *
 * Modbus, holding:
 *   360  1 = börja, 2 = bekräfta, 3 = avbryt. Läses som 0.
 *   361  längd i byte
 *   362  CRC låg, aktiv bild
 *   363  CRC hög, aktiv bild
 *   364  byte-offset för nästa datord
 *   365–380  sexton ord payload, big-endian per ord
 * Input 340:
 *   bit0 bild giltig, bit1 fel, bit2 puls-fas, bit3 överföring pågår
 */

#include "plc_runtime.h"

#include <stdbool.h>
#include <stdint.h>

#define PROT_MAX_IMAGE 256u
#define PROT_MAX_STEPS 64u
#define PROT_HEADER_LEN 12u

#define PROT_REG_CTRL 360u
#define PROT_REG_LEN 361u
#define PROT_REG_CRC_LO 362u
#define PROT_REG_CRC_HI 363u
#define PROT_REG_OFF 364u
#define PROT_REG_DATA 365u
#define PROT_REG_DATA_N 16u
#define PROT_REG_LAST 380u
#define PROT_IN_STATUS 340u

#define PROT_OP_END 0x00u
#define PROT_OP_LD_BOOL 0x01u
#define PROT_OP_LD_WORD 0x02u
#define PROT_OP_LDC 0x03u
#define PROT_OP_NOT 0x10u
#define PROT_OP_AND 0x11u
#define PROT_OP_OR 0x12u
#define PROT_OP_XOR 0x13u
#define PROT_OP_EQ 0x14u
#define PROT_OP_NE 0x15u
#define PROT_OP_LT 0x16u
#define PROT_OP_GT 0x17u
#define PROT_OP_LE 0x18u
#define PROT_OP_GE 0x19u
#define PROT_OP_TON 0x20u
#define PROT_OP_RTRIG 0x21u
#define PROT_OP_FTRIG 0x22u
#define PROT_OP_INHIBIT 0x30u
#define PROT_OP_ST_LOCAL 0x50u
#define PROT_OP_LD_LOCAL 0x51u

#define PROT_SRC_DIO0 0u
#define PROT_SRC_AI0 4u

#define PROT_INH_H1 0x0001u
#define PROT_INH_H2 0x0002u
#define PROT_INH_DIO 0x0004u
#define PROT_INH_SIP 0x0008u
#define PROT_INH_AO 0x0010u
#define PROT_INH_PWM 0x0020u
#define PROT_INH_ALL 0x003fu

#define PROT_SCAN_MS 10u

void protect_init(void);
bool protect_ok(void);
bool protect_fault(void);

typedef struct {
    bool dio[4];
    uint16_t ai[6];
} ProtectIn;

typedef struct {
    uint16_t mask;
    bool fault;
} ProtectOut;

void protect_step(const ProtectIn *in, ProtectOut *out);
void protect_apply(uint16_t mask, PlcOutputs *out);

/* Växlar varje 1 kHz-avbrott. Detektorn på säkerhetskortet tappar slingan utan flank. */
void protect_kick_tick(void);

bool protect_is_holding(uint16_t addr);
bool protect_holding_writable(uint16_t addr);
bool protect_write_reg(uint16_t addr, uint16_t value);
bool protect_read_holding(uint16_t addr, uint16_t *value);
bool protect_is_input(uint16_t addr);
uint16_t protect_read_input(uint16_t addr);

uint32_t protect_crc32(const uint8_t *data, uint16_t len);

#endif
