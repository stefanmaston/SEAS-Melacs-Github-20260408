/*
 *  File name: BSP_PWM.h
 *
 *  Description: Board Support Package function declarations for PWM processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_PWM_H
#define BSP_PWM_H

extern volatile uint8_t	BSP_PWM_Trigger_Sync;

void BSP_PWM_Core_Enable(void);
void BSP_PWM_Core_Disable(void);
void BSP_PWM_Core_Init(void);
void BSP_PWM_Set_TimeBase(unsigned char TimeBase_Source, unsigned long Freq_Hz);
void BSP_PWM_Channel_Init(char Channel, unsigned char Pins_Enable, unsigned char Pins_Polarity, unsigned char Pins_Mode, unsigned char Dead_Time_Mode);
void BSP_PWM_Channel_Set_DeadTime(char Channel, unsigned long Rising_Edge_Dead_Time, unsigned long Falling_Edge_Dead_Time);
//void BSP_PWM_Channel_Set_Trigger(char Channel, unsigned long Location, unsigned char Cycle, unsigned char Start);
void BSP_PWM_Channel_Set_Trigger(char Channel, unsigned long First_Location, unsigned long Second_Location, unsigned char Cycle, unsigned char Start, unsigned char Int_Enable);
void BSP_PWM_Channel_Set_DutyCycle(char Channel, uint16_t Duty_Cycle);
void BSP_PWM_Channel_Off_Outputs(char Channel, unsigned char Pins_Enable, unsigned char Pins_Polarity);
void BSP_PWM_Channel_On_Outputs(char Channel, unsigned char Pins_Enable);
void BSP_PWM_Interrupt_Enable(char Channel, unsigned char Level);

inline void BSP_PWM_Channel_1_Set_DutyCycle(uint16_t Duty_Cycle);
inline void BSP_PWM_Channel_2_Set_DutyCycle(uint16_t Duty_Cycle);
inline void BSP_PWM_Channel_3_Set_DutyCycle(uint16_t Duty_Cycle);
inline void BSP_PWM_Channel_4_Set_DutyCycle(uint16_t Duty_Cycle);
inline void BSP_PWM_Channel_5_Set_DutyCycle(uint16_t Duty_Cycle);
inline void BSP_PWM_Channel_6_Set_DutyCycle(uint16_t Duty_Cycle);

inline void BSP_PWM_Channel_1_Interrupt_Clear(void);
inline void BSP_PWM_Channel_2_Interrupt_Clear(void);
inline void BSP_PWM_Channel_3_Interrupt_Clear(void);
inline void BSP_PWM_Channel_4_Interrupt_Clear(void);
inline void BSP_PWM_Channel_5_Interrupt_Clear(void);

#endif	// BSP_PWM_H
