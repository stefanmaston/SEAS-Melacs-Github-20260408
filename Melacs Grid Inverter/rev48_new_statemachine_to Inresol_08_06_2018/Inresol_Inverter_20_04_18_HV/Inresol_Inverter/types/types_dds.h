/*
 *  File name: types_dds.h
 *
 *  Description: Type definitions for DDS
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_DDS_H
#define TYPES_DDS_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_DDS_ChannelNumber
{
	APP_DDS_CHANNEL_NUMBER_1 = 0,
	APP_DDS_CHANNEL_NUMBER_2,
	APP_DDS_CHANNEL_NUMBER_3,
	APP_DDS_CHANNELS_MAX
} DDS_ChannelNumber_t;

#endif	// TYPES_DDS_H
