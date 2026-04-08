/*
 *  File name: BSP_System.c
 *
 *  Description: Board Support Package function implementations for System processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

volatile uint16_t	BSP_System_Reset_State = 0;

void BSP_System_PLL_Main_Setup(void)
{
	// Configure PLL
	PLLFBD = SETTINGS_PLLFBD;
	CLKDIVbits.PLLPRE = SETTINGS_CLKDIV_PLLPRE;
	CLKDIVbits.PLLPOST = SETTINGS_CLKDIV_PLLPOST;
}

void BSP_System_OSC_Switch(void)
{
	// Change oscillator to FRC + PLL
#ifndef USE_FRC_CLOCK
	// Setup the uC to use the external crystal with the PLL
	__builtin_write_OSCCONH(0x03);		// New Oscillator FRC w/ PLL
	__builtin_write_OSCCONL(0x01);		// Enable Clock Switch
	while(OSCCONbits.COSC != 0b011);	// Wait for new Oscillator to become FRC w/ PLL
	while(OSCCONbits.LOCK != 1);		// Wait for Pll to Lock
#else    // USE_FRC_CLOCK
	// Setup the uC to use the internal FRCPLL mode
	__builtin_write_OSCCONH(0x01);		// New Oscillator FRC w/ PLL
	__builtin_write_OSCCONL(0x01);		// Enable Clock Switch
	while(OSCCONbits.COSC != 0b001);	// Wait for new Oscillator to become FRC w/ PLL
	while(OSCCONbits.LOCK != 1);		// Wait for PLL to Lock
#endif   // USE_FRC_CLOCK
}

void BSP_System_PLL_Aux_Setup(void)
{
	// Setup the ADC and PWM clock for 120MHz	((FRC * 16) / APSTSCLR ) = (7.37MHz * 16) / 1 = 117.9MHz
	ACLKCONbits.FRCSEL = 1;				// FRC provides input for Auxiliary PLL (x16)
	ACLKCONbits.SELACLK = 1;			// Auxiliary Oscillator provides clock source for PWM & ADC
	ACLKCONbits.APSTSCLR = 7;			// Divide Auxiliary clock by 1
	ACLKCONbits.ENAPLL = 1;				// Enable Auxiliary PLL
	while(ACLKCONbits.APLLCK != 1);		// Wait for Auxiliary PLL to Lock
}

void BSP_System_WDT_Disable(void)
{
	// Disable Watch Dog Timer
	RCONbits.SWDTEN = 0;
}

void BSP_System_RST_Read(void)
{
	BSP_System_Reset_State = RCON;
	RCONbits.POR = 0;
	RCONbits.BOR = 0;
	RCONbits.IDLE = 0;
	RCONbits.SLEEP = 0;
	RCONbits.WDTO = 0;
	RCONbits.SWR = 0;
	RCONbits.EXTR = 0;
	RCONbits.CM = 0;
	RCONbits.IOPUWR = 0;
	RCONbits.TRAPR = 0;
}

void BSP_System_SW_Reset(void)
{
	asm("RESET");
}
