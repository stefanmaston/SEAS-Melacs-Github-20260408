#include <stddef.h>
#include "Common.h"
#include "Analog.h"


/******************************************************************************
 * A/D channel definitions and data storage
 ******************************************************************************/
struct _Analog _Analog =
{
#	define _CH(ch) (_B2(ch) | _B0(1))
#	define _LIM(touch, lim) ((lim) & 0xFFFE | (touch))
#	define _CUR(range, trim) (_B2(range) | _B0(trim))

	offsetof(struct _Analog, Array),
	{
		// Average Limit          History Chain Status  Current
		{  0xFFFF, _LIM(0, 0x8000), 0x00, _CH( 2), 0, _CUR(0,   0) }, // AN2: Light sneosr
	}
};


/******************************************************************************
 * Configure hardware and kick off the sampling interrupt
 ******************************************************************************/
void Analog_Init(void)
{
	ADCON2 =
		_B7(1) | // Right-justified
		_B3(7) | // 20x Tad acquisition time
		_B0(6);  // Fosc/64 clock source
	ADCON1 =
		_B7(0) | // Special trigger from CCP2
		_B5(0) | // Use AVSS (pin #20) as voltage reference
		_B4(0) | // Use AVDD (pin #19) as voltage reference
		_B0(15); // Use AN0-11 as digital inputs (!)
	ADCON0 =
		_B7(0) | // No calibration
		_B2(0) | // Select channel #0
		_B1(0) | // Stop conversion
		_B0(1);  // Enable A/D converter

	CTMUCONL =
		_B7(0) | // Edge #2 negative response
		_B5(2) | // Edge #2 from CTEDG2
		_B4(1) | // Edge #1 positive response
		_B2(3);  // Edge #1 from CTEDG1
	CTMUCONH =
		_B7(1) | // Enable CTMU
		_B5(1) | // Stop in idle mode
		_B4(0) | // Disable edge delay
		_B3(0) | // Edges are blocked
		_B2(0) | // No edge sequence needed
		_B1(0);  // Trigger output disabled

	// Sample at 8000 Hz (~5% CPU usage.)
	// The 250x period is also used by the display backlight PWM
	PR2 = 250 - 1;

	T2CON =
		_B3(3) |  // 4x postscale
		_B2(1)  | // Enable timer
		_B0(1);   // 4x prescale

	PIE1bits.TMR2IE = 1;
}

// A kludge for setting the baseline touch level.
// Call this soon after startup and pray that no one is touching the display
void Analog_Calibrate(void)
{
	uint8_t len = 4;
	const struct _Analog_Channel *ptr = _Analog.Array;

	do
	{
		// Fifteen-sixteenths of max
		unsigned limit = (uint24_t) ptr->Average * 0xF0 >> 8;
		// Combine with old "touch" indication bit
		ptr->Limit = ptr->Limit & 0x0001 | limit & 0xFFFE;
	}
	while(++ptr, --len);
}