/*
 * File:   speedControl.h
 * Author: Bala
 *
 * Created on November 9, 2015, 1:59 PM
 */

#ifndef SPEEDCONTROL_H
#define	SPEEDCONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

void hBridgeInit();
void setJP18volt(float voltage);
void setJP19volt(float voltage);
bool isJP18currentOkay();
void setJP18volt_CurrentLimiter(float voltage, int direction);
bool isJP19currentOkay();
void setJP19volt_CurrentLimiter(float voltage,int direction);

#ifdef	__cplusplus
}
#endif

#endif	/* SPEEDCONTROL_H */

