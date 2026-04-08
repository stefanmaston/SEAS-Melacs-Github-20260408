/* ************************************************************************** */
/** Description
 * 
 * Author:  Alf Gisslen
 *          ARG Utveckling AB
 *
 * File:    main.h
 *
 * Port definitions
 *
 */
/* ************************************************************************** */

#ifndef _MAIN_H    /* Guard against multiple inclusion */
#define _MAIN_H

#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#define SYSCLK                  (72000000)
#define WAIT_TIME 10000


/* JP1 */
#define TRIS_SLAVE_CS_BIT   TRISDbits.TRISD14   // in
#define SLAVE_CS_BIT        PORTDbits.RD14      // enabled when low

// SPI for MELACS JP1
#define SPICLK_DIR  	    TRISDbits.TRISD15   // in
#define SPIMISO_DIR	        TRISFbits.TRISF2    // in when idle, out when talking to MELACS7
#define SPIMOSI_DIR 	    TRISFbits.TRISF8    // in

// SPI for RS485 JP14
#define SPIMISO1_DIR	    TRISGbits.TRISG7    // input, RX when ExtBoard <-> RS485
#define SPIMOSI1_DIR 	    TRISGbits.TRISG8    // U18 IO 4B, 
                                    // input (unused) when MELACS7 <-> RS485,
                                    // output (TX) when ExtBoard <-> RS485
    
// JP14 Ext. board controlling RS485
#define RS485_TX_EN_DIR     TRISGbits.TRISG12   // output
#define RS485_RX_EN_DIR     TRISGbits.TRISG13   // output
#define RS485_TX_EN         PORTGbits.RG12       // output, HIGH for TX_out
#define RS485_RX_EN         PORTGbits.RG13       // output, LOW for RX_in
    
/* RS485-comm */
#define SPIMISO1            PORTGbits.RG7
#define SPIMOSI1            PORTGbits.RG8
    
/* RS485-MUX */
#define TRIS_U18_OE         TRISAbits.TRISA7    // Out:low, enables MUX and RS485
#define TRIS_U18_AB         TRISGbits.TRISG14   // Out:low, sets MELACS7 controlling RS485
                                                // Out:high for RS485 -> Ext-board comm
#define U18_OE              PORTAbits.RA7       // low, enables MUX
#define U18_AB              PORTGbits.RG14      // low, sets MELACS7 controlling RS485

/* A/D-MUX: */
#define TRIS_AD_MUX_INH     TRISEbits.TRISE1	// Out
#define TRIS_AD_MUX_A       TRISEbits.TRISE2	// Out
#define TRIS_AD_MUX_B       TRISEbits.TRISE3	// Out
#define TRIS_AD_MUX_C       TRISEbits.TRISE4	// Out
#define AD_MUX_INH          PORTEbits.RE1       // high, disables MUX
#define AD_MUX_A            PORTEbits.RE2       // high
#define AD_MUX_B            PORTEbits.RE3       // high
#define AD_MUX_C            PORTEbits.RE4       // high

//#define NO_PRI_OSC
//#define EIGTH_MHZ_OSC
#define SIXTEEN_MHZ_OSC
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _MAIN_H */


