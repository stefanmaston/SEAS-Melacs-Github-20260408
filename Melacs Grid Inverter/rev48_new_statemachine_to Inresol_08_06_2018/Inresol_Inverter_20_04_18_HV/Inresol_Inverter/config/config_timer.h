/*
 *  File name: config_timer.h
 *
 *  Description: Timer peripheral settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_TIMER_H
#define CONFIG_TIMER_H

#include "types_timer.h"
#include "config_system.h"

//*****************************************************************************
//
// Timer App settings.
//
//*****************************************************************************

// Timer 1 Configuration (SysTick)
#define APP_SETTINGS_SYSTICK_FREQ					1000	// 1000Hz (1ms)
#define APP_SETTINGS_SYSTICK_PRESCALER				8		// FCY / 8
#define APP_SETTINGS_SYSTICK_CONFIG				(	\
	BSP_TIMER_SOURCE_INT &							\
	BSP_TIMER_PS_1_8 &								\
	BSP_TIMER_OFF &									\
	BSP_TIMER_IDLE_CON &							\
	BSP_TIMER_GATE_OFF &							\
	BSP_TIMER16_SYNC_EXT_OFF)
#define APP_SETTINGS_SYSTICK_INTERRUPT_LEVEL		5

#if 0	// Just an example
// Timer 2_3 Configuration
#define APP_SETTINGS_TIMER2_3_CONFIG			(	\
	BSP_TIMER32_32BIT_MODE_ON &						\
	BSP_TIMER_SOURCE_INT &							\
	BSP_TIMER_PS_1_1 &								\
	BSP_TIMER_OFF &									\
	BSP_TIMER_IDLE_CON &							\
	BSP_TIMER_GATE_OFF)
#define BSP_TIMER_23_INTERRUPT_LEVEL				5
#else
#define APP_SETTINGS_TIMER_MODBUS_PRESCALER			64		// FCY / 64
// Timer 2_3 Configuration
#define APP_SETTINGS_TIMER_MODBUS_CONFIG		(	\
	BSP_TIMER32_32BIT_MODE_ON &						\
	BSP_TIMER_SOURCE_INT &							\
	BSP_TIMER_PS_1_64 &								\
	BSP_TIMER_OFF &									\
	BSP_TIMER_IDLE_CON &							\
	BSP_TIMER16_SYNC_EXT_OFF &						\
	BSP_TIMER_GATE_OFF)
#define APP_SETTINGS_TIMER_MODBUS_INTERRUPT_LEVEL	3
#endif

#define BSP_TIMER_1_INTERRUPT_HANDLER()				_T1Interrupt()
#define BSP_TIMER_1_INTERRUPT_CALLBACK()			App_SysTick_Process()
#define BSP_TIMER_1_INTERRUPT_CLEAR()				BSP_Timer_1_Interrupt_Clear()

#define BSP_TIMER_23_INTERRUPT_HANDLER()			_T3Interrupt()
#define BSP_TIMER_23_INTERRUPT_CALLBACK()			vMBPortTimerInterrupt()
#define BSP_TIMER_23_INTERRUPT_CLEAR()				BSP_Timer_23_Interrupt_Clear()

#endif	// CONFIG_TIMER_H
