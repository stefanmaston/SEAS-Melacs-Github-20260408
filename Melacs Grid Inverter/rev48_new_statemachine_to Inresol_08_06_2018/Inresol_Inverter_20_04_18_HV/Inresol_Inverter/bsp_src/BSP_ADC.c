/*
 *  File name: BSP_ADC.c
 *
 *  Description: Board Support Package function implementations for ADC processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

void BSP_ADC_Module_Enable(void)
{
	ADCON1Lbits.ADON = 1;		// Enable the ADC module
}

void BSP_ADC_Module_Disable(void)
{
	ADCON1Lbits.ADON = 0;		// Disable the ADC module
}

void BSP_ADC_Module_Init(void)
{
/////////////////////
	// Configure the common ADC clock.
	ADCON3Hbits.CLKSEL = 3;				// clock from Auxiliary PLL
	ADCON3Hbits.CLKDIV = 0;				// clock divider (1:1)
	// Configure the ADC reference sources.
	ADCON3Lbits.REFSEL = 0;				// AVdd as voltage reference
	// Configure the integer of fractional output format.
	ADCON1Hbits.FORM = 0;				// unsigned integer format
	// Set initialization time to maximum
	ADCON5Hbits.WARMTIME = 15;

	//ADLVLTRGL = 0x0000;				// input triggers edge sensitive

	// Turn on ADC module
	BSP_ADC_Module_Enable();
}

void BSP_ADC_Core_Enable(char Core)
{
	switch(Core) {
		case BSP_ADC_CORE_NUMBER_1:
			// Configure the I/O pins to be used as analog inputs.
#ifdef ADC_CORE1_AN0_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE1_AN0_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE1_AN0_PORTPIN);
#endif
#ifdef ADC_CORE1_AN7_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE1_AN7_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE1_AN7_PORTPIN);
#endif
			// Configure the core ADC clock.
			ADCORE0Hbits.ADCS = 0;				// clock divider (1:2);	ADC clock = FADC / 2 = 120MHz / 2 = 60MHz;	14.5*Tad = 4.14 MSPS
			// Select single-ended input configuration and unsigned output format.
			ADMOD0Lbits.SIGN0 = 0;
			ADMOD0Lbits.DIFF0 = 0;
			// Turn on analog power for dedicated core 0
			ADCON5Lbits.C0PWR = 1;
			// Wait when the core 0 is ready for operation
			while(ADCON5Lbits.C0RDY == 0) {};
			// Turn on digital power to enable triggers to the core 0
			ADCON3Hbits.C0EN = 1;
			break;
		case BSP_ADC_CORE_NUMBER_2:
			// Configure the I/O pins to be used as analog inputs.
#ifdef ADC_CORE2_AN1_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE2_AN1_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE2_AN1_PORTPIN);
#endif
#ifdef ADC_CORE2_AN18_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE2_AN18_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE2_AN18_PORTPIN);
#endif
			// Configure the core ADC clock.
			ADCORE1Hbits.ADCS = 0;				// clock divider (1:2)
			// Select single-ended input configuration and unsigned output format.
			ADMOD0Lbits.SIGN1 = 0;
			ADMOD0Lbits.DIFF1 = 0;
			// Turn on analog power for dedicated core 1
			ADCON5Lbits.C1PWR = 1;
			// Wait when the core 1 is ready for operation
			while(ADCON5Lbits.C1RDY == 0) {};
			// Turn on digital power to enable triggers to the core 1
			ADCON3Hbits.C1EN = 1;
			break;
		case BSP_ADC_CORE_NUMBER_3:
			// Configure the I/O pins to be used as analog inputs.
#ifdef ADC_CORE3_AN2_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE3_AN2_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE3_AN2_PORTPIN);
#endif
#ifdef ADC_CORE3_AN11_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE3_AN11_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE3_AN11_PORTPIN);
#endif
			// Configure the core ADC clock.
			ADCORE2Hbits.ADCS = 0;				// clock divider (1:2)
			// Select single-ended input configuration and unsigned output format.
			ADMOD0Lbits.SIGN2 = 0;
			ADMOD0Lbits.DIFF2 = 0;
			// Turn on analog power for dedicated core 2
			ADCON5Lbits.C2PWR = 1;
			// Wait when the core 2 is ready for operation
			while(ADCON5Lbits.C2RDY == 0) {};
			// Turn on digital power to enable triggers to the core 2
			ADCON3Hbits.C2EN = 1;
			break;
		case BSP_ADC_CORE_NUMBER_4:
			// Configure the I/O pins to be used as analog inputs.
#ifdef ADC_CORE4_AN3_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE4_AN3_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE4_AN3_PORTPIN);
#endif
#ifdef ADC_CORE4_AN15_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE4_AN15_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE4_AN15_PORTPIN);
#endif
			// Configure the core ADC clock.
			ADCORE3Hbits.ADCS = 0;				// clock divider (1:2)
			// Select single-ended input configuration and unsigned output format.
			ADMOD0Lbits.SIGN3 = 0;
			ADMOD0Lbits.DIFF3 = 0;
			// Turn on analog power for dedicated core 3
			ADCON5Lbits.C3PWR = 1;
			// Wait when the core 3 is ready for operation
			while(ADCON5Lbits.C3RDY == 0) {};
			// Turn on digital power to enable triggers to the core 3
			ADCON3Hbits.C3EN = 1;
			break;
		case BSP_ADC_CORE_NUMBER_5:
			// Configure the I/O pins to be used as analog inputs.
#ifdef ADC_CORE5_AN4_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN4_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN4_PORTPIN);
#endif
#ifdef ADC_CORE5_AN5_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN5_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN5_PORTPIN);
#endif
#ifdef ADC_CORE5_AN6_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN6_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN6_PORTPIN);
#endif
#ifdef ADC_CORE5_AN8_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN8_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN8_PORTPIN);
#endif
#ifdef ADC_CORE5_AN9_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN9_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN9_PORTPIN);
#endif
#ifdef ADC_CORE5_AN10_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN10_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN10_PORTPIN);
#endif
#ifdef ADC_CORE5_AN12_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN12_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN12_PORTPIN);
#endif
#ifdef ADC_CORE5_AN13_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN13_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN13_PORTPIN);
#endif
#ifdef ADC_CORE5_AN14_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN14_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN14_PORTPIN);
#endif
#ifdef ADC_CORE5_AN16_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN16_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN16_PORTPIN);
#endif
#ifdef ADC_CORE5_AN17_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN17_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN17_PORTPIN);
#endif
#ifdef ADC_CORE5_AN19_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN19_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN19_PORTPIN);
#endif
#ifdef ADC_CORE5_AN20_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN20_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN20_PORTPIN);
#endif
#ifdef ADC_CORE5_AN21_PORTPIN
			BSP_IO_GPIO_AN_ON(ADC_CORE5_AN21_PORTPIN);
			BSP_IO_GPIO_DIR_IN(ADC_CORE5_AN21_PORTPIN);
#endif
			// Configure the core ADC clock.
			ADCON2Lbits.SHRADCS = 0; 			// clock divider (1:2)
			// Select single-ended input configuration and unsigned output format.
			ADMOD0Lbits.SIGN4 = 0;
			ADMOD0Lbits.DIFF4 = 0;
			// Turn on analog power for shared core
			ADCON5Lbits.SHRPWR = 1;
			// Wait when the shared core is ready for operation
			while(ADCON5Lbits.SHRRDY == 0) {};
			// Turn on digital power to enable triggers to the shared core
			ADCON3Hbits.SHREN = 1;
			break;
	}
}

void BSP_ADC_Core_Calibrate(char Core)
{
	switch(Core) {
		case BSP_ADC_CORE_NUMBER_1:
			// Enable calibration for the dedicated core 0
			ADCAL0Lbits.CAL0EN = 1;
			// Single-ended input calibration
			ADCAL0Lbits.CAL0DIFF = 0;
			// Start calibration
			ADCAL0Lbits.CAL0RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Lbits.CAL0RDY == 0) {};
			// Differential input calibration
			ADCAL0Lbits.CAL0DIFF = 1;
			// Start calibration
			ADCAL0Lbits.CAL0RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Lbits.CAL0RDY == 0) {};
			// End the core 0 calibration
			ADCAL0Lbits.CAL0EN = 0;
			break;
		case BSP_ADC_CORE_NUMBER_2:
			// Enable calibration for the dedicated core 1
			ADCAL0Lbits.CAL1EN = 1;
			// Single-ended input calibration
			ADCAL0Lbits.CAL1DIFF = 0;
			// Start calibration
			ADCAL0Lbits.CAL1RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Lbits.CAL1RDY == 0) {};
			// Differential input calibration
			ADCAL0Lbits.CAL1DIFF = 1;
			// Start calibration
			ADCAL0Lbits.CAL1RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Lbits.CAL1RDY == 0) {};
			// End the core 1 calibration
			ADCAL0Lbits.CAL1EN = 0;
			break;
		case BSP_ADC_CORE_NUMBER_3:
			// Enable calibration for the dedicated core 2
			ADCAL0Hbits.CAL2EN = 1;
			// Single-ended input calibration
			ADCAL0Hbits.CAL2DIFF = 0;
			// Start calibration
			ADCAL0Hbits.CAL2RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Hbits.CAL2RDY == 0) {};
			// Differential input calibration
			ADCAL0Hbits.CAL2DIFF = 1;
			// Start calibration
			ADCAL0Hbits.CAL2RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Hbits.CAL2RDY == 0) {};
			// End the core 1 calibration
			ADCAL0Hbits.CAL2EN = 0;
			break;
		case BSP_ADC_CORE_NUMBER_4:
			// Enable calibration for the dedicated core 4
			ADCAL0Hbits.CAL3EN = 1;
			// Single-ended input calibration
			ADCAL0Hbits.CAL3DIFF = 0;
			// Start calibration
			ADCAL0Hbits.CAL3RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Hbits.CAL3RDY == 0) {};
			// Differential input calibration
			ADCAL0Hbits.CAL3DIFF = 1;
			// Start calibration
			ADCAL0Hbits.CAL3RUN = 1;
			// Poll for the calibration end
			while(ADCAL0Hbits.CAL3RDY == 0) {};
			// End the core 1 calibration
			ADCAL0Hbits.CAL3EN = 0;
			break;
		case BSP_ADC_CORE_NUMBER_5:
			// Enable calibration for the shared core
			ADCAL1Hbits.CSHREN = 1;
			// Single-ended input calibration
			ADCAL1Hbits.CSHRDIFF = 0;
			// Start calibration
			ADCAL1Hbits.CSHRRUN = 1;
			// Poll for the calibration end
			while(ADCAL1Hbits.CSHRRDY == 0) {};
			// Differential input calibration
			ADCAL1Hbits.CSHRDIFF = 1;
			// Start calibration
			ADCAL1Hbits.CSHRRUN = 1;
			// Poll for the calibration end
			while(ADCAL1Hbits.CSHRRDY == 0) {};
			// End the shared core calibration
			ADCAL1Hbits.CSHREN = 0;
			break;
	}
}

void BSP_ADC_Set_Trigger(char Core, char Source)
{
	// Set same trigger source for all inputs to sample signals simultaneously.
	switch(Core) {
		case BSP_ADC_CORE_NUMBER_1:
			ADTRIG0Lbits.TRGSRC0 = Source;		// AN0
			break;
		case BSP_ADC_CORE_NUMBER_2:
			ADTRIG0Lbits.TRGSRC1 = Source;		// AN1
			break;
		case BSP_ADC_CORE_NUMBER_3:
			ADTRIG0Hbits.TRGSRC2 = Source;		// AN2
			break;
		case BSP_ADC_CORE_NUMBER_4:
			ADTRIG0Hbits.TRGSRC3 = Source;		// AN3
			break;
		case BSP_ADC_CORE_NUMBER_5:
			ADTRIG1Lbits.TRGSRC4 = Source;		// AN4
			ADTRIG1Lbits.TRGSRC5 = Source;		// AN5
			ADTRIG1Hbits.TRGSRC6 = Source;		// AN6
#ifdef DSPIC_7XX_FAMILY
			ADTRIG2Lbits.TRGSRC8 = Source;		// AN8
			ADTRIG2Lbits.TRGSRC9 = Source;		// AN9
			ADTRIG2Hbits.TRGSRC10 = Source;		// AN10
			ADTRIG2Hbits.TRGSRC11 = Source;		// AN12
			ADTRIG3Lbits.TRGSRC13 = Source;		// AN13
			ADTRIG3Hbits.TRGSRC14 = Source;		// AN14
			ADTRIG4Lbits.TRGSRC16 = Source;		// AN16
			ADTRIG4Lbits.TRGSRC17 = Source;		// AN17
#endif
			ADTRIG4Hbits.TRGSRC19 = Source;		// AN19
			ADTRIG5Lbits.TRGSRC20 = Source;		// AN20
			ADTRIG5Lbits.TRGSRC21 = Source;		// AN21
			ADCON3Lbits.SHRSAMP = 1;
			break;
	}		
}

#ifndef INLINE_UNSUPPORTED
inline void BSP_ADC_Core_1_Interrupt_Clear(void)
{
	_ADCAN0IF = 0;						// clear interrupt flag for AN0
}

inline void BSP_ADC_Core_2_Interrupt_Clear(void)
{
	_ADCAN1IF = 0;						// clear interrupt flag for AN1
}

inline void BSP_ADC_Core_3_Interrupt_Clear(void)
{
	_ADCAN2IF = 0;						// clear interrupt flag for AN2
}

inline void BSP_ADC_Core_4_Interrupt_Clear(void)
{
	_ADCAN3IF = 0;						// clear interrupt flag for AN3
}

inline void BSP_ADC_Core_5_Interrupt_Clear(void)
{
	_ADCAN4IF = 0;						// clear interrupt flag for AN4
}
#endif	// INLINE_UNSUPPORTED

void BSP_ADC_Interrupt_Enable(char Core, unsigned char Level)
{
	// Configure and enable ADC interrupts.
	switch(Core) {
		case BSP_ADC_CORE_NUMBER_1:
			_ADCAN0IP = Level;
			_ADCAN0IF = 0;						// clear interrupt flag for AN0
			_ADCAN0IE = 1;						// enable interrupt for AN0
			_IE0 = 1;							// enable interrupt for AN0
			break;
		case BSP_ADC_CORE_NUMBER_2:
			_ADCAN1IP = Level;
			_ADCAN1IF = 0;						// clear interrupt flag for AN1
			_ADCAN1IE = 1;						// enable interrupt for AN1
			_IE1 = 1;							// enable interrupt for AN1
			break;
		case BSP_ADC_CORE_NUMBER_3:
			_ADCAN2IP = Level;
			_ADCAN2IF = 0;						// clear interrupt flag for AN2
			_ADCAN2IE = 1;						// enable interrupt for AN2
			_IE2 = 1;							// enable interrupt for AN2
			break;
		case BSP_ADC_CORE_NUMBER_4:
			_ADCAN3IP = Level;
			_ADCAN3IF = 0;						// clear interrupt flag for AN3
			_ADCAN3IE = 1;						// enable interrupt for AN3
			_IE3 = 1;							// enable interrupt for AN3
			break;
		case BSP_ADC_CORE_NUMBER_5:
			_ADCAN4IP = Level;
			_ADCAN4IF = 0;						// clear interrupt flag for AN4
			_ADCAN4IE = 1;						// enable interrupt for AN4
			_IE4 = 1;							// enable interrupt for AN4
			break;
	}
}

#ifndef INLINE_UNSUPPORTED
inline uint16_t BSP_ADC_Core_1_Value_Get(void)
{
	return ADCBUF0;
}

inline uint16_t BSP_ADC_Core_2_Value_Get(void)
{
	return ADCBUF1;
}

inline uint16_t BSP_ADC_Core_3_Value_Get(void)
{
	return ADCBUF2;
}

inline uint16_t BSP_ADC_Core_4_Value_Get(void)
{
	return ADCBUF3;
}

inline uint16_t BSP_ADC_Core_5_AN4_Value_Get(void)
{
	return ADCBUF4;
}

inline uint16_t BSP_ADC_Core_5_AN5_Value_Get(void)
{
	return ADCBUF5;
}

inline uint16_t BSP_ADC_Core_5_AN6_Value_Get(void)
{
	return ADCBUF6;
}

inline uint16_t BSP_ADC_Core_5_AN8_Value_Get(void)
{
	return ADCBUF8;
}

inline uint16_t BSP_ADC_Core_5_AN9_Value_Get(void)
{
	return ADCBUF9;
}

inline uint16_t BSP_ADC_Core_5_AN10_Value_Get(void)
{
	return ADCBUF10;
}

inline uint16_t BSP_ADC_Core_5_AN12_Value_Get(void)
{
	return ADCBUF12;
}

inline uint16_t BSP_ADC_Core_5_AN13_Value_Get(void)
{
	return ADCBUF13;
}

inline uint16_t BSP_ADC_Core_5_AN14_Value_Get(void)
{
	return ADCBUF14;
}

inline uint16_t BSP_ADC_Core_5_AN16_Value_Get(void)
{
	return ADCBUF16;
}

inline uint16_t BSP_ADC_Core_5_AN17_Value_Get(void)
{
	return ADCBUF17;
}

inline uint16_t BSP_ADC_Core_5_AN19_Value_Get(void)
{
	return ADCBUF19;
}

inline uint16_t BSP_ADC_Core_5_AN20_Value_Get(void)
{
	return ADCBUF20;
}

inline uint16_t BSP_ADC_Core_5_AN21_Value_Get(void)
{
	return ADCBUF21;
}

inline void BSP_ADC_Core_1_Input_Set(char Input)
{
	ADCON4Hbits.C0CHS = Input;
}

inline void BSP_ADC_Core_2_Input_Set(char Input)
{
	ADCON4Hbits.C1CHS = Input;
}

inline void BSP_ADC_Core_3_Input_Set(char Input)
{
	ADCON4Hbits.C2CHS = Input;
}

inline void BSP_ADC_Core_4_Input_Set(char Input)
{
	ADCON4Hbits.C3CHS = Input;
}

inline void BSP_ADC_Core_5_Input_Set(char Input)
{
	//ADCON3Lbits.SHRSAMP = 1;
	ADCON3Lbits.CNVCHSEL = Input;
	//ADCON3Lbits.SHRSAMP = 0;
	ADCON3Lbits.CNVRTCH = 1;
}
#endif// INLINE_UNSUPPORTED

void __attribute__((__interrupt__, no_auto_psv)) BSP_ADC_INTERRUPT_HANDLER()
{
	PWM_TST2_SET();
	BSP_ADC_INTERRUPT_CALLBACK();
	BSP_ADC_INTERRUPT_CLEAR();
	PWM_TST2_CLR();
}
