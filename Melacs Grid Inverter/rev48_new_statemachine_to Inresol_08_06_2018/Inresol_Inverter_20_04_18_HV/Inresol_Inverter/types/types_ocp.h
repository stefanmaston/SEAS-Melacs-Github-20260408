/*
 *  File name: types_ocp.h
 *
 *  Description: Type definitions for Over Current Protection
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_OCP_H
#define TYPES_OCP_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_OCP_ITrip_ChannelNumber
{
	APP_OCP_ITRIP_CHANNEL_NUMBER_1 = 0,
	APP_OCP_ITRIP_CHANNEL_NUMBER_2,
	APP_OCP_ITRIP_CHANNELS_MAX
} OCP_ITrip_ChannelNumber_t;

typedef enum tag_OCP_OC_Detected
{
	APP_OCP_OC_L1_INV = 0,
	APP_OCP_OC_L2_INV,
	APP_OCP_OC_L3_INV,
	APP_OCP_OC_L1_GRID,
	APP_OCP_OC_L2_GRID,
	APP_OCP_OC_L3_GRID,
	APP_OCP_OC_MAX
} OCP_OC_Detected_t;

#endif	// TYPES_OCP_H
