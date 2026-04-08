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

#ifndef _MODBUS_SERVER_H    /* Guard against multiple inclusion */
#define _MODBUS_SERVER_H

#define MODBUS_BUFFER_SIZE 0x100





typedef enum
{   MODBUS_STARTUP,
    MODBUS_SET,
    MODBUS_READ,
	MODBUS_IDLE,
	MODBUS_WAITING_FOR_RESPONSE,
} ModbusClientState_t;
	

typedef struct ModbusRequest_tag
{
  	//uint8_t schedule_index;
	uint8_t device_address;
	uint16_t register_address;
    uint8_t function_code;
	uint16_t register_count;
    uint8_t num_data_bytes;
    uint8_t written_data[12];
	uint8_t expected_response_length;
} ModbusRequest_t;

typedef struct ModbusClient_tag
{
  	//int16_t focus_address;
	
	ModbusClientState_t state;
	// Request sent
	ModbusRequest_t request;
} ModbusClient_t;






#endif /* _MODBUS_SERVER_H */


/* *****************************************************************************
 End of File
 */
