/*
 * FreeModbus Port Library: dsPIC
 * Copyright (C) 2018 Future Electronics
 */

/* ----------------------- Platform includes --------------------------------*/
#include "global_includes.h"
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_TIMER_PRESCALER      (APP_SETTINGS_TIMER_MODBUS_PRESCALER)
#define MB_TIMER_TICKS          (FCY / MB_TIMER_PRESCALER)
#define MB_50US_TICKS           (20000UL)

/* ----------------------- Static variables ---------------------------------*/
static ULONG   usTimerDelta;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit(USHORT usTimerout50us)
{
	// Calculate overflow counter for two different prescalers and baudrates.
	// 70041600Hz / 256 = 273600Hz * 35 / 20000 = 478.8		// > 19200 bps
	// 70041600Hz / 256 = 273600Hz * 641 / 20000 = 8768.9	// e.g. 1200 bps
	// 70041600Hz / 64 = 1094400Hz * 35 / 20000 = 1915.2	// > 19200 bps
	// 70041600Hz / 64 = 1094400Hz * 641 / 20000 = 35075.5	// e.g. 1200 bps
	usTimerDelta = (ULONG)MB_TIMER_TICKS * usTimerout50us / (MB_50US_TICKS);
	BSP_Timer_23_Open(APP_SETTINGS_TIMER_MODBUS_CONFIG, usTimerDelta);
	BSP_Timer_23_Interrupt_Clear();
	BSP_Timer_23_Interrupt_Priority(APP_SETTINGS_TIMER_MODBUS_INTERRUPT_LEVEL);
	BSP_Timer_23_Interrupt_Enable();

	vMBPortTimersDisable();
	return TRUE;
}

void xMBPortTimersClose(void)
{
	// Not needed
}

void vMBPortTimersEnable(void)
{
	BSP_Timer_23_Stop();
	BSP_Timer_23_Set_Timer(0);
	BSP_Timer_23_Start();
}

void vMBPortTimersDisable(void)
{
	BSP_Timer_23_Stop();
}

void vMBPortTimersDelay(USHORT usTimeOutMS)
{
	// Not needed
}

void vMBPortTimerInterrupt(void)
{
	(void)pxMBPortCBTimerExpired();
}
