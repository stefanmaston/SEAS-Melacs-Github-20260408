#include "Common.h"
#include "Timer.h"

#if !TIMER_EXTERNAL_OSCILLATOR
volatile uint8_t Timer_Overflow;
#endif

void Timer_Init(void)
{
	TMR1L = 0x00;
	TMR1H = 0x00;

#	if TIMER_EXTERNAL_OSCILLATOR
	T1CON =
		_B7(1) | // Latched 16-bit access
		_B4(3) | // 8x prescaler
		_B3(1) | // Timer #1 oscillator enabled
		_B2(0) | // Synchronize external input (?)
		_B1(1) | // External clock from RC0
		_B0(1);  // Enable timer
#	else
	T1CON =
		_B7(0) | // Unlatched 8-bit access
		_B4(3) | // 8x prescaler
		_B0(1);  // Enable timer

	IPR1bits.TMR1IP = 0;
	PIE1bits.TMR1IE = 1;
#	endif
}

Timer_t Timer_Get(Timer_t timer)
{
	return timer - Timer_Tick();
}

bool Timer_CheckRaw(Timer_t *timer, Timer_t period)
{
	Timer_t target = *timer + period;

	if((int16_t) (target - Timer_Tick()) > 0)
		return false;

	*timer = target;
	return true;
}

#if TIMER_EXTERNAL_OSCILLATOR
Timer_t Timer_Tick(void)
{
	uint8_t lsb = TMR1L;
	return lsb | (uint16_t) TMR1H << 8;
}
#else
Timer_t Timer_Tick(void)
{
	uint8_t lsb, msb;

	do
	{
		lsb = TMR1H;
		msb = Timer_Overflow;
	}
	until(lsb == TMR1H);

	return lsb | (uint16_t) msb << 8;
}
#endif
