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
#include "alarmCode.h"
#include "uart.h"
#include <sys.h>
#include "modbus_client.h"
//
extern Serial_Instance_t Serial_Instance;
/*
extern const uint16_t hexTemperatureNTC[25];
extern const int8_t temperatureNTC[25];

extern const uint16_t hexThermocouple[68];
extern const uint16_t tempThermocouple[68];
 */

extern const float hexTempConst;

struct timespec currentTime;

melacsSend sendCollection;
melacsReceive recvCollection;    
oemStruct os;

int lowestCoolerTemp = 5;
int highestCoolerTemp = 95;
int lowestHeaterTemp = 0;
int highestHeaterTemp = 1050;
int lowestGasPressure = 6;
int highestGasPressure = 50;

int displayTime = 0;
int burstReadTime = 0;
int fuelFeedTime = 0;
int FeederTime = 0;

void pinInit()
{

    CNEN = 28; //Weak Pull up on CN2, CN3, CN4
    AD1PCFG = 0xffff; //Make all port B pin as digital
    
//    TRIS_SIP0 = 0;
//    LAT_SIP0 = 0;
//
//    TRIS_SIP1 = 0;
//    LAT_SIP1 = 0;
//
//    //TRIS_SIP2 = 0;
//    //LAT_SIP2 = 0;
//
//    TRIS_SIP3 = 0;
//    LAT_SIP3 = 0;
//
//    TRIS_SIP4 = 0;
//    LAT_SIP4 = 0;

    TRIS_DIO0 = 1;
    TRIS_DIO1 = 1;
    TRIS_DIO2 = 1;
    TRIS_DIO3 = 1;
    TRIS_DIO4 = 0;
    TRIS_DIO5 = 0;
    TRIS_DIO6 = 0;
    TRIS_DIO7 = 0;

    //M1DIS to enable HBridge
    TRIS_M1DIS = 0;
    LAT_M1DIS = 0;

    //Set M1AHI as output
    TRIS_M1AHI = 0;
    LAT_M1AHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1ALI = 0;
    LAT_M1ALI = 0;

    //Set M1AHI as output and to low
    TRIS_M1BHI = 0;
    LAT_M1BHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1BLI = 0;
    LAT_M1BLI = 1;

    //M2DIS to enable HBridge
    TRIS_M2DIS = 0;
    LAT_M2DIS = 0;

    //Set M2BHI as output
    TRIS_M2AHI = 0;
    LAT_M2AHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2ALI = 0;
    LAT_M2ALI = 0;

    //Set M2BHI as output and to low
    TRIS_M2BHI = 0;
    LAT_M2BHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2BLI = 0;
    LAT_M2BLI = 1;
}

void AppInit()
{
    //Melacs_Init();
    pinInit();

    OpenOC1( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenOC3( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenTimer2( T2_ON | T2_PS_1_1 | T2_SOURCE_INT, 0x2FFF);
    
    readConfig("/dev/sd/d1/oem_parameters.txt");
    getParameters();
    
    clock_gettime(CLOCK_REALTIME, &currentTime);
    xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);

    displayTime = currentTime.tv_sec;
    burstReadTime = currentTime.tv_sec;
}

THREAD USBMain(void *);

void EscapeToOtherThreads()
{
    //somehow the below code causes the speed control to run on time    
    int i = 128;
    do
    {
        usleep(1);
    }
    while(--i);        
}
void forkUSBThread()
{
    
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
    
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 1;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 2048);

    SPI_Enable();        
    SD_SPI_SetHighSpeed();                

    if(pthread_create(&pid, &attr, &USBMain, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return;    
}

void initOemStruct(oemStruct * os)
{
    os->pressureTop = 0.0;
    os->tempSensor = 0.0;
    os->tempThermoC = 0.0;
    os->displayPage = 1;

    os->tcAvg = 0;
    os->lastTcAvg = 0;
    os->pressAvg = 0;
    os->maxTopPressure = 0;
    os->minTopPressure = 0;

    os->displayChange = 0;
    os->pageChngEn = 0;
    os->circulationPump = 0;
    os->keyStatus = 0;
    os->boardTemp = 0;

    os->logReturn = 0;
    os->lastLogReturn = 0;

    os->inverterStatus = 0;
    os->inverterOnCounter = 0;
    os->inverterOffCounter = 0;

    os->releaseValve = 0;
    os->fillValve = 0;
    os->enableHeater = 0;
    os->sd_mount = 0;
    os->error = 0;
    os->errorCode = 0;
}

//Function for OEM system
void Application(bool is_sdcard_ok_)
{
    
    initOemStruct(&os); 
    uint8_t test = 0;
    os.is_sdcard_ok = is_sdcard_ok_;  

    if(-2 == initMelacsRecv(&recvCollection))
    {
        os.errorCode = ERROR_SD_CORRUPTION;  
        os.warning = 1;        
    }

    initMelacsSend(&sendCollection);      
    writeToUsbSendBuffer(&sendCollection);      

    xprintf("ApplicationGeneral1!\n");
    
    forkUSBThread();    
//#ifdef DISPLAY
//    DISPLAYThread();
//#endif

//    #ifdef _ETHERNET_
//    ServerMain();
//    #endif
    AppInit();
#ifdef _ETHERNET_
    ETHERThread();
#endif
    #ifdef _QUEUE_
    QueueMain();
    #endif
    OemMainRun();
}

#endif
