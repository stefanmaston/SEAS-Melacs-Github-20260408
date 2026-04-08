/*
 *  File name: App_SysTick.h
 *
 *  Description: High level function declarations for SysTick processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_SYSTICK_H
#define APP_SYSTICK_H

extern volatile uint16_t App_SysTick_Counter_ms;
extern volatile uint16_t App_LED_HB_Delay;
extern volatile uint16_t App_RTC_Counter_ms;
extern volatile uint32_t App_RTC_Counter_s;

void App_SysTick_Init(void *Parameters);
inline void App_SysTick_Process(void);
void App_SysTick_Delay(uint16_t Delay_ms);

#define TimerInterruptCount		App_SysTick_Counter_ms		// For DC/DC Converter software compatibility

#endif // APP_SYSTICK_H
