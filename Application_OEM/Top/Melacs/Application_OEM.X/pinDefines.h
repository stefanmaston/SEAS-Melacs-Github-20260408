/* 
 * File:   pinDefines.h
 * Author: Bala
 *
 * Created on March 30, 2015, 5:08 PM
 */

#ifndef PINDEFINES_H
#define	PINDEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 *   Display Pins - Begin
 */

#define TRIS_D_ACK1 TRISEbits.TRISE0
#define LAT_D_ACK1 LATEbits.LATE0

//#define TRIS_D_ACK2 TRISGbits.TRISG8
//#define D_ACK2 PORTGbits.RG8
#define TRIS_D_ACK2 TRISCbits.TRISC1
#define D_ACK2 PORTCbits.RC1

#define TRIS_D_ATN TRISCbits.TRISC2
#define LAT_D_ATN LATCbits.LATC2

#define TRIS_DATA0 TRISGbits.TRISG6
#define LAT_DATA0 LATGbits.LATG6
#define FIRST_KEY PORTGbits.RG6

#define TRIS_DATA1 TRISEbits.TRISE4
#define LAT_DATA1 LATEbits.LATE4
#define SECOND_KEY PORTEbits.RE4

#define TRIS_DATA2 TRISGbits.TRISG15
#define LAT_DATA2 LATGbits.LATG15
#define THIRD_KEY PORTGbits.RG15

#define TRIS_DATA3 TRISEbits.TRISE5
#define LAT_DATA3 LATEbits.LATE5
#define FOURTH_KEY PORTEbits.RE5

#define TRIS_D_CLK TRISCbits.TRISC1
#define LAT_D_CLK LATCbits.LATC1

/*
 *   Display Pins - End
 */

/*
 *   DIO pins - Begin
 */

#define TRIS_DIO0 TRISDbits.TRISD11
#define LAT_DIO0 LATDbits.LATD11
#define DIO0_IN _RD11

#define TRIS_DIO1 TRISDbits.TRISD9
#define LAT_DIO1 LATDbits.LATD9
#define DIO1_IN _RD9

#define TRIS_DIO2 TRISDbits.TRISD8
#define LAT_DIO2 LATDbits.LATD8
#define DIO2_IN _RD8

#define TRIS_DIO3 TRISDbits.TRISD10
#define LAT_DIO3 LATDbits.LATD10
#define DIO3_IN _RD10

#define TRIS_DIO4 TRISBbits.TRISB8
#define LAT_DIO4 LATBbits.LATB8
#define DIO4_IN _RB8

#define TRIS_DIO5 TRISBbits.TRISB0
#define LAT_DIO5 LATBbits.LATB0
#define DIO5_IN _RB0

#define TRIS_DIO6 TRISBbits.TRISB1
#define LAT_DIO6 LATBbits.LATB1
#define DIO6_IN _RB1

#define TRIS_DIO7 TRISBbits.TRISB2
#define LAT_DIO7 LATBbits.LATB2
#define DIO7_IN _RB2

/*
 *   DIO Pins - End
 */

/*
 *   SIP pins - Begin
 */

//#define TRIS_SIP0 TRISAbits.TRISA1
//#define LAT_SIP0 LATAbits.LATA1
//
//#define TRIS_SIP1 TRISFbits.TRISF13
//#define LAT_SIP1 LATFbits.LATF13

//#define TRIS_SIP2 TRISFbits.TRISF12
//#define LAT_SIP2 LATFbits.LATF12

//#define TRIS_SIP3 TRISBbits.TRISB12
//#define LAT_SIP3 LATBbits.LATB12
//
//#define TRIS_SIP4 TRISDbits.TRISD12
//#define LAT_SIP4 LATDbits.LATD12

#define TRIS_SIP5 TRISCbits.TRISC13
#define LAT_SIP5 LATCbits.LATC13

#define TRIS_SIP6 TRISCbits.TRISC14
#define LAT_SIP6 LATCbits.LATC14

#define TRIS_SIP7 TRISDbits.TRISD13
#define LAT_SIP7 LATDbits.LATD13

/*
 *   SIP pins - End
 */

/*
 *   Motor Pins - Begin
 */


#define TRIS_M1DIS TRISAbits.TRISA14
#define LAT_M1DIS LATAbits.LATA14

#define TRIS_M1AHI TRISDbits.TRISD0
#define LAT_M1AHI LATDbits.LATD0

#define TRIS_M1ALI TRISGbits.TRISG9
#define LAT_M1ALI LATGbits.LATG9

#define TRIS_M1BHI TRISDbits.TRISD1
#define LAT_M1BHI LATDbits.LATD1

#define TRIS_M1BLI TRISGbits.TRISG13
#define LAT_M1BLI LATGbits.LATG13

#define TRIS_M2DIS TRISAbits.TRISA15
#define LAT_M2DIS LATAbits.LATA15

#define TRIS_M2AHI TRISDbits.TRISD2
#define LAT_M2AHI LATDbits.LATD2

#define TRIS_M2ALI TRISEbits.TRISE7
#define LAT_M2ALI LATEbits.LATE7

#define TRIS_M2BHI TRISDbits.TRISD3
#define LAT_M2BHI LATDbits.LATD3

#define TRIS_M2BLI TRISEbits.TRISE3
#define LAT_M2BLI LATEbits.LATE3
/*
 *   Motor Pins - End
 */

/*
 *   Buzzer - Begin
 */

#define TRIS_BUZZER TRISFbits.TRISF4
#define LAT_BUZZER LATFbits.LATF4


/*
 *   Buzzer - End
 */

#ifdef	__cplusplus
}
#endif

#endif	/* PINDEFINES_H */

