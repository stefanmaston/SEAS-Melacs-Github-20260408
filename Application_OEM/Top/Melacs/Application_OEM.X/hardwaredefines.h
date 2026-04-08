/*
 * File:   OnBoardRTCC.h
 * Author: Bala
 *
 * Created on November 13, 2014, 2:52 PM
 */

#ifndef HARDWAREDEFINES_H
#define	HARDWAREDEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CS_RTC          LATGbits.LATG1
#define CS_RTC_DIR		TRISGbits.TRISG1
#define SPICLK  		LATDbits.LATD15
#define SPICLK_DIR  	TRISDbits.TRISD15
#define SPIMISO 		PORTFbits.RF2
#define SPIMISO_DIR		TRISFbits.TRISF2
//#define SPIMOSI 		PORTFbits.RF8
#define SPIMOSI 		LATFbits.LATF8
#define SPIMOSI_DIR 	TRISFbits.TRISF8


#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREDEFINES_H */

