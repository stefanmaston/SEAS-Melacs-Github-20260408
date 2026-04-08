/*
 *  File name: config_system.h
 *
 *  Description: System settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_SYSTEM_H
#define CONFIG_SYSTEM_H

#ifdef __dsPIC33EP128GS706__
#define DSPIC_7XX_FAMILY
#endif

//-----------------------------------------------------------------------------
// Global settings:
//-----------------------------------------------------------------------------
// Clock and PLL settings
// Fosc = Fin * M /(N1 * N2), Fcy = Fosc / 2

// Comment the line out to use the external oscillator
#define USE_FRC_CLOCK

#define FRCFREQ				7372800			// FRC frequency

#if 1	// ifdef EVAL_BOARD
    #define XTFREQ          7372800         // XT frequency
    #ifdef FULL_SPEED
        // Configure Oscillator to operate the device at 70 MIPS (-40*C to +85*C)
        // FOSC = Fin*(PLLDIV+2)/((PLLPRE+2)*2(PLLPOST+1))
        // FOSC = 7.3728MHz*(74+2)/((0+2)*2*(0+1)) = 140.083200Mhz
        #define SETTINGS_PLLFBD 74
        #define SETTINGS_CLKDIV_PLLPRE 0
        #define SETTINGS_CLKDIV_PLLPOST 0
        // FCY = FOSC/2
        #define FCY             70041600        // Instruction Cycle Frequency
    #else   // FULL_SPEED
        // Configure Oscillator to operate the device at 60 MIPS (-40*C to +125*C)
        // FOSC = Fin*(PLLDIV+2)/((PLLPRE+2)*2(PLLPOST+1))
        // FOSC = 7.3728MHz*(63+2)/((0+2)*2*(0+1)) = 119.808000Mhz
        #define SETTINGS_PLLFBD 63
        #define SETTINGS_CLKDIV_PLLPRE 0
        #define SETTINGS_CLKDIV_PLLPOST 0
        // FCY = FOSC/2
        #define FCY             59904000        // Instruction Cycle Frequency
    #endif  // FULL_SPEED
#else   // EVAL_BOARD
    #define XTFREQ          8000000         // XT frequency
    #ifdef FULL_SPEED
        // Configure Oscillator to operate the device at 70 MIPS (-40*C to +85*C)
        // FOSC = Fin*(PLLDIV+2)/((PLLPRE+2)*2(PLLPOST+1))
        // FOSC = 8.0000MHz*(68+2)/((0+2)*2*(0+1)) = 140.000000Mhz
        #define SETTINGS_PLLFBD 68
        #define SETTINGS_CLKDIV_PLLPRE 0
        #define SETTINGS_CLKDIV_PLLPOST 0
        // FCY = FOSC/2
        #define FCY             70000000        // Instruction Cycle Frequency
    #else   // FULL_SPEED
        // Configure Oscillator to operate the device at 60 MIPS (-40*C to +125*C)
        // FOSC = Fin*(PLLDIV+2)/((PLLPRE+2)*2(PLLPOST+1))
        // FOSC = 8.0000MHz*(58+2)/((0+2)*2*(0+1)) = 120.000000Mhz
        #define SETTINGS_PLLFBD 58
        #define SETTINGS_CLKDIV_PLLPRE 0
        #define SETTINGS_CLKDIV_PLLPOST 0
        // FCY = FOSC/2
        #define FCY             60000000        // Instruction Cycle Frequency
    #endif  // FULL_SPEED
#endif  // EVAL_BOARD

#define Fcy             FCY                     // Compatible with delay function from library

//#define BAUDRATE        38400
//#define BRGVAL			((FCY / (BAUDRATE * 16)) - 1)

#endif	// CONFIG_SYSTEM_H
