/*
 * File:   speedControl.h
 * Author: Bala
 *
 * Created on November 9, 2015, 1:59 PM
 */

#ifndef THREE_WAYVALVE_H
#define	THREE_WAYVALVE_H

#ifdef	__cplusplus
extern "C" {
#endif

int getTimeDifferenceSec(int currentSec, int lastSec);
long getTimeDifferenceNano(long currentNano, long lastNano);
int valvePosition(int percent);

#ifdef	__cplusplus
}
#endif

#endif	/* THREE_WAYVALVE_H */

