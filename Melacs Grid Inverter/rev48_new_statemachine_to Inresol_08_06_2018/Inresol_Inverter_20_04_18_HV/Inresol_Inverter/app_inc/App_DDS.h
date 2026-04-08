/*
 *  File name: App_DDS.h
 *
 *  Description: High level function declarations for DDS (Direct Digital Synthesis) generator
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_DDS_H
#define APP_DDS_H
 
#include "global_includes.h"

extern volatile uint16_t	App_DDS_Waves_Freq;			// Frequency of waveforms
extern volatile int16_t		App_DDS_Shift_Phase_Chn2;	// Phase shift tuning word for channel 2
extern volatile int16_t		App_DDS_Shift_Phase_Chn3;	// Phase shift tuning word for channel 3
extern volatile uint16_t	App_DDS_Gain_Chn1;			// Magnitude for channel 1
extern volatile uint16_t	App_DDS_Gain_Chn2;			// Magnitude for channel 2
extern volatile uint16_t	App_DDS_Gain_Chn3;			// Magnitude for channel 3

void App_DDS_Init(void *Parameters);
inline void App_DDS_Process(void);
void App_DDS_Set_Freq(uint16_t Freq);
void App_DDS_Set_Phase(uint8_t Channel, int16_t Phase_Shift);
void App_DDS_Set_Gain(uint8_t Channel, uint16_t Gain);
uint16_t App_DDS_Get_Sample_Table(uint8_t Channel);
uint16_t App_DDS_Get_Sample_Scaled(uint8_t Channel);

inline void App_DDS_Set_Phase_Ch2(int16_t Phase_Shift);
inline void App_DDS_Set_Phase_Ch3(int16_t Phase_Shift);

inline void App_DDS_Set_Gain_Ch1(uint16_t Gain);
inline void App_DDS_Set_Gain_Ch2(uint16_t Gain);
inline void App_DDS_Set_Gain_Ch3(uint16_t Gain);

inline uint16_t App_DDS_Get_Sample_Table_Ch1(void);
inline uint16_t App_DDS_Get_Sample_Table_Ch2(void);
inline uint16_t App_DDS_Get_Sample_Table_Ch3(void);

inline uint16_t App_DDS_Get_Sample_Scaled_Ch1(void);
inline uint16_t App_DDS_Get_Sample_Scaled_Ch2(void);
inline uint16_t App_DDS_Get_Sample_Scaled_Ch3(void);

#endif  // APP_DDS_H
