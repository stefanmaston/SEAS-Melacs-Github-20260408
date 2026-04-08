#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _MELACS_SPI_
#include "melacs_spi.h"

#include "stdint.h"
#include <sys.h>
#include <p32xxxx.h>
#include "configurations.h"



#define SPI_STATbits	(SPI3STATbits)
#define SPI_STAT_CLR	(SPI3STATCLR)
#define SPICON		(SPI3CON)
#define SPICONbits	(SPI3CONbits)
#define SPIBRG		(SPI3BRG)
#define SPIBUF   	(SPI3BUF)
#define SPI_RFIF_BIT 	(IFS0bits.SPI3RXIF)

#define TRIS_MASTER_CS_BIT TRISDbits.TRISD6
#define MASTER_CS_BIT      LATDbits.LATD6
//#define TRIS_MASTER_CS_BIT TRISFbits.TRISF0
//#define MASTER_CS_BIT      LATFbits.LATF0

//#define TRIS_SLAVE_CS_BIT  TRISDbits.TRISD6
//#define SLAVE_CS_BIT       PORTDbits.RD6

#define SPICLK_DIR  	   TRISDbits.TRISD15
#define SPIMISO_DIR	   TRISFbits.TRISF2
#define SPIMOSI_DIR 	   TRISFbits.TRISF8

#define WAIT_TIME 10000

//main transport function
uint8_t Master_SPI_Send_(uint8_t data)
{
    uint8_t received_data = 0;
    int counter = 0;
    /* wait until there's room in the buffer */
    //while(Master_SPI_STATbits.SPITBE == 0);
    SPIBUF = data;
    while((!SPI_STATbits.SPIRBF) && (counter < WAIT_TIME))
    {
        counter++;
    }
    received_data = SPIBUF;
    return received_data;
}

//main transport function
uint8_t Master_SPI_Send(uint8_t data)
{
    uint8_t received_data = 0;
    /* wait until there's room in the buffer */
    //while(Master_SPI_STATbits.SPITBE == 0);
    SPIBUF = data;
    while(!SPI_STATbits.SPIRBF);
    received_data = SPIBUF;
    return received_data;
}

static uint8_t lastByte;

//main transport function
uint8_t Master_SPI_Receive_()
{
    uint8_t received_data = 0;
    int counter = 0;
    /* wait until there's room in the buffer */
    //while(Master_SPI_STATbits.SPITBE == 0);
    SPIBUF = lastByte; //First byte is 00, but should be
    while((!SPI_STATbits.SPIRBF) && (counter < WAIT_TIME))
    {
        counter++;
    }
    received_data = SPIBUF;
    lastByte = received_data;
    return received_data;
}

//main transport function
uint8_t Master_SPI_Receive()
{
    uint8_t received_data = 0;
    /* wait until there's room in the buffer */
    //while(Master_SPI_STATbits.SPITBE == 0);
    SPIBUF = lastByte; //First byte is 00, but should be
    while(!SPI_STATbits.SPIRBF);
    received_data = SPIBUF;
    lastByte = received_data;
    return received_data;
}

uint8_t Slave_SPI_Receive_()
{
    uint8_t received_data = 0;
    int counter = 0;
    while((!SPI_STATbits.SPIRBF) && (counter < WAIT_TIME))
    {
        counter++;
    }
    received_data = SPIBUF;

    counter = 0;
    while((!SPI_STATbits.SPITBE) && (counter < WAIT_TIME))
    {
        counter++;
    }
    //Slave_SPIBUF = data;
    SPIBUF = received_data;
    return received_data;
}

//main transport function
uint8_t Slave_SPI_Receive()
{
    uint8_t received_data = 0;
    while(!SPI_STATbits.SPIRBF);
    received_data = SPIBUF;
    while(!SPI_STATbits.SPITBE);
    //Slave_SPIBUF = data;
    SPIBUF = received_data;
    return received_data;
}

uint8_t Slave_SPI_send_(uint8_t data)
{
    uint8_t received_data = 0;
    int counter = 0;
    while((!SPI_STATbits.SPIRBF) && (counter < WAIT_TIME))
    {
        counter++;
    }
    received_data = SPIBUF;
    counter = 0;
    while((!SPI_STATbits.SPITBE) && (counter < WAIT_TIME))
    {
        counter++;
    }
    SPIBUF = data;
    //Slave_SPIBUF = received_data;
    return received_data;
}

uint8_t Slave_SPI_send(uint8_t data)
{
    uint8_t received_data = 0;
    while(!SPI_STATbits.SPIRBF);
    received_data = SPIBUF;
    while(!SPI_STATbits.SPITBE);
    SPIBUF = data;
    //Slave_SPIBUF = received_data;
    return received_data;
}


void Slave_SPI_clear_stat()
{
    Slave_SPI_Init();
}

//setup SPI and enable
void Master_SPI_Init()
{

    int rdata;
    SPICON			= 0;
    rdata 				= SPIBUF;
    //Master_SPIBRG 			= (PBCLK-1ul)/2ul/SPI_FREQ;
    SPIBRG 			= 40;
    SPI_STAT_CLR		= 0x40;   //SPIROV = 0;
    //Master_SPICONbits.CKP 	= 1;
    //Master_SPICONbits.MSTEN = 1;    //SPI Master Mode
    //Master_SPICONbits.ON 	= 1;
    //Master_SPICON=0x8220;
    SPICON = 0x8220;

    TRIS_MASTER_CS_BIT = 0;

}

//setup SPI and enable
void Slave_SPI_Init()
{

    int rdata;

    SPICLK_DIR = 1;
    SPIMISO_DIR = 1;
    SPIMOSI_DIR = 0;

    IEC0CLR = 0x03800000; // disable all interrupts
    SPICON			= 0;
    rdata 				= SPIBUF;
    //Slave_SPIBRG 			= (PBCLK-1ul)/2ul/SPI_FREQ;
    IFS0CLR=0x03800000;// clear any existing event
    IPC5CLR=0x1f000000;// clear the priority
    IPC5SET=0x0d000000;// Set IPL=3, Subpriority 1
    IEC0SET=0x03800000;// Enable RX, TX and Error interrupts

    SPI_STAT_CLR		= 0x40;   //SPIROV = 0;
    //Slave_SPICONbits.CKP 	= 1;
    //Slave_SPICONbits.MSTEN = 0;  //Slave Mode
    //Slave_SPICONbits.ON 	= 1;
    SPICON = 0x8200;// SPI ON, 8 bits transfer, Slave mode

}

void Master_SPI_Select()
{
    MASTER_CS_BIT = 0;
}

void Master_SPI_Deselect()
{
    MASTER_CS_BIT = 1;
}

#endif