/*
 * File:   speedControl.h
 * Author: Bala
 *
 * Created on November 9, 2015, 1:59 PM
 */

#ifndef TIMEDIFFERENCE_H
#define	TIMEDIFFERENCE_H

#ifdef	__cplusplus
extern "C" {
#endif

int getTimeDifferenceSec(int currentSec, int lastSec);
long getTimeDifferenceNano(long currentNano, long lastNano);
void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result);

#ifdef	__cplusplus
}
#endif

#endif	/* SPEEDCONTROL_H */

