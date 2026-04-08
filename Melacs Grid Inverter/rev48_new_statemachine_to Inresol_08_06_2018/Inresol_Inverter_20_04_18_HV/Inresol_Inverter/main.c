/*
 *  File name: main.c
 *
 *  Description: main function
 *
 *  Author: Future Electronics
 *
 */

#include <xc.h>

#if __XC16_VERSION < 1011
    #warning "Please upgrade to XC16 v1.11 or newer."
#endif

#include "global_includes.h"
#include "config_fuses.h"

int main(void)
{
	// Read and Store RESET bits
	BSP_System_RST_Read();

	// Configure PLL
	BSP_System_PLL_Main_Setup();

	// Disable Watch Dog Timer
	BSP_System_WDT_Disable();

	// Change oscillator to FRC + PLL
	BSP_System_OSC_Switch();

	// Setup the ADC and PWM clock
	BSP_System_PLL_Aux_Setup();

	// Configure all analog ports as digital I/O & all pins to input first
	BSP_IO_Pins_DeInit();

	// Configure pins as inputs or outputs
	BSP_IO_Pins_Init();

	// Set Non Volatile Memory
	App_NVMemory_Init(NULL);

	// Set TIMER1 peripheral and interrupt
	App_SysTick_Init(NULL);

	// Configure pins for relays
	App_Relay_Init(NULL);

	// Set UART1 peripheral and interrupt
	App_Debug_Init(NULL);

	// Set Data Recording
#ifdef APP_DATAREC_ENABLED
	App_DataRec_Init(NULL);
#endif	// APP_DATAREC_ENABLED

	// Set PWM peripheral and interrupt
	App_PWM_Init(NULL);

	// Set ADC peripheral and interrupt
	App_ADC_Init(NULL);

	// Set Temperature Sensor
	App_TempSens_Init(NULL);
	
	// Set MODBUS interface
	App_MODBUS_Init(NULL);
	
	// Set Over Current Protection
//	App_OCP_Init(NULL);									// Moved to PWM
	
	// Set Non Volatile Memory
	//App_NVMemory_Init(NULL);
	
	// Configure DPLL
	App_DPLL_Init(NULL);

	// Set Main State Machine
	App_SM_Init(NULL);

	while(1) {
		App_Debug_Process(NULL);
		App_SM_Process((void*)&App_SysTick_Counter_ms);
		App_Relay_Process(NULL);
		App_PWM_Process_IDLE(NULL);
		App_ADC_Process_IDLE(NULL);
		App_TempSens_Process((void*)&App_SysTick_Counter_ms);
//		App_OCP_Process(&App_SysTick_Counter_ms);		// Moved to PWM
		App_MODBUS_Process(NULL);
		App_NVMemory_Process(NULL);
#ifdef APP_DATAREC_ENABLED
		App_DataRec_Process(NULL);
#endif	// APP_DATAREC_ENABLED
	}	// End of the infinite loop

	return 0;
}
