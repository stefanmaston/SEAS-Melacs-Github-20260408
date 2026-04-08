/*
 *  File name: types_relay.h
 *
 *  Description: Type definitions for Main State Machine
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_SM_H
#define TYPES_SM_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_System_Mode
{
#if 0
	APP_SM_SYSTEM_MODE_STANDALONE = 0,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED
#else
	APP_SM_SYSTEM_MODE_STANDALONE_1_PHASE = 0,
	APP_SM_SYSTEM_MODE_STANDALONE_3_PHASES,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE_NO_BAT,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES_NO_BAT,
	APP_SM_SYSTEM_MODE_TEST,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_1_PHASE,
	APP_SM_SYSTEM_MODE_GRID_CONNECTED_3_PHASES,
	APP_SM_SYSTEM_MODE_IDLE
#endif
} System_Mode_t;

#endif	// TYPES_SM_H
