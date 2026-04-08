/******************************************************************************
 * Expose a hardware timer's counter for application's use, and add a some
 * utility functions for generating perodic events.
 *
 * The 16-bit TMR1 is used with the 32 kHz oscillator as input with an 8x
 * prescaler, giving use 4096 ticks per second and a 16-second period
 ******************************************************************************/
#ifndef _TIMER_H
#define _TIMER_H
#include "Common.h"

#define TIMER_EXTERNAL_OSCILLATOR 0

#if TIMER_EXTERNAL_OSCILLATOR
#	define TIMER_TICKS_PER_SECOND 4096U
#	define Timer_MS(num) ((Timer_t) (((uint24_t) (num) << 10) / 125UL))
#	define Timer_Interrupt() ((void) 0)
#else
#	define TIMER_TICKS_PER_SECOND 3906U // +1/4
#	define Timer_MS(num) ((Timer_t) ((uint24_t) (num) * 125U >> 5))
#	define Timer_Interrupt() ((void) (PIR1bits.TMR1IF = 0, ++Timer_Overflow))
#endif

typedef uint16_t Timer_t;

void Timer_Init(void);
Timer_t Timer_Get(Timer_t timer);
bool Timer_CheckRaw(Timer_t *timer, Timer_t period);
Timer_t Timer_Tick(void);
#define Timer_Check(timer, period) (Timer_CheckRaw((timer), Timer_MS((period)))) 

#if !TIMER_EXTERNAL_OSCILLATOR
extern volatile uint8_t Timer_Overflow;
#endif

#endif
