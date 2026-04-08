#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "main.h"
#include <GenericTypeDefs.h>
#include <plib.h>
#include <sys/attribs.h>
#include "configurations.h"
#include <stdio.h>
#include <xc.h>
#include<unistd.h>
#include <stdlib.h>
#include <mrendez.h>
#include <sys/interrupt.h>
#include "display.h"
#include <string.h>
#include "delay.h"
#include "sd_spi.h"
#include "uart.h"
#include "appOEM.h"
extern struct timespec currentTime;
extern melacsSend sendCollection;
extern melacsReceive recvCollection;    
extern oemStruct os;
extern spi_active;

THREAD OemMainThread(void *);

void OemMainRun (){
   
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
    
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 3;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 1024);             

    if(pthread_create(&pid, &attr, &OemMainThread, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return; 
}

THREAD OemMainThread (void *arg)
{
   while(1)
    {
       if (spi_active != OEM_SPI_ACTIVE)
       {
        while(pthread_mutex_trylock(&testmutex_test)!=0)
            {
                //LED1 =~ LED1;
                usleep(100000);
                
            }
        spi_active = OEM_SPI_ACTIVE;
        ClearWDT(); //WDTCONbits.WDTCLR = 1; 
        clock_gettime(CLOCK_REALTIME, &currentTime);
        xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);
       
        readFromUsbReceiveBuffer(&recvCollection);
        
        ExecuteReceivedCommands(&os,&recvCollection, &sendCollection);          
        
        EscapeToOtherThreads();
        
        Inputs(&os);       
        
        if(os.keyStatus)
        {
            os.enableHeater = 1;
        }
        else
        {
            os.enableHeater = 0;     
        }
                   
        SystemRegulation(&os);        

        OutputControl(&os);

        EscapeToOtherThreads(); 

        SendToUsb(&os, &sendCollection);        
        
        Log(&os);          
        
        Gsm(&os); 
        
        Display(&os);
        pthread_mutex_unlock(&testmutex_test);
       }
        pthread_mutex_unlock(&testmutex_test);
        sleep(5);
    }
   
   
}
