#include "main.h"
#ifdef APPLICATION_OEM
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <stdio.h>
#include <time.h>
#include "onBoardADC.h"
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include "math.h"
#include "readConfig.h"
#include "onBoardRTCC.h"
#include "appOEM.h"
#include "uart.h"
#include "modbus_data_storage.h"
//#include "modbus_client.h"


extern uint8_t mutexresult[8];
extern int lowestCoolerTemp;
extern int highestCoolerTemp;
extern int lowestHeaterTemp;
extern int highestHeaterTemp;
extern int lowestGasPressure;
extern int highestGasPressure;


extern Device_info_t Device_info;
extern Discrete_Inputs_t Discrete_Inputs;
extern Calib_info_t Calib_info;
extern Relay_Output_t Relay_Output;
extern System_Status_t System_Status;
extern Reset_Source_t Reset_Source;
extern Adc_Reading_t Adc_Reading;
extern Mode_Reading_t Mode_Reading;
extern DDS_Reading_t DDS_Reading;
extern ITRIP_Reading_t ITRIP_Reading;
extern DPLL_Reading_t DPLL_Reading;

extern struct timespec currentTime;
//extern melacsSend sendCollection;
#ifdef LOG_OEM

extern LOGDATA logData;
#endif

extern int displayTime;
            
        
        
      
        /*char my_string[13*3]; // each byte takes 2 hex digits + 1 spac
        for(i = 0; i < 12; i++) {
            sprintf(&my_string[i*3], "%02X ", Serial_Instance.receive.buffer[i]); // add space after each byte
        }
        my_string[sizeof(my_string)-1] = '\0';
        DisplayTransmitString(my_string);*/
       
//        sleep(5);
//            pthread_mutex_unlock(&testmutex_test);


//void Display();
////void IntUart5Handler(uint_32 arg);
//THREAD DisplayMain(void *);
//
//
//void DISPLAYThread (){
//    pthread_attr_t attr;
//    pthread_t pid;
//    struct sched_param myNewPriority;
//    
//    pthread_attr_init(&attr);
//    myNewPriority.sched_priority = 3;
//    pthread_attr_setschedparam(&attr, &myNewPriority);
//    pthread_attr_setstacksize(&attr, 1024);             
//
//    if(pthread_create(&pid, &attr, &DisplayMain, 0)!=0)
//    {
//        xprintf("pthread_create = %d\n", errno);
//    }
//
//    pthread_attr_destroy(&attr);    
//    return; 
//}
//THREAD DisplayMain (void *arg)
//{
//    
//    Display();
//}
//void Display()
//{
//    
//    while(1)
//    {
//#ifdef DISPLAY
//            DisplayRestartScreen();
//            DisplayParameterAndIntValue("UartTrylock", (mutexresult[0]));
//            DisplayParameterAndIntValue("Uartlock&Unlock", (mutexresult[1]));
//            //mutexresult[2] = pthread_mutex_trylock(&testmutex_test);
//            
////            while(mutexresult[2] = pthread_mutex_trylock(&testmutex_test)!=0)
////            {
////                
////                LED3 =~ LED3;
////                usleep(100000);
////            }
//            DisplayParameterAndIntValue("DisplayLock", (mutexresult[2]));
//            DisplayParameterAndIntValue("Counter", (mutexresult[3]));
//            DisplayDateTime();
////            DisplayParameterAndFloatValue("Thread 5", (mutexresult[4]));
////            DisplayParameterAndFloatValue("Thread 6", (mutexresult[5]));
////            DisplayParameterAndFloatValue("Thread 7", (mutexresult[6]));
////            DisplayParameterAndFloatValue("Thread 8", (mutexresult[7]));
////            sleep(1);
////            pthread_mutex_unlock(&testmutex_test);
//            sleep(5);
//#endif
//    }
////    {   //MEMLED = ~MEMLED;
////        //DisplayParameterAndIntValue("FW_DATE", Device_info.FW_DATE);            
////       // DisplayParameterAndIntValue("FW_MONTH_DAY", (Device_info.FW_MONTH_DAY >> 8)&0xFF);
////        //DisplayParameterAndIntValue("FW_MONTH_DAY", Device_info.FW_MONTH_DAY & 0xFF);
////        //DisplayParameterAndIntValue("Fw_Version", Device_info.FW_VERSION);
////        //DisplayParameterAndIntValue("PowerUpTimer ", Mode_Reading.POWERUP_COUNTER);
////#ifdef DISPLAY
////            DisplayRestartScreen();
////            DisplayParameterAndFloatValue("AD0", (adcresult[0]*3.3)/4096);
////            DisplayParameterAndFloatValue("AD1", (adcresult[1]*3.3)/4096);   
////            DisplayParameterAndFloatValue("AD2", (adcresult[2]*3.3)/4096);  
////            DisplayParameterAndFloatValue("AD3", (adcresult[3]*3.3)/4096);          
////            DisplayParameterAndFloatValue("AD4", (adcresult[4]*3.3)/4096);
////            DisplayParameterAndFloatValue("AD5", (adcresult[5]*3.3)/4096);
////            DisplayParameterAndFloatValue("AD6", (adcresult[6]*3.3)/4096);
////            DisplayParameterAndFloatValue("AD7", (adcresult[7]*3.3)/4096);
////            DisplayDateTime();
////#endif
////        /*else if(count%2 == 1)
////        {
////            DisplayParameterAndIntValue("IO0", logData.AD0);
////            DisplayParameterAndIntValue("IO1", logData.AD1);   
////            DisplayParameterAndIntValue("IO2", logData.AD2);  
////            DisplayParameterAndIntValue("IO3", logData.AD3);          
////            DisplayParameterAndIntValue("IO4", logData.AD4);
////            DisplayParameterAndIntValue("IO5", logData.AD5);
////            DisplayParameterAndIntValue("IO6", logData.AD6);
////            DisplayParameterAndIntValue("IO7", logData.AD7);
////        
////        }*/
////        
////        //sleep(1);
////        //MEMLED = ~MEMLED;
////        sleep(5);
////    }
//}    
void Display(oemStruct * os)
{
#ifdef DISPLAY
    if(DIO0_IN)
    {   
        os->displayChange = 0;
        if(currentTime.tv_sec < displayTime)
        {
            if((currentTime.tv_sec + 60) > (displayTime + DISPLAY_CHNG_TIME))
            {
                os->displayChange = 1;
            }
        }
        else if(currentTime.tv_sec > (displayTime + DISPLAY_CHNG_TIME))
        {
            os->displayChange = 1;
        }

        if(1 == os->displayChange)
        {
            displayTime = currentTime.tv_sec;
            os->displayPage++;
            if(3 == os->displayPage)
            {
                os->displayPage = 1;
            }
        }

        os->pageChngEn = 0;
    }
    else
    {
        if(adcresult[0] <= 2048)
        {
            os->displayPage = 1;
        }
        else
        {
            os->displayPage = 2;
        }

        os->pageChngEn = 1;
    }

    if(1 == os->displayPage)
    {   DisplayParameterAndIntValue("Key Status", os->keyStatus);            
        DisplayParameterAndIntValue("Heater Celsius", os->tcAvg);
        DisplayParameterAndIntValue("Engine Celsius", os->tempSensor);  
        //DisplayParameterAndIntValue("MaxTopPres", maxTopPressure);
        //DisplayParameterAndIntValue("MinTopPres", minTopPressure);
        DisplayParameterAndIntValue("PressureNow", os->pressAvg);
        DisplayParameterAndIntValue("CirculationPump", os->circulationPump);   
        DisplayParameterAndIntValue("InverterStatus", os->inverterStatus);  
        DisplayParameterAndIntValue("Is_sdcard_ok", os->is_sdcard_ok);          
        DisplayParameterAndIntValue("SD mount", os->sd_mount);
        DisplayParameterAndIntValue("ErrorCode", os->errorCode);
        DisplayDateTime();
        DisplayRestartScreen();
        
    }
    else if(2 == os->displayPage)
    {  

        DisplayParameterAndIntValue("InverterOnCounter", os->inverterOnCounter);
        DisplayParameterAndIntValue("InverterOffCounter", os->inverterOffCounter);             
        DisplayParameterAndIntValue("LogReturn", os->logReturn);
        DisplayParameterAndIntValue("LastLogReturn", os->lastLogReturn); 
        DisplayParameterAndIntValue("lowCoolerTemp", lowestCoolerTemp);
        DisplayParameterAndIntValue("highCoolerTemp", highestCoolerTemp);
        DisplayParameterAndIntValue("lowHeaterTemp", lowestHeaterTemp);
        DisplayParameterAndIntValue("highHeaterTemp", highestHeaterTemp);
        DisplayParameterAndIntValue("lowGasPressure", lowestGasPressure);
        DisplayParameterAndIntValue("highGasPressure", highestGasPressure);
        DisplayRestartScreen();
 
    }
#endif    
}

#endif

