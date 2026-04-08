/*
 *  File name: App_SysTick.c
 *
 *  Description: High level function implementations for SysTick
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

//										70041600Hz / 8 = 8755200Hz / 1000Hz = 8755
#define APP_MACRO_SYSTICK_RELOAD		(FCY / APP_SETTINGS_SYSTICK_PRESCALER / APP_SETTINGS_SYSTICK_FREQ)

volatile uint16_t	App_SysTick_Counter_ms = 0;
volatile uint16_t	App_RTC_Counter_ms = 0;
volatile uint32_t	App_RTC_Counter_s = 0;
volatile uint16_t	App_LED_HB_Delay = 500;

void App_SysTick_Init(void *Parameters)
{
	(void)Parameters;
	BSP_Timer_1_Open(APP_SETTINGS_SYSTICK_CONFIG, APP_MACRO_SYSTICK_RELOAD);
	BSP_Timer_1_Interrupt_Clear();
	BSP_Timer_1_Interrupt_Priority(APP_SETTINGS_SYSTICK_INTERRUPT_LEVEL);
	BSP_Timer_1_Interrupt_Enable();
	BSP_Timer_1_Start();
}

static const char TestString[] = {"Test String: 0123456789\r\n"};

inline void App_SysTick_Process(void)
{
#if 1
	static uint16_t cnt;
	cnt++;
	if(cnt > App_LED_HB_Delay) {
		cnt = 0;
		GPIO_LED_HB_TGL();			// Toggle LED HeartBeat
#if 0
		BSP_UART_1_Send_Data_NoBlocking(&TestString, strlen((char*)TestString));
//		BSP_UART_1_Send_Data_Blocking(&TestString, strlen((char*)TestString));
#endif
	}
#endif
	App_SysTick_Counter_ms++;	// Increment interrupt counter
	App_RTC_Counter_ms++;
	if(App_RTC_Counter_ms >= 1000) {
		App_RTC_Counter_ms = 0;
		App_RTC_Counter_s++;
	}
}

void App_SysTick_Delay(uint16_t Delay_ms)
{
	uint16_t Timer_Last_Value;
	uint16_t Timer_Current_Value;

	Timer_Last_Value = App_SysTick_Counter_ms;
	do {
		Timer_Current_Value = App_SysTick_Counter_ms;
		if(Timer_Last_Value != Timer_Current_Value) {				// Enter each 1ms Tick
			Timer_Last_Value = Timer_Current_Value;
			if(Delay_ms > 0)
				Delay_ms--;
		}
	} while (Delay_ms > 0);
}
