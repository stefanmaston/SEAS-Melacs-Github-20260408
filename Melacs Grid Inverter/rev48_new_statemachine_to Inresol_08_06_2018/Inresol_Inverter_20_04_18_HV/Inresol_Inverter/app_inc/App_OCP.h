/*
 *  File name: App_OCP.h
 *
 *  Description: High level function declarations for Over Current Protection processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_OCP_H
#define APP_OCP_H

extern volatile uint16_t App_OCP_ITrip_Inv;
extern volatile uint16_t App_OCP_ITrip_Grid;
extern volatile uint8_t	 App_OCP_OC_Status;

void App_OCP_Init(void *Parameters);
inline void App_OCP_Process(void);

inline uint16_t App_OCP_Get_Sample_Scaled_Ch1(void);
inline uint16_t App_OCP_Get_Sample_Scaled_Ch2(void);
uint16_t App_OCP_Get_Sample_Scaled(uint8_t Channel);

#endif // APP_OCP_H
