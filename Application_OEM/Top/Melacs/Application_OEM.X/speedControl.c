#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _SPEED_CONTROL_FUNC_
#include "speedControl.h"
#include "pinDefines.h"
#include "onBoardADC.h"
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"


void set_jp7(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay)
{
    int i = 0;
    int timeOn = 0;
    int timeOff = 0;

    if(0 == percent)
    {
        TRIS_SIP4 = 0;
        LAT_SIP4 = 0;
        return;
    }
    else if (100 == percent)
    {
        TRIS_SIP4 = 0;
        LAT_SIP4 = 1;
        return;
    }

    timeOn = percent;
    timeOff = 100 - percent;
    timeOff = timeOff;

    TRIS_SIP4 = 0;
    for(i = 0; i < num_iterations; i++)
    {
        LAT_SIP4 = 1;
        //DelayUs(timeOn*time_on_factor);
        DelayUs(time_on_factor);
        LAT_SIP4 = 0;
        DelayUs(time_off_factor);
    }
    DelayUs(end_delay);
    TRIS_SIP4 = 1;
}

void set_jp8(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay)
{
    int i = 0;
    int timeOn = 0;
    int timeOff = 0;

    if(0 == percent)
    {
        TRIS_SIP5 = 0;
        LAT_SIP5 = 0;
        return;
    }
    else if (100 == percent)
    {
        TRIS_SIP5 = 0;
        LAT_SIP5 = 1;
        return;
    }

    timeOn = percent;
    timeOff = 100 - percent;
    timeOff = timeOff;

    TRIS_SIP5 = 0;
    for(i = 0; i < num_iterations; i++)
    {
        LAT_SIP5 = 1;
        //DelayUs(timeOn*time_on_factor);
        DelayUs(time_on_factor);
        LAT_SIP5 = 0;
        DelayUs(time_off_factor);
    }
    DelayUs(end_delay);
    TRIS_SIP5 = 1;
}

void set_jp9(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay)
{
    int i = 0;
    int timeOn = 0;
    int timeOff = 0;

    if(0 == percent)
    {
        TRIS_SIP6 = 0;
        LAT_SIP6 = 0;
        return;
    }
    else if (100 == percent)
    {
        TRIS_SIP6 = 0;
        LAT_SIP6 = 1;
        return;
    }

    timeOn = percent;
    timeOff = 100 - percent;
    timeOff = timeOff;

    TRIS_SIP6 = 0;
    for(i = 0; i < num_iterations; i++)
    {
        LAT_SIP6 = 1;
        //DelayUs(timeOn*time_on_factor);
        DelayUs(time_on_factor);
        LAT_SIP6 = 0;
        DelayUs(time_off_factor);
    }
    DelayUs(end_delay);
    TRIS_SIP6 = 1;
}


void set_jp10_(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay)
{
    int i = 0;
    int timeOn = 0;
    int timeOff = 0;

    if(0 == percent)
    {
        TRIS_SIP7 = 0;
        LAT_SIP7 = 0;
        return;
    }
    else if (100 == percent)
    {
        TRIS_SIP7 = 0;
        LAT_SIP7 = 1;
        return;
    }

    TRIS_SIP7 = 0;
    for(i = 0; i < num_iterations; i++)
    {
        LAT_SIP7 = 1;
        //DelayUs(timeOn*time_on_factor);
        DelayUs(time_on_factor);
        LAT_SIP7 = 0;
        DelayUs(time_off_factor);
    }
    DelayUs(end_delay);
    TRIS_SIP7 = 1;
}


void set_jp10(int percent, int time_on_factor, int time_off_factor, int num_iterations, int end_delay)
{
    int i = 0;
    int timeOn = 0;
    int timeOff = 0;

    timeOn = percent;
    timeOff = 100 - percent;

    TRIS_SIP7 = 0;
    for(i = 0; i < 100; i++)
    {
        LAT_SIP7 = 1;
        DelayUs(timeOn);
        LAT_SIP7 = 0;
        DelayUs(timeOff);
    }

    TRIS_SIP7 = 1;
}


#endif