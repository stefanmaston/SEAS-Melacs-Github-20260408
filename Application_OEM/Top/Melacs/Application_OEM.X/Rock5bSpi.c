

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "main.h"
#include <sys.h>
#include <plib.h>
#include <p32xxxx.h>
#include "configurations.h"
#include "main.h"
#include "mutex.h"
#include <mrendez.h>
#include <sys/interrupt.h>
#include "uart.h"
#define CSPI1_TRIS         TRISDbits.TRISD6
#define CSPI1_BIT       PORTDbits.RD6



// Configuration settings

#define SYS_FREQ    80000000
#define SPI_BAUD    1000000 // Desired SPI clock frequency

void SPI_Init(void);
void SPI_Write(char data);
void SPI_SendString(const char *str);

int main() {
    SPI_Init();

    while (1) {
        SPI_SendString("Hello");
    }

    return 0;
}

void SPI_Init(void) {
    // Configure SPI pins
    TRISFbits.TRISF8 = 0;   // Set RF8 (SDO1) as output
    TRISFbits.TRISF6 = 0;   // Set RF6 (SCK1) as output
    TRISFbits.TRISF2 = 1;   // Set RF2 (SDI1) as input

    // Configure SPI peripheral
    SPI1CONbits.ON = 0;     // Disable SPI before configuring it

    SPI1BUF = 0;            // Clear receive buffer
    SPI1BRG = (SYS_FREQ / (2 * SPI_BAUD)) - 1;  // Set the baud rate

    SPI1STATbits.SPIROV = 0;    // Clear overflow flag
    SPI1CONbits.CKE = 0;        // Clock edge select: Idle state is low, active state is high
    SPI1CONbits.CKP = 0;        // Clock polarity select: Clock idle state is low, active state is high
    SPI1CONbits.MSTEN = 1;      // Enable master mode
    SPI1CONbits.MODE16 = 0;     // 8-bit mode
    SPI1CONbits.MODE32 = 0;     // 8-bit mode
    SPI1CONbits.ENHBUF = 0;     // Disable Enhanced Buffer mode

    SPI1CONbits.ON = 1;         // Enable SPI
}

void SPI_Write(char data) {
    SPI1BUF = data;             // Write data to SPI buffer
    while (!SPI1STATbits.SPITBF); // Wait until data is transmitted
    while (!SPI1STATbits.SPIRBF); // Wait until data is received
}

void SPI_SendString(const char *str) {
    while (*str) {
        SPI_Write(*str);
        str++;
    }
}
