/******************************************************************************
 * Analog-to-digital conversion and touch button decoding
 ******************************************************************************/
#ifndef _ANALOG_H
#define _ANALOG_H
#include "Common.h"

// Functions
void Analog_Init(void);
void Analog_Interrupt(void);
uint16_t _Analog_Value(void);
void Analog_Calibrate(void);
/* void Analog_Stop(void); */
/* uint16_t Analog_Value(uint8_t ch); */
/* bool Analog_Touch(uint8_t ch); */

// Accessors
#define Analog_Stop()    ((void) (PIE1bits.TMR2IE = 0))
#define Analog_Value(ch) (WREG = (ch), _Analog_Value())
#define Analog_Touch(ch) (!_Analog.Array[(ch)].Status)

// Note: This structure must be kept in sync with the equivalent definition
// in Core.asm
extern struct _Analog
{
	volatile uint8_t Scan;
	struct _Analog_Channel
	{
		volatile uint16_t Average;
		volatile uint16_t Limit;
		volatile uint8_t History;
		volatile uint8_t Chain : 6;
		volatile uint8_t Status : 1;
		volatile uint8_t Current;
	}
	Array[1];
} _Analog;

#endif