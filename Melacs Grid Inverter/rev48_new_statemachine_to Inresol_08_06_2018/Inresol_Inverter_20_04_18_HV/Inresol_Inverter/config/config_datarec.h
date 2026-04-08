/*
 *  File name: config_datarec.h
 *
 *  Description: Data Recording settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_DATA_REC_H
#define CONFIG_DATA_REC_H

//*****************************************************************************
//
// Data Recording APP settings.
//
//*****************************************************************************

#define APP_DATAREC_ENABLED
//#define APP_DATAREC_BUFFER_LENGTH				6400		// 3200 samples * 16bit (200ms@16kHz)
//#define APP_DATAREC_BUFFER_LENGTH				4800		// 2400 samples * 16bit (200ms@16kHz)
#define APP_DATAREC_BUFFER_LENGTH				500		// 900 samples
//#define APP_DATAREC_PACKET_LENGTH				8
#define APP_DATAREC_PACKET_LENGTH				12

#endif	// CONFIG_DATA_REC_H
