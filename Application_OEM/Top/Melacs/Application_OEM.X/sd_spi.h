/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2008 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
/*-----------------------------------------------------------------------*/
/* Only rcvr_spi(), xmit_spi(), disk_timerproc() and some macros         */
/* are platform dependent.                                               */
/*-----------------------------------------------------------------------*/

#ifndef __SD_SPI_H__
#define __SD_SPI_H__

#define SD_SPI_Write(data)	SD_SPI_Transfer(data)
#define SD_SPI_Read()		SD_SPI_Transfer(0xFF)

/* Generic command */
#define CTRL_SYNC			0	/* Mandatory for write functions */
#define GET_SECTOR_COUNT	1	/* Mandatory for only f_mkfs() */
#define GET_SECTOR_SIZE		2
#define GET_BLOCK_SIZE		3	/* Mandatory for only f_mkfs() */
#define CTRL_POWER			4
#define CTRL_LOCK			5
#define CTRL_EJECT			6

typedef enum
{
	 SD_NONE,
	 SD_VER2,
	 SD_VER1,
	 SD_MMC,
} SD_TYPE;

//#define SOCKPORT		PORTF		// Socket contact port
//#define SOCKWP			(1<<1)		// Write protect switch
//#define SOCKINS			(1<<0)		// Card detect switch
#define SDSPI_STATbits	(SPI3STATbits)
#define SDSPI_STAT_CLR	(SPI3STATCLR)
#define SDSPICON		(SPI3CON)
#define SDSPICONbits	(SPI3CONbits)
#define SD_SPIBRG		(SPI3BRG)
#define SDSPIBUF   		(SPI3BUF)
#define SD_CS_BIT		(PORTFbits.RF5)
#define SDSPI_RFIF_BIT 	(IFS0bits.SPI3RXIF)
void SPI_Enable();
void SPI_Disable();
void SPI_Clear();
void SD_SPI_SetHighSpeed();
uint_8 SD_SPI_Transfer(uint_8 data);
void SD_SPI_Select();
void SD_SPI_Deselect();
void SD_send_initial_clock_train(void);
uint_16 SD_WP_bit (void);
uint_16 SD_INS_bit (void);

void SD_SPI_Enable();

#define SPI_PROTECT 		1		// 0/1 - disable/enable spi bus protect by a mutex
#define	MS_IN_ONE_OS_TICK	2		// millisecond in one OS tick	

#define ETHER_SPI_ACTIVE 1
#define OEM_SPI_ACTIVE 2

/*
Mutex lock/unlock protection could be used for systems with more then one devices
connected to one SPI bus. For such kind of configuration define SPI_PROTECT == 1 and
make sure you are using same variable - "spi_mutex" for your spi driver too.
*/
#if SPI_PROTECT == 1
	extern  pthread_mutex_t		spi_mutex;
	#define SPI_MUTEX_INIT		pthread_mutex_init(&spi_mutex, 0);
	#define SPI_MUTEX_LOCK		pthread_mutex_lock(&spi_mutex);
	#define SPI_MUTEX_UNLOCK	pthread_mutex_unlock(&spi_mutex);


#else
	#define SPI_MUTEX_INIT  
	#define SPI_MUTEX_LOCK      
	#define SPI_MUTEX_UNLOCK    

#endif
    
	extern  pthread_mutex_t		testmutex_test;
    extern  pthread_cond_t      cond;
	#define TEST_MUTEX_INIT		pthread_mutex_init(&testmutex_test, 0);
	#define TEST_MUTEX_LOCK		pthread_mutex_lock(&testmutex_test);
    #define TEST_MUTEX_TRY_LOCK pthread_mutex_trylock(&testmutex_test);
	#define TEST_MUTEX_UNLOCK	pthread_mutex_unlock(&testmutex_test);
    
uint8_t mutexresult[8];
  
    
unsigned int spi_dev_int_dis(void );
void spi_dev_int_res(unsigned int );
void ether_int_on(void);
void ether_int_off(void);
void ETHERThread ();
void OemMainRun ();


#endif //__SD_SPI_H__
