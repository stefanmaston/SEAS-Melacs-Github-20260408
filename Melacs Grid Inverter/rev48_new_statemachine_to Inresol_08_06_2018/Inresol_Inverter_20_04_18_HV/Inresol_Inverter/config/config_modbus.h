/*
 *  File name: config_modbus.h
 *
 *  Description: Modbus settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_MODBUS_H
#define CONFIG_MODBUS_H

//*****************************************************************************
//
// Modbus App parameters.
//
//*****************************************************************************
#define APP_SETTINGS_MODBUS_BAUDRATE					115200
//#define APP_SETTINGS_MODBUS_PARITY						MB_PAR_EVEN
#define APP_SETTINGS_MODBUS_PARITY						MB_PAR_NONE
#define APP_SETTINGS_MODBUS_SLAVE_ADDR					0x01
#define APP_SETTINGS_MODBUS_SLAVE_ID_MAIN				0x34
#define APP_SETTINGS_MODBUS_SLAVE_ID_ADDITIONAL			0xAA, 0xBB, 0xCC

#if 0
#define MB_TST1_SET()	GPIO_TST1_SET()
#define MB_TST1_CLR()	GPIO_TST1_CLR()
#define MB_TST1_TGL()	GPIO_TST1_TGL()
#define MB_TST2_SET()	GPIO_TST2_SET()
#define MB_TST2_CLR()	GPIO_TST2_CLR()
#define MB_TST2_TGL()	GPIO_TST2_TGL()
#define MB_TST3_SET()	GPIO_TST3_SET()
#define MB_TST3_CLR()	GPIO_TST3_CLR()
#define MB_TST3_TGL()	GPIO_TST3_TGL()
#else
#define MB_TST1_SET()
#define MB_TST1_CLR()
#define MB_TST1_TGL()
#define MB_TST2_SET()
#define MB_TST2_CLR()
#define MB_TST2_TGL()
#define MB_TST3_SET()
#define MB_TST3_CLR()
#define MB_TST3_TGL()
#endif

#endif	// CONFIG_MODBUS_H
