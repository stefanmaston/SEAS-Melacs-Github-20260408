/*
 *  File name: App_PWM.h
 *
 *  Description: High level function declarations for PWM processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_PWM_H
#define APP_PWM_H
void App_PWM_Init(void *Parameters);
inline void App_PWM_Process_IRQ(void);
void App_PWM_Process_IDLE(void *Parameters);
void App_PWM_All_IGBTs_Off(bool all_channels);
void App_PWM_All_IGBTs_On(bool all_channels);

#endif // APP_PWM_H
