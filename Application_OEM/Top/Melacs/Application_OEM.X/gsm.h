/* 
 * File:   GSM.h
 * Author: Bala
 *
 * Created on February 24, 2015, 4:16 PM
 */

#ifndef GSM_H
#define	GSM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
    
void GSM_init();
void GSM_deinit();
void GSM_send();

typedef struct
{ 
    bool statusKey;
    bool compressorStatus; 
    bool fillPressureStatus;  
    bool ignitorStatus; 
    bool inverterStatus;    
    int heaterTemperature; 
    int engineTemperature;
    float enginePressure;
    int radiatorFanPercentage; 
    int burnerFanPercentage; 
    int boardTemperature;
    float voltage3V3;
    float voltage5V;
    float voltage12V;
    float voltage24V;
    int alarmCode;
    int timeIncrement;
} gsmSend;

#ifdef	__cplusplus
}
#endif

#endif	/* GSM_H */

