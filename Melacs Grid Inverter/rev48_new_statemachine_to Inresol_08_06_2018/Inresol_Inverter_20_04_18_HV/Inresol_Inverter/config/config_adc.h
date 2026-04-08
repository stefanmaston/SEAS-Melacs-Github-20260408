/*
 *  File name: config_adc.h
 *
 *  Description: ADC peripheral settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_ADC_H
#define CONFIG_ADC_H

#include "types_adc.h"

//*****************************************************************************
//
// ADC BSP settings.
//
//*****************************************************************************

// Enable time shift between ADC Dedicated and Shared cores
//#define ADC_TIME_SHIFT_ENABLED

// Enable ADC Auto Calibration
#define ADC_AUTO_CALIBRATION

// Trigger Source Selection for All Analog Inputs
#define BSP_ADC_CORE_1_TRIGGER_SOURCE_SELECTION			6			// PWM Generator 2 primary trigger
#define BSP_ADC_CORE_2_TRIGGER_SOURCE_SELECTION			6			// PWM Generator 2 primary trigger
#define BSP_ADC_CORE_3_TRIGGER_SOURCE_SELECTION			6			// PWM Generator 2 primary trigger
#define BSP_ADC_CORE_4_TRIGGER_SOURCE_SELECTION			6			// PWM Generator 2 primary trigger
#ifndef ADC_TIME_SHIFT_ENABLED										// Enable time shift between conversion of ADC Dedicated and Shared cores
#define BSP_ADC_CORE_5_TRIGGER_SOURCE_SELECTION			6			// PWM Generator 2 primary trigger
#else	// ADC_TIME_SHIFT_ENABLED
#define BSP_ADC_CORE_5_TRIGGER_SOURCE_SELECTION			5			// PWM Generator 1 primary trigger
#endif	// ADC_TIME_SHIFT_ENABLED

#if (defined HARDWARE_VERSION_1)
#define BSP_SETTINGS_ADC_DEDICATED_CORE_INP_SWITCHINGS	2			// Number of input switchings on dedicated cores (2 -> between I & U or P & N)
#define BSP_SETTINGS_ADC_DEDICATED_CORE_INP_MODULO		2
#define BSP_SETTINGS_ADC_SHARED_CORE_INP_SWITCHINGS		12			// Number of input switchings on shared core (12 -> all inputs other than INV: MID, GRID, TEMP)
#define BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO			16
#define BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES			4096		// 4096samples * 1/16kHz switching *  2 input switchings / 2 phases = 256ms update period
#define BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES			512			//  512samples * 1/16kHz switching * 12 input switchings / 2 phases = 192ms update period
#elif (defined HARDWARE_VERSION_2)
#define BSP_SETTINGS_ADC_X1_CNT_MODULO					1
#define BSP_SETTINGS_ADC_X8_CNT_MODULO					8
#define BSP_SETTINGS_ADC_X16_CNT_MODULO					2
#define BSP_SETTINGS_ADC_X32_CNT_MODULO					4
#define BSP_SETTINGS_ADC_X1_SIG_SAMPLES					4096		// 4096samples * 1/16kHz switching *   2 input switchings / 2 phases = 256ms update period
#define BSP_SETTINGS_ADC_X8_SIG_SAMPLES					512			//  512samples * 1/16kHz switching *  16 input switchings / 2 phases = 256ms update period
#define BSP_SETTINGS_ADC_X16_SIG_SAMPLES				256			//  256samples * 1/16kHz switching *  16 input switchings / 2 phases * 2 alternates = 256ms update period
#define BSP_SETTINGS_ADC_X32_SIG_SAMPLES				1024		// 1024samples * 1/16kHz switching *  16 input switchings / 2 phases * 4 alternates = 2048ms update period
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

// ADC resolution: 12-bit -> 4096 levels
// Voltage measurements:
// Measurement precision: 65536 / 4096 = 64 -> 1/64 V = 0,015625 V
// Full measurement scale: 0.015625 V * 65535 (max of uint16) = 1023.984375 V
// Voltage result = (ADC_Value * (3.3 V full adc scale / 4096 adc resolution) / x voltage divider ratio) * 64 precision;
// Current measurements:
// Measurement precision: 65536 / 4096 = 64 -> 1/64 A = 0,015625 A
// Full measurement scale: 0,015625 A * 65535 (max of uint16) = 1023.984375 A
// Current result = (ADC_Value * (3.3 V full adc scale / 4096 adc resolution) / x voltage divider ratio) * 64 precision;

#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter

#ifndef LOW_VOLTAGE_SCALERS
// U_INV and U_MID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.0036219) * 32;
//	Result = ADC_Value * (330 * 32 * 2761 / 100 / 10 / 4096);
//	Result = ADC_Value * 330 * 2761 / 1000 / 128;
//	Result = ADC_Value * 165 * 2761 / 64000;
#define	BSP_SETTINGS_ADC_U_INV_SCALING					165 * 2761 / 64000
#define	BSP_SETTINGS_ADC_U_MID_SCALING					165 * 2761 / 64000

// U_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.0021829) * 32;
//	Result = ADC_Value * (330 * 32 * 4581 / 100 / 10 / 4096);
//	Result = ADC_Value * 330 * 4581 / 1000 / 128;
//	Result = ADC_Value * 165 * 4581 / 64000;
#define	BSP_SETTINGS_ADC_U_GRID_SCALING					165 * 4148 / 64000

// P_UDC and N_UDC Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.0060168) * 32;
//	Result = ADC_Value * (330 * 32 * 1662 / 100 / 10 / 4096);
//	Result = ADC_Value * (330 * 1662 / 1000 / 128);
//	Result = ADC_Value * 165 * 1662 / 64000;
//#define	BSP_SETTINGS_ADC_U_DC_SCALING				165 * 1910 / 64000
#define	BSP_SETTINGS_ADC_U_DC_SCALING					165 * 1662 / 64000

// I_INV and I_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.0296) * 32;
//	Result = ADC_Value * (33 * 32 * 3378 / 10 / 100 / 4096);
//	Result = ADC_Value * 33 * 3378 / 1000 / 128;
//	Result = ADC_Value * 33 * 1689 / 64000;
#define	BSP_SETTINGS_ADC_I_INV_SCALING					33 * 1689 / 64000
#define	BSP_SETTINGS_ADC_I_GRID_SCALING					33 * 1689 / 64000

#else	// LOW_VOLTAGE_SCALERS
// U_INV and U_MID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.09722) * 32;
//	Result = ADC_Value * (3300 * 32 * 10286 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 10286 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_INV_SCALING					33 * 10286 / 10000 / 128
#define	BSP_SETTINGS_ADC_U_MID_SCALING					33 * 10286 / 10000 / 128

// U_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.06357) * 32;
//	Result = ADC_Value * (3300 * 32 * 15730 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 15730 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_GRID_SCALING					33 * 15730 / 10000 / 128

// P_UDC and N_UDC Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.14473) * 32;
//	Result = ADC_Value * (3300 * 32 * 6909 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 6272 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_DC_SCALING					33 * 6909 / 10000 / 128

// I_INV and I_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.0296) * 32;
//	Result = ADC_Value * (33 * 32 * 3378 / 10 / 100 / 4096);
//	Result = ADC_Value * 33 * 3378 / 1000 / 128;
//	Result = ADC_Value * 33 * 1689 / 64000;
#define	BSP_SETTINGS_ADC_I_INV_SCALING					33 * 169 / 64000
#define	BSP_SETTINGS_ADC_I_GRID_SCALING					33 * 169 / 64000

#endif	// LOW_VOLTAGE_SCALERS

#else
// Engineering Sample Evaluation Board
// 28-pins Starter Board

// U_INV and U_MID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.199) * 32;
//	Result = ADC_Value * (3300 * 32 * 5025 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 5025 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_INV_SCALING					33 * 5025 / 10000 / 128
#define	BSP_SETTINGS_ADC_U_MID_SCALING					33 * 5025 / 10000 / 128

// U_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.199) * 32;
//	Result = ADC_Value * (3300 * 32 * 5025 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 5025 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_GRID_SCALING					33 * 5025 / 10000 / 128

// P_UDC and N_UDC Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.18) * 32;
//	Result = ADC_Value * (3300 * 32 * 5555 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 5555 / 10000 / 128;
#define	BSP_SETTINGS_ADC_U_DC_SCALING					33 * 5555 / 10000 / 128

// I_INV and I_GRID Scaling:
//	Result = (ADC_Value * (3.3 / 4096) / 0.199) * 32;
//	Result = ADC_Value * (3300 * 32 * 5025 / 1000 / 1000 / 4096);
//	Result = ADC_Value * 33 * 5025 / 10000 / 128;
#define	BSP_SETTINGS_ADC_I_INV_SCALING					33 * 5025 / 10000 / 128
#define	BSP_SETTINGS_ADC_I_GRID_SCALING					33 * 5025 / 10000 / 128
#endif

// T Scaling:
#define	BSP_SETTINGS_ADC_T_SCALING						1

// ADC Interrupt Channel, Handler, Level
#define BSP_ADC_INTERRUPT_CORE							BSP_ADC_CORE_NUMBER_2
#define BSP_ADC_INTERRUPT_HANDLER()						_ADCAN1Interrupt()
#define BSP_ADC_INTERRUPT_CALLBACK()					App_ADC_Process_IRQ()
#define BSP_ADC_INTERRUPT_LEVEL							4
#define BSP_ADC_INTERRUPT_CLEAR()						do {	\
															BSP_ADC_Core_1_Interrupt_Clear();	\
															BSP_ADC_Core_2_Interrupt_Clear();	\
															BSP_ADC_Core_3_Interrupt_Clear();	\
															BSP_ADC_Core_4_Interrupt_Clear();	\
															BSP_ADC_Core_5_Interrupt_Clear();	\
														} while (0);

#endif	// CONFIG_ADC_H
