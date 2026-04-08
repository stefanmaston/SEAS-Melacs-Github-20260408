#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "main.h"
//#include <stdbool.h>
#include "modbus.h"
#include "modbus_format.h"

#include "UART.h"



uint16_t Modbus_GetLSBValue(uint8_t ptr[2])
{
	return ((uint16_t)ptr[1]<<8) + ptr[0];
}
void Modbus_PutLSBValue(uint8_t ptr[2], uint16_t value)
{
	ptr[0] = (uint8_t)(value >> 0);
	ptr[1] = (uint8_t)(value >> 8);
}
uint16_t Modbus_GetMSBValue(uint8_t ptr[2])
{
	return ((uint16_t)ptr[0]<<8) + ptr[1];
}
void Modbus_PutMSBValue(uint8_t ptr[2], uint16_t value)
{
	ptr[0] = (uint8_t)(value >> 8);
	ptr[1] = (uint8_t)(value >> 0);
}

/* Apply any scaling */
int32_t Modbus_Scale(int32_t value, int8_t pow)
{
  	if(pow == 0U)
	{
	  	return value;
	}
	
	/* Scale up or down */ 
	if(pow > 0)
	{
		while(pow)
		{
			value *= 10;
			pow--;
		}
	}
	else
	{
		while(pow)
		{
			value /= 10;
			pow++;
		}
	}
	return value;
}

uint16_t Modbus_GainCalculator(double gain)
{
    uint16_t result = (uint16_t)(gain*(1<<16));
    return result;
}
uint16_t Modbus_PhaseCalculator(double phase)
{
    uint16_t result = (uint16_t)(phase*91.01662156938539);
    return result; 
}
uint16_t Modbus_FreqCalculator(double freq)
{
    return (uint16_t)freq*10;

}
uint8_t Modbus_ReadUInt8(uint8_t ptr[0x100], uint16_t index)
{
  	return ptr[index];
}

int16_t Modbus_ReadInt16(int16_t ptr[0x100], uint16_t index)
{
  	return ptr[index];
}

uint16_t Modbus_ReadUInt16(uint16_t ptr[0x100], uint16_t index)
{
  	return ptr[index];
}

int32_t Modbus_ReadInt32(int32_t ptr[0x100], uint16_t index)
{
  	return ptr[index];
}

void Modbus_WriteUInt8(uint8_t ptr[0x100], uint16_t index, uint8_t value)
{
  	ptr[index] = value;
}

void Modbus_WriteInt16(int16_t ptr[0x100], uint16_t index, int16_t value)
{
  	ptr[index] = value;
}

void Modbus_WriteUInt16(uint16_t ptr[0x100], uint16_t index, uint16_t value)
{
  	ptr[index] = value;
}

void Modbus_WriteInt32(int32_t ptr[0x100], uint16_t index, int32_t value)
{
  	ptr[index] = value;
}

void Modbus_WriteUInt64(uint64_t ptr[0x100], uint16_t index, uint64_t value)
{
    ptr[index] = value;
}
void Modbus_WriteBool(uint8_t ptr[0x100], uint16_t index, uint8_t value)
{
    ptr[index]   = (value & 0x01)  !=0;
    ptr[index+1] = (value & 0x02)  !=0;
    ptr[index+2] = (value & 0x04)  !=0;
    ptr[index+3] = (value & 0x08)  !=0;
    ptr[index+4] = (value & 0x16)  !=0;
    ptr[index+5] = (value & 0x32)  !=0;
    ptr[index+6] = (value & 0x64)  !=0;
    ptr[index+7] = (value & 0x128) !=0;
}

				