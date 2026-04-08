/* 
 * File:   main.c
 * Author: Alf Gisslen
 *      Blinks LEDs on port G1
 *      Enables RS485-MUX and disconnects MELACS
 *      Extension board sends string "From Extension board!\n\r" continously
 *
 * Created 2021-12-23
 * 
 */
#include "melacs_spi.h"
#include "configurations.h"
#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

#include "stdint.h"
#include <p32xxxx.h>

#define OpenUART3(config1, config2, ubrg) (\
        U3BRG = (ubrg), \
        U3MODE = (config1), \
        U3STA = (config2) \
)

#define testLED     LATGbits.LATG1
#define testLED_DIR TRISGbits.TRISG1

void initPorts(int Melax_to_RS485);
void UARTsendString( UART_MODULE selectedUart,char *str);
void setUartBaud(int uart, uint32_t baudrate);
int UARTsendByte(UART_MODULE selectedUart, uint8_t c);

void initPorts(int Melax_to_RS485) {
    /* JP1 Communication with MELACS7 */
    TRIS_SLAVE_CS_BIT = 1;  // (D14) For SPI from MELACS7

    SPICLK_DIR = 1; // in (RD15)
    SPIMISO_DIR = 1; //	in (RF2) when idle, out when talking to MELACS7
    SPIMOSI_DIR = 1; //	in (RF8)


    TRIS_U18_OE	= 0; // Out (RA7)
    TRIS_U18_AB = 0; // Out (RG14)
    U18_OE = 0; // low, enables MUX
    
    if (Melax_to_RS485 > 0) {
        U18_AB = 0; // low, sets MELACS7 controlling RS485
        /* JP14  RS485-MUX */
        SPIMOSI1_DIR = 0; //	out, (RG7) handles RS485-mux, low when MELACS7 <-> RS485 
        SPIMISO1_DIR = 1; //	in,  (RG8) handles RS485, disconnected when MELACS7 <-> RS485
     } else {
        U18_AB = 1; // high, sets Ext.board controlling RS485
                    // TX on SPIMOSI1 (handled by MPU-UART)
                    // RX on SPIMISO1 (handled by MPU-UART)
    }

// JP14 Ext. board controlling RS485
    RS485_TX_EN_DIR = 0;    // output (RG12)
    RS485_RX_EN_DIR = 0;    // output (RG13)
    RS485_TX_EN = 1;        // output, (RG12) HIGH for TX_out
    RS485_RX_EN = 0;        // output, (RG13) LOW for RX_in

    /* A/D-MUX: */
    TRIS_AD_MUX_INH	= 0; // Out (RE1)
    TRIS_AD_MUX_A	= 0; // Out (RE2)
    TRIS_AD_MUX_B	= 0; // Out (RE3)
    TRIS_AD_MUX_C	= 0; // Out (RE4)

    AD_MUX_INH = 1; // high, (RE1) disables MUX
    AD_MUX_A = 1;   // high (RE2)
    AD_MUX_B = 1;   // high (RE3)
    AD_MUX_C = 1;   // high (RE4)

}


int main(int argc, char** argv)
{
    long waitcount = 0;
    long waitmax = 11450; // ~ 1ms waitloop
    UART_MODULE UartUsed;
    
    int i = 0;
    int j = 0;
    char name[] = {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78};
    //int recd_Data = 0;
    //uint8_t spibuff[30];
    //int spiPtr = 0;
    //uint8_t spiByte;
    
#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
    DDPCONbits.JTAGEN = 0;
#endif
    SYSTEMConfig(SYSCLK, SYS_CFG_WAIT_STATES|SYS_CFG_PCACHE); 

    /* Initialize I/O and Peripherals for application */
    for (waitcount = 0; waitcount < waitmax; waitcount++) {
        __asm("nop");
    }

    /* Initialize I/O and Peripherals for application */
    testLED_DIR = 0;
    testLED = 1;

    initPorts(1);
    int ledcount = 0;
    OpenUART3(UART_EN, UART_TX_ENABLE, BAUD_VALUE);

    UartUsed = UART3;
    Slave_SPI_Init();
    
    while(1) {
        ledcount++;
        if (ledcount > 100) {
            testLED = (testLED+1)%2;
            ledcount = 0;
        }
        //UARTsendByte(UartUsed, Slave_SPI_Receive());
//        Slave_SPI_clear_stat();
        //spibuff[spiPtr] = Slave_SPI_Receive();
        //Slave_SPI_clear_stat();
        //if (spibuff[spiPtr] == 0) {
        //    for (i = 0; i <= spiPtr;) {
        //        i += UARTsendByte(UartUsed, spibuff[i]);
        //    }
        //    i = 0;
        //}
        //spiPtr++;
//            UARTsendString(UartUsed, "From Extension board_v4!\n\r");

//        for (waitcount = 0; waitcount < waitmax; waitcount++) {
//            __asm("nop");
//        }
    }

    return (EXIT_SUCCESS);
}

int UARTsendByte(UART_MODULE selectedUart, uint8_t c) {
    UART_DATA inoutdata;
    inoutdata.data8bit = c;
    if (UARTTransmitterIsReady(selectedUart)) {
        UARTSendData(selectedUart, inoutdata);
        return 1;
    }
    return 0;
}

void UARTsendString( UART_MODULE selectedUart,char *str) {
    int i = 0;
    while (str[i] != 0) {
        i += UARTsendByte(selectedUart, str[i]);
    }
}
