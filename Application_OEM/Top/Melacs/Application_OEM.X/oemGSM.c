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

void Gsm(oemStruct * os)
{
#ifdef GSM
    BoardSpiChannelInit(
            SPI_CONFIG_MSTEN |
            SPI_CONFIG_MODE8 |
            SPI_CONFIG_SMP_END |
            SPI_CONFIG_ON,
            400000
            );
    GSM_send();
    BoardSpiChannelDeinit();        
#endif
}   


#endif
