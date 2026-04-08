/*
 *  File name: config_version.h
 *
 *  Description: HW & FW Version Information
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_VERSION_H
#define CONFIG_VERSION_H

//*****************************************************************************
//
// Version settings.
//
//*****************************************************************************

// HW Version
#if (defined HARDWARE_VERSION_1)
#define APP_SETTINGS_VERSION_HW_INFO			0x0100
#elif (defined HARDWARE_VERSION_2)
#define APP_SETTINGS_VERSION_HW_INFO			0x0200
#else	// HARDWARE_VERSION_x
#error HARDWARE_VERSION_x not defined
#endif	// HARDWARE_VERSION_x

// FW Version
#define APP_SETTINGS_VERSION_FW_VERSION			0x0118

// FW Date
#define APP_SETTINGS_VERSION_FW_DATE_YEAR		2018
#define APP_SETTINGS_VERSION_FW_DATE_MONTH		2
#define APP_SETTINGS_VERSION_FW_DATE_DAY		15

#endif	// CONFIG_VERSION_H
