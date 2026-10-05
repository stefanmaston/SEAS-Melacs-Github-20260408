#ifndef PLAT_HOST_H
#define PLAT_HOST_H

#include "rtc.h"

void plat_host_clock_step(const RtcClock *start);
void plat_host_clock_wall(void);
int plat_host_beep_count(void);

#endif
