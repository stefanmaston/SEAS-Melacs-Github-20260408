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
extern spi_active;
void Ether_Init();
THREAD EtherMain(void *);

void ETHERThread (){
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
    
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 3;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 1024);             

    if(pthread_create(&pid, &attr, &EtherMain, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return; 
}

THREAD EtherMain (void *arg)
{
    int i = 0;
    while(1)
    {
        
        
       if (spi_active != ETHER_SPI_ACTIVE)
       {
            while(pthread_mutex_trylock(&testmutex_test)!=0)
                {
                    usleep(100000);
                }
            spi_active = ETHER_SPI_ACTIVE;
#ifdef _ETHERNET_    
            ether_int_on(); 
            sleep(5);
            ether_int_off();
#endif
            pthread_mutex_unlock(&testmutex_test);
       }
        pthread_mutex_unlock(&testmutex_test);
        sleep(5);

        
    }
}
