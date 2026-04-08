/*
 *  File name: types_adc.h
 *
 *  Description: Type definitions for ADC
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_ADC_H
#define TYPES_ADC_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_ADC_CoreNumber
{
	BSP_ADC_CORE_NUMBER_1 = 0,	// Dedicated ADC Core 0
	BSP_ADC_CORE_NUMBER_2,		// Dedicated ADC Core 1
	BSP_ADC_CORE_NUMBER_3,		// Dedicated ADC Core 2
	BSP_ADC_CORE_NUMBER_4,		// Dedicated ADC Core 3
	BSP_ADC_CORE_NUMBER_5,		// Shared ADC Core
	BSP_ADC_CORES_MAX
} PWM_CoreNumber_t;

#define BSP_ADC_CORE1_MUX_AN0	0			// AN0
#define BSP_ADC_CORE1_MUX_AN7	1			// AN7
#define BSP_ADC_CORE2_MUX_AN1	0			// AN1
#define BSP_ADC_CORE2_MUX_AN18	1			// AN18
#define BSP_ADC_CORE3_MUX_AN2	0			// AN2
#define BSP_ADC_CORE3_MUX_AN11	1			// AN11
#define BSP_ADC_CORE4_MUX_AN3	0			// AN3
#define BSP_ADC_CORE4_MUX_AN15	1			// AN15
#define BSP_ADC_CORE5_MUX_AN4	4			// AN4
#define BSP_ADC_CORE5_MUX_AN5	5			// AN5
#define BSP_ADC_CORE5_MUX_AN6	6			// AN6
#define BSP_ADC_CORE5_MUX_AN8	8			// AN8
#define BSP_ADC_CORE5_MUX_AN9	9			// AN9
#define BSP_ADC_CORE5_MUX_AN10	10			// AN10
#define BSP_ADC_CORE5_MUX_AN12	12			// AN12
#define BSP_ADC_CORE5_MUX_AN13	13			// AN13
#define BSP_ADC_CORE5_MUX_AN14	14			// AN14
#define BSP_ADC_CORE5_MUX_AN16	16			// AN16
#define BSP_ADC_CORE5_MUX_AN17	17			// AN17
#define BSP_ADC_CORE5_MUX_AN19	19			// AN19
#define BSP_ADC_CORE5_MUX_AN20	20			// AN20
#define BSP_ADC_CORE5_MUX_AN21	21			// AN21

#endif	// TYPES_ADC_H
