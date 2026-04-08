/*
 *  File name: types_pwm.h
 *
 *  Description: Type definitions for PWM
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_PWM_H
#define TYPES_PWM_H

#include "config_system.h"

/*****************/
/* Basic Defines */
/*****************/

#if 0
typedef enum tag_PWM_MasterTimeBase
{
	BSP_PWM_MASTER_TIME_BASE_PRIMARY = 0,
	BSP_PWM_MASTER_TIME_BASE_SECONDARY
} PWM_MasterTimeBase_t;
#else
#define BSP_PWM_MASTER_TIME_BASE_PRIMARY		0
#define BSP_PWM_MASTER_TIME_BASE_SECONDARY		1
#endif

typedef enum tag_PWM_ChannelNumber
{
	BSP_PWM_CHANNEL_NUMBER_1 = 0,
	BSP_PWM_CHANNEL_NUMBER_2,
	BSP_PWM_CHANNEL_NUMBER_3,
	BSP_PWM_CHANNEL_NUMBER_4,
	BSP_PWM_CHANNEL_NUMBER_5,
#ifdef DSPIC_7XX_FAMILY
	BSP_PWM_CHANNEL_NUMBER_6,
	BSP_PWM_CHANNEL_NUMBER_7,
#endif
	BSP_PWM_CHANNELS_MAX
} PWM_ChannelNumber_t;

#endif	// TYPES_PWM_H
