#ifndef PIN_MAP_H
#define PIN_MAP_H

/*
 * PIC32MX795F512L på MELACS7 R3A.
 * Samma ben som OEM-kortet. Namnen är pin-nummer för PLC, inte pump, fläkt eller brännare.
 * U1-pin och J1-nät kommer från MELACS7_R3A och MCU-kortet R3A.
 *
 * DIO0–DIO3 är ingångar. DIO4–DIO7 är utgångar.
 */

#define PIN_DIO0_TRIS TRISDbits.TRISD11
#define PIN_DIO0_LAT  LATDbits.LATD11
#define PIN_DIO0_PORT _RD11
#define PIN_DIO0_U1   71

#define PIN_DIO1_TRIS TRISDbits.TRISD9
#define PIN_DIO1_LAT  LATDbits.LATD9
#define PIN_DIO1_PORT _RD9
#define PIN_DIO1_U1   69

#define PIN_DIO2_TRIS TRISDbits.TRISD8
#define PIN_DIO2_LAT  LATDbits.LATD8
#define PIN_DIO2_PORT _RD8
#define PIN_DIO2_U1   68

#define PIN_DIO3_TRIS TRISDbits.TRISD10
#define PIN_DIO3_LAT  LATDbits.LATD10
#define PIN_DIO3_PORT _RD10
#define PIN_DIO3_U1   70

#define PIN_DIO4_TRIS TRISBbits.TRISB8
#define PIN_DIO4_LAT  LATBbits.LATB8
#define PIN_DIO4_PORT _RB8

#define PIN_DIO5_TRIS TRISBbits.TRISB0
#define PIN_DIO5_LAT  LATBbits.LATB0
#define PIN_DIO5_PORT _RB0
#define PIN_DIO5_U1   25

#define PIN_DIO6_TRIS TRISBbits.TRISB1
#define PIN_DIO6_LAT  LATBbits.LATB1
#define PIN_DIO6_PORT _RB1
#define PIN_DIO6_U1   24

#define PIN_DIO7_TRIS TRISBbits.TRISB2
#define PIN_DIO7_LAT  LATBbits.LATB2
#define PIN_DIO7_PORT _RB2
#define PIN_DIO7_U1   23

/* SIP1 och SIP2 sitter på RA3 och RA2. SIP0 och SIP3 har inget bekräftat ben. */
#define PIN_SIP1_TRIS TRISAbits.TRISA3
#define PIN_SIP1_LAT  LATAbits.LATA3
#define PIN_SIP2_TRIS TRISAbits.TRISA2
#define PIN_SIP2_LAT  LATAbits.LATA2
/* SIP4 styr JP7 och LED10. Låg nivå är av. */
#define PIN_SIP4_TRIS TRISDbits.TRISD12
#define PIN_SIP4_LAT  LATDbits.LATD12
#define PIN_SIP5_TRIS TRISCbits.TRISC13
#define PIN_SIP5_LAT  LATCbits.LATC13
#define PIN_SIP6_TRIS TRISCbits.TRISC14
#define PIN_SIP6_LAT  LATCbits.LATC14
#define PIN_SIP7_TRIS TRISDbits.TRISD13
#define PIN_SIP7_LAT  LATDbits.LATD13

/* LED7, gul minnesdiod. 3V3 via motstånd, så låg nivå tänder. */
#define PIN_LED7_TRIS TRISFbits.TRISF1
#define PIN_LED7_LAT  LATFbits.LATF1

/* Gemensam SPI3-buss: SCK RD15, MOSI RF8, MISO RF2. */
#define PIN_SPI_SCK_TRIS  TRISDbits.TRISD15
#define PIN_SPI_SCK_LAT   LATDbits.LATD15
#define PIN_SPI_MOSI_TRIS TRISFbits.TRISF8
#define PIN_SPI_MOSI_LAT  LATFbits.LATF8
#define PIN_SPI_MISO_TRIS TRISFbits.TRISF2
#define PIN_SPI_MISO_PORT PORTFbits.RF2
#define PIN_CS_AD_TRIS    TRISGbits.TRISG0
#define PIN_CS_AD_LAT     LATGbits.LATG0
#define PIN_CS_RTC_TRIS   TRISGbits.TRISG1
#define PIN_CS_RTC_LAT    LATGbits.LATG1
#define PIN_CS_SD_TRIS    TRISFbits.TRISF5
#define PIN_CS_SD_LAT     LATFbits.LATF5
#define PIN_CS_ETH_TRIS   TRISAbits.TRISA6
#define PIN_CS_ETH_LAT    LATAbits.LATA6

#define PIN_H1_DIS_TRIS TRISAbits.TRISA14
#define PIN_H1_DIS_LAT  LATAbits.LATA14
#define PIN_H1_AHI_TRIS TRISDbits.TRISD0
#define PIN_H1_AHI_LAT  LATDbits.LATD0
#define PIN_H1_ALI_TRIS TRISGbits.TRISG9
#define PIN_H1_ALI_LAT  LATGbits.LATG9
#define PIN_H1_BHI_TRIS TRISDbits.TRISD1
#define PIN_H1_BHI_LAT  LATDbits.LATD1
#define PIN_H1_BLI_TRIS TRISGbits.TRISG13
#define PIN_H1_BLI_LAT  LATGbits.LATG13

#define PIN_H2_DIS_TRIS TRISAbits.TRISA15
#define PIN_H2_DIS_LAT  LATAbits.LATA15
#define PIN_H2_AHI_TRIS TRISDbits.TRISD2
#define PIN_H2_AHI_LAT  LATDbits.LATD2
#define PIN_H2_ALI_TRIS TRISEbits.TRISE7
#define PIN_H2_ALI_LAT  LATEbits.LATE7
#define PIN_H2_BHI_TRIS TRISDbits.TRISD3
#define PIN_H2_BHI_LAT  LATDbits.LATD3
#define PIN_H2_BLI_TRIS TRISEbits.TRISE3
#define PIN_H2_BLI_LAT  LATEbits.LATE3

/*
 * Inbyggd ADC, samma skanningsordning som på kortet:
 * AN0 RB0, AN1 RB1, AN2 RB2, AN3 RB3, AN4 RB4, AN5 RB5,
 * AN10 RB10, AN13 RB13, AN14 RB14, AN15 RB15.
 * AD0–AD7 är de åtta yttre analogkanalerna.
 * AI10–AI15 är ingångsregister 10–15. AO0–AO2 är holding 100–102.
 */

#endif
