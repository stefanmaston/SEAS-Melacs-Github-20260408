#ifndef LOC_RUNTIME_H
#define LOC_RUNTIME_H

/*
 * Lokal styrbild från POU:er som märkts @MELACS LOCAL.
 * Bilden får bara skriva de utgångar den äger. OpenPLC:s kommandobild
 * (g_cmd / coil 16–45 / holding 100–114) rörs inte.
 *
 * Bild, little-endian:
 *   0..3   'M','P','L','1'
 *   4..5   version 1
 *   6..7   kroppslängd (ägarmask + kod)
 *   8..11  CRC-32 (IEEE) av kroppen
 *   12..15 ägarmask
 *   16..   kod
 *
 * Modbus, holding:
 *   400  1 = börja, 2 = bekräfta, 3 = avbryt, 4 = spara till SD. Läses som 0.
 *   401  längd i byte, högst 1024
 *   402  CRC låg, aktiv bild. Skrivningar ignoreras.
 *   403  CRC hög, aktiv bild. Skrivningar ignoreras.
 *   404  byte-offset för nästa datord
 *   405–420  sexton ord payload, big-endian per ord
 *   421  ägarmask låg. Skrivningar ignoreras.
 *   422  ägarmask hög. Skrivningar ignoreras.
 * Input 370:
 *   bit0 bild giltig, bit1 fel, bit2 kör, bit3 överföring, bit4 oberoende av master
 */

#include "plc_runtime.h"

#include <stdbool.h>
#include <stdint.h>

#define LOC_MAX_IMAGE 1024u
#define LOC_MAX_STEPS 256u
#define LOC_HEADER_LEN 12u
#define LOC_MASK_LEN 4u

#define LOC_REG_CTRL 400u
#define LOC_REG_LEN 401u
#define LOC_REG_CRC_LO 402u
#define LOC_REG_CRC_HI 403u
#define LOC_REG_OFF 404u
#define LOC_REG_DATA 405u
#define LOC_REG_DATA_N 16u
#define LOC_REG_OWN_LO 421u
#define LOC_REG_OWN_HI 422u
#define LOC_REG_LAST 422u
#define LOC_IN_STATUS 370u
#define LOC_IN_STEPS 371u
#define LOC_IN_CRC_LO 372u
#define LOC_IN_CRC_HI 373u
#define LOC_IN_FAULT 374u

#define LOC_OP_END 0x00u
#define LOC_OP_LD_BOOL 0x01u
#define LOC_OP_LD_WORD 0x02u
#define LOC_OP_LDC 0x03u
#define LOC_OP_NOT 0x10u
#define LOC_OP_AND 0x11u
#define LOC_OP_OR 0x12u
#define LOC_OP_XOR 0x13u
#define LOC_OP_EQ 0x14u
#define LOC_OP_NE 0x15u
#define LOC_OP_LT 0x16u
#define LOC_OP_GT 0x17u
#define LOC_OP_LE 0x18u
#define LOC_OP_GE 0x19u
#define LOC_OP_TON 0x20u
#define LOC_OP_RTRIG 0x21u
#define LOC_OP_FTRIG 0x22u
#define LOC_OP_ST_Q_BOOL 0x40u
#define LOC_OP_ST_Q_WORD 0x41u
#define LOC_OP_ST_LOCAL 0x50u
#define LOC_OP_LD_LOCAL 0x51u

#define LOC_OWN_DIO4 (1u << 0)
#define LOC_OWN_DIO5 (1u << 1)
#define LOC_OWN_DIO6 (1u << 2)
#define LOC_OWN_DIO7 (1u << 3)
#define LOC_OWN_SIP0 (1u << 4)
#define LOC_OWN_H1_DIS (1u << 12)
#define LOC_OWN_H2_DIS (1u << 15)
#define LOC_OWN_AO0 (1u << 18)
#define LOC_OWN_H1_AHI (1u << 21)

#define LOC_SCAN_MS 10u
#define LOC_FILE_NAME "MELACS.LOC"

void loc_init(void);
bool loc_ok(void);
bool loc_fault(void);
uint32_t loc_own_mask(void);
uint16_t loc_steps(void);
uint16_t loc_fault_code(void);

void loc_step(const PlcInputs *in, PlcOutputs *out);
void loc_apply(uint32_t mask, const PlcOutputs *local, PlcOutputs *out);

bool loc_is_holding(uint16_t addr);
bool loc_holding_writable(uint16_t addr);
bool loc_write_reg(uint16_t addr, uint16_t value);
bool loc_read_holding(uint16_t addr, uint16_t *value);
bool loc_is_input(uint16_t addr);
uint16_t loc_read_input(uint16_t addr);

bool loc_take_save(void);
void loc_load_sd(void);
void loc_save_sd(void);

#endif
