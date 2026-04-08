#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING


#include "main.h"
#include "queuehandler.h"
#include "uart.h"
#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include "onBoardRTCC.h"

extern char TCPbuffer[512];
bool TimeUpdate = false;
THREAD QUEUE_HANDLE(void *arg); 
void QueueMain()
{  
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
        
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 3;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 2048);             
    
    if(pthread_create(&pid, &attr, &QUEUE_HANDLE, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return; 

}
THREAD QUEUE_HANDLE(void *arg) 
{

    char msg[16];
    QUEUE_t QueueState; 
    ssize_t len;
   // char expect;
    mqd_t mq;
    /*Message queue test here where Ethernet wants to send*/
    if((mq = mq_open("TCPQUEUE", O_RDONLY, 0, 0)) == -1)
    {
        pthread_exit(0);
    }

    
    while(1)
    {   
        memset(msg, 0, sizeof(msg));
        if((len = mq_receive(mq, msg, sizeof(msg), 0)) == -1)
        {
            xprintf("Receive failed");
        }
        else
        {
          QueueState = TCPbuffer[1] - '0';
            
          switch(QueueState)
          {  
                  case DISPLAYONELED: 
                  { 
                        LED1 = 1;
                        LED2 = 0;
                        LED4 = 0;
                        LED3 = 0;
//                        DisplayTransmitString("LED 1 ON");
//                        DisplayTransmitString("LED 2 OFF");
//                        DisplayTransmitString("LED 3 OFF");
//                        DisplayTransmitString("LED 4 OFF");
//                        DisplayRestartScreen();
                  }break;
                  case DISPLAYTWOLED: 
                  {
                        LED1 = 1;
                        LED2 = 1;
                        LED4 = 0;
                        LED3 = 0;
//                        DisplayTransmitString("LED 1 ON");
//                        DisplayTransmitString("LED 2 ON");
//                        DisplayTransmitString("LED 3 OFF");
//                        DisplayTransmitString("LED 4 OFF");
//                        DisplayRestartScreen();
                  
                  
                  }break;
                  case DISPLAYTHREELED: 
                  {
                        LED1 = 1;
                        LED2 = 1;
                        LED4 = 1;
                        LED3 = 0;
//                        DisplayTransmitString("LED 1 ON");
//                        DisplayTransmitString("LED 2 ON");
//                        DisplayTransmitString("LED 3 ON");
//                        DisplayTransmitString("LED 4 OFF");
//                        DisplayRestartScreen();
                  
                  }break;
                  case DISPLAYFOURLED: 
                  {
                        LED1 = 1;
                        LED2 = 1;
                        LED4 = 1;
                        LED3 = 1;
//                        DisplayTransmitString("LED 1 ON");
//                        DisplayTransmitString("LED 2 ON");
//                        DisplayTransmitString("LED 3 ON");
//                        DisplayTransmitString("LED 4 ON");
//                        DisplayRestartScreen();
                  }break;
                  case TIMEUPDATE:
                  {
                     
                      yr = TCPbuffer[2];
                      mt = TCPbuffer[3];
                      dy = TCPbuffer[4];
                      hr = TCPbuffer[5];
                      mn = TCPbuffer[6];
                      sc = TCPbuffer[7];
                      wd = TCPbuffer[8];
                      TimeUpdate = true;
                      
                  }break;
                  case RECEIVEPACKET:
                  {
                  
                  }break;
                  case NONELED:            //0
                  default:
                  {
                        LED1 = 0;
                        LED2 = 0;
                        LED4 = 0;
                        LED3 = 0;
//                        DisplaySendClearScreen();
//                        DisplayTransmitString("LED 1 OFF");
//                        DisplayTransmitString("LED 2 OFF");
//                        DisplayTransmitString("LED 3 OFF");
//                        DisplayTransmitString("LED 4 OFF");
//                        DisplayRestartScreen();
                  
                }break;
            }
        }
    }
}