#include <stdlib.h>
#include <string.h>
#include "Analog.h"
#include "Bus.h"
#include "Common.h"
#include "Display.h"
#include "EPFlash.h"
#include "LED.h"
#include "Numeric.h"
#include "Protocol.h"
#include "Logo.h"
#include "Timer.h"
#include "UART.h"
#include "Window.h"

/******************************************************************************
 * The main loop!
 ******************************************************************************/
void main(void)
{
	Pins_Init();
	UART_Init();
	LED_Init();

	// Show some sign of life on the serial port as early as possible
	UART_PutString (
		" \33[2J\33[H"
		"Welcome to Firmware\n"
	);

	Timer_Init();
	Analog_Init();
	Win_Init();
	Bus_Init();
	Proto_Init();
	EPFlash_Init();

	// Initialize the display. This may block (and blink)
	Disp_Init();

	// Commit the entire program to the external FLASH so that images may be
	// accessed through it as a test
	EPFlash_Erase(0);
	EPFlash_WriteROM(0, NULL, 0x20000);

	// Run the demo
//	for(;;)
    {
//        Proto_Run();
		Show_Logo();
    }
}
