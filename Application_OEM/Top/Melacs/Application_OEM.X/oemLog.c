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
#ifdef LOG_OEM
extern LOGDATA logData;
#endif
void Log(oemStruct * os)
{
#ifdef LOGGING        
   // if(((true == os->is_sdcard_ok) && (1 == os->sd_mount)) && ((1 == os->keyStatus) || (os->tcAvg > 50)))           
    //{
        logData.keyStatus = os->keyStatus;
        logData.circulationPump = os->circulationPump;
        logData.boardTemp = os->boardTemp;
        logData.maxPressure = os->maxTopPressure;
        logData.minPressure = os->minTopPressure;
        logData.pressureNow = os->pressAvg;
        logData.engineTemperature = os->tempSensor;
        logData.heaterTemperature = os->tcAvg;
        logData.releaseValve = os->releaseValve;
        logData.fillValve = os->fillValve;
        logData.error = os->error;
        logData.ErrorCode = os->errorCode;

        //logRun();
        SD_SPI_SetHighSpeed();
        os->logReturn = logRunAvg(SAMPLE_PERIOD, TOTAL_SAMPLES_IN_EACH_LOG);
        if(0 != os->logReturn)
        {
            os->lastLogReturn = os->logReturn;
        }
        logBurst(5, LOGBURST_PERIOD*LOGBURST_COUNTER, NUM_BURST_READS);
   // }
#endif               
}


#endif
