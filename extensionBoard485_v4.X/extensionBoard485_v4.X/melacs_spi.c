#define _SUPPRESS_PLIB_WARNING

#include "melacs_spi.h"

#include "stdint.h"
#include <p32xxxx.h>
#include <plib.h>


static uint8_t lastByte;
/*
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
*/

//main transport function
uint8_t Slave_SPI_Receive()
{
    uint8_t received_data = 0;
    while(!SPI_STATbits.SPIRBF);
    received_data = SPIBUF;
    while(!SPI_STATbits.SPITBE);
    //Slave_SPIBUF = data;
    SPIBUF = (received_data + 3);
    return received_data;
}
/*
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
*/

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
    //SPI3CONbits.MSTEN = 0;
    SPI3CONbits.SMP = 1;
    SPI3CONbits.ON = 1;    
    SPI3CONbits.SSEN = 1;
    //Slave_SPICONbits.ON 	= 1;
    //SPICON = 0x8200;// SPI ON, 8 bits transfer, Slave mode

}

