#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _TIME_DIFFERENCE_FUNC_

#include <plib.h>
#include <stdio.h>
#include <time.h>

#include "timeDifference.h"

int getTimeDifferenceSec(int currentSec, int lastSec)
{
    if(currentSec < lastSec)
        return (60 + lastSec) - currentSec;
    else
        return currentSec - lastSec;
}

long getTimeDifferenceNano(long currentNano, long lastNano)
{
    if(currentNano < lastNano)
        return (1000000000 + lastNano) - currentNano;
    else
        return currentNano - lastNano;
}


//https://gist.github.com/diabloneo/9619917
void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}

#endif