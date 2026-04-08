/*
 *  File name: App_SM.h
 *
 *  Description: High level function declarations for Main State Machine processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_SM_H
#define APP_SM_H

extern bool	Sys_Reloaded;
extern bool	Sys_Reset;
extern bool	Sys_Calib;
extern bool	Sys_Shutdown;
extern const uint16_t	Sys_HW_Info;
extern const uint16_t	Sys_FW_Version;
extern const uint16_t	Sys_FW_Date_Year;
extern const uint16_t	Sys_FW_Date_Month_and_Day;

extern volatile uint8_t	App_SM_System_Mode;
extern volatile uint8_t	SMRecState;

void App_SM_Init(void *Parameters);
void App_SM_Process(void *Parameters);
void App_SM_Status_Get(uint8_t *State, uint8_t *Error, uint16_t *TimeStamp_ms, uint32_t *TimeStamp_s);
#endif // APP_SM_H
