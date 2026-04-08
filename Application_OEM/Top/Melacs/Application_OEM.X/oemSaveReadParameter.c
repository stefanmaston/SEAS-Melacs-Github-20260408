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


extern char variableNames[NUM_OF_PARAMETERS][LENGTH_VARIABLE_NAME];
extern char variableValues[NUM_OF_PARAMETERS][LENGTH_VARIABLE_VALUES];
extern int writeConfig(char * filename);

extern int lowestCoolerTemp;
extern int highestCoolerTemp;
extern int lowestHeaterTemp;
extern int highestHeaterTemp;
extern int lowestGasPressure;
extern int highestGasPressure;


void getParameters()
{
    int lowestCoolerTemp_ = 0;
    int highestCoolerTemp_ = 0;
    int lowestHeaterTemp_ = 0;
    int highestHeaterTemp_ = 0;
    int lowestGasPressure_ = 0;
    int highestGasPressure_ = 0;
    int writeDate = 0;

    if(0 == strcmp(variableNames[8],"lowest_cooler_temp"))
    {
        lowestCoolerTemp_ = atoi(variableValues[8]);
        if((lowestCoolerTemp_ > 0) && (lowestCoolerTemp_ < 30))
        {
            lowestCoolerTemp = lowestCoolerTemp_;
        }
    }
    else
    {
        return;
    }

    if(0 == strcmp(variableNames[9],"highest_cooler_temp"))
    {
        highestCoolerTemp_ = atoi(variableValues[9]);
        if((highestCoolerTemp_  > 0) && (highestCoolerTemp_ < 100))
        {
            highestCoolerTemp = highestCoolerTemp_;
        }
    }
    else
    {
        return;
    }
    
    if(0 == strcmp(variableNames[10],"lowest_heater_temp"))
    {
        lowestHeaterTemp_ = atoi(variableValues[10]);
        if((lowestHeaterTemp_ >= 0) && (lowestHeaterTemp_ < 1000))
        {
            lowestHeaterTemp = lowestHeaterTemp_;
        }
    }
    else
    {
        return;
    }
    
    if(0 == strcmp(variableNames[11],"highest_heater_temp"))
    {
        highestHeaterTemp_ = atoi(variableValues[11]);
        if((highestHeaterTemp_ >= 0) && (highestHeaterTemp_ < 1200))
        {
            highestHeaterTemp = highestHeaterTemp_;
        }
    }
    else
    {
        return;
    }

    if(0 == strcmp(variableNames[12],"lowest_gas_pressure"))
    {
        lowestGasPressure_ = atoi(variableValues[12]);
        if((lowestGasPressure_ > 0) && (lowestGasPressure_ < 40))
        {
            lowestGasPressure = lowestGasPressure_;
        }
    }
    else
    {
        return;
    }

    if(0 == strcmp(variableNames[13],"highest_gas_pressure"))
    {
        highestGasPressure_ = atoi(variableValues[13]);
        if((highestGasPressure_ > 0) && (highestGasPressure_ < 60))
        {
            highestGasPressure = highestGasPressure_;
        }
    }
    else
    {
        return;
    }

    if(0 == strcmp(variableNames[0],"Write_Date"))
    {
        writeDate = atoi(variableValues[0]);
        if(1 == writeDate)
        {
           
            yr = atoi(variableValues[1]);
            mt = atoi(variableValues[2]);
            dy = atoi(variableValues[3]);
            hr = atoi(variableValues[4]);
            mn = atoi(variableValues[5]);
            sc = atoi(variableValues[6]);
            wd = atoi(variableValues[7]);

            SPI_Disable();
            RTC_Write_Clock();
            SPI_Enable();
            
            strcpy(variableValues[0],"0"); 
            //Set Write_Date to 0 for Next time
            writeConfig("/dev/sd/d1/oem_parameters.txt");            
        }
    }


}



int readParametersFromFile(melacsReceive * recvCollection)
{
    return -1;
}

int saveParametersToFile(melacsReceive * recvCollection)
{
    return -1;
}
#endif
