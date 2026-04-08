/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _MODBUS_H    /* Guard against multiple inclusion */
#define _MODBUS_H

#include "modbus_client.h"


typedef struct ModbusRegister_tag
{
	/* Register address */
	uint16_t address;
	/* Type, from the list above */
	uint8_t type;
	/* Exponent to apply for scaling */
	//int8_t reg_exp;
	/* Number of registers available at this address */
	uint16_t count;
	/* Writable? */
	bool write;
	/* The value where the data for this register is to be found */
	const void* value;
	/* Optionally the value can be found through a pointer to a pointer instead */
	const void** ptr;
	/* Update period for clients */
	//uint16_t request_period;
} ModbusRegister_t;



int32_t Modbus_Scale(int32_t value, int8_t pow);
uint16_t Modbus_GetLSBValue(uint8_t ptr[2]);
void Modbus_PutLSBValue(uint8_t ptr[2], uint16_t value);
uint16_t Modbus_GetMSBValue(uint8_t ptr[2]);
void Modbus_PutMSBValue(uint8_t ptr[2], uint16_t value);
uint8_t Modbus_GetBoolValue(uint8_t ptr[2]);

uint8_t Modbus_ReadUInt8(uint8_t ptr[MODBUS_BUFFER_SIZE], uint16_t index);
int16_t Modbus_ReadInt16(int16_t ptr[MODBUS_BUFFER_SIZE], uint16_t index);
uint16_t Modbus_ReadUInt16(uint16_t ptr[MODBUS_BUFFER_SIZE], uint16_t index);
int32_t Modbus_ReadInt32(int32_t ptr[MODBUS_BUFFER_SIZE], uint16_t index);

void Modbus_WriteUInt8(uint8_t ptr[MODBUS_BUFFER_SIZE], uint16_t index, uint8_t value);
void Modbus_WriteInt16(int16_t ptr[MODBUS_BUFFER_SIZE], uint16_t index, int16_t value);
void Modbus_WriteUInt16(uint16_t ptr[MODBUS_BUFFER_SIZE], uint16_t index, uint16_t value);
void Modbus_WriteInt32(int32_t ptr[MODBUS_BUFFER_SIZE], uint16_t index, int32_t value);
void Modbus_WriteBool(uint8_t ptr[MODBUS_BUFFER_SIZE], uint16_t index, uint8_t value);
void Modbus_WriteUInt64(uint64_t ptr[0x100], uint16_t index, uint64_t value);


uint16_t Modbus_GainCalculator(double gain);
uint16_t Modbus_PhaseCalculator(double phase);
uint16_t Modbus_FreqCalculator(double freq);
#endif /* _MODBUS_H */





/* *****************************************************************************
 End of File
 */
