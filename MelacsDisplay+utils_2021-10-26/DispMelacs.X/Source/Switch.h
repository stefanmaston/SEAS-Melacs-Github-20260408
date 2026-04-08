/******************************************************************************
 * Sample and debounce the digital input switches
 ******************************************************************************/
#ifndef _SWITCH_H
#define _SWITCH_H

// Gather the available switches into a bitfield
typedef enum
{
	SWITCH_1   = 0x01U,
	SWITCH_2   = 0x02U,
	SWITCH_3   = 0x04U,
	SWITCH_4   = 0x08U,
	SWITCH_ON  = 0x10U,
	SWITCH_OFF = 0x20U
}
Switch_t;

// Functions
void Switch_Run(void);
/* Switch_t Switch_State(Switch_t mask); */
/* Switch_t Switch_Press(Switch_t mask); */
/* Switch_t Switch_Release(Switch_t mask); */

// Accessors
#define Switch_State(mask) \
(_Switch_State & (mask))
#define Switch_Press(mask) \
(_Switch_Press & (mask))
#define Switch_Release(mask) \
(_Switch_Release & (mask))

extern Switch_t _Switch_State;
extern Switch_t _Switch_Press;
extern Switch_t _Switch_Release;

#endif