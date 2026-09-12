#ifndef PLC_IEC_H
#define PLC_IEC_H

#include "plc_runtime.h"

typedef uint8_t IEC_BOOL;
typedef uint16_t IEC_UINT;
typedef uint16_t IEC_WORD;

/* MatIEC-style located pointers (samma namn som iec2c genererar). */
extern IEC_BOOL *__IX0_0;
extern IEC_BOOL *__IX0_1;
extern IEC_BOOL *__IX0_2;
extern IEC_BOOL *__IX0_3;
extern IEC_BOOL *__QX0_0;
extern IEC_BOOL *__QX0_1;
extern IEC_BOOL *__QX0_2;
extern IEC_BOOL *__QX0_3;
extern IEC_UINT *__IW0;
extern IEC_UINT *__IW1;
extern IEC_UINT *__IW10;
extern IEC_UINT *__QW0;
extern IEC_UINT *__QW1;
extern IEC_UINT *__QW2;

void plc_iec_bind(PlcInputs *in, PlcOutputs *out);
void plc_iec_commit(PlcOutputs *out);

/* Genereras av MatIEC / ligger i plc_generated. */
void config_init__(void);
void config_run__(unsigned long tick);

#endif
