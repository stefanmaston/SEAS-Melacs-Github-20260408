/*
 *  File name: BSP_Timer.c
 *
 *  Description: Board Support Package function implementations for Timer processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

// TIMER 1 (16-bit)
void BSP_Timer_1_Open(uint16_t Config, uint16_t Period)
{
	TMR1 = 0;			// Reset Timer1 to 0x0000
	PR1 = Period;		// Assigning Period to Timer period register
	T1CON = Config;		// Configure timer control reg
}

void BSP_Timer_1_Close(void)
{
	_T1IE = 0;			// Disable the Timer1 interrupt
	T1CONbits.TON = 0;	// Disable Timer1
	_T1IF = 0;			// Clear Timer1 interrupt flag
}

inline void BSP_Timer_1_Start(void)
{
	T1CONbits.TON = 1;	// Enable Timer1
}

inline void BSP_Timer_1_Stop(void)
{
	T1CONbits.TON = 0;	// Disable Timer1
}

inline void BSP_Timer_1_Set_Period(uint16_t Period)
{
	PR1 = Period;		// Assigning Period to Timer1 period register
}

inline void BSP_Timer_1_Set_Timer(uint16_t Timer)
{
	TMR1 = Timer;		// Assign timer value to Timer1 Register
}

inline uint16_t BSP_Timer_1_Get_Timer(void)
{
	return (TMR1);		// Return the Timer1 register
}

inline void BSP_Timer_1_Interrupt_Enable(void)
{
	_T1IE = 1;			// Interrupt Enable
}

inline void BSP_Timer_1_Interrupt_Disable(void)
{
	_T1IE = 0;			// Interrupt Disable
}

inline void BSP_Timer_1_Interrupt_Clear(void)
{
	_T1IF = 0;			// Clear IF bit
}

inline void BSP_Timer_1_Interrupt_Priority(uint8_t Priority)
{
	_T1IP = (Priority & 0x0007);	// Assigning Interrupt Priority
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_TIMER_1_INTERRUPT_HANDLER()
{
	BSP_TIMER_1_INTERRUPT_CALLBACK();
	BSP_TIMER_1_INTERRUPT_CLEAR();
}

// TIMER 2-3 (32-bit)

void BSP_Timer_23_Open(uint16_t Config, uint32_t Period)
{
	TMR2 = 0;			// Reset Timer2 to 0x0000
	TMR3 = 0;			// Reset Timer3 to 0x0000
	PR2 = Period;		// Assigning Period to PR2
	PR3 = Period >> 16;	// Period to PR3 Register
	T2CON = Config;		// Configure timer control reg
	T2CONbits.T32 = 1;
}

void BSP_Timer_23_Close(void)
{
	_T3IE = 0;			// Disable the Timer3 interrupt
	if(T2CONbits.T32 == 1)
		T2CONbits.TON = 0;	// Disable Timer2
	_T3IF = 0;			// Clear Timer3 interrupt flag
}

inline void BSP_Timer_23_Start(void)
{
	T2CONbits.TON = 1;	// Enable Timer2
	MB_TST3_SET();
	MB_TST3_CLR();
	MB_TST3_SET();
}

inline void BSP_Timer_23_Stop(void)
{
	T2CONbits.TON = 0;	// Disable Timer2
	T3CONbits.TON = 0;	// Disable Timer3
	MB_TST2_SET();
	MB_TST2_CLR();
}

inline void BSP_Timer_23_Set_Period(uint32_t Period)
{
	PR2 = Period;		// Assigning Period to PR2
	PR3 = Period >> 16;	// Period to PR3 Register
}

inline void BSP_Timer_23_Set_Timer(uint32_t Timer)
{
	TMR3HLD = (Timer >> 16);
	TMR2 = Timer;		// LSB to Timer2 and MSB to Timer3HLD
}

inline uint32_t BSP_Timer_23_Get_Timer(void)
{
	uint32_t Timer;
	Timer = TMR2;		// Copy Timer2 into timer low 16bit
	Timer |= (uint32_t)TMR3HLD << 16;	// Shift 16 times as TMR 3 contains MSB, TMR2 LSB 
	return(Timer);
}

inline void BSP_Timer_23_Interrupt_Enable(void)
{
	_T3IE = 1;			// Interrupt Enable
}

inline void BSP_Timer_23_Interrupt_Disable(void)
{
	_T3IE = 0;			// Interrupt Disable
}

inline void BSP_Timer_23_Interrupt_Clear(void)
{
	_T3IF = 0;			// Clear IF bit
}

inline void BSP_Timer_23_Interrupt_Priority(uint8_t Priority)
{
	_T3IP = (Priority & 0x0007);	// Assigning Interrupt Priority
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_TIMER_23_INTERRUPT_HANDLER()
{
	BSP_TIMER_23_INTERRUPT_CLEAR();
	MB_TST3_CLR();
	MB_TST3_SET();
	MB_TST3_CLR();
	BSP_TIMER_23_INTERRUPT_CALLBACK();
}
