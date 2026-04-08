/*
 *  File name: config_dds.h
 *
 *  Description: DDS generator settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_DDS_H
#define CONFIG_DDS_H

#include "config_pwm.h"

//*****************************************************************************
//
// DDS App settings.
//
//*****************************************************************************

// Sampling Frequency for DDS Generator
#define APP_SETTINGS_DDS_SAMP_FREQ				APP_SETTINGS_PWM_IGBT_SW_FREQ

// Default Generated Frequency by DDS Generator
#define APP_SETTINGS_DDS_DEF_GEN_FREQ			50		// 50Hz
// Default Phase Shifts in range: max: +32767 (+2PI or +360deg); min: -32768 (-2PI or -360deg)
#define APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH2	120		// +120deg
#define APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH3	240		// +240deg
// Default Magnitudes
#define APP_SETTINGS_DDS_DEF_MAGNITUDE_CH1		0		// 0%		100		// 100%
#define APP_SETTINGS_DDS_DEF_MAGNITUDE_CH2		0		// 0%		75		// 75%
#define APP_SETTINGS_DDS_DEF_MAGNITUDE_CH3		0		// 0%		50		// 50%

// Precision Settings for DDS Generator
#define APP_SETTINGS_DDS_ACC_BITS				32		// Phase Accumulator stored in 32 bits
#define APP_SETTINGS_DDS_SAMP_BITS				11		// 11 most significant bits used for phase table index (2048 samples)

#define APP_SETTINGS_DDS_MIN_GEN_FREQ			450		// 45.0Hz (in 0.1Hz units)
#define APP_SETTINGS_DDS_MAX_GEN_FREQ			650		// 65.0Hz (in 0.1Hz units)

#endif	// CONFIG_PWM_H
