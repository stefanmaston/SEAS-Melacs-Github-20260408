#include "main.h"
#ifdef APPLICATION_OEM
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "onBoardADC.h"
#include <pthread.h>
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include "math.h"
#include "readConfig.h"
#include "onBoardRTCC.h"
#include "appOEM.h"
#include "sensors.h"
#include <pthread.h>


extern int lowestCoolerTemp;
extern int highestCoolerTemp;
extern int lowestHeaterTemp;
extern int highestHeaterTemp;
extern int lowestGasPressure;
extern int highestGasPressure;
extern bool TimeUpdate;
void ReadAdAndRTC()
{
    SPI_Disable();
#ifdef _ONBOARD_ADC_FUNC_ 
    ReadSignals();
#endif
#ifdef RTC
    if(TimeUpdate)
    {
        RTC_Write_Clock();
        TimeUpdate = false;
    }
    else
      RTC_Read_Clock();   
#endif   
   
    SPI_Enable();
 
}

void GetInputValues(oemStruct * os)
{
    
    if(DIO1_IN)
    {
        os->sd_mount = 0;
    }
    else
    {
        os->sd_mount = 1;
    }         
#ifdef _ONBOARD_ADC_FUNC_    
    os->pressureTop = getPressureTop();
    os->tempSensor = getEngineTemperature();
    os->tempThermoC = getThermocoupleTemp();
#endif
    os->lastTcAvg = os->tcAvg;
    os->tcAvg = getTcAvgValue(os->tempThermoC);
    os->pressAvg = getPressAvgValue(os->pressureTop);
    os->keyStatus = getKeyStatus(DIO2_IN);
    //getBurstPressureRead(&os->maxTopPressure, &os->minTopPressure);
    os->boardTemp = getBoardTemperature();              
}

void SensorCheck(oemStruct * os)
{
    if(os->tempSensor < lowestCoolerTemp)
    {
        os->error = 1;
        os->errorCode = 2;
    }
    else
    {
        if(2 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }

    if(os->tempSensor > highestCoolerTemp)
    {
        os->error = 1;
        os->errorCode = 3;
    }
    else
    {
        if(3 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }

    if(os->tcAvg < lowestHeaterTemp)
    {
        os->error = 1;
        os->errorCode = 6;
    }
    else
    {
        if(6 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }

    if(os->tcAvg > highestHeaterTemp)
    {
        os->error = 1;
        os->errorCode = 7;
    }
    else
    {
        if(7 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }

    if(os->pressAvg < lowestGasPressure)
    {
        os->error = 1;
        os->errorCode = 8;
    }
    else
    {
        if(8 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }

    if(os->pressAvg > highestGasPressure)
    {
        os->error = 1;
        os->errorCode = 9;
    }
    else
    {
        if(9 == os->errorCode)
        {
            os->error = 0;
            os->errorCode = 0;                
        }
    }    
}

void Inputs(oemStruct * os)
{   
    
    ReadAdAndRTC();
   
    GetInputValues(os);

    SensorCheck(os);
}

#endif
