#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _THREEWAYVALVE_FUNC_
#include <stdio.h>
#include "speedControl.h"
#include "pinDefines.h"
#include "onBoardADC.h"
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include <time.h>
#include "timeDifference.h"

extern struct timespec currentTime;

int timeToMove100 = 4000;
int timeToMove1 = 400;
int currentPositionValve = 0;

int valvePosition(int percent)
{
    static int lastPostionSeconds = 0;
    static int lastPostionNanoseconds = 0; 
    static int direction = 2;
    float timeDifference = 0;
    static int lastStaticPostion = 0;
    int numPositions = 0;
    
    if(currentPositionValve > percent)
    {
        if(direction != 0)
        {
            lastPostionSeconds = currentTime.tv_sec;
            lastPostionNanoseconds = currentTime.tv_nsec;   
            lastStaticPostion = currentPositionValve;            
        }
        direction = 0;  
        
        timeDifference = 1000*getTimeDifferenceSec(currentTime.tv_sec,lastPostionSeconds) + getTimeDifferenceNano(currentTime.tv_nsec,lastPostionNanoseconds)/1000000;
        numPositions = timeDifference/timeToMove1;
        currentPositionValve = lastStaticPostion - numPositions;
        
        LAT_SIP4 = 1;
        LAT_SIP5 = 0; 
    }
    else if(currentPositionValve < percent)
    {
        if(direction != 1)
        {
            lastPostionSeconds = currentTime.tv_sec;
            lastPostionNanoseconds = currentTime.tv_nsec;  
            lastStaticPostion = currentPositionValve;
        }   

        direction = 1;
        timeDifference = 1000*getTimeDifferenceSec(currentTime.tv_sec,lastPostionSeconds) + getTimeDifferenceNano(currentTime.tv_nsec,lastPostionNanoseconds)/1000000;
        numPositions = timeDifference/timeToMove1;        
        currentPositionValve  = lastStaticPostion + numPositions;    
        LAT_SIP4 = 0;
        LAT_SIP5 = 1;         
    }
    else
    {
        lastStaticPostion = currentPositionValve;
        LAT_SIP4 = 0;
        LAT_SIP5 = 0; 
        direction = 2;
    }
    
    if(0 == percent)
    {
        lastStaticPostion = 0;
        currentPositionValve = 0;
        LAT_SIP4 = 1;
        LAT_SIP5 = 0; 
        direction = 2;
    }    
    
    if(9 < percent)
    {
        lastStaticPostion = 10;
        currentPositionValve = 10;
        LAT_SIP4 = 0;
        LAT_SIP5 = 1;
        direction = 2;                
    }
    
    return currentPositionValve;
}

#endif