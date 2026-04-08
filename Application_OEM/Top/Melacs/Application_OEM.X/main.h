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

#ifndef __MAIN_H__
#define __MAIN_H__

#include <device.h>
#include <stdbool.h>
//#define NO_PRI_OSC
//#define EIGTH_MHZ_OSC
#define SIXTEEN_MHZ_OSC

#define SD_DISK_SIZE (1024ul*1024ul*32ul)
#define SD_DISK_MAX_FILES 100

#define FATFS_DIRECTORY "/dev/sd"
#define FATFS_MOUNT FATFS_DIRECTORY "/d1"

//#define LOGGING
#define MAKE_DISK_FORMATTING		//enable/disable disk formatting
//##define MAKE_DISK_FORMATTINGdefine DISPLAY

#ifndef RTOS_DEBUG
#define RTOS_DEBUG 1
#endif
#define YEAR 23
#define MONTH 06
#define DAY 14
#define HOUR 9
#define MINUTE 00
#define SECOND 10
#define WEEKDAY 3


#define APPLICATION_OEM                   //prio Ok

#define READ_CONFIG


#define INITIALIZATION


#ifdef APPLICATION_OEM
#define LOGGING
#define LOG_OEM
#define DISPLAY
#define MAIN_STACK_SIZE 2348
#define RTC
#define WRITE_RTC
//define _WRAPPER_BASE_
#define _QUEUE_
#define _ETHERNET_
#define MELACS_SERVER1
#define TCP_SEND_BUFFER_SIZE 75
#define TCP_RECV_BUFFER_SIZE 80
#define USB_SEND_BUFFER_SIZE 75
#define USB_RECV_BUFFER_SIZE 80


#define SPI_MUTEX
#define _MMC_FUNC_
#define _ONBOARD_ADC_FUNC_
#define _COMMON_FUNC_
#define _ONBOARD_RTCC_FUNC_
#define _SD_SPI_FUNC_
#define _MUTEX_FUNC_
//#define _MELACS_SPI_
#define _ANALOGSENSOR10BIT_FUNC_
#define _ANALOG_TO_PHYSICAL_FUNC_
#define _SENSOR_VALUE_CONV_FUNC_
#define _READ_CONFIG_FUNC_
#define _MALLOC_FUNC_
#define _UART_
#define _USB_

#endif




#define	FW_NAME				"/firmware/fw.ocf"
#define	OLD_FW_NAME			"/firmware/old_fw.ocf"

#define	FW_PATH				FATFS_MOUNT FW_NAME
#define	OLD_FW_PATH			FATFS_MOUNT OLD_FW_NAME

DSTATUS sd_disk_initialize (void);
DSTATUS sd_disk_status ();
DRESULT sd_disk_read (unsigned char *,unsigned long , unsigned char );
DRESULT sd_disk_write (const unsigned char *, unsigned long, unsigned char );
DRESULT sd_disk_ioctl (unsigned char , void *);
void sd_disk_timerproc (void);


#ifdef MELACS_SERVER1
#define IPV6_5 0x55
#define IPV4STRING "192.168.1.160"
#endif

#ifdef MELACS_SERVER2
#define IPV6_5 0x56
#define IPV4STRING "192.168.16.161"
#endif

#ifdef MELACS_SERVER3
#define IPV6_5 0x57
#define IPV4STRING "192.168.16.162"
#endif

#ifdef MELACS_SERVER4
#define IPV6_5 0x58
#define IPV4STRING "192.168.16.163"
#endif

#ifdef MELACS_SERVER5
#define IPV6_5 0x59
#define IPV4STRING "192.168.16.164"
#endif

#ifdef MELACS_SERVER6
#define IPV6_5 0x60
#define IPV4STRING "192.168.16.165"
#endif

#ifdef MELACS_SERVER7
#define IPV6_5 0x61
#define IPV4STRING "192.168.16.166"
#endif

#ifdef MELACS_SERVER8
#define IPV6_5 0x62
#define IPV4STRING "192.168.16.167"
#endif

#ifdef MELACS_SERVER9
#define IPV6_5 0x63
#define IPV4STRING "192.168.16.168"
#endif

#ifdef MELACS_SERVER10
#define IPV6_5 0x64
#define IPV4STRING "192.168.16.169"
#endif

#ifdef MELACS_SERVER11
#define IPV6_5 0x65
#define IPV4STRING "192.168.16.170"
#endif

#ifdef MELACS_SERVER12
#define IPV6_5 0x66
#define IPV4STRING "192.168.16.171"
#endif

int xprintf (const char *format, ...);

#ifdef LOGGING
#define FILENUM 4
#define MAXOPENFILES 4
#define DIRSTRING "/dev/sd/d1/LogDir"
#define LOG_FIRST "/Log"
#define LOG_EXTENSION ".csv"
#define MAXSTRINGLEN 50
#define DIRSIZE  (sizeof(struct dirent))

#define SAMPLE_PERIOD 2
#define LOG_PERIOD 4
#define TOTAL_SAMPLES_IN_EACH_LOG 2 //(LOG_PERIOD / SAMPLE_PERIOD)
#define MAX_INTEGER_LENGTH 8
#define MAX_FILE_SIZE_BYTES 100000
//#define MAX_FILE_SIZE_BYTES 1000

#define BURST_MAXPATHLEN 70
#define BURST_DIRSTRING "/dev/sd/d1/BurstLogDir"
#define BURST_LOG_FIRST "/BurstLog"

#define LOGBURST_PERIOD 10
#define LOGBURST_COUNTER 36 //36 //So we are burst logging after time LOGBURST_PERIOD*LOGBURST_COUNTER
#define NUM_BURST_READS 100 //A huge number like 1000 will cause the stack to overflow
#endif

#endif
