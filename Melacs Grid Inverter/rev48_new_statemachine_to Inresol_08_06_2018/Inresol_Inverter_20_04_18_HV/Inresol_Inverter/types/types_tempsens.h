/*
 *  File name: types_tempsens.h
 *
 *  Description: Type definitions for Temperature Sensors
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_TEMP_SENS_H
#define TYPES_TEMP_SENS_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_TempSens_Number
{
	APP_TEMP_SENS_CHANNEL_1 = 0,
	APP_TEMP_SENS_CHANNEL_2,
	APP_TEMP_SENS_CHANNEL_3,
	APP_TEMP_SENS_CHANNELS_MAX
} TempSens_Number_t;

#if 0
typedef enum tag_TempSens_State
{
	APP_TEMP_SENS_READY = 0,
	APP_TEMP_SENS_OPEN,
	APP_TEMP_SENS_SHORT
} TempSens_State_t;
#else
#define APP_TEMP_SENS_READY				0x01
#define APP_TEMP_SENS_FAILURE_OPEN		0x02
#define APP_TEMP_SENS_FAILURE_SHORT		0x04
#endif

#endif	// TYPES_TEMP_SENS_H
