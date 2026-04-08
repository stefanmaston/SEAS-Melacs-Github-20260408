#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "delay.h"

Timer_t Timer_Reset(void) 
{
     return ReadCoreTimer(); //Timer Reset
}

int32_t Timer_GetMS(Timer_t *timer) 
{
      return (ReadCoreTimer() - *timer) / ( GetSystemClock() / 2000); // Millisecond delay
}
int32_t Timer_GetUS(Timer_t *timer) 
{
     return (ReadCoreTimer() - *timer) / ( GetSystemClock() / 2000000); // Microsecond delay
}

int32_t Timer_AfterTick(Timer_t *timer)
{   

}
