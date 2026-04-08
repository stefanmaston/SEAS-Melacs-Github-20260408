/*
 *  File name: App_ADC.c
 *
 *  Description: High level function implementations for ADC processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

#define BUILTIN_OPTIMISATION_ENABLED
#define CURRENT_OFFSET_CORRECTION
#define VOLTAGE_OFFSET_CORRECTION

#ifndef INT16_MIN
#define INT16_MIN (-32768)
#endif
#ifndef INT16_MAX
#define INT16_MAX (32767)
#endif
#ifndef UINT16_MIN
#define UINT16_MIN (0)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX (65535U)
#endif

#ifndef BUILTIN_OPTIMISATION_ENABLED
#define FUNCTION_MULTIPLY_SS(VALUE_S1, VALUE_S2)	((int32_t)VALUE_S1 * VALUE_S2)
#define FUNCTION_MULTIPLY_UU(VALUE_U1, VALUE_U2)	((uint32_t)VALUE_U1 * VALUE_U2)
#else	// BUILTIN_OPTIMISATION_ENABLED
#define FUNCTION_MULTIPLY_SS(VALUE_S1, VALUE_S2)	__builtin_mulss(VALUE_S1, VALUE_S2)
#define FUNCTION_MULTIPLY_UU(VALUE_U1, VALUE_U2)	__builtin_muluu(VALUE_U1, VALUE_U2)
#endif	// BUILTIN_OPTIMISATION_ENABLED

uint16_t ADC_P_U_DC_RAW;
uint16_t ADC_P_U_DC_Mean;
uint16_t ADC_P_U_DC_PkPk;
uint16_t ADC_P_U_DC_RMS;
uint16_t ADC_N_U_DC_RAW;
uint16_t ADC_N_U_DC_Mean;
uint16_t ADC_N_U_DC_PkPk;
uint16_t ADC_N_U_DC_RMS;
uint16_t ADC_L1_U_Inv_RAW;
int16_t  ADC_L1_U_Inv_Conv;
int16_t  ADC_L1_U_Inv_Mean;
int16_t  ADC_L1_U_Inv_PkPk;
int16_t  ADC_L1_U_Inv_Pk_L;
int16_t  ADC_L1_U_Inv_Pk_H;
int16_t  ADC_L1_U_Inv_RMS;
uint16_t ADC_L1_I_Inv_RAW;
int16_t  ADC_L1_I_Inv_Conv;
int16_t  ADC_L1_I_Inv_Mean;
int16_t  ADC_L1_I_Inv_PkPk;
int16_t  ADC_L1_I_Inv_RMS;
uint16_t ADC_L2_U_Inv_RAW;
int16_t  ADC_L2_U_Inv_Conv;
int16_t  ADC_L2_U_Inv_Mean;
int16_t  ADC_L2_U_Inv_PkPk;
int16_t  ADC_L2_U_Inv_Pk_L;
int16_t  ADC_L2_U_Inv_Pk_H;
int16_t  ADC_L2_U_Inv_RMS;
uint16_t ADC_L2_I_Inv_RAW;
int16_t  ADC_L2_I_Inv_Conv;
int16_t  ADC_L2_I_Inv_Mean;
int16_t  ADC_L2_I_Inv_PkPk;
int16_t  ADC_L2_I_Inv_RMS;
uint16_t ADC_L3_U_Inv_RAW;
int16_t  ADC_L3_U_Inv_Conv;
int16_t  ADC_L3_U_Inv_Mean;
int16_t  ADC_L3_U_Inv_PkPk;
int16_t  ADC_L3_U_Inv_Pk_L;
int16_t  ADC_L3_U_Inv_Pk_H;
int16_t  ADC_L3_U_Inv_RMS;
uint16_t ADC_L3_I_Inv_RAW;
int16_t  ADC_L3_I_Inv_Conv;
int16_t  ADC_L3_I_Inv_Mean;
int16_t  ADC_L3_I_Inv_PkPk;
int16_t  ADC_L3_I_Inv_RMS;
uint16_t ADC_L1_U_Mid_RAW;
int16_t  ADC_L1_U_Mid_Conv;
int16_t  ADC_L1_U_Mid_Mean;
int16_t  ADC_L1_U_Mid_PkPk;
int16_t  ADC_L1_U_Mid_Pk_L;
int16_t  ADC_L1_U_Mid_Pk_H;
int16_t  ADC_L1_U_Mid_RMS;
uint16_t ADC_L2_U_Mid_RAW;
int16_t  ADC_L2_U_Mid_Conv;
int16_t  ADC_L2_U_Mid_Mean;
int16_t  ADC_L2_U_Mid_PkPk;
int16_t  ADC_L2_U_Mid_Pk_L;
int16_t  ADC_L2_U_Mid_Pk_H;
int16_t  ADC_L2_U_Mid_RMS;
uint16_t ADC_L3_U_Mid_RAW;
int16_t  ADC_L3_U_Mid_Conv;
int16_t  ADC_L3_U_Mid_Mean;
int16_t  ADC_L3_U_Mid_PkPk;
int16_t  ADC_L3_U_Mid_Pk_L;
int16_t  ADC_L3_U_Mid_Pk_H;
int16_t  ADC_L3_U_Mid_RMS;
uint16_t ADC_L1_U_Grid_RAW;
int16_t  ADC_L1_U_Grid_Conv;
int16_t  ADC_L1_U_Grid_Mean;
int16_t  ADC_L1_U_Grid_PkPk;
int16_t  ADC_L1_U_Grid_Pk_L;
int16_t  ADC_L1_U_Grid_Pk_H;
int16_t  ADC_L1_U_Grid_RMS;
uint16_t ADC_L1_I_Grid_RAW;
int16_t  ADC_L1_I_Grid_Conv;
int16_t  ADC_L1_I_Grid_Mean;
int16_t  ADC_L1_I_Grid_PkPk;
int16_t  ADC_L1_I_Grid_RMS;
uint16_t ADC_L2_U_Grid_RAW;
int16_t  ADC_L2_U_Grid_Conv;
int16_t  ADC_L2_U_Grid_Mean;
int16_t  ADC_L2_U_Grid_PkPk;
int16_t  ADC_L2_U_Grid_Pk_L;
int16_t  ADC_L2_U_Grid_Pk_H;
int16_t  ADC_L2_U_Grid_RMS;
uint16_t ADC_L2_I_Grid_RAW;
int16_t  ADC_L2_I_Grid_Conv;
int16_t  ADC_L2_I_Grid_Mean;
int16_t  ADC_L2_I_Grid_PkPk;
int16_t  ADC_L2_I_Grid_RMS;
uint16_t ADC_L3_U_Grid_RAW;
int16_t  ADC_L3_U_Grid_Conv;
int16_t  ADC_L3_U_Grid_Mean;
int16_t  ADC_L3_U_Grid_PkPk;
int16_t  ADC_L3_U_Grid_Pk_L;
int16_t  ADC_L3_U_Grid_Pk_H;
int16_t  ADC_L3_U_Grid_RMS;
uint16_t ADC_L3_I_Grid_RAW;
int16_t  ADC_L3_I_Grid_Conv;
int16_t  ADC_L3_I_Grid_Mean;
int16_t  ADC_L3_I_Grid_PkPk;
int16_t  ADC_L3_I_Grid_RMS;
uint16_t ADC_T1_RAW;
uint16_t ADC_T1_Mean;
uint16_t ADC_T2_RAW;
uint16_t ADC_T2_Mean;
uint16_t ADC_T3_RAW;
uint16_t ADC_T3_Mean;
uint16_t ADC_AUX4_RAW;
uint16_t ADC_AUX4_Mean;
bool     ADC_Ready = false;
bool     ADC_Calib = false;

static uint32_t Loc_P_U_DC_Mean = 0;
static uint32_t Loc_N_U_DC_Mean = 0;
static  int32_t Loc_L1_U_Inv_Mean = 0;
static  int32_t Loc_L1_I_Inv_Mean = 0;
static  int32_t Loc_L2_U_Inv_Mean = 0;
static  int32_t Loc_L2_I_Inv_Mean = 0;
static  int32_t Loc_L3_U_Inv_Mean = 0;
static  int32_t Loc_L3_I_Inv_Mean = 0;
static  int32_t Loc_L1_U_Mid_Mean = 0;
static  int32_t Loc_L2_U_Mid_Mean = 0;
static  int32_t Loc_L3_U_Mid_Mean = 0;
static  int32_t Loc_L1_U_Grid_Mean = 0;
static  int32_t Loc_L1_I_Grid_Mean = 0;
static  int32_t Loc_L2_U_Grid_Mean = 0;
static  int32_t Loc_L2_I_Grid_Mean = 0;
static  int32_t Loc_L3_U_Grid_Mean = 0;
static  int32_t Loc_L3_I_Grid_Mean = 0;
static uint32_t Loc_T1_Mean = 0;
static uint32_t Loc_T2_Mean = 0;
static uint32_t Loc_T3_Mean = 0;
static uint32_t Loc_AUX4_Mean = 0;
static uint16_t Loc_P_U_DC_PkPk_L = UINT16_MAX;
static uint16_t Loc_P_U_DC_PkPk_H = UINT16_MIN;
static uint16_t Loc_N_U_DC_PkPk_L = UINT16_MAX;
static uint16_t Loc_N_U_DC_PkPk_H = UINT16_MIN;
static  int16_t Loc_L1_U_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L1_U_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L1_I_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L1_I_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L2_U_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L2_U_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L2_I_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L2_I_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L3_U_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L3_U_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L3_I_Inv_PkPk_L = INT16_MAX;
static  int16_t Loc_L3_I_Inv_PkPk_H = INT16_MIN;
static  int16_t Loc_L1_U_Mid_PkPk_L = INT16_MAX;
static  int16_t Loc_L1_U_Mid_PkPk_H = INT16_MIN;
static  int16_t Loc_L2_U_Mid_PkPk_L = INT16_MAX;
static  int16_t Loc_L2_U_Mid_PkPk_H = INT16_MIN;
static  int16_t Loc_L3_U_Mid_PkPk_L = INT16_MAX;
static  int16_t Loc_L3_U_Mid_PkPk_H = INT16_MIN;
static  int16_t Loc_L1_U_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L1_U_Grid_PkPk_H = INT16_MIN;
static  int16_t Loc_L1_I_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L1_I_Grid_PkPk_H = INT16_MIN;
static  int16_t Loc_L2_U_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L2_U_Grid_PkPk_H = INT16_MIN;
static  int16_t Loc_L2_I_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L2_I_Grid_PkPk_H = INT16_MIN;
static  int16_t Loc_L3_U_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L3_U_Grid_PkPk_H = INT16_MIN;
static  int16_t Loc_L3_I_Grid_PkPk_L = INT16_MAX;
static  int16_t Loc_L3_I_Grid_PkPk_H = INT16_MIN;
static uint64_t Loc_P_U_DC_RMS = 0;
static uint64_t Loc_N_U_DC_RMS = 0;
static  int64_t Loc_L1_U_Inv_RMS = 0;
static  int64_t Loc_L1_I_Inv_RMS = 0;
static  int64_t Loc_L2_U_Inv_RMS = 0;
static  int64_t Loc_L2_I_Inv_RMS = 0;
static  int64_t Loc_L3_U_Inv_RMS = 0;
static  int64_t Loc_L3_I_Inv_RMS = 0;
static  int64_t Loc_L1_U_Mid_RMS = 0;
static  int64_t Loc_L2_U_Mid_RMS = 0;
static  int64_t Loc_L3_U_Mid_RMS = 0;
static  int64_t Loc_L1_U_Grid_RMS = 0;
static  int64_t Loc_L1_I_Grid_RMS = 0;
static  int64_t Loc_L2_U_Grid_RMS = 0;
static  int64_t Loc_L2_I_Grid_RMS = 0;
static  int64_t Loc_L3_U_Grid_RMS = 0;
static  int64_t Loc_L3_I_Grid_RMS = 0;

#if (defined HARDWARE_VERSION_1)
static uint16_t Loc_Dedicated_Cnt = 0;
static uint16_t Loc_Shared_Cnt = 0;
static bool Loc_Dedicated_Busy = false;
static bool Loc_Shared_Busy = false;
static int8_t Loc_Dedicated_CntDwn = 2;
static int8_t Loc_Shared_CntDwn = 2;
#elif (defined HARDWARE_VERSION_2)
static uint16_t Loc_x1_Cnt = 0;
static uint16_t Loc_x8_Cnt = 0;
static uint16_t Loc_x16_Cnt = 0;
static uint16_t Loc_x32_Cnt = 0;
static bool Loc_x1_Busy = false;
static bool Loc_x8_Busy = false;
static bool Loc_x16_Busy = false;
static bool Loc_x32_Busy = false;
static int8_t Loc_x1_CntDwn = 2;
static int8_t Loc_x8_CntDwn = 2;
static int8_t Loc_x16_CntDwn = 2;
static int8_t Loc_x32_CntDwn = 2;
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

#ifdef CURRENT_OFFSET_CORRECTION
static int16_t  Loc_L1_I_Inv_Error = 0;
static int16_t  Loc_L2_I_Inv_Error = 0;
static int16_t  Loc_L3_I_Inv_Error = 0;
static int16_t  Loc_L1_I_Grid_Error = 0;
static int16_t  Loc_L2_I_Grid_Error = 0;
static int16_t  Loc_L3_I_Grid_Error = 0;
#define ADC_L1_I_INV_CONV_CORRECT()		ADC_L1_I_Inv_Conv += Loc_L1_I_Inv_Error
#define ADC_L2_I_INV_CONV_CORRECT()		ADC_L2_I_Inv_Conv += Loc_L2_I_Inv_Error
#define ADC_L3_I_INV_CONV_CORRECT()		ADC_L3_I_Inv_Conv += Loc_L3_I_Inv_Error
#define ADC_L1_I_GRID_CONV_CORRECT()	ADC_L1_I_Grid_Conv += Loc_L1_I_Grid_Error
#define ADC_L2_I_GRID_CONV_CORRECT()	ADC_L2_I_Grid_Conv += Loc_L2_I_Grid_Error
#define ADC_L3_I_GRID_CONV_CORRECT()	ADC_L3_I_Grid_Conv += Loc_L3_I_Grid_Error
#else	// CURRENT_OFFSET_CORRECTION
#define ADC_L1_I_INV_CONV_CORRECT()
#define ADC_L2_I_INV_CONV_CORRECT()
#define ADC_L3_I_INV_CONV_CORRECT()
#define ADC_L1_I_GRID_CONV_CORRECT()
#define ADC_L2_I_GRID_CONV_CORRECT()
#define ADC_L3_I_GRID_CONV_CORRECT()
#endif	// CURRENT_OFFSET_CORRECTION
#ifdef VOLTAGE_OFFSET_CORRECTION
static int16_t  Loc_L1_U_Inv_Error = 0;
static int16_t  Loc_L2_U_Inv_Error = 0;
static int16_t  Loc_L3_U_Inv_Error = 0;
static int16_t  Loc_L1_U_Mid_Error = 0;
static int16_t  Loc_L2_U_Mid_Error = 0;
static int16_t  Loc_L3_U_Mid_Error = 0;
static int16_t  Loc_L1_U_Grid_Error = 0;
static int16_t  Loc_L2_U_Grid_Error = 0;
static int16_t  Loc_L3_U_Grid_Error = 0;
#define ADC_L1_U_INV_CONV_CORRECT()		ADC_L1_U_Inv_Conv += Loc_L1_U_Inv_Error
#define ADC_L2_U_INV_CONV_CORRECT()		ADC_L2_U_Inv_Conv += Loc_L2_U_Inv_Error
#define ADC_L3_U_INV_CONV_CORRECT()		ADC_L3_U_Inv_Conv += Loc_L3_U_Inv_Error
#define ADC_L1_U_MID_CONV_CORRECT()		ADC_L1_U_Mid_Conv += Loc_L1_U_Mid_Error
#define ADC_L2_U_MID_CONV_CORRECT()		ADC_L2_U_Mid_Conv += Loc_L2_U_Mid_Error
#define ADC_L3_U_MID_CONV_CORRECT()		ADC_L3_U_Mid_Conv += Loc_L3_U_Mid_Error
#define ADC_L1_U_GRID_CONV_CORRECT()	ADC_L1_U_Grid_Conv += Loc_L1_U_Grid_Error
#define ADC_L2_U_GRID_CONV_CORRECT()	ADC_L2_U_Grid_Conv += Loc_L2_U_Grid_Error
#define ADC_L3_U_GRID_CONV_CORRECT()	ADC_L3_U_Grid_Conv += Loc_L3_U_Grid_Error
#else	// VOLTAGE_OFFSET_CORRECTION
#define ADC_L1_U_INV_CONV_CORRECT()
#define ADC_L2_U_INV_CONV_CORRECT()
#define ADC_L3_U_INV_CONV_CORRECT()
#define ADC_L1_U_MID_CONV_CORRECT()
#define ADC_L2_U_MID_CONV_CORRECT()
#define ADC_L3_U_MID_CONV_CORRECT()
#define ADC_L1_U_GRID_CONV_CORRECT()
#define ADC_L2_U_GRID_CONV_CORRECT()
#define ADC_L3_U_GRID_CONV_CORRECT()
#endif	// VOLTAGE_OFFSET_CORRECTION

static void ADC_Save_to_NVM(void)
{
	if(ADC_Calib == true) {
#ifdef ADC_AUTO_CALIBRATION
#ifdef VOLTAGE_OFFSET_CORRECTION
		NVMemory.ADC.L1_U_Inv_Error = Loc_L1_U_Inv_Error;
		NVMemory.ADC.L2_U_Inv_Error = Loc_L2_U_Inv_Error;
		NVMemory.ADC.L3_U_Inv_Error = Loc_L3_U_Inv_Error;
		NVMemory.ADC.L1_U_Mid_Error = Loc_L1_U_Mid_Error;
		NVMemory.ADC.L2_U_Mid_Error = Loc_L2_U_Mid_Error;
		NVMemory.ADC.L3_U_Mid_Error = Loc_L3_U_Mid_Error;
		NVMemory.ADC.L1_U_Grid_Error = Loc_L1_U_Grid_Error;
		NVMemory.ADC.L2_U_Grid_Error = Loc_L2_U_Grid_Error;
		NVMemory.ADC.L3_U_Grid_Error = Loc_L3_U_Grid_Error;
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
		NVMemory.ADC.L1_I_Inv_Error = Loc_L1_I_Inv_Error;
		NVMemory.ADC.L2_I_Inv_Error = Loc_L2_I_Inv_Error;
		NVMemory.ADC.L3_I_Inv_Error = Loc_L3_I_Inv_Error;
		NVMemory.ADC.L1_I_Grid_Error = Loc_L1_I_Grid_Error;
		NVMemory.ADC.L2_I_Grid_Error = Loc_L2_I_Grid_Error;
		NVMemory.ADC.L3_I_Grid_Error = Loc_L3_I_Grid_Error;
#endif	// CURRENT_OFFSET_CORRECTION
		NVMemoryDoUpdate = true;		// This will cause NV Write & System Reset
#endif	// ADC_AUTO_CALIBRATION
	}
}

void App_ADC_Init(void *Parameters)
{
	(void)Parameters;
	BSP_ADC_Module_Disable();
	BSP_ADC_Module_Init();
	BSP_ADC_Core_Enable(BSP_ADC_CORE_NUMBER_1);
	BSP_ADC_Core_Enable(BSP_ADC_CORE_NUMBER_2);
	BSP_ADC_Core_Enable(BSP_ADC_CORE_NUMBER_3);
	BSP_ADC_Core_Enable(BSP_ADC_CORE_NUMBER_4);
	BSP_ADC_Core_Enable(BSP_ADC_CORE_NUMBER_5);
	BSP_ADC_Core_Calibrate(BSP_ADC_CORE_NUMBER_1);
	BSP_ADC_Core_Calibrate(BSP_ADC_CORE_NUMBER_2);
	BSP_ADC_Core_Calibrate(BSP_ADC_CORE_NUMBER_3);
	BSP_ADC_Core_Calibrate(BSP_ADC_CORE_NUMBER_4);
	BSP_ADC_Core_Calibrate(BSP_ADC_CORE_NUMBER_5);
	BSP_ADC_Set_Trigger(BSP_ADC_CORE_NUMBER_1, BSP_ADC_CORE_1_TRIGGER_SOURCE_SELECTION);
	BSP_ADC_Set_Trigger(BSP_ADC_CORE_NUMBER_2, BSP_ADC_CORE_2_TRIGGER_SOURCE_SELECTION);
	BSP_ADC_Set_Trigger(BSP_ADC_CORE_NUMBER_3, BSP_ADC_CORE_3_TRIGGER_SOURCE_SELECTION);
	BSP_ADC_Set_Trigger(BSP_ADC_CORE_NUMBER_4, BSP_ADC_CORE_4_TRIGGER_SOURCE_SELECTION);
	BSP_ADC_Set_Trigger(BSP_ADC_CORE_NUMBER_5, BSP_ADC_CORE_5_TRIGGER_SOURCE_SELECTION);
	BSP_ADC_Interrupt_Enable(BSP_ADC_INTERRUPT_CORE, BSP_ADC_INTERRUPT_LEVEL);
#ifdef ADC_AUTO_CALIBRATION
#ifdef VOLTAGE_OFFSET_CORRECTION
	if(ADC_Calib == false) {
		Loc_L1_U_Inv_Error = NVMemory.ADC.L1_U_Inv_Error;
		Loc_L2_U_Inv_Error = NVMemory.ADC.L2_U_Inv_Error;
		Loc_L3_U_Inv_Error = NVMemory.ADC.L3_U_Inv_Error;
		Loc_L1_U_Mid_Error = NVMemory.ADC.L1_U_Mid_Error;
		Loc_L2_U_Mid_Error = NVMemory.ADC.L2_U_Mid_Error;
		Loc_L3_U_Mid_Error = NVMemory.ADC.L3_U_Mid_Error;
		Loc_L1_U_Grid_Error = NVMemory.ADC.L1_U_Grid_Error;
		Loc_L2_U_Grid_Error = NVMemory.ADC.L2_U_Grid_Error;
		Loc_L3_U_Grid_Error = NVMemory.ADC.L3_U_Grid_Error;
	} else {
		Loc_L1_U_Inv_Error = 0;
		Loc_L2_U_Inv_Error = 0;
		Loc_L3_U_Inv_Error = 0;
		Loc_L1_U_Mid_Error = 0;
		Loc_L2_U_Mid_Error = 0;
		Loc_L3_U_Mid_Error = 0;
		Loc_L1_U_Grid_Error = 0;
		Loc_L2_U_Grid_Error = 0;
		Loc_L3_U_Grid_Error = 0;
	}
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
	if(ADC_Calib == false) {
		Loc_L1_I_Inv_Error = NVMemory.ADC.L1_I_Inv_Error;
		Loc_L2_I_Inv_Error = NVMemory.ADC.L2_I_Inv_Error;
		Loc_L3_I_Inv_Error = NVMemory.ADC.L3_I_Inv_Error;
		Loc_L1_I_Grid_Error = NVMemory.ADC.L1_I_Grid_Error;
		Loc_L2_I_Grid_Error = NVMemory.ADC.L2_I_Grid_Error;
		Loc_L3_I_Grid_Error = NVMemory.ADC.L3_I_Grid_Error;
	} else {
		Loc_L1_I_Inv_Error = 0;
		Loc_L2_I_Inv_Error = 0;
		Loc_L3_I_Inv_Error = 0;
		Loc_L1_I_Grid_Error = 0;
		Loc_L2_I_Grid_Error = 0;
		Loc_L3_I_Grid_Error = 0;
	}
		
#endif	// CURRENT_OFFSET_CORRECTION
#endif	// ADC_AUTO_CALIBRATION
}

#ifndef INLINE_UNSUPPORTED
static inline int16_t convert_u12_to_s16(uint16_t Value)
{
	return (Value >= 2048) ? (Value - 2048) : (-2048 + Value);
}

static inline uint16_t convert_u12_to_u16(uint16_t Value)
{
	return Value;
}
#else	// INLINE_UNSUPPORTED
#define convert_u12_to_s16(Value)						\
			(Value >= 2048) ? (Value - 2048) : (-2048 + Value)

#define convert_u12_to_u16(Value)	\
			Value
#endif	// INLINE_UNSUPPORTED

#if (defined HARDWARE_VERSION_1)
inline void App_ADC_Process_Trigger_Primary(void)
{
//	PWM_TST3_SET();
	// *****************
	// *** READ ONLY ***
	// *****************
	// L1_U_Inv
	ADC_L1_U_Inv_RAW = BSP_ADC_Core_1_Value_Get();
#ifdef APP_DATAREC_ENABLED
//	App_DataRec_Store_16bit((uint16_t)ADC_L1_U_Inv_RAW);
#endif	// APP_DATAREC_ENABLED
	ADC_L1_U_Inv_Conv = convert_u12_to_s16(ADC_L1_U_Inv_RAW);
	ADC_L1_U_INV_CONV_CORRECT();
	BSP_ADC_Core_1_Input_Set(BSP_ADC_CORE1_MUX_AN0);	// Switch to Current (L1_I_INV)
	// L2_U_Inv
	ADC_L2_U_Inv_RAW = BSP_ADC_Core_2_Value_Get();
	ADC_L2_U_Inv_Conv = convert_u12_to_s16(ADC_L2_U_Inv_RAW);
	ADC_L2_U_INV_CONV_CORRECT();
	BSP_ADC_Core_2_Input_Set(BSP_ADC_CORE2_MUX_AN1);	// Switch to Current (L2_I_INV)
	// L3_U_Inv
	ADC_L3_U_Inv_RAW = BSP_ADC_Core_3_Value_Get();
	ADC_L3_U_Inv_Conv = convert_u12_to_s16(ADC_L3_U_Inv_RAW);
	ADC_L3_U_INV_CONV_CORRECT();
	BSP_ADC_Core_3_Input_Set(BSP_ADC_CORE3_MUX_AN2);	// Switch to Current (L3_I_INV)
	// P_U_DC
	ADC_P_U_DC_RAW = BSP_ADC_Core_4_Value_Get();
	BSP_ADC_Core_4_Input_Set(BSP_ADC_CORE4_MUX_AN15);	// Switch to Voltage (N_U_DC)
//	PWM_TST3_CLR();
	switch(Loc_Shared_Cnt & (BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO - 1)) {	// Modulo 16
		case 0:		// L1_U_Mid
			ADC_L1_U_Mid_RAW = BSP_ADC_Core_5_AN4_Value_Get();
			ADC_L1_U_Mid_Conv = convert_u12_to_s16(ADC_L1_U_Mid_RAW);
			ADC_L1_U_MID_CONV_CORRECT();
#ifdef APP_DATAREC_ENABLED
//			App_DataRec_Store_16bit((uint16_t)ADC_L1_U_Mid_Conv);
#endif	// APP_DATAREC_ENABLED
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN16);	// Switch to Voltage (T1)
			break;
		case 2:		// L2_U_Mid
			ADC_L2_U_Mid_RAW = BSP_ADC_Core_5_AN5_Value_Get();
			ADC_L2_U_Mid_Conv = convert_u12_to_s16(ADC_L2_U_Mid_RAW);
			ADC_L2_U_MID_CONV_CORRECT();
#ifdef APP_DATAREC_ENABLED
//			App_DataRec_Store_16bit((uint16_t)ADC_L2_U_Mid_Conv);
#endif	// APP_DATAREC_ENABLED
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN17);	// Switch to Voltage (T2)
			break;
		case 4:		// L3_U_Mid
			ADC_L3_U_Mid_RAW = BSP_ADC_Core_5_AN6_Value_Get();
			ADC_L3_U_Mid_Conv = convert_u12_to_s16(ADC_L3_U_Mid_RAW);
			ADC_L3_U_MID_CONV_CORRECT();
#ifdef APP_DATAREC_ENABLED
//			App_DataRec_Store_16bit((uint16_t)ADC_L3_U_Mid_Conv);
#endif	// APP_DATAREC_ENABLED
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN19);	// Switch to Voltage (T3)
			break;
		case 6:		// L1_U_Grid
#ifdef ADCBUF8
			ADC_L1_U_Grid_RAW = BSP_ADC_Core_5_AN8_Value_Get();
#else
			ADC_L1_U_Grid_RAW = 0;
#endif
			ADC_L1_U_Grid_Conv = convert_u12_to_s16(ADC_L1_U_Grid_RAW);
			ADC_L1_U_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN12);	// Switch to Voltage (L1_I_GRID)
			break;
		case 8:		// L2_U_Grid
#ifdef ADCBUF9
			ADC_L2_U_Grid_RAW = BSP_ADC_Core_5_AN9_Value_Get();
#else
			ADC_L2_U_Grid_RAW = 0;
#endif
			ADC_L2_U_Grid_Conv = convert_u12_to_s16(ADC_L2_U_Grid_RAW);
			ADC_L2_U_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN13);	// Switch to Voltage (L2_I_GRID)
			break;
		case 10:	// L3_U_Grid
#ifdef ADCBUF10
			ADC_L3_U_Grid_RAW = BSP_ADC_Core_5_AN10_Value_Get();
#else
			ADC_L3_U_Grid_RAW = 0;
#endif
			ADC_L3_U_Grid_Conv = convert_u12_to_s16(ADC_L3_U_Grid_RAW);
			ADC_L3_U_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN14);	// Switch to Voltage (L3_I_GRID)
			break;
	}
}
#elif (defined HARDWARE_VERSION_2)
inline void App_ADC_Process_Trigger_Primary(void)
{
//	PWM_TST3_SET();
	// *****************
	// *** READ ONLY ***
	// *****************
#ifndef U_GRID_AS_HIRES
	// L1_U_Mid
	ADC_L1_U_Mid_RAW = BSP_ADC_Core_1_Value_Get();
	ADC_L1_U_Mid_Conv = convert_u12_to_s16(ADC_L1_U_Mid_RAW);
	ADC_L1_U_MID_CONV_CORRECT();
#ifdef APP_DATAREC_ENABLED
//	App_DataRec_Store_16bit((uint16_t)ADC_L1_U_Mid_Conv);
#endif	// APP_DATAREC_ENABLED
	BSP_ADC_Core_1_Input_Set(BSP_ADC_CORE1_MUX_AN0);	// Switch to Current (L1_I_INV)
	// L2_U_Mid
	ADC_L2_U_Mid_RAW = BSP_ADC_Core_2_Value_Get();
	ADC_L2_U_Mid_Conv = convert_u12_to_s16(ADC_L2_U_Mid_RAW);
	ADC_L2_U_MID_CONV_CORRECT();
	BSP_ADC_Core_2_Input_Set(BSP_ADC_CORE2_MUX_AN1);	// Switch to Current (L2_I_INV)
	// L3_U_Mid
	ADC_L3_U_Mid_RAW = BSP_ADC_Core_3_Value_Get();
	ADC_L3_U_Mid_Conv = convert_u12_to_s16(ADC_L3_U_Mid_RAW);
	ADC_L3_U_MID_CONV_CORRECT();
	BSP_ADC_Core_3_Input_Set(BSP_ADC_CORE3_MUX_AN2);	// Switch to Current (L3_I_INV)
#else	// U_GRID_AS_HIRES
	// L1_U_Grid
	ADC_L1_U_Grid_RAW = BSP_ADC_Core_1_Value_Get();
	ADC_L1_U_Grid_Conv = convert_u12_to_s16(ADC_L1_U_Grid_RAW);
	ADC_L1_U_GRID_CONV_CORRECT();
	BSP_ADC_Core_1_Input_Set(BSP_ADC_CORE1_MUX_AN0);	// Switch to Current (L1_I_INV)
	// L2_U_Grid
	ADC_L2_U_Grid_RAW = BSP_ADC_Core_2_Value_Get();
	ADC_L2_U_Grid_Conv = convert_u12_to_s16(ADC_L2_U_Grid_RAW);
	ADC_L2_U_GRID_CONV_CORRECT();
	BSP_ADC_Core_2_Input_Set(BSP_ADC_CORE2_MUX_AN1);	// Switch to Current (L2_I_INV)
	// L3_U_Grid
	ADC_L3_U_Grid_RAW = BSP_ADC_Core_3_Value_Get();
	ADC_L3_U_Grid_Conv = convert_u12_to_s16(ADC_L3_U_Grid_RAW);
	ADC_L3_U_GRID_CONV_CORRECT();
	BSP_ADC_Core_3_Input_Set(BSP_ADC_CORE3_MUX_AN2);	// Switch to Current (L3_I_INV)
#endif	// U_GRID_AS_HIRES
	// L2_U_Inv
	ADC_L2_U_Inv_RAW = BSP_ADC_Core_4_Value_Get();
	ADC_L2_U_Inv_Conv = convert_u12_to_s16(ADC_L2_U_Inv_RAW);
	ADC_L2_U_INV_CONV_CORRECT();
	BSP_ADC_Core_4_Input_Set(BSP_ADC_CORE4_MUX_AN3);	// Switch to Voltage (L1_U_INV)
	// L3_U_Inv
#ifdef ADCBUF10
	ADC_L3_U_Inv_RAW = BSP_ADC_Core_5_AN10_Value_Get();
#else	// ADCBUF10
	ADC_L3_U_Inv_RAW = 0;
#endif	// ADCBUF10
	ADC_L3_U_Inv_Conv = convert_u12_to_s16(ADC_L3_U_Inv_RAW);
	ADC_L3_U_INV_CONV_CORRECT();
//	PWM_TST3_CLR();
	switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
		case 0:		// L1_U_Grid or L1_U_Mid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN4);	// Switch to Voltage (L1_U_GRID or L1_U_MID)
			break;
		case 1:		// L1_I_Grid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN12);	// Switch to Current (L1_I_GRID)
			break;
		case 2:		// L2_U_Grid or L2_U_Mid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN5);	// Switch to Voltage (L2_U_GRID or L2_U_MID)
			break;
		case 3:		// L2_I_Grid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN13);	// Switch to Current (L2_I_GRID)
			break;
		case 4:		// L3_U_Grid or L3_U_Mid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN6);	// Switch to Voltage (L3_U_GRID or L3_U_MID)
			break;
		case 5:		// L3_I_Grid
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN14);	// Switch to Current (L3_I_GRID)
			break;
		case 6:		// N_U_DC, P_U_DC
			switch(Loc_x16_Cnt & (BSP_SETTINGS_ADC_X16_CNT_MODULO - 1)) {	// Modulo 2
				case 0:		// N_U_DC
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN9);	// Switch to Voltage (N_U_DC)
					break;
				case 1:		// P_U_DC
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN8);	// Switch to Voltage (P_U_DC)
					break;
			}
			break;
		case 7:		// T1, T2, T3, AUX4
			switch(Loc_x32_Cnt & (BSP_SETTINGS_ADC_X32_CNT_MODULO - 1)) {	// Modulo 2
				case 0:		// T1
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN16);	// Switch to Temperature (T1)
					break;
				case 1:		// T2
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN17);	// Switch to Temperature (T2)
					break;
				case 2:		// T3
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN19);	// Switch to Temperature (T3)
					break;
				case 3:		// AUX4
					BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN21);	// Switch to Temperature (AUX4)
					break;
			}
			break;
	}
}
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

#if (defined HARDWARE_VERSION_1)
inline void App_ADC_Process_Trigger_Secondary(void)
{
	int16_t value_s;
	uint16_t value_u;

	// ************
	// *** READ ***
	// ************
	// L1_I_Inv
	ADC_L1_I_Inv_RAW = BSP_ADC_Core_1_Value_Get();
#ifdef APP_DATAREC_ENABLED
//	App_DataRec_Store_16bit((uint16_t)ADC_L1_I_Inv_RAW);
#endif	// APP_DATAREC_ENABLED
	ADC_L1_I_Inv_Conv = convert_u12_to_s16(ADC_L1_I_Inv_RAW);
	ADC_L1_I_INV_CONV_CORRECT();
	BSP_ADC_Core_1_Input_Set(BSP_ADC_CORE1_MUX_AN7);	// Switch to Voltage (L1_U_INV)
	// L2_I_Inv
	ADC_L2_I_Inv_RAW = BSP_ADC_Core_2_Value_Get();
	ADC_L2_I_Inv_Conv = convert_u12_to_s16(ADC_L2_I_Inv_RAW);
	ADC_L2_I_INV_CONV_CORRECT();
	BSP_ADC_Core_2_Input_Set(BSP_ADC_CORE2_MUX_AN18);	// Switch to Voltage (L2_U_INV)
	// L3_I_Inv
	ADC_L3_I_Inv_RAW = BSP_ADC_Core_3_Value_Get();
	ADC_L3_I_Inv_Conv = convert_u12_to_s16(ADC_L3_I_Inv_RAW);
	ADC_L3_I_INV_CONV_CORRECT();
	BSP_ADC_Core_3_Input_Set(BSP_ADC_CORE3_MUX_AN11);	// Switch to Voltage (L3_U_INV)
	// N_U_DC
	ADC_N_U_DC_RAW = BSP_ADC_Core_4_Value_Get();
	BSP_ADC_Core_4_Input_Set(BSP_ADC_CORE4_MUX_AN3);	// Switch to Voltage (P_U_DC)
	switch(Loc_Shared_Cnt & (BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO - 1)) {	// Modulo 16
		case 0:		// T1
#ifdef ADCBUF16
			ADC_T1_RAW = BSP_ADC_Core_5_AN16_Value_Get();
#else
			ADC_T1_RAW = 0;
#endif
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN5);	// Switch to Voltage (L2_U_MID)
			break;
		case 2:		// T2
#ifdef ADCBUF17
			ADC_T2_RAW = BSP_ADC_Core_5_AN17_Value_Get();
#else
			ADC_T2_RAW = 0;
#endif
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN6);	// Switch to Voltage (L3_U_MID)
			break;
		case 4:		// T3
#ifdef ADCBUF19
			ADC_T3_RAW = BSP_ADC_Core_5_AN19_Value_Get();
#else
			ADC_T3_RAW = 0;
#endif
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN8);	// Switch to Voltage (L1_U_GRID)
			break;
		case 6:		// L1_I_Grid
#ifdef ADCBUF12
			ADC_L1_I_Grid_RAW = BSP_ADC_Core_5_AN12_Value_Get();
#else
			ADC_L1_I_Grid_RAW = 0;
#endif
			ADC_L1_I_Grid_Conv = convert_u12_to_s16(ADC_L1_I_Grid_RAW);
			ADC_L1_I_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN9);	// Switch to Voltage (L2_U_GRID)
			break;
		case 8:		// L2_I_Grid
#ifdef ADCBUF13
			ADC_L2_I_Grid_RAW = BSP_ADC_Core_5_AN13_Value_Get();
#else
			ADC_L2_I_Grid_RAW = 0;
#endif
			ADC_L2_I_Grid_Conv = convert_u12_to_s16(ADC_L2_I_Grid_RAW);
			ADC_L2_I_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN10);	// Switch to Voltage (L3_U_GRID)
			break;
		case 10:	// L3_I_Grid
#ifdef ADCBUF14
			ADC_L3_I_Grid_RAW = BSP_ADC_Core_5_AN14_Value_Get();
#else
			ADC_L3_I_Grid_RAW = 0;
#endif
			ADC_L3_I_Grid_Conv = convert_u12_to_s16(ADC_L3_I_Grid_RAW);
			ADC_L3_I_GRID_CONV_CORRECT();
			BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN4);	// Switch to Voltage (L1_U_MID)
			break;
	}
	// ******************
	// *** ACCUMULATE ***
	// ******************
	if(Loc_Dedicated_Busy == false) {
		// L1_U_Inv
		value_s = ADC_L1_U_Inv_Conv;
		Loc_L1_U_Inv_Mean += value_s;
		Loc_L1_U_Inv_PkPk_H = (Loc_L1_U_Inv_PkPk_H > value_s) ? Loc_L1_U_Inv_PkPk_H : value_s;
		Loc_L1_U_Inv_PkPk_L = (Loc_L1_U_Inv_PkPk_L < value_s) ? Loc_L1_U_Inv_PkPk_L : value_s;
		Loc_L1_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_U_Inv
		value_s = ADC_L2_U_Inv_Conv;
		Loc_L2_U_Inv_Mean += value_s;
		Loc_L2_U_Inv_PkPk_H = (Loc_L2_U_Inv_PkPk_H > value_s) ? Loc_L2_U_Inv_PkPk_H : value_s;
		Loc_L2_U_Inv_PkPk_L = (Loc_L2_U_Inv_PkPk_L < value_s) ? Loc_L2_U_Inv_PkPk_L : value_s;
		Loc_L2_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_U_Inv
		value_s = ADC_L3_U_Inv_Conv;
		Loc_L3_U_Inv_Mean += value_s;
		Loc_L3_U_Inv_PkPk_H = (Loc_L3_U_Inv_PkPk_H > value_s) ? Loc_L3_U_Inv_PkPk_H : value_s;
		Loc_L3_U_Inv_PkPk_L = (Loc_L3_U_Inv_PkPk_L < value_s) ? Loc_L3_U_Inv_PkPk_L : value_s;
		Loc_L3_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// P_U_DC
		value_u = convert_u12_to_u16(ADC_P_U_DC_RAW);
		Loc_P_U_DC_Mean += value_u;
		Loc_P_U_DC_PkPk_H = (Loc_P_U_DC_PkPk_H > value_u) ? Loc_P_U_DC_PkPk_H : value_u;
		Loc_P_U_DC_PkPk_L = (Loc_P_U_DC_PkPk_L < value_u) ? Loc_P_U_DC_PkPk_L : value_u;
		Loc_P_U_DC_RMS += FUNCTION_MULTIPLY_UU(value_u, value_u);
		// L1_I_Inv
		value_s = ADC_L1_I_Inv_Conv;
		Loc_L1_I_Inv_Mean += value_s;
		Loc_L1_I_Inv_PkPk_H = (Loc_L1_I_Inv_PkPk_H > value_s) ? Loc_L1_I_Inv_PkPk_H : value_s;
		Loc_L1_I_Inv_PkPk_L = (Loc_L1_I_Inv_PkPk_L < value_s) ? Loc_L1_I_Inv_PkPk_L : value_s;
		Loc_L1_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_I_Inv
		value_s = ADC_L2_I_Inv_Conv;
		Loc_L2_I_Inv_Mean += value_s;
		Loc_L2_I_Inv_PkPk_H = (Loc_L2_I_Inv_PkPk_H > value_s) ? Loc_L2_I_Inv_PkPk_H : value_s;
		Loc_L2_I_Inv_PkPk_L = (Loc_L2_I_Inv_PkPk_L < value_s) ? Loc_L2_I_Inv_PkPk_L : value_s;
		Loc_L2_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_I_Inv
		value_s = ADC_L3_I_Inv_Conv;
		Loc_L3_I_Inv_Mean += value_s;
		Loc_L3_I_Inv_PkPk_H = (Loc_L3_I_Inv_PkPk_H > value_s) ? Loc_L3_I_Inv_PkPk_H : value_s;
		Loc_L3_I_Inv_PkPk_L = (Loc_L3_I_Inv_PkPk_L < value_s) ? Loc_L3_I_Inv_PkPk_L : value_s;
		Loc_L3_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// N_U_DC
		value_u = convert_u12_to_u16(ADC_N_U_DC_RAW);
		Loc_N_U_DC_Mean += value_u;
		Loc_N_U_DC_PkPk_H = (Loc_N_U_DC_PkPk_H > value_u) ? Loc_N_U_DC_PkPk_H : value_u;
		Loc_N_U_DC_PkPk_L = (Loc_N_U_DC_PkPk_L < value_u) ? Loc_N_U_DC_PkPk_L : value_u;
		Loc_N_U_DC_RMS += FUNCTION_MULTIPLY_UU(value_u, value_u);
	}
	Loc_Dedicated_Cnt += 2;
	if(Loc_Dedicated_Cnt >= (BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES * BSP_SETTINGS_ADC_DEDICATED_CORE_INP_MODULO)) {
		Loc_Dedicated_Cnt = 0;
		Loc_Dedicated_Busy = true;
	}
	if(Loc_Shared_Busy == false) {
		switch(Loc_Shared_Cnt & (BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO - 1)) {	// Modulo 16
			case 0:
				// L1_U_Mid
				value_s = ADC_L1_U_Mid_Conv;
				Loc_L1_U_Mid_Mean += value_s;
				Loc_L1_U_Mid_PkPk_H = (Loc_L1_U_Mid_PkPk_H > value_s) ? Loc_L1_U_Mid_PkPk_H : value_s;
				Loc_L1_U_Mid_PkPk_L = (Loc_L1_U_Mid_PkPk_L < value_s) ? Loc_L1_U_Mid_PkPk_L : value_s;
				Loc_L1_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				// L2_U_Mid
				value_s = ADC_L2_U_Mid_Conv;
				Loc_L2_U_Mid_Mean += value_s;
				Loc_L2_U_Mid_PkPk_H = (Loc_L2_U_Mid_PkPk_H > value_s) ? Loc_L2_U_Mid_PkPk_H : value_s;
				Loc_L2_U_Mid_PkPk_L = (Loc_L2_U_Mid_PkPk_L < value_s) ? Loc_L2_U_Mid_PkPk_L : value_s;
				Loc_L2_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 2:
				// L3_U_Mid
				value_s = ADC_L3_U_Mid_Conv;
				Loc_L3_U_Mid_Mean += value_s;
				Loc_L3_U_Mid_PkPk_H = (Loc_L3_U_Mid_PkPk_H > value_s) ? Loc_L3_U_Mid_PkPk_H : value_s;
				Loc_L3_U_Mid_PkPk_L = (Loc_L3_U_Mid_PkPk_L < value_s) ? Loc_L3_U_Mid_PkPk_L : value_s;
				Loc_L3_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				// L1_U_Grid
				value_s = ADC_L1_U_Grid_Conv;
				Loc_L1_U_Grid_Mean += value_s;
				Loc_L1_U_Grid_PkPk_H = (Loc_L1_U_Grid_PkPk_H > value_s) ? Loc_L1_U_Grid_PkPk_H : value_s;
				Loc_L1_U_Grid_PkPk_L = (Loc_L1_U_Grid_PkPk_L < value_s) ? Loc_L1_U_Grid_PkPk_L : value_s;
				Loc_L1_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 4:
				// L2_U_Grid
				value_s = ADC_L2_U_Grid_Conv;
				Loc_L2_U_Grid_Mean += value_s;
				Loc_L2_U_Grid_PkPk_H = (Loc_L2_U_Grid_PkPk_H > value_s) ? Loc_L2_U_Grid_PkPk_H : value_s;
				Loc_L2_U_Grid_PkPk_L = (Loc_L2_U_Grid_PkPk_L < value_s) ? Loc_L2_U_Grid_PkPk_L : value_s;
				Loc_L2_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				// L3_U_Grid
				value_s = ADC_L3_U_Grid_Conv;
				Loc_L3_U_Grid_Mean += value_s;
				Loc_L3_U_Grid_PkPk_H = (Loc_L3_U_Grid_PkPk_H > value_s) ? Loc_L3_U_Grid_PkPk_H : value_s;
				Loc_L3_U_Grid_PkPk_L = (Loc_L3_U_Grid_PkPk_L < value_s) ? Loc_L3_U_Grid_PkPk_L : value_s;
				Loc_L3_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 6:
				// L1_I_Grid
				value_s = ADC_L1_I_Grid_Conv;
				Loc_L1_I_Grid_Mean += value_s;
				Loc_L1_I_Grid_PkPk_H = (Loc_L1_I_Grid_PkPk_H > value_s) ? Loc_L1_I_Grid_PkPk_H : value_s;
				Loc_L1_I_Grid_PkPk_L = (Loc_L1_I_Grid_PkPk_L < value_s) ? Loc_L1_I_Grid_PkPk_L : value_s;
				Loc_L1_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				// L2_I_Grid
				value_s = ADC_L2_I_Grid_Conv;
				Loc_L2_I_Grid_Mean += value_s;
				Loc_L2_I_Grid_PkPk_H = (Loc_L2_I_Grid_PkPk_H > value_s) ? Loc_L2_I_Grid_PkPk_H : value_s;
				Loc_L2_I_Grid_PkPk_L = (Loc_L2_I_Grid_PkPk_L < value_s) ? Loc_L2_I_Grid_PkPk_L : value_s;
				Loc_L2_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 8:
				// L3_I_Grid
				value_s = ADC_L3_I_Grid_Conv;
				Loc_L3_I_Grid_Mean += value_s;
				Loc_L3_I_Grid_PkPk_H = (Loc_L3_I_Grid_PkPk_H > value_s) ? Loc_L3_I_Grid_PkPk_H : value_s;
				Loc_L3_I_Grid_PkPk_L = (Loc_L3_I_Grid_PkPk_L < value_s) ? Loc_L3_I_Grid_PkPk_L : value_s;
				Loc_L3_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				// T1
				value_u = convert_u12_to_u16(ADC_T1_RAW);
				Loc_T1_Mean += value_u;
				break;
			case 10:
				// T2
				value_u = convert_u12_to_u16(ADC_T2_RAW);
				Loc_T2_Mean += value_u;
				// T3
				value_u = convert_u12_to_u16(ADC_T3_RAW);
				Loc_T3_Mean += value_u;
				break;
		}
	}
	switch(Loc_Shared_Cnt & (BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO - 1)) {	// Modulo 16
		case 10:
			// Skip 4 steps (from 12 to 16) needed for modulo 16
			Loc_Shared_Cnt += (BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO - BSP_SETTINGS_ADC_SHARED_CORE_INP_SWITCHINGS);
			break;
	}
	Loc_Shared_Cnt += 2;
	if(Loc_Shared_Cnt >= (BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES * BSP_SETTINGS_ADC_SHARED_CORE_INP_MODULO)) {
		Loc_Shared_Cnt = 0;
		Loc_Shared_Busy = true;
	}
}
#elif (defined HARDWARE_VERSION_2)
inline void App_ADC_Process_Trigger_Secondary(void)
{
	int16_t value_s;
	uint16_t value_u;

	// ************
	// *** READ ***
	// ************
	// L1_I_Inv
	ADC_L1_I_Inv_RAW = BSP_ADC_Core_1_Value_Get();
	ADC_L1_I_Inv_Conv = convert_u12_to_s16(ADC_L1_I_Inv_RAW);
	ADC_L1_I_INV_CONV_CORRECT();
	BSP_ADC_Core_1_Input_Set(BSP_ADC_CORE1_MUX_AN7);	// Switch to Voltage (L1_U_MID or L1_U_GRID)
	// L2_I_Inv
	ADC_L2_I_Inv_RAW = BSP_ADC_Core_2_Value_Get();
	ADC_L2_I_Inv_Conv = convert_u12_to_s16(ADC_L2_I_Inv_RAW);
	ADC_L2_I_INV_CONV_CORRECT();
	BSP_ADC_Core_2_Input_Set(BSP_ADC_CORE2_MUX_AN18);	// Switch to Voltage (L2_U_MID or L2_U_GRID)
	// L3_I_Inv
	ADC_L3_I_Inv_RAW = BSP_ADC_Core_3_Value_Get();
	ADC_L3_I_Inv_Conv = convert_u12_to_s16(ADC_L3_I_Inv_RAW);
	ADC_L3_I_INV_CONV_CORRECT();
	BSP_ADC_Core_3_Input_Set(BSP_ADC_CORE3_MUX_AN11);	// Switch to Voltage (L3_U_MID or L3_U_GRID)
	// L1_U_Inv
	ADC_L1_U_Inv_RAW = BSP_ADC_Core_4_Value_Get();
	ADC_L1_U_Inv_Conv = convert_u12_to_s16(ADC_L1_U_Inv_RAW);
	ADC_L1_U_INV_CONV_CORRECT();
	BSP_ADC_Core_4_Input_Set(BSP_ADC_CORE4_MUX_AN15);	// Switch to Voltage (L2_U_INV)
	switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
		case 0:		// L1_U_Grid or L1_U_Mid
#ifndef U_GRID_AS_HIRES
			ADC_L1_U_Grid_RAW = BSP_ADC_Core_5_AN4_Value_Get();
			ADC_L1_U_Grid_Conv = convert_u12_to_s16(ADC_L1_U_Grid_RAW);
			ADC_L1_U_GRID_CONV_CORRECT();
#else	// U_GRID_AS_HIRES
			ADC_L1_U_Mid_RAW = BSP_ADC_Core_5_AN4_Value_Get();
			ADC_L1_U_Mid_Conv = convert_u12_to_s16(ADC_L1_U_Mid_RAW);
			ADC_L1_U_MID_CONV_CORRECT();
#endif	// U_GRID_AS_HIRES
			break;
		case 1:		// L1_I_Grid
#ifdef ADCBUF12
			ADC_L1_I_Grid_RAW = BSP_ADC_Core_5_AN12_Value_Get();
#else	// ADCBUF12
			ADC_L1_I_Grid_RAW = 0;
#endif	// ADCBUF12
			ADC_L1_I_Grid_Conv = convert_u12_to_s16(ADC_L1_I_Grid_RAW);
			ADC_L1_I_GRID_CONV_CORRECT();
			break;
		case 2:		// L2_U_Grid or L2_U_Mid
#ifndef U_GRID_AS_HIRES
			ADC_L2_U_Grid_RAW = BSP_ADC_Core_5_AN5_Value_Get();
			ADC_L2_U_Grid_Conv = convert_u12_to_s16(ADC_L2_U_Grid_RAW);
			ADC_L2_U_GRID_CONV_CORRECT();
#else	// U_GRID_AS_HIRES
			ADC_L2_U_Mid_RAW = BSP_ADC_Core_5_AN5_Value_Get();
			ADC_L2_U_Mid_Conv = convert_u12_to_s16(ADC_L2_U_Mid_RAW);
			ADC_L2_U_MID_CONV_CORRECT();
#endif	// U_GRID_AS_HIRES
			break;
		case 3:		// L2_I_Grid
#ifdef ADCBUF13
			ADC_L2_I_Grid_RAW = BSP_ADC_Core_5_AN13_Value_Get();
#else	// ADCBUF13
			ADC_L2_I_Grid_RAW = 0;
#endif	// ADCBUF13
			ADC_L2_I_Grid_Conv = convert_u12_to_s16(ADC_L2_I_Grid_RAW);
			ADC_L2_I_GRID_CONV_CORRECT();
			break;
		case 4:		// L3_U_Grid or L3_U_Mid
#ifndef U_GRID_AS_HIRES
			ADC_L3_U_Grid_RAW = BSP_ADC_Core_5_AN6_Value_Get();
			ADC_L3_U_Grid_Conv = convert_u12_to_s16(ADC_L3_U_Grid_RAW);
			ADC_L3_U_GRID_CONV_CORRECT();
#else	// U_GRID_AS_HIRES
			ADC_L3_U_Mid_RAW = BSP_ADC_Core_5_AN6_Value_Get();
			ADC_L3_U_Mid_Conv = convert_u12_to_s16(ADC_L3_U_Mid_RAW);
			ADC_L3_U_MID_CONV_CORRECT();
#endif	// U_GRID_AS_HIRES
			break;
		case 5:		// L3_I_Grid
#ifdef ADCBUF14
			ADC_L3_I_Grid_RAW = BSP_ADC_Core_5_AN14_Value_Get();
#else	// ADCBUF14
			ADC_L3_I_Grid_RAW = 0;
#endif	// ADCBUF14
			ADC_L3_I_Grid_Conv = convert_u12_to_s16(ADC_L3_I_Grid_RAW);
			ADC_L3_I_GRID_CONV_CORRECT();
			break;
		case 6:		// N_U_DC, P_U_DC
			switch(Loc_x16_Cnt & (BSP_SETTINGS_ADC_X16_CNT_MODULO - 1)) {	// Modulo 2
				case 0:		// N_U_DC
					ADC_N_U_DC_RAW = BSP_ADC_Core_5_AN9_Value_Get();
					break;
				case 1:		// P_U_DC
					ADC_P_U_DC_RAW = BSP_ADC_Core_5_AN8_Value_Get();
					break;
			}
			break;
		case 7:		// T1, T2, T3, AUX4
			switch(Loc_x32_Cnt & (BSP_SETTINGS_ADC_X32_CNT_MODULO - 1)) {	// Modulo 2
				case 0:		// T1
#ifdef ADCBUF16
					ADC_T1_RAW = BSP_ADC_Core_5_AN16_Value_Get();
#else	// ADCBUF16
					ADC_T1_RAW = 0;
#endif	// ADCBUF16
					break;
				case 1:		// T2
#ifdef ADCBUF17
					ADC_T2_RAW = BSP_ADC_Core_5_AN17_Value_Get();
#else	// ADCBUF17
					ADC_T2_RAW = 0;
#endif	// ADCBUF17
					break;
				case 2:		// T3
#ifdef ADCBUF19
					ADC_T3_RAW = BSP_ADC_Core_5_AN19_Value_Get();
#else	// ADCBUF19
					ADC_T3_RAW = 0;
#endif	// ADCBUF19
					break;
				case 3:		// AUX4
#ifdef ADCBUF21
					ADC_AUX4_RAW = BSP_ADC_Core_5_AN21_Value_Get();
#else	// ADCBUF21
					ADC_AUX4_RAW = 0;
#endif	// ADCBUF21
					break;
			}
			break;
	}
	BSP_ADC_Core_5_Input_Set(BSP_ADC_CORE5_MUX_AN10);	// Switch to Voltage (L3_U_INV)
	// ******************
	// *** ACCUMULATE ***
	// ******************
	if(Loc_x1_Busy == false) {
#ifndef U_GRID_AS_HIRES
		// L1_U_Mid
		value_s = ADC_L1_U_Mid_Conv;
		Loc_L1_U_Mid_Mean += value_s;
		Loc_L1_U_Mid_PkPk_H = (Loc_L1_U_Mid_PkPk_H > value_s) ? Loc_L1_U_Mid_PkPk_H : value_s;
		Loc_L1_U_Mid_PkPk_L = (Loc_L1_U_Mid_PkPk_L < value_s) ? Loc_L1_U_Mid_PkPk_L : value_s;
		Loc_L1_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_U_Mid
		value_s = ADC_L2_U_Mid_Conv;
		Loc_L2_U_Mid_Mean += value_s;
		Loc_L2_U_Mid_PkPk_H = (Loc_L2_U_Mid_PkPk_H > value_s) ? Loc_L2_U_Mid_PkPk_H : value_s;
		Loc_L2_U_Mid_PkPk_L = (Loc_L2_U_Mid_PkPk_L < value_s) ? Loc_L2_U_Mid_PkPk_L : value_s;
		Loc_L2_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_U_Mid
		value_s = ADC_L3_U_Mid_Conv;
		Loc_L3_U_Mid_Mean += value_s;
		Loc_L3_U_Mid_PkPk_H = (Loc_L3_U_Mid_PkPk_H > value_s) ? Loc_L3_U_Mid_PkPk_H : value_s;
		Loc_L3_U_Mid_PkPk_L = (Loc_L3_U_Mid_PkPk_L < value_s) ? Loc_L3_U_Mid_PkPk_L : value_s;
		Loc_L3_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#else	// U_GRID_AS_HIRES
		// L1_U_Grid
		value_s = ADC_L1_U_Grid_Conv;
		Loc_L1_U_Grid_Mean += value_s;
		Loc_L1_U_Grid_PkPk_H = (Loc_L1_U_Grid_PkPk_H > value_s) ? Loc_L1_U_Grid_PkPk_H : value_s;
		Loc_L1_U_Grid_PkPk_L = (Loc_L1_U_Grid_PkPk_L < value_s) ? Loc_L1_U_Grid_PkPk_L : value_s;
		Loc_L1_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_U_Grid
		value_s = ADC_L2_U_Grid_Conv;
		Loc_L2_U_Grid_Mean += value_s;
		Loc_L2_U_Grid_PkPk_H = (Loc_L2_U_Grid_PkPk_H > value_s) ? Loc_L2_U_Grid_PkPk_H : value_s;
		Loc_L2_U_Grid_PkPk_L = (Loc_L2_U_Grid_PkPk_L < value_s) ? Loc_L2_U_Grid_PkPk_L : value_s;
		Loc_L2_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_U_Grid
		value_s = ADC_L3_U_Grid_Conv;
		Loc_L3_U_Grid_Mean += value_s;
		Loc_L3_U_Grid_PkPk_H = (Loc_L3_U_Grid_PkPk_H > value_s) ? Loc_L3_U_Grid_PkPk_H : value_s;
		Loc_L3_U_Grid_PkPk_L = (Loc_L3_U_Grid_PkPk_L < value_s) ? Loc_L3_U_Grid_PkPk_L : value_s;
		Loc_L3_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#endif	// U_GRID_AS_HIRES
		// L1_U_Inv
		value_s = ADC_L1_U_Inv_Conv;
		Loc_L1_U_Inv_Mean += value_s;
		Loc_L1_U_Inv_PkPk_H = (Loc_L1_U_Inv_PkPk_H > value_s) ? Loc_L1_U_Inv_PkPk_H : value_s;
		Loc_L1_U_Inv_PkPk_L = (Loc_L1_U_Inv_PkPk_L < value_s) ? Loc_L1_U_Inv_PkPk_L : value_s;
		Loc_L1_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_U_Inv
		value_s = ADC_L2_U_Inv_Conv;
		Loc_L2_U_Inv_Mean += value_s;
		Loc_L2_U_Inv_PkPk_H = (Loc_L2_U_Inv_PkPk_H > value_s) ? Loc_L2_U_Inv_PkPk_H : value_s;
		Loc_L2_U_Inv_PkPk_L = (Loc_L2_U_Inv_PkPk_L < value_s) ? Loc_L2_U_Inv_PkPk_L : value_s;
		Loc_L2_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_U_Inv
		value_s = ADC_L3_U_Inv_Conv;
		Loc_L3_U_Inv_Mean += value_s;
		Loc_L3_U_Inv_PkPk_H = (Loc_L3_U_Inv_PkPk_H > value_s) ? Loc_L3_U_Inv_PkPk_H : value_s;
		Loc_L3_U_Inv_PkPk_L = (Loc_L3_U_Inv_PkPk_L < value_s) ? Loc_L3_U_Inv_PkPk_L : value_s;
		Loc_L3_U_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L1_I_Inv
		value_s = ADC_L1_I_Inv_Conv;
		Loc_L1_I_Inv_Mean += value_s;
		Loc_L1_I_Inv_PkPk_H = (Loc_L1_I_Inv_PkPk_H > value_s) ? Loc_L1_I_Inv_PkPk_H : value_s;
		Loc_L1_I_Inv_PkPk_L = (Loc_L1_I_Inv_PkPk_L < value_s) ? Loc_L1_I_Inv_PkPk_L : value_s;
		Loc_L1_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L2_I_Inv
		value_s = ADC_L2_I_Inv_Conv;
		Loc_L2_I_Inv_Mean += value_s;
		Loc_L2_I_Inv_PkPk_H = (Loc_L2_I_Inv_PkPk_H > value_s) ? Loc_L2_I_Inv_PkPk_H : value_s;
		Loc_L2_I_Inv_PkPk_L = (Loc_L2_I_Inv_PkPk_L < value_s) ? Loc_L2_I_Inv_PkPk_L : value_s;
		Loc_L2_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
		// L3_I_Inv
		value_s = ADC_L3_I_Inv_Conv;
		Loc_L3_I_Inv_Mean += value_s;
		Loc_L3_I_Inv_PkPk_H = (Loc_L3_I_Inv_PkPk_H > value_s) ? Loc_L3_I_Inv_PkPk_H : value_s;
		Loc_L3_I_Inv_PkPk_L = (Loc_L3_I_Inv_PkPk_L < value_s) ? Loc_L3_I_Inv_PkPk_L : value_s;
		Loc_L3_I_Inv_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
	}
	if(Loc_x8_Busy == false) {
		switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
			case 0:		// L1_U_Grid or L1_U_Mid
#ifndef U_GRID_AS_HIRES
				value_s = ADC_L1_U_Grid_Conv;
				Loc_L1_U_Grid_Mean += value_s;
				Loc_L1_U_Grid_PkPk_H = (Loc_L1_U_Grid_PkPk_H > value_s) ? Loc_L1_U_Grid_PkPk_H : value_s;
				Loc_L1_U_Grid_PkPk_L = (Loc_L1_U_Grid_PkPk_L < value_s) ? Loc_L1_U_Grid_PkPk_L : value_s;
				Loc_L1_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#else	// U_GRID_AS_HIRES
				value_s = ADC_L1_U_Mid_Conv;
				Loc_L1_U_Mid_Mean += value_s;
				Loc_L1_U_Mid_PkPk_H = (Loc_L1_U_Mid_PkPk_H > value_s) ? Loc_L1_U_Mid_PkPk_H : value_s;
				Loc_L1_U_Mid_PkPk_L = (Loc_L1_U_Mid_PkPk_L < value_s) ? Loc_L1_U_Mid_PkPk_L : value_s;
				Loc_L1_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#endif	// U_GRID_AS_HIRES
				break;
			case 1:		// L1_I_Grid
				value_s = ADC_L1_I_Grid_Conv;
				Loc_L1_I_Grid_Mean += value_s;
				Loc_L1_I_Grid_PkPk_H = (Loc_L1_I_Grid_PkPk_H > value_s) ? Loc_L1_I_Grid_PkPk_H : value_s;
				Loc_L1_I_Grid_PkPk_L = (Loc_L1_I_Grid_PkPk_L < value_s) ? Loc_L1_I_Grid_PkPk_L : value_s;
				Loc_L1_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 2:		// L2_U_Grid or L2_U_Mid
#ifndef U_GRID_AS_HIRES
				value_s = ADC_L2_U_Grid_Conv;
				Loc_L2_U_Grid_Mean += value_s;
				Loc_L2_U_Grid_PkPk_H = (Loc_L2_U_Grid_PkPk_H > value_s) ? Loc_L2_U_Grid_PkPk_H : value_s;
				Loc_L2_U_Grid_PkPk_L = (Loc_L2_U_Grid_PkPk_L < value_s) ? Loc_L2_U_Grid_PkPk_L : value_s;
				Loc_L2_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#else	// U_GRID_AS_HIRES
				value_s = ADC_L2_U_Mid_Conv;
				Loc_L2_U_Mid_Mean += value_s;
				Loc_L2_U_Mid_PkPk_H = (Loc_L2_U_Mid_PkPk_H > value_s) ? Loc_L2_U_Mid_PkPk_H : value_s;
				Loc_L2_U_Mid_PkPk_L = (Loc_L2_U_Mid_PkPk_L < value_s) ? Loc_L2_U_Mid_PkPk_L : value_s;
				Loc_L2_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#endif	// U_GRID_AS_HIRES
				break;
			case 3:		// L2_I_Grid
				value_s = ADC_L2_I_Grid_Conv;
				Loc_L2_I_Grid_Mean += value_s;
				Loc_L2_I_Grid_PkPk_H = (Loc_L2_I_Grid_PkPk_H > value_s) ? Loc_L2_I_Grid_PkPk_H : value_s;
				Loc_L2_I_Grid_PkPk_L = (Loc_L2_I_Grid_PkPk_L < value_s) ? Loc_L2_I_Grid_PkPk_L : value_s;
				Loc_L2_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
			case 4:		// L3_U_Grid or L3_U_Mid
#ifndef U_GRID_AS_HIRES
				value_s = ADC_L3_U_Grid_Conv;
				Loc_L3_U_Grid_Mean += value_s;
				Loc_L3_U_Grid_PkPk_H = (Loc_L3_U_Grid_PkPk_H > value_s) ? Loc_L3_U_Grid_PkPk_H : value_s;
				Loc_L3_U_Grid_PkPk_L = (Loc_L3_U_Grid_PkPk_L < value_s) ? Loc_L3_U_Grid_PkPk_L : value_s;
				Loc_L3_U_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#else	// U_GRID_AS_HIRES
				value_s = ADC_L3_U_Mid_Conv;
				Loc_L3_U_Mid_Mean += value_s;
				Loc_L3_U_Mid_PkPk_H = (Loc_L3_U_Mid_PkPk_H > value_s) ? Loc_L3_U_Mid_PkPk_H : value_s;
				Loc_L3_U_Mid_PkPk_L = (Loc_L3_U_Mid_PkPk_L < value_s) ? Loc_L3_U_Mid_PkPk_L : value_s;
				Loc_L3_U_Mid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
#endif	// U_GRID_AS_HIRES
				break;
			case 5:		// L3_I_Grid
				value_s = ADC_L3_I_Grid_Conv;
				Loc_L3_I_Grid_Mean += value_s;
				Loc_L3_I_Grid_PkPk_H = (Loc_L3_I_Grid_PkPk_H > value_s) ? Loc_L3_I_Grid_PkPk_H : value_s;
				Loc_L3_I_Grid_PkPk_L = (Loc_L3_I_Grid_PkPk_L < value_s) ? Loc_L3_I_Grid_PkPk_L : value_s;
				Loc_L3_I_Grid_RMS += FUNCTION_MULTIPLY_SS(value_s, value_s);
				break;
/*
			case 6:		// N_U_DC, P_U_DC
				break;
			case 7:		// T1, T2, T3, AUX4
				break;
*/ 
		}
	}
	if(Loc_x16_Busy == false) {
		switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
			case 6:		// N_U_DC, P_U_DC
				switch(Loc_x16_Cnt & (BSP_SETTINGS_ADC_X16_CNT_MODULO - 1)) {	// Modulo 2
					case 0:		// N_U_DC
						value_u = convert_u12_to_u16(ADC_N_U_DC_RAW);
						Loc_N_U_DC_Mean += value_u;
						Loc_N_U_DC_PkPk_H = (Loc_N_U_DC_PkPk_H > value_u) ? Loc_N_U_DC_PkPk_H : value_u;
						Loc_N_U_DC_PkPk_L = (Loc_N_U_DC_PkPk_L < value_u) ? Loc_N_U_DC_PkPk_L : value_u;
						Loc_N_U_DC_RMS += FUNCTION_MULTIPLY_UU(value_u, value_u);
						break;
					case 1:		// P_U_DC
						value_u = convert_u12_to_u16(ADC_P_U_DC_RAW);
						Loc_P_U_DC_Mean += value_u;
						Loc_P_U_DC_PkPk_H = (Loc_P_U_DC_PkPk_H > value_u) ? Loc_P_U_DC_PkPk_H : value_u;
						Loc_P_U_DC_PkPk_L = (Loc_P_U_DC_PkPk_L < value_u) ? Loc_P_U_DC_PkPk_L : value_u;
						Loc_P_U_DC_RMS += FUNCTION_MULTIPLY_UU(value_u, value_u);
						break;
				}
				break;
		}
	}
	if(Loc_x32_Busy == false) {
		switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
			case 7:		// T1, T2, T3, AUX4
				switch(Loc_x32_Cnt & (BSP_SETTINGS_ADC_X32_CNT_MODULO - 1)) {	// Modulo 2
					case 0:		// T1
						value_u = convert_u12_to_u16(ADC_T1_RAW);
						Loc_T1_Mean += value_u;
						break;
					case 1:		// T2
						value_u = convert_u12_to_u16(ADC_T2_RAW);
						Loc_T2_Mean += value_u;
						break;
					case 2:		// T3
						value_u = convert_u12_to_u16(ADC_T3_RAW);
						Loc_T3_Mean += value_u;
						break;
					case 3:		// AUX4
						value_u = convert_u12_to_u16(ADC_AUX4_RAW);
						Loc_AUX4_Mean += value_u;
						break;
				}
				break;
		}
	}
	Loc_x1_Cnt++;
	if(Loc_x1_Cnt >= (BSP_SETTINGS_ADC_X1_SIG_SAMPLES * BSP_SETTINGS_ADC_X1_CNT_MODULO)) {
		Loc_x1_Cnt = 0;
		Loc_x1_Busy = true;
	}
	switch(Loc_x8_Cnt & (BSP_SETTINGS_ADC_X8_CNT_MODULO - 1)) {	// Modulo 8
		case 6:		// N_U_DC, P_U_DC
			Loc_x16_Cnt++;
			if(Loc_x16_Cnt >= (BSP_SETTINGS_ADC_X16_SIG_SAMPLES * BSP_SETTINGS_ADC_X16_CNT_MODULO)) {
				Loc_x16_Cnt = 0;
				Loc_x16_Busy = true;
			}
			break;
		case 7:		// T1, T2, T3, AUX4
			Loc_x32_Cnt++;
			if(Loc_x32_Cnt >= (BSP_SETTINGS_ADC_X32_SIG_SAMPLES * BSP_SETTINGS_ADC_X32_CNT_MODULO)) {
				Loc_x32_Cnt = 0;
				Loc_x32_Busy = true;
			}
			break;
	}
	Loc_x8_Cnt++;
	if(Loc_x8_Cnt >= (BSP_SETTINGS_ADC_X8_SIG_SAMPLES * BSP_SETTINGS_ADC_X8_CNT_MODULO)) {
		Loc_x8_Cnt = 0;
		Loc_x8_Busy = true;
	}
}
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

inline void App_ADC_Process_IRQ(void)
{
	static uint16_t Counter = 0;

	switch(BSP_PWM_Trigger_Sync) {
		case 0:
			App_ADC_Process_Trigger_Primary();
			BSP_PWM_Trigger_Sync++;
			App_DPLL_Process(&Counter);
			break;
		case 1:
			App_ADC_Process_Trigger_Secondary();
			PWM_TST2_CLR();
			Nop();
			PWM_TST2_SET();
			App_PWM_Process_IRQ();
			PWM_TST2_CLR();
			Nop();
			PWM_TST2_SET();
			App_DPLL_Process_Control();
			Counter += 205;
			break;
	}
}

#if (defined HARDWARE_VERSION_1)
void App_ADC_Process_IDLE(void *Parameters)
{
	(void)Parameters;
	if(Loc_Dedicated_Busy == true) {
		// L1_U_Inv
		ADC_L1_U_Inv_Mean = Loc_L1_U_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L1_U_Inv_Mean = 0;
		ADC_L1_U_Inv_Pk_L = Loc_L1_U_Inv_PkPk_L;
		ADC_L1_U_Inv_Pk_H = Loc_L1_U_Inv_PkPk_H;
		ADC_L1_U_Inv_PkPk = Loc_L1_U_Inv_PkPk_H - Loc_L1_U_Inv_PkPk_L;
		Loc_L1_U_Inv_PkPk_H = INT16_MIN;
		Loc_L1_U_Inv_PkPk_L = INT16_MAX;
		ADC_L1_U_Inv_RMS = sqrt(Loc_L1_U_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L1_U_Inv_RMS = 0;
		// L2_U_Inv
		ADC_L2_U_Inv_Mean = Loc_L2_U_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L2_U_Inv_Mean = 0;
		ADC_L2_U_Inv_Pk_L = Loc_L2_U_Inv_PkPk_L;
		ADC_L2_U_Inv_Pk_H = Loc_L2_U_Inv_PkPk_H;
		ADC_L2_U_Inv_PkPk = Loc_L2_U_Inv_PkPk_H - Loc_L2_U_Inv_PkPk_L;
		Loc_L2_U_Inv_PkPk_H = INT16_MIN;
		Loc_L2_U_Inv_PkPk_L = INT16_MAX;
		ADC_L2_U_Inv_RMS = sqrt(Loc_L2_U_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L2_U_Inv_RMS = 0;
		// L3_U_Inv
		ADC_L3_U_Inv_Mean = Loc_L3_U_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L3_U_Inv_Mean = 0;
		ADC_L3_U_Inv_Pk_L = Loc_L3_U_Inv_PkPk_L;
		ADC_L3_U_Inv_Pk_H = Loc_L3_U_Inv_PkPk_H;
		ADC_L3_U_Inv_PkPk = Loc_L3_U_Inv_PkPk_H - Loc_L3_U_Inv_PkPk_L;
		Loc_L3_U_Inv_PkPk_H = INT16_MIN;
		Loc_L3_U_Inv_PkPk_L = INT16_MAX;
		ADC_L3_U_Inv_RMS = sqrt(Loc_L3_U_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L3_U_Inv_RMS = 0;
		// P_U_DC
		ADC_P_U_DC_Mean = Loc_P_U_DC_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_P_U_DC_Mean = 0;
		ADC_P_U_DC_PkPk = Loc_P_U_DC_PkPk_H - Loc_P_U_DC_PkPk_L;
		Loc_P_U_DC_PkPk_H = UINT16_MIN;
		Loc_P_U_DC_PkPk_L = UINT16_MAX;
		ADC_P_U_DC_RMS = sqrt(Loc_P_U_DC_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_P_U_DC_RMS = 0;
		// L1_I_Inv
		ADC_L1_I_Inv_Mean = Loc_L1_I_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L1_I_Inv_Mean = 0;
		ADC_L1_I_Inv_PkPk = Loc_L1_I_Inv_PkPk_H - Loc_L1_I_Inv_PkPk_L;
		Loc_L1_I_Inv_PkPk_H = INT16_MIN;
		Loc_L1_I_Inv_PkPk_L = INT16_MAX;
		ADC_L1_I_Inv_RMS = sqrt(Loc_L1_I_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L1_I_Inv_RMS = 0;
		// L2_I_Inv
		ADC_L2_I_Inv_Mean = Loc_L2_I_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L2_I_Inv_Mean = 0;
		ADC_L2_I_Inv_PkPk = Loc_L2_I_Inv_PkPk_H - Loc_L2_I_Inv_PkPk_L;
		Loc_L2_I_Inv_PkPk_H = INT16_MIN;
		Loc_L2_I_Inv_PkPk_L = INT16_MAX;
		ADC_L2_I_Inv_RMS = sqrt(Loc_L2_I_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L2_I_Inv_RMS = 0;
		// L3_I_Inv
		ADC_L3_I_Inv_Mean = Loc_L3_I_Inv_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_L3_I_Inv_Mean = 0;
		ADC_L3_I_Inv_PkPk = Loc_L3_I_Inv_PkPk_H - Loc_L3_I_Inv_PkPk_L;
		Loc_L3_I_Inv_PkPk_H = INT16_MIN;
		Loc_L3_I_Inv_PkPk_L = INT16_MAX;
		ADC_L3_I_Inv_RMS = sqrt(Loc_L3_I_Inv_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_L3_I_Inv_RMS = 0;
		// N_U_DC
		ADC_N_U_DC_Mean = Loc_N_U_DC_Mean / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES;
		Loc_N_U_DC_Mean = 0;
		ADC_N_U_DC_PkPk = Loc_N_U_DC_PkPk_H - Loc_N_U_DC_PkPk_L;
		Loc_N_U_DC_PkPk_H = UINT16_MIN;
		Loc_N_U_DC_PkPk_L = UINT16_MAX;
		ADC_N_U_DC_RMS = sqrt(Loc_N_U_DC_RMS / BSP_SETTINGS_ADC_DEDICATED_CORE_SAMPLES);
		Loc_N_U_DC_RMS = 0;
		// Reset flag
		Loc_Dedicated_Busy = false;
		if(Loc_Dedicated_CntDwn > 0) {
			if(Loc_Dedicated_CntDwn == 1) {
				if(ADC_Calib == true) {
#ifdef VOLTAGE_OFFSET_CORRECTION
					Loc_L1_U_Inv_Error = 0 - ADC_L1_U_Inv_Mean;
					Loc_L2_U_Inv_Error = 0 - ADC_L2_U_Inv_Mean;
					Loc_L3_U_Inv_Error = 0 - ADC_L3_U_Inv_Mean;
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
					Loc_L1_I_Inv_Error = 0 - ADC_L1_I_Inv_Mean;
					Loc_L2_I_Inv_Error = 0 - ADC_L2_I_Inv_Mean;
					Loc_L3_I_Inv_Error = 0 - ADC_L3_I_Inv_Mean;
#endif	// CURRENT_OFFSET_CORRECTION
				}
				if(Loc_Shared_CntDwn == 0) {
					ADC_Ready = true;
					ADC_Save_to_NVM();
				}
			}
			Loc_Dedicated_CntDwn--;
		}
	}
	if(Loc_Shared_Busy == true) {
		// L1_U_Mid
		ADC_L1_U_Mid_Mean = Loc_L1_U_Mid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L1_U_Mid_Mean = 0;
		ADC_L1_U_Mid_Pk_L = Loc_L1_U_Mid_PkPk_L;
		ADC_L1_U_Mid_Pk_H = Loc_L1_U_Mid_PkPk_H;
		ADC_L1_U_Mid_PkPk = Loc_L1_U_Mid_PkPk_H - Loc_L1_U_Mid_PkPk_L;
		Loc_L1_U_Mid_PkPk_H = INT16_MIN;
		Loc_L1_U_Mid_PkPk_L = INT16_MAX;
		ADC_L1_U_Mid_RMS = sqrt(Loc_L1_U_Mid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L1_U_Mid_RMS = 0;
		// L2_U_Mid
		ADC_L2_U_Mid_Mean = Loc_L2_U_Mid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L2_U_Mid_Mean = 0;
		ADC_L2_U_Mid_Pk_L = Loc_L2_U_Mid_PkPk_L;
		ADC_L2_U_Mid_Pk_H = Loc_L2_U_Mid_PkPk_H;
		ADC_L2_U_Mid_PkPk = Loc_L2_U_Mid_PkPk_H - Loc_L2_U_Mid_PkPk_L;
		Loc_L2_U_Mid_PkPk_H = INT16_MIN;
		Loc_L2_U_Mid_PkPk_L = INT16_MAX;
		ADC_L2_U_Mid_RMS = sqrt(Loc_L2_U_Mid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L2_U_Mid_RMS = 0;
		// L3_U_Mid
		ADC_L3_U_Mid_Mean = Loc_L3_U_Mid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L3_U_Mid_Mean = 0;
		ADC_L3_U_Mid_Pk_L = Loc_L3_U_Mid_PkPk_L;
		ADC_L3_U_Mid_Pk_H = Loc_L3_U_Mid_PkPk_H;
		ADC_L3_U_Mid_PkPk = Loc_L3_U_Mid_PkPk_H - Loc_L3_U_Mid_PkPk_L;
		Loc_L3_U_Mid_PkPk_H = INT16_MIN;
		Loc_L3_U_Mid_PkPk_L = INT16_MAX;
		ADC_L3_U_Mid_RMS = sqrt(Loc_L3_U_Mid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L3_U_Mid_RMS = 0;
		// L1_U_Grid
		ADC_L1_U_Grid_Mean = Loc_L1_U_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L1_U_Grid_Mean = 0;
		ADC_L1_U_Grid_Pk_L = Loc_L1_U_Grid_PkPk_L;
		ADC_L1_U_Grid_Pk_H = Loc_L1_U_Grid_PkPk_H;
		ADC_L1_U_Grid_PkPk = Loc_L1_U_Grid_PkPk_H - Loc_L1_U_Grid_PkPk_L;
		Loc_L1_U_Grid_PkPk_H = INT16_MIN;
		Loc_L1_U_Grid_PkPk_L = INT16_MAX;
		ADC_L1_U_Grid_RMS = sqrt(Loc_L1_U_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L1_U_Grid_RMS = 0;
		// L2_U_Grid
		ADC_L2_U_Grid_Mean = Loc_L2_U_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L2_U_Grid_Mean = 0;
		ADC_L2_U_Grid_Pk_L = Loc_L2_U_Grid_PkPk_L;
		ADC_L2_U_Grid_Pk_H = Loc_L2_U_Grid_PkPk_H;
		ADC_L2_U_Grid_PkPk = Loc_L2_U_Grid_PkPk_H - Loc_L2_U_Grid_PkPk_L;
		Loc_L2_U_Grid_PkPk_H = INT16_MIN;
		Loc_L2_U_Grid_PkPk_L = INT16_MAX;
		ADC_L2_U_Grid_RMS = sqrt(Loc_L2_U_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L2_U_Grid_RMS = 0;
		// L3_U_Grid
		ADC_L3_U_Grid_Mean = Loc_L3_U_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L3_U_Grid_Mean = 0;
		ADC_L3_U_Grid_Pk_L = Loc_L3_U_Grid_PkPk_L;
		ADC_L3_U_Grid_Pk_H = Loc_L3_U_Grid_PkPk_H;
		ADC_L3_U_Grid_PkPk = Loc_L3_U_Grid_PkPk_H - Loc_L3_U_Grid_PkPk_L;
		Loc_L3_U_Grid_PkPk_H = INT16_MIN;
		Loc_L3_U_Grid_PkPk_L = INT16_MAX;
		ADC_L3_U_Grid_RMS = sqrt(Loc_L3_U_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L3_U_Grid_RMS = 0;
		// L2_I_Grid
		ADC_L1_I_Grid_Mean = Loc_L1_I_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L1_I_Grid_Mean = 0;
		ADC_L1_I_Grid_PkPk = Loc_L1_I_Grid_PkPk_H - Loc_L1_I_Grid_PkPk_L;
		Loc_L1_I_Grid_PkPk_H = INT16_MIN;
		Loc_L1_I_Grid_PkPk_L = INT16_MAX;
		ADC_L1_I_Grid_RMS = sqrt(Loc_L1_I_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L1_I_Grid_RMS = 0;
		// L2_I_Grid
		ADC_L2_I_Grid_Mean = Loc_L2_I_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L2_I_Grid_Mean = 0;
		ADC_L2_I_Grid_PkPk = Loc_L2_I_Grid_PkPk_H - Loc_L2_I_Grid_PkPk_L;
		Loc_L2_I_Grid_PkPk_H = INT16_MIN;
		Loc_L2_I_Grid_PkPk_L = INT16_MAX;
		ADC_L2_I_Grid_RMS = sqrt(Loc_L2_I_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L2_I_Grid_RMS = 0;
		// L3_I_Grid
		ADC_L3_I_Grid_Mean = Loc_L3_I_Grid_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_L3_I_Grid_Mean = 0;
		ADC_L3_I_Grid_PkPk = Loc_L3_I_Grid_PkPk_H - Loc_L3_I_Grid_PkPk_L;
		Loc_L3_I_Grid_PkPk_H = INT16_MIN;
		Loc_L3_I_Grid_PkPk_L = INT16_MAX;
		ADC_L3_I_Grid_RMS = sqrt(Loc_L3_I_Grid_RMS / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES);
		Loc_L3_I_Grid_RMS = 0;
		// T1
		ADC_T1_Mean = Loc_T1_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_T1_Mean = 0;
		// T2
		ADC_T2_Mean = Loc_T2_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_T2_Mean = 0;
		// T3
		ADC_T3_Mean = Loc_T3_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_T3_Mean = 0;
		// AUX4
		ADC_AUX4_Mean = Loc_AUX4_Mean / BSP_SETTINGS_ADC_SHARED_CORE_SAMPLES;
		Loc_AUX4_Mean = 0;
		// Reset flag
		Loc_Shared_Busy = false;
		if(Loc_Shared_CntDwn > 0) {
			if(Loc_Shared_CntDwn == 1) {
				if(ADC_Calib == true) {
#ifdef VOLTAGE_OFFSET_CORRECTION
					Loc_L1_U_Mid_Error = 0 - ADC_L1_U_Mid_Mean;
					Loc_L2_U_Mid_Error = 0 - ADC_L2_U_Mid_Mean;
					Loc_L3_U_Mid_Error = 0 - ADC_L3_U_Mid_Mean;
					Loc_L1_U_Grid_Error = 0 - ADC_L1_U_Grid_Mean;
					Loc_L2_U_Grid_Error = 0 - ADC_L2_U_Grid_Mean;
					Loc_L3_U_Grid_Error = 0 - ADC_L3_U_Grid_Mean;
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
					Loc_L1_I_Grid_Error = 0 - ADC_L1_I_Grid_Mean;
					Loc_L2_I_Grid_Error = 0 - ADC_L2_I_Grid_Mean;
					Loc_L3_I_Grid_Error = 0 - ADC_L3_I_Grid_Mean;
#endif	// CURRENT_OFFSET_CORRECTION
				}
				if(Loc_Dedicated_CntDwn == 0) {
					ADC_Ready = true;
					ADC_Save_to_NVM();
				}
			}
			Loc_Shared_CntDwn--;
		}
	}
}
#elif (defined HARDWARE_VERSION_2)
void App_ADC_Process_IDLE(void *Parameters)
{
	(void)Parameters;
	if(Loc_x1_Busy == true) {
#ifndef U_GRID_AS_HIRES
		// L1_U_Mid
		ADC_L1_U_Mid_Mean = Loc_L1_U_Mid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L1_U_Mid_Mean = 0;
		ADC_L1_U_Mid_Pk_L = Loc_L1_U_Mid_PkPk_L;
		ADC_L1_U_Mid_Pk_H = Loc_L1_U_Mid_PkPk_H;
		ADC_L1_U_Mid_PkPk = Loc_L1_U_Mid_PkPk_H - Loc_L1_U_Mid_PkPk_L;
		Loc_L1_U_Mid_PkPk_H = INT16_MIN;
		Loc_L1_U_Mid_PkPk_L = INT16_MAX;
		ADC_L1_U_Mid_RMS = sqrt(Loc_L1_U_Mid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L1_U_Mid_RMS = 0;
		// L2_U_Mid
		ADC_L2_U_Mid_Mean = Loc_L2_U_Mid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L2_U_Mid_Mean = 0;
		ADC_L2_U_Mid_Pk_L = Loc_L2_U_Mid_PkPk_L;
		ADC_L2_U_Mid_Pk_H = Loc_L2_U_Mid_PkPk_H;
		ADC_L2_U_Mid_PkPk = Loc_L2_U_Mid_PkPk_H - Loc_L2_U_Mid_PkPk_L;
		Loc_L2_U_Mid_PkPk_H = INT16_MIN;
		Loc_L2_U_Mid_PkPk_L = INT16_MAX;
		ADC_L2_U_Mid_RMS = sqrt(Loc_L2_U_Mid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L2_U_Mid_RMS = 0;
		// L3_U_Mid
		ADC_L3_U_Mid_Mean = Loc_L3_U_Mid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L3_U_Mid_Mean = 0;
		ADC_L3_U_Mid_Pk_L = Loc_L3_U_Mid_PkPk_L;
		ADC_L3_U_Mid_Pk_H = Loc_L3_U_Mid_PkPk_H;
		ADC_L3_U_Mid_PkPk = Loc_L3_U_Mid_PkPk_H - Loc_L3_U_Mid_PkPk_L;
		Loc_L3_U_Mid_PkPk_H = INT16_MIN;
		Loc_L3_U_Mid_PkPk_L = INT16_MAX;
		ADC_L3_U_Mid_RMS = sqrt(Loc_L3_U_Mid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L3_U_Mid_RMS = 0;
#else	// U_GRID_AS_HIRES
		// L1_U_Grid
		ADC_L1_U_Grid_Mean = Loc_L1_U_Grid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L1_U_Grid_Mean = 0;
		ADC_L1_U_Grid_Pk_L = Loc_L1_U_Grid_PkPk_L;
		ADC_L1_U_Grid_Pk_H = Loc_L1_U_Grid_PkPk_H;
		ADC_L1_U_Grid_PkPk = Loc_L1_U_Grid_PkPk_H - Loc_L1_U_Grid_PkPk_L;
		Loc_L1_U_Grid_PkPk_H = INT16_MIN;
		Loc_L1_U_Grid_PkPk_L = INT16_MAX;
		ADC_L1_U_Grid_RMS = sqrt(Loc_L1_U_Grid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L1_U_Grid_RMS = 0;
		// L2_U_Grid
		ADC_L2_U_Grid_Mean = Loc_L2_U_Grid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L2_U_Grid_Mean = 0;
		ADC_L2_U_Grid_Pk_L = Loc_L2_U_Grid_PkPk_L;
		ADC_L2_U_Grid_Pk_H = Loc_L2_U_Grid_PkPk_H;
		ADC_L2_U_Grid_PkPk = Loc_L2_U_Grid_PkPk_H - Loc_L2_U_Grid_PkPk_L;
		Loc_L2_U_Grid_PkPk_H = INT16_MIN;
		Loc_L2_U_Grid_PkPk_L = INT16_MAX;
		ADC_L2_U_Grid_RMS = sqrt(Loc_L2_U_Grid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L2_U_Grid_RMS = 0;
		// L3_U_Grid
		ADC_L3_U_Grid_Mean = Loc_L3_U_Grid_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L3_U_Grid_Mean = 0;
		ADC_L3_U_Grid_Pk_L = Loc_L3_U_Grid_PkPk_L;
		ADC_L3_U_Grid_Pk_H = Loc_L3_U_Grid_PkPk_H;
		ADC_L3_U_Grid_PkPk = Loc_L3_U_Grid_PkPk_H - Loc_L3_U_Grid_PkPk_L;
		Loc_L3_U_Grid_PkPk_H = INT16_MIN;
		Loc_L3_U_Grid_PkPk_L = INT16_MAX;
		ADC_L3_U_Grid_RMS = sqrt(Loc_L3_U_Grid_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L3_U_Grid_RMS = 0;
#endif	// U_GRID_AS_HIRES
		// L1_U_Inv
		ADC_L1_U_Inv_Mean = Loc_L1_U_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L1_U_Inv_Mean = 0;
		ADC_L1_U_Inv_Pk_L = Loc_L1_U_Inv_PkPk_L;
		ADC_L1_U_Inv_Pk_H = Loc_L1_U_Inv_PkPk_H;
		ADC_L1_U_Inv_PkPk = Loc_L1_U_Inv_PkPk_H - Loc_L1_U_Inv_PkPk_L;
		Loc_L1_U_Inv_PkPk_H = INT16_MIN;
		Loc_L1_U_Inv_PkPk_L = INT16_MAX;
		ADC_L1_U_Inv_RMS = sqrt(Loc_L1_U_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L1_U_Inv_RMS = 0;
		// L2_U_Inv
		ADC_L2_U_Inv_Mean = Loc_L2_U_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L2_U_Inv_Mean = 0;
		ADC_L2_U_Inv_Pk_L = Loc_L2_U_Inv_PkPk_L;
		ADC_L2_U_Inv_Pk_H = Loc_L2_U_Inv_PkPk_H;
		ADC_L2_U_Inv_PkPk = Loc_L2_U_Inv_PkPk_H - Loc_L2_U_Inv_PkPk_L;
		Loc_L2_U_Inv_PkPk_H = INT16_MIN;
		Loc_L2_U_Inv_PkPk_L = INT16_MAX;
		ADC_L2_U_Inv_RMS = sqrt(Loc_L2_U_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L2_U_Inv_RMS = 0;
		// L3_U_Inv
		ADC_L3_U_Inv_Mean = Loc_L3_U_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L3_U_Inv_Mean = 0;
		ADC_L3_U_Inv_Pk_L = Loc_L3_U_Inv_PkPk_L;
		ADC_L3_U_Inv_Pk_H = Loc_L3_U_Inv_PkPk_H;
		ADC_L3_U_Inv_PkPk = Loc_L3_U_Inv_PkPk_H - Loc_L3_U_Inv_PkPk_L;
		Loc_L3_U_Inv_PkPk_H = INT16_MIN;
		Loc_L3_U_Inv_PkPk_L = INT16_MAX;
		ADC_L3_U_Inv_RMS = sqrt(Loc_L3_U_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L3_U_Inv_RMS = 0;
		// L1_I_Inv
		ADC_L1_I_Inv_Mean = Loc_L1_I_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L1_I_Inv_Mean = 0;
		ADC_L1_I_Inv_PkPk = Loc_L1_I_Inv_PkPk_H - Loc_L1_I_Inv_PkPk_L;
		Loc_L1_I_Inv_PkPk_H = INT16_MIN;
		Loc_L1_I_Inv_PkPk_L = INT16_MAX;
		ADC_L1_I_Inv_RMS = sqrt(Loc_L1_I_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L1_I_Inv_RMS = 0;
		// L2_I_Inv
		ADC_L2_I_Inv_Mean = Loc_L2_I_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L2_I_Inv_Mean = 0;
		ADC_L2_I_Inv_PkPk = Loc_L2_I_Inv_PkPk_H - Loc_L2_I_Inv_PkPk_L;
		Loc_L2_I_Inv_PkPk_H = INT16_MIN;
		Loc_L2_I_Inv_PkPk_L = INT16_MAX;
		ADC_L2_I_Inv_RMS = sqrt(Loc_L2_I_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L2_I_Inv_RMS = 0;
		// L3_I_Inv
		ADC_L3_I_Inv_Mean = Loc_L3_I_Inv_Mean / BSP_SETTINGS_ADC_X1_SIG_SAMPLES;
		Loc_L3_I_Inv_Mean = 0;
		ADC_L3_I_Inv_PkPk = Loc_L3_I_Inv_PkPk_H - Loc_L3_I_Inv_PkPk_L;
		Loc_L3_I_Inv_PkPk_H = INT16_MIN;
		Loc_L3_I_Inv_PkPk_L = INT16_MAX;
		ADC_L3_I_Inv_RMS = sqrt(Loc_L3_I_Inv_RMS / BSP_SETTINGS_ADC_X1_SIG_SAMPLES);
		Loc_L3_I_Inv_RMS = 0;
		// Reset flag
		Loc_x1_Busy = false;
		if(Loc_x1_CntDwn > 0) {
			if(Loc_x1_CntDwn == 1) {
				if(ADC_Calib == true) {
#ifdef VOLTAGE_OFFSET_CORRECTION
#ifndef U_GRID_AS_HIRES
					Loc_L1_U_Mid_Error = 0 - ADC_L1_U_Mid_Mean;
					Loc_L2_U_Mid_Error = 0 - ADC_L2_U_Mid_Mean;
					Loc_L3_U_Mid_Error = 0 - ADC_L3_U_Mid_Mean;
#else	// U_GRID_AS_HIRES
					Loc_L1_U_Grid_Error = 0 - ADC_L1_U_Grid_Mean;
					Loc_L2_U_Grid_Error = 0 - ADC_L2_U_Grid_Mean;
					Loc_L3_U_Grid_Error = 0 - ADC_L3_U_Grid_Mean;
#endif	// U_GRID_AS_HIRES
					Loc_L1_U_Inv_Error = 0 - ADC_L1_U_Inv_Mean;
					Loc_L2_U_Inv_Error = 0 - ADC_L2_U_Inv_Mean;
					Loc_L3_U_Inv_Error = 0 - ADC_L3_U_Inv_Mean;
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
					Loc_L1_I_Inv_Error = 0 - ADC_L1_I_Inv_Mean;
					Loc_L2_I_Inv_Error = 0 - ADC_L2_I_Inv_Mean;
					Loc_L3_I_Inv_Error = 0 - ADC_L3_I_Inv_Mean;
#endif	// CURRENT_OFFSET_CORRECTION
				}
				if((Loc_x8_CntDwn == 0) &&
					(Loc_x16_CntDwn == 0) &&
					(Loc_x32_CntDwn == 0)) {
						ADC_Ready = true;
						ADC_Save_to_NVM();
				}
			}
			Loc_x1_CntDwn--;
		}
	}
	if(Loc_x8_Busy == true) {
#ifndef U_GRID_AS_HIRES
		// L1_U_Grid
		ADC_L1_U_Grid_Mean = Loc_L1_U_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L1_U_Grid_Mean = 0;
		ADC_L1_U_Grid_Pk_L = Loc_L1_U_Grid_PkPk_L;
		ADC_L1_U_Grid_Pk_H = Loc_L1_U_Grid_PkPk_H;
		ADC_L1_U_Grid_PkPk = Loc_L1_U_Grid_PkPk_H - Loc_L1_U_Grid_PkPk_L;
		Loc_L1_U_Grid_PkPk_H = INT16_MIN;
		Loc_L1_U_Grid_PkPk_L = INT16_MAX;
		ADC_L1_U_Grid_RMS = sqrt(Loc_L1_U_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L1_U_Grid_RMS = 0;
		// L2_U_Grid
		ADC_L2_U_Grid_Mean = Loc_L2_U_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L2_U_Grid_Mean = 0;
		ADC_L2_U_Grid_Pk_L = Loc_L2_U_Grid_PkPk_L;
		ADC_L2_U_Grid_Pk_H = Loc_L2_U_Grid_PkPk_H;
		ADC_L2_U_Grid_PkPk = Loc_L2_U_Grid_PkPk_H - Loc_L2_U_Grid_PkPk_L;
		Loc_L2_U_Grid_PkPk_H = INT16_MIN;
		Loc_L2_U_Grid_PkPk_L = INT16_MAX;
		ADC_L2_U_Grid_RMS = sqrt(Loc_L2_U_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L2_U_Grid_RMS = 0;
		// L3_U_Grid
		ADC_L3_U_Grid_Mean = Loc_L3_U_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L3_U_Grid_Mean = 0;
		ADC_L3_U_Grid_Pk_L = Loc_L3_U_Grid_PkPk_L;
		ADC_L3_U_Grid_Pk_H = Loc_L3_U_Grid_PkPk_H;
		ADC_L3_U_Grid_PkPk = Loc_L3_U_Grid_PkPk_H - Loc_L3_U_Grid_PkPk_L;
		Loc_L3_U_Grid_PkPk_H = INT16_MIN;
		Loc_L3_U_Grid_PkPk_L = INT16_MAX;
		ADC_L3_U_Grid_RMS = sqrt(Loc_L3_U_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L3_U_Grid_RMS = 0;
#else	// U_GRID_AS_HIRES
		// L1_U_Mid
		ADC_L1_U_Mid_Mean = Loc_L1_U_Mid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L1_U_Mid_Mean = 0;
		ADC_L1_U_Mid_Pk_L = Loc_L1_U_Mid_PkPk_L;
		ADC_L1_U_Mid_Pk_H = Loc_L1_U_Mid_PkPk_H;
		ADC_L1_U_Mid_PkPk = Loc_L1_U_Mid_PkPk_H - Loc_L1_U_Mid_PkPk_L;
		Loc_L1_U_Mid_PkPk_H = INT16_MIN;
		Loc_L1_U_Mid_PkPk_L = INT16_MAX;
		ADC_L1_U_Mid_RMS = sqrt(Loc_L1_U_Mid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L1_U_Mid_RMS = 0;
		// L2_U_Mid
		ADC_L2_U_Mid_Mean = Loc_L2_U_Mid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L2_U_Mid_Mean = 0;
		ADC_L2_U_Mid_Pk_L = Loc_L2_U_Mid_PkPk_L;
		ADC_L2_U_Mid_Pk_H = Loc_L2_U_Mid_PkPk_H;
		ADC_L2_U_Mid_PkPk = Loc_L2_U_Mid_PkPk_H - Loc_L2_U_Mid_PkPk_L;
		Loc_L2_U_Mid_PkPk_H = INT16_MIN;
		Loc_L2_U_Mid_PkPk_L = INT16_MAX;
		ADC_L2_U_Mid_RMS = sqrt(Loc_L2_U_Mid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L2_U_Mid_RMS = 0;
		// L3_U_Mid
		ADC_L3_U_Mid_Mean = Loc_L3_U_Mid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L3_U_Mid_Mean = 0;
		ADC_L3_U_Mid_Pk_L = Loc_L3_U_Mid_PkPk_L;
		ADC_L3_U_Mid_Pk_H = Loc_L3_U_Mid_PkPk_H;
		ADC_L3_U_Mid_PkPk = Loc_L3_U_Mid_PkPk_H - Loc_L3_U_Mid_PkPk_L;
		Loc_L3_U_Mid_PkPk_H = INT16_MIN;
		Loc_L3_U_Mid_PkPk_L = INT16_MAX;
		ADC_L3_U_Mid_RMS = sqrt(Loc_L3_U_Mid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L3_U_Mid_RMS = 0;
#endif	// U_GRID_AS_HIRES
		// L2_I_Grid
		ADC_L1_I_Grid_Mean = Loc_L1_I_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L1_I_Grid_Mean = 0;
		ADC_L1_I_Grid_PkPk = Loc_L1_I_Grid_PkPk_H - Loc_L1_I_Grid_PkPk_L;
		Loc_L1_I_Grid_PkPk_H = INT16_MIN;
		Loc_L1_I_Grid_PkPk_L = INT16_MAX;
		ADC_L1_I_Grid_RMS = sqrt(Loc_L1_I_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L1_I_Grid_RMS = 0;
		// L2_I_Grid
		ADC_L2_I_Grid_Mean = Loc_L2_I_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L2_I_Grid_Mean = 0;
		ADC_L2_I_Grid_PkPk = Loc_L2_I_Grid_PkPk_H - Loc_L2_I_Grid_PkPk_L;
		Loc_L2_I_Grid_PkPk_H = INT16_MIN;
		Loc_L2_I_Grid_PkPk_L = INT16_MAX;
		ADC_L2_I_Grid_RMS = sqrt(Loc_L2_I_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L2_I_Grid_RMS = 0;
		// L3_I_Grid
		ADC_L3_I_Grid_Mean = Loc_L3_I_Grid_Mean / BSP_SETTINGS_ADC_X8_SIG_SAMPLES;
		Loc_L3_I_Grid_Mean = 0;
		ADC_L3_I_Grid_PkPk = Loc_L3_I_Grid_PkPk_H - Loc_L3_I_Grid_PkPk_L;
		Loc_L3_I_Grid_PkPk_H = INT16_MIN;
		Loc_L3_I_Grid_PkPk_L = INT16_MAX;
		ADC_L3_I_Grid_RMS = sqrt(Loc_L3_I_Grid_RMS / BSP_SETTINGS_ADC_X8_SIG_SAMPLES);
		Loc_L3_I_Grid_RMS = 0;
		// Reset flag
		Loc_x8_Busy = false;
		if(Loc_x8_CntDwn > 0) {
			if(Loc_x8_CntDwn == 1) {
				if(ADC_Calib == true) {
#ifdef VOLTAGE_OFFSET_CORRECTION
#ifndef U_GRID_AS_HIRES
					Loc_L1_U_Grid_Error = 0 - ADC_L1_U_Grid_Mean;
					Loc_L2_U_Grid_Error = 0 - ADC_L2_U_Grid_Mean;
					Loc_L3_U_Grid_Error = 0 - ADC_L3_U_Grid_Mean;
#else	// U_GRID_AS_HIRES
					Loc_L1_U_Mid_Error = 0 - ADC_L1_U_Mid_Mean;
					Loc_L2_U_Mid_Error = 0 - ADC_L2_U_Mid_Mean;
					Loc_L3_U_Mid_Error = 0 - ADC_L3_U_Mid_Mean;
#endif	// U_GRID_AS_HIRES
#endif	// VOLTAGE_OFFSET_CORRECTION
#ifdef CURRENT_OFFSET_CORRECTION
					Loc_L1_I_Grid_Error = 0 - ADC_L1_I_Grid_Mean;
					Loc_L2_I_Grid_Error = 0 - ADC_L2_I_Grid_Mean;
					Loc_L3_I_Grid_Error = 0 - ADC_L3_I_Grid_Mean;
#endif	// CURRENT_OFFSET_CORRECTION
				}
				if((Loc_x1_CntDwn == 0) &&
					(Loc_x16_CntDwn == 0) &&
					(Loc_x32_CntDwn == 0)) {
						ADC_Ready = true;
						ADC_Save_to_NVM();
				}
			}
			Loc_x8_CntDwn--;
		}
	}
	if(Loc_x16_Busy == true) {
		// N_U_DC
		ADC_N_U_DC_Mean = Loc_N_U_DC_Mean / BSP_SETTINGS_ADC_X16_SIG_SAMPLES;
		Loc_N_U_DC_Mean = 0;
		ADC_N_U_DC_PkPk = Loc_N_U_DC_PkPk_H - Loc_N_U_DC_PkPk_L;
		Loc_N_U_DC_PkPk_H = UINT16_MIN;
		Loc_N_U_DC_PkPk_L = UINT16_MAX;
		ADC_N_U_DC_RMS = sqrt(Loc_N_U_DC_RMS / BSP_SETTINGS_ADC_X16_SIG_SAMPLES);
		Loc_N_U_DC_RMS = 0;
		// P_U_DC
		ADC_P_U_DC_Mean = Loc_P_U_DC_Mean / BSP_SETTINGS_ADC_X16_SIG_SAMPLES;
		Loc_P_U_DC_Mean = 0;
		ADC_P_U_DC_PkPk = Loc_P_U_DC_PkPk_H - Loc_P_U_DC_PkPk_L;
		Loc_P_U_DC_PkPk_H = UINT16_MIN;
		Loc_P_U_DC_PkPk_L = UINT16_MAX;
		ADC_P_U_DC_RMS = sqrt(Loc_P_U_DC_RMS / BSP_SETTINGS_ADC_X16_SIG_SAMPLES);
		Loc_P_U_DC_RMS = 0;
		// Reset flag
		Loc_x16_Busy = false;
		if(Loc_x16_CntDwn > 0) {
			if(Loc_x16_CntDwn == 1) {
				if((Loc_x1_CntDwn == 0) &&
					(Loc_x8_CntDwn == 0) &&
					(Loc_x32_CntDwn == 0)) {
						ADC_Ready = true;
						ADC_Save_to_NVM();
				}
			}
			Loc_x16_CntDwn--;
		}
	}
	if(Loc_x32_Busy == true) {
		// T1
		ADC_T1_Mean = Loc_T1_Mean / BSP_SETTINGS_ADC_X32_SIG_SAMPLES;
		Loc_T1_Mean = 0;
		// T2
		ADC_T2_Mean = Loc_T2_Mean / BSP_SETTINGS_ADC_X32_SIG_SAMPLES;
		Loc_T2_Mean = 0;
		// T3
		ADC_T3_Mean = Loc_T3_Mean / BSP_SETTINGS_ADC_X32_SIG_SAMPLES;
		Loc_T3_Mean = 0;
		// AUX4
		ADC_AUX4_Mean = Loc_AUX4_Mean / BSP_SETTINGS_ADC_X32_SIG_SAMPLES;
		Loc_AUX4_Mean = 0;
		// Reset flag
		Loc_x32_Busy = false;
		if(Loc_x32_CntDwn > 0) {
			if(Loc_x32_CntDwn == 1) {
				if((Loc_x1_CntDwn == 0) &&
					(Loc_x8_CntDwn == 0) &&
					(Loc_x16_CntDwn == 0)) {
						ADC_Ready = true;
						ADC_Save_to_NVM();
				}
			}
			Loc_x32_CntDwn--;
		}
	}
}
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x
