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
#include "sensorValueConversion.h"
#include "appOEM.h"


extern struct timespec currentTime;
extern int burstReadTime;

int getTcAvgValue(int tcTemperature)
{
    static int thermocoupleAvg[AVERAGING_LENGTH_THERMOCOUPLE] = {0};
    static int thermocoupleAvgIndex = 0;

    int tcAvg = 0;
    int i = 0;

    thermocoupleAvg[thermocoupleAvgIndex] = tcTemperature;
    thermocoupleAvgIndex++;


    //Calculate the Average Thermocouple Value
    {
        if(AVERAGING_LENGTH_THERMOCOUPLE == thermocoupleAvgIndex)
        {
            thermocoupleAvgIndex = 0;
        }

        tcAvg = 0;
        for(i = 0; i < AVERAGING_LENGTH_THERMOCOUPLE; i++)
        {
            tcAvg += thermocoupleAvg[i];
        }

        tcAvg = tcAvg/AVERAGING_LENGTH_THERMOCOUPLE;
    }

    return tcAvg;
}

int getPressAvgValue(int pressure)
{
    static int pressureAvg[AVERAGING_LENGTH_PRESSURE] = {0};
    static int pressureAvgIndex = 0;
    int i = 0;
    int pressAvg = 0;
    pressureAvg[pressureAvgIndex] = pressure;
    pressureAvgIndex++;


    //Calculate the Average Pressure Value
    {
        if(AVERAGING_LENGTH_PRESSURE == pressureAvgIndex)
        {
            pressureAvgIndex = 0;
        }

        pressAvg = 0;
        for(i = 0; i < AVERAGING_LENGTH_PRESSURE; i++)
        {
            pressAvg += pressureAvg[i];
        }

        pressAvg = pressAvg/AVERAGING_LENGTH_PRESSURE;
    }
    return pressAvg;
}



void getBurstPressureRead(int *maxTopPressure, int * minTopPressure)
{
    static int maxTopPressureHex = 0;
    static int minTopPressureHex = 4096;

    int pressureAvgBurst[AVERAGING_LENGTH_PRESSURE] = {0};
    int burstRead = 0;
    int pressAvgBurst = 0;
    int pressureAvgBurstIndex = 0;
    int i = 0;
    int j = 0;

    
    burstRead = 0;
    if(currentTime.tv_sec < burstReadTime)
    {
        if((currentTime.tv_sec + 60) > (burstReadTime + BURST_PERIOD))
        {
            burstRead = 1;
        }
    }
    else if(currentTime.tv_sec > (burstReadTime + BURST_PERIOD))
    {
        burstRead = 1;
    }

    if(1 == burstRead)
    {
        maxTopPressureHex = 0;
        minTopPressureHex = 4096;

        SPI_Disable();

        for(j = 0; j < AVERAGING_LENGTH_PRESSURE_BURST; j++)
        {
#ifdef _ONBOARD_ADC_FUNC_
            ReadSignals();
            pressureAvgBurst[pressureAvgBurstIndex] = adcresult[5];
            pressureAvgBurstIndex++;

        }

        if(AVERAGING_LENGTH_PRESSURE_BURST <= pressureAvgBurstIndex)
        {
            pressureAvgBurstIndex = 0;
        }

        for(i = 0; i < DEFAULT_BURST_LEN; i++)
        {
            ReadSignals();

            pressureAvgBurst[pressureAvgBurstIndex] = adcresult[5];
            pressureAvgBurstIndex++;

#endif
            //Calculate the Average Pressure Value
            {
                if(AVERAGING_LENGTH_PRESSURE_BURST <= pressureAvgBurstIndex)
                {
                    pressureAvgBurstIndex = 0;
                }

                pressAvgBurst = 0;
                for(j = 0; j < AVERAGING_LENGTH_PRESSURE_BURST; j++)
                {
                    pressAvgBurst += pressureAvgBurst[j];
                }

                pressAvgBurst = pressAvgBurst/AVERAGING_LENGTH_PRESSURE_BURST;
            }


            if(pressAvgBurst > maxTopPressureHex)
            {
                maxTopPressureHex = pressAvgBurst;
            }

            if(pressAvgBurst < minTopPressureHex)
            {
                minTopPressureHex = pressAvgBurst;
            }

            //DelayUs(1); //Put the delay needed, if any
        }

        SPI_Enable();

        burstReadTime = currentTime.tv_sec;
    }

    *maxTopPressure = getMLH060BGB01AhexToBar(maxTopPressureHex);
    *minTopPressure = getMLH060BGB01AhexToBar(minTopPressureHex);
}

bool getKeyStatus(int keyValue)
{
    static int keyAvg[AVERAGING_LENGTH_KEY] = {0};
    static int keyAvgIndex = 0;
    int i = 0;
    int keyAvgValue = 0;
    keyAvg[keyAvgIndex] = keyValue;
    keyAvgIndex++;

    //Calculate the Average Pressure Value
    {
        if(AVERAGING_LENGTH_KEY == keyAvgIndex)
        {
            keyAvgIndex = 0;
        }

        keyAvgValue = 0;
        for(i = 0; i < AVERAGING_LENGTH_KEY; i++)
        {
            keyAvgValue += keyAvg[i];
        }
    }

    if(keyAvgValue > AVG_KEY_MAX)
    {
        return false; //Key Status
    }
    else if(keyAvgValue < AVG_KEY_MIN)
    {
        return false; //Key Status
    }
        return true; //Key Status
}


#endif
