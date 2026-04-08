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
#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _MMC_FUNC_

#include <sys.h>
#include <device.h>
#include "sd_spi.h"

/*
Mutex lock/unlock protection could be used for systems with more then one devices
connected to one SPI bus. For such kind of configuration define SPI_PROTECT == 1 and
make sure you are using same variable - "spi_mutex" for your spi driver too.
*/

int sd_protected = 1;


/*--------------------------------------------------------------------------

   Module Private Functions and Variables

---------------------------------------------------------------------------*/
static SD_TYPE card_type;
static uint_8 is_high_capacity;
static volatile int sd_mmc_wdt_timer, app_sd_mmc_wdt_timer;
static volatile DSTATUS Stat = STA_NOINIT;	/* Disk status */
static int SD_SendCommand(uint_8 command_index, uint_32 argument, uint_8 *response, uint_8 resp_len, uint_8 manage_cs);
static int SD_ReadDataBlock(uint_8 *buffer, uint_16 len);
static int SD_WriteDataBlock(const uint_8 *buffer);



int sd_block_num=0;
int sd_block_size=0;



/* USB Mass storage Standard Inquiry Data */
const int_8  sd_disc_standart_inquiry_data[] = 
{ 
  0x00, 0x80, 0x02, 0x02, 0x1F, 0x00, 0x00, 0x00,
  'I','N','R','E','S','O','L',' ',                                 /* Manufacturer : 8 bytes */
  'm','i','c','r','o',' ','S','D',' ','F','l','a','s','h',' ',' ', /* Product      : 16 Bytes */
  '1','.','0','0',                                                 /* Version      : 4 Bytes */
}; 

/*-----------------------------------------------------------------------*/
/* Update watchdog timer for driver                                      */
/*-----------------------------------------------------------------------*/
static void sd_mmc_update_wdt (void)
{
    if (sd_mmc_wdt_timer) --sd_mmc_wdt_timer;
    if (app_sd_mmc_wdt_timer) --app_sd_mmc_wdt_timer;
}

/*-----------------------------------------------------------------------*/
/* Waiting for SD card ready state                                       */
/*-----------------------------------------------------------------------*/
static uint_8 SD_wait_ready (void)
{
    uint_8 res;

    sd_mmc_wdt_timer = 700/MS_IN_ONE_OS_TICK;    /* Wait for ready in timeout of 700ms */
    SD_SPI_Read();
    do{
        res = SD_SPI_Read();
		if (res == 0xFF) break;
		//usleep(500);			//usleep will do context switch, but driver speed will be slower
	}while (sd_mmc_wdt_timer);

    return res;
}

/*-----------------------------------------------------------------------*/
/* Send CMD0 with CS low, to switch SD to SPI mode                       */
/*-----------------------------------------------------------------------*/
static int SD_put_to_SPI_mode (void)
	{
uint_8 read;

	SD_SPI_Select();

	SD_SPI_Write(0x40);
	SD_SPI_Write(0);
	SD_SPI_Write(0);
	SD_SPI_Write(0);
	SD_SPI_Write(0);
	SD_SPI_Write(0x95);

    sd_mmc_wdt_timer = 100/MS_IN_ONE_OS_TICK;    // Wait for ready in timeout of 100ms
    do{
		read = SD_SPI_Read();
		if (read == 0x01)
	{
			break;
	}
		usleep(2000);
    }while (sd_mmc_wdt_timer);

	SD_SPI_Deselect();

	// Send dummy byte: 8 Clock pulses of delay
	SD_SPI_Read();

   	if (sd_mmc_wdt_timer == 0)	return 0;

	return 1;
}


/*-----------------------------------------------------------------------*/
/* Send command to SD by SPI                                             */
/*-----------------------------------------------------------------------*/
static int SD_SendCommand(uint_8 command_index, uint_32 argument, uint_8 *response, uint_8 resp_len, uint_8 manage_cs)
{
	int i;
	uint_8 read, crc, cmd;

	switch(command_index)
	{
		case 0:
			crc = 0x94;
			break;
		case 8:
			crc = 0x86;
			break;
		default:
			crc = 0xFF;
			break;
	}

	//framing bits
	cmd = command_index;
	cmd &= ~(1<<7); 	// start bit
	cmd |= (1<<6);  	// transmission bit
	crc |= (1<<0);		// stop bit

	if (manage_cs)	SD_SPI_Select();

	if (SD_wait_ready() != 0xFF)
	{
	    if (manage_cs) 	SD_SPI_Deselect();
	    return 1;
	}

	SD_SPI_Write(cmd);
	SD_SPI_Write((uint_8)(argument >> 24));
	SD_SPI_Write((uint_8)(argument >> 16));
	SD_SPI_Write((uint_8)(argument >> 8));
	SD_SPI_Write((uint_8)(argument));
	SD_SPI_Write(crc);

 	if (command_index == 12) SD_SPI_Read();        /* Skip a stuff byte when stop reading */

    sd_mmc_wdt_timer = 40/MS_IN_ONE_OS_TICK;    // Wait for ready in timeout of 40ms
    do{
		read = SD_SPI_Read();
		if ((read & 0x80)==0)
		{
		    response[resp_len - 1] = read;
		    break;
		}
    }while (sd_mmc_wdt_timer);

   	if (sd_mmc_wdt_timer == 0)
   	{
   	    if (manage_cs) 	SD_SPI_Deselect();
   	    return 2;
   	}

	for (i = resp_len - 2; i >= 0; i--)
		response[i] = SD_SPI_Read();

	if (manage_cs) 	SD_SPI_Deselect();

	return 0;
}


/*-----------------------------------------------------------------------*/
/* Read data block from SD by SPI                                        */
/*-----------------------------------------------------------------------*/
static int SD_ReadDataBlock( uint_8 *buffer,   uint_16 len )
{
	int i;
	uint_8 token = 0xFF;

	// Read the start token
    sd_mmc_wdt_timer = 100/MS_IN_ONE_OS_TICK;
    do {                            /* Wait for data packet in timeout of 100ms */
        token = SD_SPI_Read();
		if(token != 0xFF) break;
	} while (sd_mmc_wdt_timer);

    if(token != 0xFE) return 1;    /* If not valid data token, return with error */

	for (i = 0; i < len; i++)
	{
		buffer[i] = SD_SPI_Read();
	}

	// Discard the 16-bit CRC
	SD_SPI_Read();
	SD_SPI_Read();
	return 0;
}

/*-----------------------------------------------------------------------*/
/* Write data block to SD by SPI                                         */
/*-----------------------------------------------------------------------*/
static int SD_WriteDataBlock(
           const uint_8 *buffer     /* 512 byte data block to be transmitted */
)
{
	int i;
	uint_8 token;

	for (i = 0; i < 512; i++)
	{
	    SD_SPI_Write(buffer[i]);
	}
	SD_SPI_Write(0xFF);
	SD_SPI_Write(0xFF);

	// Wait correct the response token, during 100ms
    sd_mmc_wdt_timer = 100/MS_IN_ONE_OS_TICK;
    do {
	token = SD_SPI_Read();
		if ((token & 0x1F) == 0x05)	break;
	} while (sd_mmc_wdt_timer);

    if (sd_mmc_wdt_timer == 0)
    {
        return 1;
    }
    if (SD_wait_ready() != 0xFF)
    {
        return 1;
    }

	return 0;
}

int_8 sd_init_(uint_8 lun);
/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/
int_8 sd_disc_init_ (uint_8 lun)
{
	static char flag_sd_init=0;
	if(flag_sd_init==0)
		sd_init_(lun);
	else
		return 0;
	flag_sd_init=1;
	return 0;
}

/*-----------------------------------------------------------------------*/
/* 						                                                */
/*-----------------------------------------------------------------------*/
int_8 sd_init_(uint_8 lun)
{
	int result, cnt;
	uint_32 arg;
	uint_8 response[5];

 	uint_8 n, csd[64];
	uint_32 csize;


	card_type = SD_NONE;
	is_high_capacity = 0;

	//mutex init
	SPI_MUTEX_INIT
	//mutex lock
	SPI_MUTEX_LOCK
    
	//setup/enable SPI peripheral
	SD_SPI_Enable();

    //Set DI and CS high and apply more than 74 pulses to SCLK for the card
    //to be able to accept a native command.
    SD_send_initial_clock_train();

	// Send CMD0  - Put SD in SPI mode
    cnt = 2;
    do
    {
	if(SD_put_to_SPI_mode()) break;
	usleep(100000);
    }while(--cnt);

    if (cnt == 0)
	{
                SPI_MUTEX_UNLOCK
		return Stat;
	}

    arg = 0;
	// Send CMD8
	result = SD_SendCommand(8, 0x1AA, response, 5, 1);
	if (result == 0)
	{
		if (response[4] == 0x01)
		{
			if (response[1] == 0x01 && response[0] == 0xAA)
			{
				// SD 2.x, assume low capacity for now
				card_type = SD_VER2;
				arg = 1UL << 30;
			}
		}
		else if (response[4] & 0x04)
		{
			// SD 1.x or MMC
			card_type = SD_VER1;
		}
	}

	if (card_type == SD_NONE)
	{
		SPI_MUTEX_UNLOCK
		return Stat;
	}

	app_sd_mmc_wdt_timer = 1000/MS_IN_ONE_OS_TICK;    //Initialization timeout of 1000 msec
	do
	{
		if (card_type != SD_MMC)
		{
			SD_SendCommand(55, 0, response, 1, 1);
			result = SD_SendCommand(41, arg, response, 1, 1);
		}
		else
		{
			result = SD_SendCommand(1, 0, response, 1, 1);
		}
		if (result == 0)
		{
			if (response[0] == 0x00)
                  break;
  			  else if (response[0] & 0x04)
                      card_type = SD_MMC;
		}
		usleep(5000);
	}while(app_sd_mmc_wdt_timer);

   	if (app_sd_mmc_wdt_timer == 0)
		{
		SPI_MUTEX_UNLOCK		  
		return Stat;
		}

	// Send CMD58
	result = SD_SendCommand(58, 0, response, 5, 1);
	if (result != 0 || response[4] != 0x00)
	{
		SPI_MUTEX_UNLOCK	  
		return Stat;
	}
	else
	{
		// Check the CCS bit
		if (response[3] & 0x40)
		{
			is_high_capacity = 1;
		}
	}

	SD_SPI_SetHighSpeed();
	SPI_MUTEX_UNLOCK



	sd_block_size = 512;

	// Get the CSD
	// Send CMD9
	SD_SPI_Select();
	result = SD_SendCommand(9, 0, response, 1, 0);
	if (result == 0 && response[0] == 0x00)
	{
		result = SD_ReadDataBlock(csd, 16);
		if (result == 0)
		{
			if ((csd[0] >> 6) == 1)
			{
				// SDHC
				csize = csd[9] + ((uint_16)csd[8] << 8) + 1;
				sd_block_num = (uint_32)csize << 10;
			}
			else
			{
				// SD ver 1.x, SD ver 2.x Standard Capacity, or MMC
				n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
				csize = (csd[8] >> 6) + ((uint_16)csd[7] << 2) + ((uint_16)(csd[6] & 3) << 10) + 1;
				sd_block_num = (uint_32)csize << (n - 9);
			}
		}
	}
	SD_SPI_Deselect();


	return Stat;
}

DSTATUS sd_disk_initialize (void)
{
	int result, cnt;
	uint_32 arg;
	uint_8 response[5];

	if (Stat & STA_NODISK) return Stat;
	if ((Stat & STA_NOINIT) == 0) return Stat;

	card_type = SD_NONE;
	is_high_capacity = 0;

	//mutex init
	SPI_MUTEX_INIT
	//mutex lock
	SPI_MUTEX_LOCK
	//setup/enable SPI peripheral
	SD_SPI_Enable();

    //Set DI and CS high and apply more than 74 pulses to SCLK for the card
    //to be able to accept a native command.
    SD_send_initial_clock_train();

	// Send CMD0  - Put SD in SPI mode
    cnt = 2;
    do
    {
	if(SD_put_to_SPI_mode()) break;
	usleep(100000);
    }while(--cnt);

    if (cnt == 0)
	{
                SPI_MUTEX_UNLOCK
		return Stat;
	}

    arg = 0;
	// Send CMD8
	result = SD_SendCommand(8, 0x1AA, response, 5, 1);
	if (result == 0)
	{
		if (response[4] == 0x01)
		{
			if (response[1] == 0x01 && response[0] == 0xAA)
			{
				// SD 2.x, assume low capacity for now
				card_type = SD_VER2;
				arg = 1UL << 30;
			}
		}
		else if (response[4] & 0x04)
		{
			// SD 1.x or MMC
			card_type = SD_VER1;
		}
	}

	if (card_type == SD_NONE)
	{
		SPI_MUTEX_UNLOCK
		return Stat;
	}

        app_sd_mmc_wdt_timer = 1000/MS_IN_ONE_OS_TICK;    //Initialization timeout of 1000 msec
	do
	{
		if (card_type != SD_MMC)
		{
		    SD_SendCommand(55, 0, response, 1, 1);
		    result = SD_SendCommand(41, arg, response, 1, 1);
		}
		else
		{
		    result = SD_SendCommand(1, 0, response, 1, 1);
		}
		if (result == 0)
		{
		    if (response[0] == 0x00)
                        break;
  		    else if (response[0] & 0x04)
                        card_type = SD_MMC;
		}
		usleep(5000);
	}while(app_sd_mmc_wdt_timer);

   	if (app_sd_mmc_wdt_timer == 0)
	{
	    SPI_MUTEX_UNLOCK		  
	    return Stat;
	}

	// Send CMD58
	result = SD_SendCommand(58, 0, response, 5, 1);
	if (result != 0 || response[4] != 0x00)
	{
		SPI_MUTEX_UNLOCK	  
		return Stat;
	}
	else
	{
		// Check the CCS bit
		if (response[3] & 0x40)
		{
			is_high_capacity = 1;
		}
	}

	SD_SPI_SetHighSpeed();
	SPI_MUTEX_UNLOCK
	Stat &= ~STA_NOINIT;

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

int_8 sd_disc_get_capacity_ (uint_8 lun, uint_32 *block_num, uint_32 *block_size)
{
	*block_size   = sd_block_size;
	*block_num = sd_block_num;
 
   return (0);
}



/******************************************************************************/
/*                                                                            */
/******************************************************************************/
int_8  sd_disc_ready_ (uint_8 lun)
{  
/*	static int_8 last_status = 0;
	
	// if not detected card
	if(PORTFbits.RF0 == 1)
	{
		sd_block_num =0;
		sd_block_size = 0;

		last_status = -1;
		return (-1); 
	}
 	else if(last_status  < 0)
   {
   	 sd_init_(lun);
     last_status = 0;
   }
*/
  return (0);
	
}

DSTATUS sd_disk_status ()
{
	return Stat;
}


/******************************************************************************/
/*                                                                            */
/******************************************************************************/
int_8  sd_disc_write_protected_ (uint_8 lun)
{
	if(sd_protected == 0)
	  return  0;
	else
      return  -1;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
int_8 sd_disc_read_ (uint_8 lun, uint_8 *buff, uint_32 sector, uint_16 count)
{
	int result/*, i*/;
	uint_8 response[1];

	//	xprintf("READ sec=%d count=%d\n",sector,count);
	
	if (!count) return RES_PARERR;

	if (!is_high_capacity)
	{
		// Convert to a byte address
		sector *= 512;
	}

	SPI_MUTEX_LOCK

	SD_SPI_Select();

	if (count == 1)
	{
		// Single block read
		result = SD_SendCommand(17, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			{
				result = SD_ReadDataBlock(buff, 512);
				if (result == 0)	count = 0;
			}
	}
	else
	{
 		// Read Multiple Blocks
		result = SD_SendCommand(18, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			 {
				do
					{
						result = SD_ReadDataBlock(buff, 512);
						if (result != 0) break;
						buff += 512;
					} while (--count);
				// STOP_TRANSMISSION
				SD_SendCommand(12, 0, response, 1, 0);
			 }
	}

	SD_SPI_Deselect();

	// Send dummy byte: 8 Clock pulses of delay
	SD_SPI_Read();

	SPI_MUTEX_UNLOCK

    return 0;
}
/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT sd_disk_read (
	unsigned char *buff,		/* Pointer to the data buffer to store read data */
	unsigned long sector,		/* Start sector number (LBA) */
	unsigned char count			/* Sector count (1..255) */
)
{
	int result/*, i*/;
	uint_8 response[1];


	if (!count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	if (!is_high_capacity)
	{
		// Convert to a byte address
		sector *= 512;
	}

	SPI_MUTEX_LOCK

	SD_SPI_Select();

	if (count == 1)
	{
		// Single block read
		result = SD_SendCommand(17, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			{
				result = SD_ReadDataBlock(buff, 512);
				if (result == 0)	count = 0;
			}
	}
	else
	{
 		// Read Multiple Blocks
		result = SD_SendCommand(18, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			 {
				do
					{
						result = SD_ReadDataBlock(buff, 512);
						if (result != 0) break;
						buff += 512;
					} while (--count);
				// STOP_TRANSMISSION
				SD_SendCommand(12, 0, response, 1, 0);
			 }
	}

	SD_SPI_Deselect();

	// Send dummy byte: 8 Clock pulses of delay
	SD_SPI_Read();

	SPI_MUTEX_UNLOCK

    return count ? RES_ERROR : RES_OK;
}




/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
int_8 sd_disc_write_ (uint_8 lun, uint_8 *buff, uint_32 sector,  uint_16 count)
{
	int result/*, i*/;
	uint_8 response[1]/*, token*/;

//	xprintf("WRITE sec=%d count=%d\n",sector,count);
	
	if (!count) return RES_PARERR;

	if (!is_high_capacity)
	{
		// Convert to a byte address
		sector *= 512;
	}

	SPI_MUTEX_LOCK

	SD_SPI_Select();

	if (count == 1)
	{
		// Single Block Write
		result = SD_SendCommand(24, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
		{
			SD_SPI_Write(0xFE);
			result = SD_WriteDataBlock(buff);
			if (result == 0) count = 0;
		}
	}
	else
	{
		// Multiple Block Write
        if (card_type != SD_MMC)
			{
				SD_SendCommand(55, 0, response, 1, 0);		
				SD_SendCommand(23, count, response, 1, 0);	//ACMD23
	        }
		result = SD_SendCommand(25, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			{
				do {
					SD_SPI_Write(0xFC);
					result = SD_WriteDataBlock(buff);
					if (result != 0) break;
					buff += 512;
					}while(--count);
				// STOP_TRAN token
				SD_SPI_Write(0xFD);
				if (SD_wait_ready() != 0xFF) count = 1;
			}
	}

	SD_SPI_Deselect();

	// Send dummy byte: 8 Clock pulses of delay
	SD_SPI_Read();

	SPI_MUTEX_UNLOCK

	return 0;
}
/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT sd_disk_write (
	const unsigned char *buff,	/* Pointer to the data to be written */
	unsigned long sector,		/* Start sector number (LBA) */
	unsigned char count			/* Sector count (1..255) */
)
{
	int result/*, i*/;
	uint_8 response[1]/*, token*/;

	if (!count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;

	if (!is_high_capacity)
	{
		// Convert to a byte address
		sector *= 512;
	}

	SPI_MUTEX_LOCK

	SD_SPI_Select();

	if (count == 1)
	{
		// Single Block Write
		result = SD_SendCommand(24, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
		{
			SD_SPI_Write(0xFE);
			result = SD_WriteDataBlock(buff);
			if (result == 0) count = 0;
		}
	}
	else
	{
		// Multiple Block Write
        if (card_type != SD_MMC)
			{
				SD_SendCommand(55, 0, response, 1, 0);		
				SD_SendCommand(23, count, response, 1, 0);	//ACMD23
	        }
		result = SD_SendCommand(25, sector, response, 1, 0);
		if (result == 0 && response[0] == 0x00)
			{
				do {
					SD_SPI_Write(0xFC);
					result = SD_WriteDataBlock(buff);
					if (result != 0) break;
					buff += 512;
					}while(--count);
				// STOP_TRAN token
				SD_SPI_Write(0xFD);
				if (SD_wait_ready() != 0xFF) count = 1;
			}
	}

	SD_SPI_Deselect();

	// Send dummy byte: 8 Clock pulses of delay
	SD_SPI_Read();

	SPI_MUTEX_UNLOCK

	return count ? RES_ERROR : RES_OK;
}
#endif /* _READONLY */


/******************************************************************************/
/*                                                                            */
/******************************************************************************/
#define SD_LUN_NBR                  1 
int_8 sd_disc_get_max_lun_ (void)
{
  // This function must return maximum LUN supported by this device.
  // For example if the device support four LUNs then return number would bu 3.
  return (SD_LUN_NBR - 1);
}

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/
DRESULT sd_disk_ioctl (
	unsigned char ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	DRESULT res;
	uint_8 n, csd[64], response[1], result;
	uint_32 csize, capacity;
	

	if (Stat & STA_NOINIT) return RES_NOTRDY;

	res = RES_ERROR;

	SPI_MUTEX_LOCK

	switch (ctrl) {
		case CTRL_SYNC :	/* Flush dirty buffer if present */
			res = RES_OK;
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (uint_32) */
			// Get the CSD
			// Send CMD9
			SD_SPI_Select();
			result = SD_SendCommand(9, 0, response, 1, 0);
			if (result == 0 && response[0] == 0x00)
			{
				result = SD_ReadDataBlock(csd, 16);
				if (result == 0)
				{
					if ((csd[0] >> 6) == 1)
					{
						// SDHC
						csize = csd[9] + ((uint_16)csd[8] << 8) + 1;
						capacity = (uint_32)csize << 10;
						*(uint_32*)buff = capacity;
						xprintf("\rCard capacity = %u x 512\r", capacity);
						res = RES_OK;
					}
					else
					{
						// SD ver 1.x, SD ver 2.x Standard Capacity, or MMC
						n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
						csize = (csd[8] >> 6) + ((uint_16)csd[7] << 2) + ((uint_16)(csd[6] & 3) << 10) + 1;
						capacity = (uint_32)csize << (n - 9);
						*(uint_32*)buff = capacity;
						xprintf("\rCard capacity = %u\r", (capacity << 9));
						res = RES_OK;
					}
				}
			}
			SD_SPI_Deselect();
			break;

		case GET_SECTOR_SIZE :	/* Get sector size (uint_16) */
			*(uint_16*)buff = 512;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sectors (uint_32) */
			*(uint_32*)buff = 1;
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
	}

	SPI_MUTEX_UNLOCK

	return res;
}

/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure  (Platform dependent)                */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 1ms                         */

void sd_disk_timerproc_ (void)
{
	
	sd_mmc_update_wdt();	
}


/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure  (Platform dependent)                */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 1ms                         */

void sd_disk_timerproc (void)
{
	static uint_16 pv;
	uint_16 p;
	uint_8 s;

	p = pv;
	pv = SD_WP_bit() | (SD_INS_bit() << 1); /* Sample socket switch */

	if (p == pv) {					/* Have contacts stabled? */
		s = Stat;

		if (p & 0x01)				/* WP is H (write protected) */
			s |= STA_PROTECT;
		else						/* WP is L (write enabled) */
			s &= ~STA_PROTECT;

		if (p & 0x02)				/* INS = H (Socket empty) */
			s |= (STA_NODISK | STA_NOINIT);
		else						/* INS = L (Card inserted) */
			s &= ~STA_NODISK;

		Stat = s;
	}
	
	sd_mmc_update_wdt();	
}


#endif