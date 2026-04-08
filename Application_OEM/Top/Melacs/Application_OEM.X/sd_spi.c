/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2012 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
*                           ALL RIGHTS RESERVED
*
*   This computer program is the property of RoweBots Research Inc.,
*   Kitchener, Ontario Canada. and may not be copied or redistributed in any 
*   form or by any means, whether in part or in whole, except under license 
*   granted by RoweBots Research Inc.
*
*   All copies of this program, whether in part or in whole, and whether 
*   modified or not, must display this and all other embedded copyright and 
*   ownership notices in full.  This notice may not be modified.
*
*   All source code is protected by international copyright laws and license
*   agreements.  Do not break the law.  You can obtain a license and source
*   code at rowebots.com subject to licensing conditions and restrictions.
*   Free development, free source code and free non commercial licenses may
*   be obtained in a few seconds on line without any difficult process.
*
*   All demonstration programs may be redistributed as source code to others  
*   as a small part of a Unison or DSPnano application. 
*
* ******************************************************************************   
*
*
*   Save Time and Money.  If you need modifications to the software to support
*   specific processors or peripherals, RoweBots Research can do this for you
*   quickly and easily at low cost.  If you need help with application develop-
*   ment, again we can solve your embedded development problems quickly and 
*   easily at very attractive prices.  We are tiny tiny embedded Linux* experts,
*   let us reduce your risk, accelerate your development and slash your time 
*   to market.  See rowebots.com - contact us.
*
*
*******************************************************************************/

/*-----------------------------------------------------------------------*/
/* MMC/SDSC/SDHC (in SPI mode) control module  (C)ChaN, 2007             */
#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _SD_SPI_FUNC_
#include <sys.h>
#include <p32xxxx.h>
#include "configurations.h"
#include "sd_spi.h"
#include "mutex.h"
#include "hardwaredefines.h"
#include "uart.h" //FOR DEBUG PURPOSE REMOVE IT WHEN THE PROBLEM HAS BEEN SOLVED THE PROBLEM IS IN SPI LINE 
#define BYTE 	unsigned char

#define SD_LOW_SPI_FREQ (250000ul)
#define SD_MAX_SPI_FREQ (10000000ul)

extern unsigned int g_cs_active;

//main transport function
uint_8 SD_SPI_Transfer(uint_8 data)
{
	/* wait until there's room in the buffer */       
	while(SDSPI_STATbits.SPITBE == 0);
	SDSPIBUF = data;	
	while(SDSPI_STATbits.SPIRBF == 0);
	return (BYTE)SDSPIBUF;   
}

int sdSPIHighSpeedEn = 0;

//setup SPI and enable
void SD_SPI_Enable()
{
    
//    int rdata;
    SDSPICON			= 0;
//    rdata 				= 
    SDSPIBUF;
    SD_SPIBRG 			= (PBCLK-1ul)/2ul/SD_LOW_SPI_FREQ;
    SDSPI_STAT_CLR		= 0x40;   //SPIROV = 0;
    SDSPICONbits.CKP 	= 1;
    SDSPICONbits.MSTEN = 1;
    SDSPICONbits.ON 	= 1;
    sdSPIHighSpeedEn = 0;
     
}

//clear SPI
void SPI_Clear()
{
    
//    int rdata;
    SDSPICON			= 0;
//    rdata 				= 
    SDSPIBUF;
    //SDSPI_STAT_CLR		= 0x40;   //SPIROV = 0;  
}

//setup SPI and enable
void SPI_Enable()
{
	SDSPICONbits.ON 	= 1;
    SPICLK = 1;			SPICLK_DIR = 1;
    SPIMISO = 1;		SPIMISO_DIR = 1;
    SPIMOSI = 1;		SPIMOSI_DIR = 1;       
    
}

//setup SPI and enable
void SPI_Disable()
{
	SDSPICONbits.ON 	= 0;
    SPICLK = 0;			SPICLK_DIR = 0;
    SPIMISO = 0;		SPIMISO_DIR = 1;
    SPIMOSI = 0;		SPIMOSI_DIR = 0;    
}

//set high speed for SPI
void SD_SPI_SetHighSpeed()
{
//    int rdata;
    SDSPICON			= 0;
//    rdata 				= 
    SDSPIBUF;
    SD_SPIBRG 			= (PBCLK-1ul)/2ul/SD_MAX_SPI_FREQ;
    SDSPI_STAT_CLR		= 0x40;   //SPIROV = 0;
    SDSPICONbits.CKP 	= 1;
    SDSPICONbits.MSTEN = 1;
    SDSPICONbits.ON 	= 1;
    sdSPIHighSpeedEn = 1;
}


//CS -> active for SPI slave
void SD_SPI_Select()
{   
    
//    if(g_cs_active != SD_SPI_ACTIVE)
//    {
//        if(sdSPIHighSpeedEn)
//        {
//        SD_SPI_SetHighSpeed();
//        }
//        else
//        {
//        SD_SPI_Enable();
//        }
//        
//        g_cs_active = SD_SPI_ACTIVE;
//        
//    }
//    
//	SD_CS_BIT = 0;
    if(sdSPIHighSpeedEn)
    {
        SD_SPI_SetHighSpeed();
    }
    else
    {
        SD_SPI_Enable();
    }

	SD_CS_BIT = 0;
}

//CS -> not active for SPI slave
void SD_SPI_Deselect()
{
	SD_CS_BIT = 1;
	SD_SPI_Transfer(0xFF);
    
    //spiUnlockMutex();
//    SpiUnlockMutex();
}


/*-----------------------------------------------------------------------*/
/* Send 80 or so clock transitions with CS and DI held high. This is     */
/* required after card power up to get it into SPI mode                  */
/*-----------------------------------------------------------------------*/
void SD_send_initial_clock_train(void)
{
    unsigned int i;

    /* Ensure CS is held high. */
    SD_SPI_Deselect();

    /* Send 10 bytes over the SSI. This causes the clock to wiggle the */
    /* required number of times. */
//    while(!SpiLockMutex())
      //  sleep(1);
    for(i = 0 ; i < 10 ; i++)
    {
      SD_SPI_Transfer(0xFF);
    }
    //SpiUnlockMutex();
}


//Get WP bit port mask
unsigned short  SD_WP_bit (void)
{
	return 0;
}

//Get Card Detect bit port mask
unsigned short  SD_INS_bit (void)
{
	return 0;
}

#endif