#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _BUZZER_FUNC_

#include <plib.h>
#include "delay.h"
#include "pinDefines.h"
#include "buzzer.h"

void buzzerInit()
{
    TRIS_BUZZER = 0;
    LAT_BUZZER = 0;
    
}

void buzzerOn()
{
    LAT_BUZZER = 1;
}

void buzzerOnTimer(int usecond)
{
    LAT_BUZZER = 1;
    DelayUs(usecond);
    LAT_BUZZER = 0;
}

void buzzerOff()
{
    LAT_BUZZER = 0;
}

#endif
