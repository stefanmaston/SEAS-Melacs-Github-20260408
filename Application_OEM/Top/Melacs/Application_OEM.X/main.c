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
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <sys.h>
#include <fsysinit.h>
#include <device.h>
#include <fsys.h>
#include <sys/mount.h>
#include "configurations.h"
#include "main.h"
#include "onBoardADC.h"
#include "onBoardRTCC.h"
#include "sd_spi.h"
#include "display.h"
#include "analogSensor10bit.h"
#include "delay.h"
#include "gsm.h"
#include "log.h"
#include "appheader.h"
#include <fcntl.h>
#include "UART.h"
#include "tcpserverstream.h"
#include <mqueue.h>

#define MAX_DISKN	1
#define RTOS_DEBUG	1
#define FSYSPRIO 	8
//#define FSYSSTACKSIZE 2048
#define FSYSSTACKSIZE 1024
THREAD Main(void *);

extern void logRun(void);
int g_flag_sd = 0;
extern int g_write_protect_sd;
 ConfigTableStruct ConfigTable = {
	Main, MAIN_STACK_SIZE, 4,		// root task
};

time_t previousLoggedTime;
time_t burst_previousLoggedTime;

#ifdef LOGGING
extern LOGDATA logData;
#endif

void RTC_init();
void Initialization(bool is_sdcard_ok);
void Termination();
void Application(bool is_sdcard_ok);
void bootloader_recovery_second_step(void);

THREAD Main(void *arg)
{

    pthread_t tid;
    pthread_attr_t  attr;
    struct fsysinit  fsysinit;
    struct sched_param myNewFsysPriority;
    int res;
    DISK_DRIVER sd_fat_drv;
    int SD_DEVNO;

    bool is_sdcard_ok = false;
    struct timespec time;
    
    /*Message queue start*/
    struct mq_attr attribute;
    mqd_t mq;
    
#ifdef BOOTAPP
   //CloseUART1();
   //DisableWDT();
#endif

    
#if RTOS_DEBUG
    dir_register("Main thread", pthread_self(), TYPE_THREAD);
#endif
    xprintf("Start Main\n");
 

    time.tv_sec = 0; time.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &time);

    previousLoggedTime = 0;
    burst_previousLoggedTime = 0;
    
    attribute.mq_flags = 0; 
    attribute.mq_maxmsg = 3;
    attribute.mq_msgsize = 16;
    if((mq =mq_open("TCPQUEUE", O_CREAT | O_RDWR, 0, &attribute)) == -1)        
        pthread_exit(0);
    if(mq_close(mq) == -1)
        pthread_exit(0);
        
   
        
#ifdef LOGGING

    is_sdcard_ok = true;
    /*
     *   FATFS Initialization
     */

    /* create the File server */
    fsysinit.fsi_msgsize = sizeof(struct fsysinit);
    fsysinit.fsi_datalog = 0;		//1 - enable xprintf output for debug purpose, 0 - disable
    fsysinit.fsi_ndrives = MAX_DISKN;	//maximum allowed disks
    
    // set up stack size and priority for main fsys threads and all clones
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, FSYSSTACKSIZE);
    myNewFsysPriority.sched_priority = 8;
    pthread_attr_setschedparam(&attr, &myNewFsysPriority);

    if(!pthread_create(&tid, &attr, (void*(*)(void*))_fatfs_server, (char*)&fsysinit))
    {
            if(!dir_register(FATFS_DIRECTORY, tid, TYPE_SERVER))
            {
                xprintf("..Unable to register name of File Server..\n");
                xprintf("..Required resource not present - aborting..\n");
#if RTOS_DEBUG
                dir_deregister("Main thread");
#endif
                pthread_exit((void*)1);
            }
    }
    else
    {
            xprintf("..Unable to create File Server..\n");
            xprintf("..Required resource for program not present - aborting..\n");
#if RTOS_DEBUG
            dir_deregister("Main thread");
#endif
            pthread_exit((void*)1);
    }

    xprintf("..FAT File server is now created..\n");
    /*preparing adding driver for SD card disk*/
    sd_fat_drv.disk_initialize = sd_disk_initialize;
    sd_fat_drv.disk_ioctl = sd_disk_ioctl;
    sd_fat_drv.disk_read = sd_disk_read;
    sd_fat_drv.disk_write = sd_disk_write;
    sd_fat_drv.disk_status = sd_disk_status;
    sd_fat_drv.disk_timerproc = sd_disk_timerproc;

    res = fatfs_add_drv(FATFS_DIRECTORY, &sd_fat_drv, &SD_DEVNO);		//add new disk driver to driver list structure
                                                                                //return DEVNO - local disk driver num
    if (res)
    {
            xprintf("Can't add SD card driver\n");
            pthread_exit((void*)1);
    }

    xprintf("SD card driver has number %d\n",SD_DEVNO);
    // parameters found in main.h
#ifdef MAKE_DISK_FORMATTING
    xprintf("..Attempting to mkfs ...");
    //res = mkfs(FATFS_DIRECTORY, SD_DEVNO,  0, 0);
    res = mkfs(FATFS_DIRECTORY, SD_DEVNO, SD_DISK_SIZE, SD_DISK_MAX_FILES);
    if(res == -1) {
            xprintf("..Unable to make a file system. errno=%d\n", errno);
            xprintf("..Please fix me..\n");
#if RTOS_DEBUG
            dir_deregister("Main thread");
#endif
            is_sdcard_ok = false;
            //pthread_exit((void*)1);
    }
#endif

    xprintf("\n..Attempting to mount it...\n");
    // must mount a directory for each mount point, here d1,
    // unique name for each
#ifdef INITIALIZATION
    if(true == is_sdcard_ok)
    {
        if(mount(SD_DEVNO, FATFS_MOUNT, 0) == -1)
        {
            xprintf("..Unable to mount flash disk. errno=%d\n", errno);
            xprintf("..Please fix me..\n");
#if RTOS_DEBUG
            dir_deregister("Main thread");
#endif
            is_sdcard_ok = false;
            
        }

    }
#endif
#endif
    xprintf("..done fsys initialization..\n");
       
//    stackReturn = pthread_stackinfo(tid , &info );    

#ifdef INITIALIZATION
    Initialization(is_sdcard_ok);
#endif
    //spiLockMutex();
    Application(is_sdcard_ok);
    
#ifdef INITIALIZATION
    Termination();
#endif

#if RTOS_DEBUG
    dir_deregister("Main thread");
#endif
    pthread_exit(0);
    return 0;
}

void Initialization(bool is_sdcard_ok)
{

#ifdef BOOTAPPS
    if(true == is_sdcard_ok)
    {
        //let's rename firmware, so bootloader will not revert to old firmware during next power on.
        bootloader_recovery_second_step();
    }
#endif
    
#ifdef _ONBOARD_ADC_FUNC_    
    ADC_SPIinit();
#endif    
#ifdef RTC
    RTC_init();
#endif
#ifdef _ANALOGSENSOR10BIT_FUNC_
    analog_sensor_10bit_init();
#endif    
#ifdef LOGGING
    if(true == is_sdcard_ok)
    {
        logInit();
        burstlogInit();
    }
#endif

#ifdef DISPLAY
   DisplayDeviceInit();
    //DISPLAYThread();
#endif

#ifdef GSM
    GSM_init();
#endif

#ifdef _UART_
    UARTThread();   
#endif

#ifdef APPLICATION_SPI_SLAVE
    Slave_SPI_Init();
#endif
#ifdef APPLICATION_SPI_MASTER
    Master_SPI_Init();
#endif
#ifdef _ETHERNET_
  ServerMain();
#endif

}
void Termination()
{
#ifdef DISPLAY
    DisplayEndCommunication();
#endif
#ifdef GSM
    GSM_deinit();
#endif
}

#ifdef RTC
void RTC_init()
{
    RTCC_SPIinit();
    
#ifdef WRITE_RTC
    yr = YEAR;
    mt = MONTH;
    dy = DAY;
    hr = HOUR;
    mn = MINUTE;
    sc = SECOND;
    wd = WEEKDAY;

    SPI_Disable();
    RTC_Write_Clock();
    SPI_Enable();
#endif
}
#endif

