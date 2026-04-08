#include "Common.h"
#include "LED.h"
#include "Pins.h"

// Left-aligned 12-bit duty-cycles and 6-bit current current calibration data
uint16_t LED_Duty[];
uint8_t LED_Current[];


/******************************************************************************
 * Clock through a variable-length word on the serial interface
 ******************************************************************************/
static void LED_Transmit(uint16_t bitbuf, uint8_t bitnum)
{
	do
	{
		if(bitbuf & 0x8000U)
			LED_SIN = 1;
		else
			LED_SIN = 0;
		LED_SCLK = 1;
		bitbuf <<= 1;
		LED_SCLK = 0;
	}
	while(--bitnum);
}


/******************************************************************************
 * Initialize the controller
 ******************************************************************************/
void LED_Init(void)
{
	// Start GSCLK via a PWM channel
	/*  
	 32 MHz
	-------- = 1000 MHz
	 4 x 8
	 */
	PR2 = 8 - 1;
	T2CON =
		_B3(0) /* 1x postscale */ |
		_B2(1) /* Timer on */ |
		_B0(0) /* 1x prescale */;
	CCPR1L = 4 /* 50% duty-cycle */;
	CCP1CON =
		_B0(12) /* PWM mode */;

}


/******************************************************************************
 * Transmit updated LED data from the RAM buffers to the driver
 ******************************************************************************/
void LED_Run(void)
{
	// Refresh the current calibration
	{
		// Transmit the 6-bit words
		const uint8_t *ptr = LED_Current;
		LED_MODE = 1;
		do
			LED_Transmit((uint16_t) *ptr++ << 8, 6);
		while(ptr != &LED_Current[LED_COUNT]);

		// Latch in the write
		LED_XLAT = 1;
		LED_XLAT = 1;
		LED_XLAT = 1;
		LED_XLAT = 0;
	}

	// Refresh the PWM duty-cycles
	{
		// Transmit the 12-bit words
		const uint16_t *ptr = LED_Duty;
		LED_MODE = 0;
		do
			LED_Transmit(*ptr++, 12);
		while(ptr != &LED_Duty[LED_COUNT]);

		// Latch in the write
		LED_XLAT = 1;
		LED_XLAT = 1;
		LED_XLAT = 1;
		LED_XLAT = 0;

		// An extra clock pulse is required to latch in pulse-widths
		// after refreshing the current
		LED_Transmit(0x0000, 1);
	}

	// Unblank the display on the first iteration
	LED_BLANK ^= 1;
}