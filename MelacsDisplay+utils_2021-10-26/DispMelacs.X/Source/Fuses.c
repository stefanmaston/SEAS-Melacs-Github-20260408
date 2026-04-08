/******************************************************************************
 * MCU Fuses. These need to be programmed manually rather than through
 * #pragma config as MCC18/MPLAB is missing the debugger enable bit
 ******************************************************************************/
enum
{
	// @ 0x300000
	CFG1L_DEBUG_MASK   = 0x80, // Background Debugger
	CFG1L_DEBUG_ON     = 0x80, // Background Debugger Disabled
	CFG1L_DEBUG_OFF    = 0x00, // Background Debugger Enabled
	CFG1L_XINST        = 0x40, // Extended Instruction Set Enable
	CFG1L_STVREN       = 0x20, // Stack Overflow/Underflow Reset Enable
	CFG1L_WDTEN        = 0x01, // Watchdog Timer Enable

	// @ 0x300001
	CFG1H_CP0_MASK     = 0x04, // Code Protection
	CFG1H_CP0_OFF      = 0x04, // Code Protection Disabled
	CFG1H_CP0_ON       = 0x00, // Code Protection Enabled

	// @ 0x300002
	CFG2L_IESO         = 0x80, // Two-Speed Startup Enable
	CFG2L_FCMEN        = 0x40, // Fail-Safe Clock Monitor Enable
	CFG2L_LPT1OSC      = 0x10, // T1OSC/SOSC Power Selection
	CFG2L_T1DIG        = 0x08, // T1CKI Digital Input Clock Enable
	CFG2L_FOSC_MASK    = 0x07, // Oscillator Selection
	CFG2L_FOSC_ECPLL   = 0x07, // ECPLL OSC1/OSC2 as primary. ECPLL oscillator with PLL enabled. CLKO on RA6
	CFG2L_FOSC_EC      = 0x06, // OSC1/OSC2 as primary. External clock with FOSC/4 output
	CFG2L_FOSC_HSPLL   = 0x05, // HSPLL OSC1/OSC2 as primary. High-speed crystal/resonator with software PLL control
	CFG2L_FOSC_HS      = 0x04, // OSC1/OSC2 as primary. High-speed crystal/resonator
	CFG2L_FOSC_INTPLL1 = 0x03, // Internal oscillator block with software PLL control. FOSC/4 output
	CFG2L_FOSC_INTIO1  = 0x02, // Internal oscillator block with FOSC/4 output on RA6 and I/O on RA7
	CFG2L_FOSC_INTPLL2 = 0x01, // Internal oscillator block with software PLL control and I/O on RA6 and RA7
	CFG2L_FOSC_INTIO2  = 0x00, // Internal oscillator block with I/O on RA6 and RA7

	// @ 0x300003
	CFG2H_WDTPS_MASK   = 0x0F, // Watchdog Timer Postscale Select bits
	CFG2H_WDTPS_32768  = 0x0F, // 1:32,768
	CFG2H_WDTPS_16384  = 0x0E, // 1:16,384
	CFG2H_WDTPS_8192   = 0x0D, // 1:8,192
	CFG2H_WDTPS_4096   = 0x0C, // 1:4,096
	CFG2H_WDTPS_2048   = 0x0B, // 1:2,048
	CFG2H_WDTPS_1024   = 0x0A, // 1:1,024
	CFG2H_WDTPS_512    = 0x09, // 1:512
	CFG2H_WDTPS_256    = 0x08, // 1:256
	CFG2H_WDTPS_128    = 0x07, // 1:128
	CFG2H_WDTPS_64     = 0x06, // 1:64
	CFG2H_WDTPS_32     = 0x05, // 1:32
	CFG2H_WDTPS_16     = 0x04, // 1:16
	CFG2H_WDTPS_8      = 0x03, // 1:8
	CFG2H_WDTPS_4      = 0x02, // 1:4
	CFG2H_WDTPS_2      = 0x01, // 1:2
	CFG2H_WDTPS_1      = 0x00, // 1:1

	// @ 0x300004
	CFG3L_RTCOSC       = 0x02, // RTCC Reference Clock Select bit
	CFG3L_RTCOSC_T1OSC = 0x02, // RTCC uses T1OSC/T1CKI as the reference clock
	CFG3L_RTCOSC_INTRC = 0x00, // RTCC uses INTRC as the reference clock

	// @ 0x300005
	CFG3H_CCP2MX       = 0x01, // CCP2 MUX bit
	CFG3H_CCP2MX_RC1   = 0x01, // CCP2 is multiplexed with RC1
	CFG3H_CCP2MX_RE7   = 0x00  // CCP2 is multiplexed with RE7
};

#pragma romdata CONFIG
rom const unsigned char Config[] =
{
	// Enable debugging and stack overflow resets but disable the watchdog
	CFG1L_DEBUG_ON |
#	ifdef __EXTENDED18__
	CFG1L_XINST | CFG1L_STVREN,
#	else
	CFG1L_STVREN,
#	endif
	// Disable code protection
	CFG1H_CP0_OFF,
	// Internal oscillator w. PLL and w/o I/O outputs
	CFG2L_FOSC_INTPLL2,
	// Watchdog postscaler
	CFG2H_WDTPS_32768,
	// RTC oscillator
	CFG3L_RTCOSC_INTRC,
	// CCP2 is multiplexed with RE7
	CFG3H_CCP2MX_RE7
};
#pragma romdata
