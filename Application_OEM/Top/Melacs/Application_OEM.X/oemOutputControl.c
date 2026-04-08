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


void OutputControl(oemStruct * os)
{
        if(1 == os->error)
        {
            os->enableHeater = 0;
        }
                
//        LAT_SIP0 = os->releaseValve;        
//        LAT_SIP1 = os->circulationPump;
////        LAT_SIP2 = os->inverterStatus;
//        LAT_SIP3 = os->fillValve;
//
//        LAT_SIP4 = os->enableHeater;
        
        if(1 == os->enableHeater)
        {
            SetDCOC1PWM(0x2FFF);
        }
        else
        {
            SetDCOC1PWM(0); 
        }
                
        
        LAT_DIO4 = os->enableHeater;
        LAT_DIO5 = os->error;
        LAT_DIO6 = os->fillValve;
        LAT_DIO7 = os->releaseValve;
}
        
#endif
