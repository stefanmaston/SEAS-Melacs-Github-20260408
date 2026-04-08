/******************************************************************************
 * A few useful mathematical functions
 ******************************************************************************/
#ifndef _MATH_H
#define _MATH_H
#include "Common.h"

#define Math_Mul8x8(f1, f2)     (PRODL = (f1), WREG = (f2), _Math_Mul8x8())
#define Math_BCDToBin(bcd)      (TABLAT = (bcd), _Math_BCDToBin())
#define Math_BinToBCD(bin)      (TABLAT = (bin), _Math_BinToBCD())
#define Math_Random(range)      (TABLAT = (range), _Math_Random())
#define Math_Entropy(data, len) (FSR0 = (uint16_t) data, PRODL = (len), _Math_Entropy())

uint16_t _Math_Mul8x8(void);
uint8_t _Math_BCDToBin(void);
uint8_t _Math_BinToBCD(void);
uint8_t _Math_Random(void);
void _Math_Entropy(void);

extern uint16_t Math_Seed;

#endif