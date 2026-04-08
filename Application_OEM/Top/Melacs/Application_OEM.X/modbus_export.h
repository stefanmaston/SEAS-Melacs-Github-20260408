/******************************************************************************
 * Common protocol data definitions to be shared between the device and host
 * while not directly related to a specific communication link
 ******************************************************************************/
#ifndef MODBUS_EXPORT_H
#define MODBUS_EXPORT_H
#include <stdint.h>

enum ModbusRegisterIdentifier_t 
{
  	#undef MODBUS_GROUP
  	#undef MODBUS_DATA
	#define MODBUS_GROUP(...)
	#define MODBUS_DATA(address_, ident_, type_, member_, ...) \
  		INVERTER_##ident_ = address_, 
	//#pragma diag_suppress=Pm121
	#include "modbus_data_client.h"
};
#endif

