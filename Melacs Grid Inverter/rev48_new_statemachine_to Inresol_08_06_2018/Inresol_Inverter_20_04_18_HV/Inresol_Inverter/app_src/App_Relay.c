/*
 *  File name: App_Relay.c
 *
 *  Description: High level function implementations for Relays
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

volatile uint8_t	RelaysState = 0;

void App_Relay_Init(void *Parameters)
{
	(void)Parameters;
	BSP_Relay_Init();
}

void App_Relay_On(uint8_t Relay)
{
	uint8_t bitmask;

	if(Relay >= APP_RELAY_MAX)
		return;
	bitmask = 1 << Relay;
	RelaysState |= bitmask;
}

void App_Relay_Off(uint8_t Relay)
{
	uint8_t bitmask;

	if(Relay >= APP_RELAY_MAX)
		return;
	bitmask = 1 << Relay;
	RelaysState &= ~bitmask;
}

void App_Relay_Process(void *Parameters)
{
	(void)Parameters;
	if((App_OCP_OC_Status != 0) || (Sys_Shutdown == true)) {
		BSP_Relay_Inv_Phase_Off();
		BSP_Relay_Inv_Neutral_Off();
		BSP_Relay_Grid_Phase_Off();
		BSP_Relay_Grid_Neutral_Off();
		// Notify
		App_Relay_Off(APP_RELAY_INV_PHASE);
		App_Relay_Off(APP_RELAY_INV_NEUTRAL);
		App_Relay_Off(APP_RELAY_GRID_PHASE);
		App_Relay_Off(APP_RELAY_GRID_NEUTRAL);
#ifdef ADC_AUTO_CALIBRATION
	} else if (ADC_Calib == true) {
		BSP_Relay_Inv_Phase_On();
		BSP_Relay_Inv_Neutral_On();
		BSP_Relay_Grid_Phase_On();
		BSP_Relay_Grid_Neutral_On();
		// Notify
		App_Relay_On(APP_RELAY_INV_PHASE);
		App_Relay_On(APP_RELAY_INV_NEUTRAL);
		App_Relay_On(APP_RELAY_GRID_PHASE);
		App_Relay_On(APP_RELAY_GRID_NEUTRAL);
#endif	// ADC_AUTO_CALIBRATION
	} else if (ADC_Ready == false) {
		BSP_Relay_Inv_Phase_Off();
		// BSP_Relay_Inv_Neutral_Off();
		BSP_Relay_Grid_Phase_Off();
		// BSP_Relay_Grid_Neutral_Off();
		// Notify
		App_Relay_Off(APP_RELAY_INV_PHASE);
		//App_Relay_Off(APP_RELAY_INV_NEUTRAL);
		App_Relay_Off(APP_RELAY_GRID_PHASE);
		//App_Relay_Off(APP_RELAY_GRID_NEUTRAL);
	} else {
		if(RelaysState & (1 << APP_RELAY_INV_PHASE)) {
			if(BSP_Relay_Inv_Phase_Get() == false)
				BSP_Relay_Inv_Phase_On();
		} else {
			if(BSP_Relay_Inv_Phase_Get() == true)
				BSP_Relay_Inv_Phase_Off();
		}
		if(RelaysState & (1 << APP_RELAY_INV_NEUTRAL)) {
			if(BSP_Relay_Inv_Neutral_Get() == false)
				BSP_Relay_Inv_Neutral_On();
		} else {
			if(BSP_Relay_Inv_Neutral_Get() == true)
				BSP_Relay_Inv_Neutral_Off();
		}
		if(RelaysState & (1 << APP_RELAY_GRID_PHASE)) {
			if(BSP_Relay_Grid_Phase_Get() == false)
				BSP_Relay_Grid_Phase_On();
		} else {
			if(BSP_Relay_Grid_Phase_Get() == true)
				BSP_Relay_Grid_Phase_Off();
		}
		if(RelaysState & (1 << APP_RELAY_GRID_NEUTRAL)) {
			if(BSP_Relay_Grid_Neutral_Get() == false)
				BSP_Relay_Grid_Neutral_On();
		} else {
			if(BSP_Relay_Grid_Neutral_Get() == true)
				BSP_Relay_Grid_Neutral_Off();
		}
	}
}
