/*
 *  File name: types_dpll.h
 *
 *  Description: Type definitions for Relays
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_DPLL_H
#define TYPES_DPLL_H

/*****************/
/* Basic Defines */
/*****************/
typedef enum tag_V_Meas_Type
{
	APP_V_INV_1 = 0,
	APP_V_MID_1,
	APP_V_GRID_1,
	APP_V_INV_3,
	APP_V_MID_3,
	APP_V_GRID_3
} V_Meas_t;

typedef enum tag_Inv_Mode_Type
{
	APP_INV_STND_1=0,
	APP_INV_STND_3,
	APP_INV_GRID_1,
	APP_INV_GRID_3,
	APP_INV_TEST_STND_NO_VCB_1_3,
	APP_INV_TEST_STND_NO_CCB_1_3,
	APP_INV_TEST_GRID_NO_VCB_1_3,
	APP_INV_TEST_GRID_NO_CCB_1_3
} Inv_Mode_t;

typedef enum tag_Dpll_Type
{
	APP_DPLL_OFF = 0,
	APP_DPLL_ON_1_PHASE,
	APP_DPLL_ON_3_PHASE,
	APP_DPLL_ON_GRID_1_PHASE,
	APP_DPLL_ON_GRID_3_PHASE
} Dpll_Mode_t;

typedef enum tag_Control_Type
{
	APP_CONTROL_OFF = 0,	// no loopback
	APP_VCB_ON,				// Voltage Control Block enabled
	APP_VCB_ORTO1_ON,
	APP_VCB_ORTO3_ON,
	APP_CCB_ON,				// Current Control Block enabled
	APP_CCB_ORTO1_ON,
	APP_CCB_ORTO3_ON
} Control_Mode_t;

typedef enum tag_SM_Main_Type
{
	SM_PRE_START = 0,
	SM_START,
	SM_IDLE,
	SM_ERROR,
	SM_GRID_RLY_CLOSE,
	SM_DPLL_INIT,
	SM_DPLL_LOCKED,
	SM_INV_RLY_CLOSE,
	SM_DELAY,
	SM_TIMEOUT,
	SM_WAIT_FOR_REINIT,
	SM_ISLAND_MODE,
	SM_ANTY_ISLANDING,
	SM_C_RAMP_BEGIN,
	SM_C_RAMP_END,
	SM_CALIBRATION,
	SM_PRE_INV_RLY
} SM_Main_t;

typedef enum tag_System_Error_Type
{
	ERROR_NONE = 0,
	ERROR_CRITICAL,
	ERROR_INITIALIZATION,
	ERROR_NO_DPLL_LOCK,
	ERROR_NO_GRID,
	ERROR_OVERCURRENT,
	ERROR_INV_VOLTAGE,
	ERROR_MID_VOLTAGE,
	ERROR_GRID_VOLTAGE,
	ERROR_TIMEOUT
} System_Error_t;

#endif	// TYPES_DPLL_H
