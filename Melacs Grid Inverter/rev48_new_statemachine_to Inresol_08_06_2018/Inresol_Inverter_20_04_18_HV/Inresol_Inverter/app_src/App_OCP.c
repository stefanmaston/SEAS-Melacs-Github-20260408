/*
 *  File name: App_OCP.c
 *
 *  Description: High level function implementations for Over Current Protection
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

#ifndef UINT16_MAX
#define UINT16_MAX (65535U)
#endif

#define APP_OCP_OC_PWM_OFFSET_25PERCENT			((((uint32_t)UINT16_MAX + 1) >> 2) * 1)		// 25% of 65536
#define APP_OCP_OC_PWM_OFFSET_75PERCENT			((((uint32_t)UINT16_MAX + 1) >> 2) * 3)		// 75% of 65536

volatile uint16_t	App_OCP_ITrip_Inv;			// I-Trip Magnitude for channel Inv or Upper
volatile uint16_t	App_OCP_ITrip_Grid;			// I-Trip Magnitude for channel Grid or Lower
volatile uint8_t	App_OCP_OC_Status;

#if (defined HARDWARE_VERSION_1)
// Note: The Over Current Protection element parameters are:
// P/N: ACS716KLATR-25CB-NL (Ip=+/-25A; Sens=18.5mV/A; No Latched Fault; Voc range=0.25Vcc<->0.4Vcc)
// Ioc Min:  0.25 * 3300mV / 18.5 =  825mV / 18.5 = 44.6A
// Ioc Max:  0.40 * 3300mV / 18.5 = 1320mV / 18.5 = 71.4A
// Ioc Max HW Limited: 3300mV / 3 = 1100mV / 18.5 = 59.5A

// Example: VOC = Sens × Ioc = 18.5 × 50A = 925mV

// PWM Max: 1100mV = 1.00
// PWM Min: 825mV / 1100mV = 0.75

inline uint16_t App_OCP_Get_Sample_Scaled_Ch1(void)
{
	uint16_t	sample_value;

	sample_value = APP_OCP_OC_PWM_OFFSET_75PERCENT + (App_OCP_ITrip_Inv >> 2);		// 0.75 <-> 1.0
	return sample_value;
}

inline uint16_t App_OCP_Get_Sample_Scaled_Ch2(void)
{
	uint16_t	sample_value;

	sample_value = APP_OCP_OC_PWM_OFFSET_75PERCENT + (App_OCP_ITrip_Grid >> 2);		// 0.75 <-> 1.0
	return sample_value;
}
#elif (defined HARDWARE_VERSION_2)
inline uint16_t App_OCP_Get_Sample_Scaled_Ch1(void)
{
	uint16_t	sample_value;

	sample_value = App_OCP_ITrip_Inv;												// 0.0 <-> 1.0
	return sample_value;
}

inline uint16_t App_OCP_Get_Sample_Scaled_Ch2(void)
{
	uint16_t	sample_value;

	sample_value = App_OCP_ITrip_Grid;												// 0.0 <-> 1.0
	return sample_value;
}
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

uint16_t App_OCP_Get_Sample_Scaled(uint8_t Channel)
{
	uint16_t	sample_value;

	switch(Channel) {
		case APP_OCP_ITRIP_CHANNEL_NUMBER_1:
			sample_value = App_OCP_Get_Sample_Scaled_Ch1();
			break;
		case APP_OCP_ITRIP_CHANNEL_NUMBER_2:
			sample_value = App_OCP_Get_Sample_Scaled_Ch2();
			break;
	}
	return sample_value;
}

void App_OCP_Init(void *Parameters)
{
	(void)Parameters;
#if (defined HARDWARE_VERSION_1)
	App_OCP_ITrip_Inv = 0;
	App_OCP_ITrip_Grid = 0;
#elif (defined HARDWARE_VERSION_2)
	App_OCP_ITrip_Inv = APP_OCP_OC_PWM_OFFSET_75PERCENT;
	App_OCP_ITrip_Grid = APP_OCP_OC_PWM_OFFSET_25PERCENT;
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x
	App_OCP_OC_Status = 0;
#ifdef OC_L1_INV_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L1_INV_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L1_INV_PORTPIN);
#endif
#ifdef OC_L2_INV_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L2_INV_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L2_INV_PORTPIN);
#endif
#ifdef OC_L3_INV_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L3_INV_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L3_INV_PORTPIN);
#endif
#ifdef OC_L1_GRID_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L1_GRID_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L1_GRID_PORTPIN);
#endif
#ifdef OC_L2_GRID_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L2_GRID_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L2_GRID_PORTPIN);
#endif
#ifdef OC_L3_GRID_PORTPIN
	BSP_IO_GPIO_DIR_IN(OC_L3_GRID_PORTPIN);
	BSP_IO_GPIO_PU_ON(OC_L3_GRID_PORTPIN);
#endif
}

inline void App_OCP_Process(void)
{
	if(ADC_Ready == false)									// We need some small delay after system power-up to stabilize OCP thresholds
		return;
#ifdef OC_L1_INV_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L1_Inv_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L1_INV_PORTPIN))) {		// Active input
		if(L1_Inv_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L1_Inv_Delay++;
		} else if(L1_Inv_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L1_Inv_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L1_INV);
		}
	} else {												// InActive input
		if(L1_Inv_Delay > 0) {
			L1_Inv_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L1_INV_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L1_INV);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#ifdef OC_L2_INV_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L2_Inv_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L2_INV_PORTPIN))) {		// Active input
		if(L2_Inv_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L2_Inv_Delay++;
		} else if(L2_Inv_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L2_Inv_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L2_INV);
		}
	} else {												// InActive input
		if(L2_Inv_Delay > 0) {
			L2_Inv_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L2_INV_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L2_INV);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#ifdef OC_L3_INV_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L3_Inv_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L3_INV_PORTPIN))) {		// Active input
		if(L3_Inv_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L3_Inv_Delay++;
		} else if(L3_Inv_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L3_Inv_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L3_INV);
		}
	} else {												// InActive input
		if(L3_Inv_Delay > 0) {
			L3_Inv_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L3_INV_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L3_INV);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#ifdef OC_L1_GRID_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L1_Grid_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L1_GRID_PORTPIN))) {		// Active input
		if(L1_Grid_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L1_Grid_Delay++;
		} else if(L1_Grid_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L1_Grid_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L1_GRID);
		}
	} else {												// InActive input
		if(L1_Grid_Delay > 0) {
			L1_Grid_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L1_GRID_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L1_GRID);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#ifdef OC_L2_GRID_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L2_Grid_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L2_GRID_PORTPIN))) {		// Active input
		if(L2_Grid_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L2_Grid_Delay++;
		} else if(L2_Grid_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L2_Grid_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L2_GRID);
		}
	} else {												// InActive input
		if(L2_Grid_Delay > 0) {
			L2_Grid_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L2_GRID_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L2_GRID);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#ifdef OC_L3_GRID_PORTPIN
#ifdef APP_OCP_OC_FILTER_ENABLED
	static uint8_t L3_Grid_Delay = 0;

	if(!(BSP_IO_GPIO_INP_STATUS(OC_L3_GRID_PORTPIN))) {		// Active input
		if(L3_Grid_Delay < (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L3_Grid_Delay++;
		} else if(L3_Grid_Delay == (APP_OCP_OC_FILTER_LENGTH - 1)) {
			L3_Grid_Delay++;
			App_OCP_OC_Status |= (1 << APP_OCP_OC_L3_GRID);
		}
	} else {												// InActive input
		if(L3_Grid_Delay > 0) {
			L3_Grid_Delay--;
		}
	}
#else	// APP_OCP_OC_FILTER_ENABLED
	if(!(BSP_IO_GPIO_INP_STATUS(OC_L3_GRID_PORTPIN)))		// Active input
		App_OCP_OC_Status |= (1 << APP_OCP_OC_L3_GRID);
#endif	// APP_OCP_OC_FILTER_ENABLED
#endif

#if 0	// Test
	if(App_OCP_OC_Status != 0)
		GPIO_LED_2_TGL();
#endif
}
