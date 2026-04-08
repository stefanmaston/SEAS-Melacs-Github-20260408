/*
 *  File name: App_TempSens.h
 *
 *  Description: High level function declarations for Temperature Sensors processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_TEMP_SENS_H
#define APP_TEMP_SENS_H

extern volatile int16_t TempSens_T_Ch1;
extern volatile int16_t TempSens_T_Ch2;
extern volatile int16_t TempSens_T_Ch3;

extern volatile uint32_t TempSens_R_Ch1;
extern volatile uint32_t TempSens_R_Ch2;
extern volatile uint32_t TempSens_R_Ch3;

extern volatile uint8_t TempSens_State[];

void App_TempSens_Init(void *Parameters);
void App_TempSens_Process(void *Parameters);

#endif // APP_TEMP_SENS_H
