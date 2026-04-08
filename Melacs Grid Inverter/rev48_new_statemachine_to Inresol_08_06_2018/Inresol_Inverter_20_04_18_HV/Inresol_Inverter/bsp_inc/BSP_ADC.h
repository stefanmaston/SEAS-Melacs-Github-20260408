/*
 *  File name: BSP_ADC.h
 *
 *  Description: Board Support Package function declarations for ADC processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_ADC_H
#define BSP_ADC_H

void BSP_ADC_Module_Enable(void);
void BSP_ADC_Module_Disable(void);
void BSP_ADC_Module_Init(void);
void BSP_ADC_Core_Enable(char Core);
void BSP_ADC_Core_Calibrate(char Core);
void BSP_ADC_Set_Trigger(char Core, char Source);
void BSP_ADC_Interrupt_Enable(char Core, unsigned char Level);

#ifdef INLINE_UNSUPPORTED
#define BSP_ADC_Core_1_Value_Get()	\
			ADCBUF0

#define BSP_ADC_Core_2_Value_Get()	\
			ADCBUF1

#define BSP_ADC_Core_3_Value_Get()	\
			ADCBUF2

#define BSP_ADC_Core_4_Value_Get()	\
			ADCBUF3

#define BSP_ADC_Core_5_AN4_Value_Get()	\
			ADCBUF4

#define BSP_ADC_Core_5_AN5_Value_Get()	\
			ADCBUF5

#define BSP_ADC_Core_5_AN6_Value_Get()	\
			ADCBUF6

#define BSP_ADC_Core_5_AN8_Value_Get()	\
			ADCBUF8

#define BSP_ADC_Core_5_AN9_Value_Get()	\
			ADCBUF9

#define BSP_ADC_Core_5_AN10_Value_Get()	\
			ADCBUF10

#define BSP_ADC_Core_5_AN12_Value_Get()	\
			ADCBUF12

#define BSP_ADC_Core_5_AN13_Value_Get()	\
			ADCBUF13

#define BSP_ADC_Core_5_AN14_Value_Get()	\
			ADCBUF14

#define BSP_ADC_Core_5_AN16_Value_Get()	\
			ADCBUF16

#define BSP_ADC_Core_5_AN17_Value_Get()	\
			ADCBUF17

#define BSP_ADC_Core_5_AN19_Value_Get()	\
			ADCBUF19

#define BSP_ADC_Core_5_AN20_Value_Get()	\
			ADCBUF20

#define BSP_ADC_Core_5_AN21_Value_Get()	\
			ADCBUF21

#define BSP_ADC_Core_1_Input_Set(Input)	\
{										\
	ADCON4Hbits.C0CHS = Input;			\
}

#define BSP_ADC_Core_2_Input_Set(Input)	\
{										\
	ADCON4Hbits.C1CHS = Input;			\
}

#define BSP_ADC_Core_3_Input_Set(Input)	\
{										\
	ADCON4Hbits.C2CHS = Input;			\
}

#define BSP_ADC_Core_4_Input_Set(Input)	\
{										\
	ADCON4Hbits.C3CHS = Input;			\
}

#define BSP_ADC_Core_5_Input_Set(Input)	\
{										\
	ADCON3Lbits.CNVCHSEL = Input;		\
	ADCON3Lbits.CNVRTCH = 1;			\
}

#define BSP_ADC_Core_1_Interrupt_Clear()	\
{											\
	_ADCAN0IF = 0;							\
}

#define BSP_ADC_Core_2_Interrupt_Clear()	\
{											\
	_ADCAN1IF = 0;							\
}

#define BSP_ADC_Core_3_Interrupt_Clear()	\
{											\
	_ADCAN2IF = 0;							\
}

#define BSP_ADC_Core_4_Interrupt_Clear()	\
{											\
	_ADCAN3IF = 0;							\
}

#define BSP_ADC_Core_5_Interrupt_Clear()	\
{											\
	_ADCAN4IF = 0;							\
}

#else	// INLINE_UNSUPPORTED
inline uint16_t BSP_ADC_Core_1_Value_Get(void);
inline uint16_t BSP_ADC_Core_2_Value_Get(void);
inline uint16_t BSP_ADC_Core_3_Value_Get(void);
inline uint16_t BSP_ADC_Core_4_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN4_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN5_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN6_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN8_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN9_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN10_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN12_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN13_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN14_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN16_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN17_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN19_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN20_Value_Get(void);
inline uint16_t BSP_ADC_Core_5_AN21_Value_Get(void);
inline void BSP_ADC_Core_1_Input_Set(char Input);
inline void BSP_ADC_Core_2_Input_Set(char Input);
inline void BSP_ADC_Core_3_Input_Set(char Input);
inline void BSP_ADC_Core_4_Input_Set(char Input);
inline void BSP_ADC_Core_5_Input_Set(char Input);
inline void BSP_ADC_Core_1_Interrupt_Clear(void);
inline void BSP_ADC_Core_2_Interrupt_Clear(void);
inline void BSP_ADC_Core_3_Interrupt_Clear(void);
inline void BSP_ADC_Core_4_Interrupt_Clear(void);
inline void BSP_ADC_Core_5_Interrupt_Clear(void);
#endif	// INLINE_UNSUPPORTED

#define BSP_ADC_Core_1_Value_Corr	

#define BSP_ADC_Core_2_Value_Get()	\
			ADCBUF1

#define BSP_ADC_Core_3_Value_Get()	\
			ADCBUF2

#define BSP_ADC_Core_4_Value_Get()	\
			ADCBUF3

#define BSP_ADC_Core_5_AN4_Value_Get()	\
			ADCBUF4

#define BSP_ADC_Core_5_AN5_Value_Get()	\
			ADCBUF5

#define BSP_ADC_Core_5_AN6_Value_Get()	\
			ADCBUF6

#define BSP_ADC_Core_5_AN8_Value_Get()	\
			ADCBUF8

#define BSP_ADC_Core_5_AN9_Value_Get()	\
			ADCBUF9

#define BSP_ADC_Core_5_AN10_Value_Get()	\
			ADCBUF10

#define BSP_ADC_Core_5_AN12_Value_Get()	\
			ADCBUF12

#define BSP_ADC_Core_5_AN13_Value_Get()	\
			ADCBUF13

#define BSP_ADC_Core_5_AN14_Value_Get()	\
			ADCBUF14

#define BSP_ADC_Core_5_AN16_Value_Get()	\
			ADCBUF16

#define BSP_ADC_Core_5_AN17_Value_Get()	\
			ADCBUF17

#define BSP_ADC_Core_5_AN19_Value_Get()	\
			ADCBUF19

#define BSP_ADC_Core_5_AN20_Value_Get()	\
			ADCBUF20

#define BSP_ADC_Core_5_AN21_Value_Get()	\
			ADCBUF21

#endif	// BSP_ADC_H
