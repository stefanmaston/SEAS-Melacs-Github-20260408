/*
 *  File name: BSP_Timer.h
 *
 *  Description: Board Support Package function declarations for Timer processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_TIMER_H
#define BSP_TIMER_H

void BSP_Timer_1_Open(uint16_t Config, uint16_t Period);
void BSP_Timer_1_Close(void);
inline void BSP_Timer_1_Start(void);
inline void BSP_Timer_1_Stop(void);
inline void BSP_Timer_1_Set_Period(uint16_t Period);
inline void BSP_Timer_1_Set_Timer(uint16_t Timer);
inline uint16_t BSP_Timer_1_Get_Timer(void);
inline void BSP_Timer_1_Interrupt_Clear(void);
inline void BSP_Timer_1_Interrupt_Enable(void);
inline void BSP_Timer_1_Interrupt_Disable(void);
inline void BSP_Timer_1_Interrupt_Priority(uint8_t Priority);

void BSP_Timer_23_Open(uint16_t Config, uint32_t Period);
void BSP_Timer_23_Close(void);
inline void BSP_Timer_23_Start(void);
inline void BSP_Timer_23_Stop(void);
inline void BSP_Timer_23_Set_Period(uint32_t Period);
inline void BSP_Timer_23_Set_Timer(uint32_t Timer);
inline uint32_t BSP_Timer_23_Get_Timer(void);
inline void BSP_Timer_23_Interrupt_Clear(void);
inline void BSP_Timer_23_Interrupt_Enable(void);
inline void BSP_Timer_23_Interrupt_Disable(void);
inline void BSP_Timer_23_Interrupt_Priority(uint8_t Priority);

#endif	// BSP_TIMER_H
