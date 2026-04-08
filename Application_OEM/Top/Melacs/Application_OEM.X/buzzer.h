/* 
 * File:   buzzer.h
 * Author: Bala
 *
 * Created on June 29, 2015, 11:47 AM
 */

#ifndef BUZZER_H
#define	BUZZER_H

#ifdef	__cplusplus
extern "C" {
#endif

void buzzerInit();
void buzzerOn();
void buzzerOnTimer(int usecond);
void buzzerOff();

#ifdef	__cplusplus
}
#endif

#endif	/* BUZZER_H */

