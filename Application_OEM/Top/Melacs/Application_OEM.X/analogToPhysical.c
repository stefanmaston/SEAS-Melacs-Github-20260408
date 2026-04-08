#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _ANALOG_TO_PHYSICAL_FUNC_
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "onBoardADC.h"
#include <pthread.h>
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include "math.h"
#include "threeWayValve.h"
#include "hBridge.h"


float convertHexToVolt(int hex)
{
    float conv;
    conv = (hex * 3.3 / 1023);
    return conv;
}


#endif