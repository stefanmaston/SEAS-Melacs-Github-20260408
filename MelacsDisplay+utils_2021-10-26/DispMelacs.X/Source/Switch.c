#include "Common.h"
#include "Pins.h"
#include "Switch.h"

#define SWITCH_DEBOUNCE 16

Switch_t _Switch_State = -1 /* No initial flanks if held at start-up */;
Switch_t _Switch_Press;
Switch_t _Switch_Release;


/******************************************************************************
 * Refresh the switch inputs
 ******************************************************************************/
void Switch_Run(void)
{
	Switch_t state;

	// Immediately accept the new state if it agrees with the last
	Switch_t expected = _Switch_State;
	uint8_t debounce = 1;
	do
	{
		// Gather the digital inputs into a single bitfield
		state = 0;
		if(!SWITCH_1_PIN)
			state |= SWITCH_1;
		if(!SWITCH_2_PIN)
			state |= SWITCH_2;
		if(!SWITCH_3_PIN)
			state |= SWITCH_3;
		if(!SWITCH_4_PIN)
			state |= SWITCH_4;
		if(!SWITCH_ON_PIN)
			state |= SWITCH_ON;
		if(!SWITCH_OFF_PIN)
			state |= SWITCH_OFF;

		// Debounce the inputs whenever they change
		if(state != expected)
		{
			expected = state;
			debounce = SWITCH_DEBOUNCE;
		}
	}
	while(--debounce);

	// Latch in the new state and report flanks
	_Switch_Press = state & ~_Switch_State;
	_Switch_Release = ~state & _Switch_State;
	_Switch_State = state;
}