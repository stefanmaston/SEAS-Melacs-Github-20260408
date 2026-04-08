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
#include "sys/mount.h"

void CheckAndDoShutdown(melacsReceive * recvCollection, melacsSend * sendCollection)
{    
    if(1 == recvCollection->variable_Shutdown)
    {

        umount(FATFS_MOUNT);  

#ifdef DISPLAY            
        DisplayTransmitString("Shut Down..............");      
        DisplayTransmitString("Safe to Switch Off.....");   
        DisplayTransmitString("                       ");     
        DisplayTransmitString("                       ");    
        DisplayTransmitString("                       ");    
        DisplayTransmitString("                       ");    
        DisplayTransmitString("                       ");    
        DisplayTransmitString("                       ");    
        DisplayTransmitString("                       ");  
        DisplayTransmitString("                       ");                
#endif      
        sendCollection->variable_SystemStatus = 0;
        writeToUsbSendBuffer(sendCollection);    
        while(1)
        {
            ClearWDT(); 
        }
        return;
    }
    

}

void ExecuteReceivedCommands(oemStruct * os, melacsReceive * recvCollection, melacsSend * sendCollection)
{
        
    if((1 == recvCollection->variable_SaveParameterFile) && (true == os->is_sdcard_ok) && (1 == recvCollection->variable_SDCardMount))
    {
        os->returnVal = saveParametersToFile(recvCollection);          
        recvCollection->variable_SaveParameterFile = 0;
    }

    if(1 == recvCollection->variable_ResetErrorAndWarnings)
    {
        os->error = 0;
        os->warning = 0;
        os->errorCode = 0;   
        recvCollection->variable_ResetErrorAndWarnings = 0;
    }

    if(1 == recvCollection->variable_SynTime)
    {
        yr = recvCollection->variable_Year;
        mt = recvCollection->variable_Month;
        dy = recvCollection->variable_Day;
        hr = recvCollection->variable_Hour;
        mn = recvCollection->variable_Minute;
        sc = recvCollection->variable_Second;
        wd = recvCollection->variable_Weekday;

        SPI_Disable();
        RTC_Write_Clock();
        SPI_Enable(); 

        recvCollection->variable_SynTime = 0;
    }
    
    CheckAndDoShutdown(recvCollection, sendCollection);    
}      

void InverterStatusCalc(oemStruct * os)
{
    if((os->tcAvg > 600) && (0 == os->inverterStatus)) //The tcAvg value should be for more that 3 seconds
    {
        os->inverterOnCounter++;
        if(os->inverterOnCounter >= INV_CTR_THRESHOLD)
        {
            os->inverterOnCounter = INV_CTR_THRESHOLD;
        }
        os->inverterOffCounter = 0;
    }

    if((os->tcAvg < 500) && (1 == os->inverterStatus))
    {
        os->inverterOffCounter++;
        if(os->inverterOffCounter >= INV_CTR_THRESHOLD)
        {
            os->inverterOffCounter = INV_CTR_THRESHOLD;
        }
        os->inverterOnCounter = 0;
    }

    if(os->inverterOnCounter >= INV_CTR_THRESHOLD)
    {
        os->inverterStatus = 1;

    }

    if(os->inverterOffCounter >= INV_CTR_THRESHOLD)
    {
        os->inverterStatus = 0;
    }    
}

void CirculationPumpCalc(oemStruct * os)
{
    os->circulationPump = 1;    
}

void SystemRegulation(oemStruct * os)
{    
    InverterStatusCalc(os);
    CirculationPumpCalc(os);    
}
  



#endif
