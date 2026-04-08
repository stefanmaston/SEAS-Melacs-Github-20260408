/******************************************************************************
 * Control the indicator LEDs through the TLC541 driver
 ******************************************************************************/
#ifndef _LED_H
#define _LED_H

enum { LED_COUNT = 16 };

// Functions
void LED_Init(void);
void LED_Run(void);

// Data
extern uint16_t LED_Duty[LED_COUNT];
extern uint8_t LED_Current[LED_COUNT];

#endif