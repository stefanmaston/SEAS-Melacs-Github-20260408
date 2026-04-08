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

#ifndef MODBUS_FORMAT_H    /* Guard against multiple inclusion */
#define MODBUS_FORMAT_H
#include <stdbool.h>
#include <stdint.h>

#define MODBUS_ADDRESS_BROADCAST       0x00U

/* Standard function request codes */
typedef enum
{
	MODBUS_FUNCTION_NONE                    = 0x00,
    MODBUS_FUNCTION_READ_COILS              = 0x01,
	MODBUS_FUNCTION_READ_DISCRETE_INPUTS    = 0x02,
	MODBUS_FUNCTION_READ_HOLDING_REGS       = 0x03,
	MODBUS_FUNCTION_READ_INPUT_REGS         = 0x04,
	MODBUS_FUNCTION_WRITE_SINGLE_COIL       = 0x05,
	MODBUS_FUNCTION_WRITE_SINGLE_REG        = 0x06,
	MODBUS_FUNCTION_READ_EXCEPTION          = 0x07,
	MODBUS_FUNCTION_DIAGNOSTIC              = 0x08,
	MODBUS_FUNCTION_GET_COM_EVENT_COUNT     = 0x0B,
	MODBUS_FUNCTION_GET_COM_EVENT_LOG       = 0x0C,
	MODBUS_FUNCTION_WRITE_MULTI_COILS       = 0x0F,
	MODBUS_FUNCTION_WRITE_MULTI_REGS        = 0x10,
	MODBUS_FUNCTION_REPORT_SLAVE_ID         = 0x11,
	MODBUS_FUNCTION_READWRITE_MULTIPLE_REGS = 0x17,
	/* A raised MSB indicates an error response */
	MODBUS_FUNCTION_EXCEPTION_MASK          = 0x80 //Error
}
Modbus_Function_t;


/* Standard exception response codes */
typedef enum
{
    //MODBUS_EXCEPTION_NONE                   = 0x00,
	MODBUS_EXCEPTION_ILLEGAL_FUNCTION       = 0x01,
	MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS   = 0x02,
	MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE     = 0x03,
	MODBUS_EXCEPTION_SLAVE_DEVICE_FAILURE   = 0x04,
	MODBUS_EXCEPTION_ACKNOWLEDGE            = 0x05,
	MODBUS_EXCEPTION_SLAVE_DEVICE_BUSY      = 0x06,
	MODBUS_EXCEPTION_MEMORY_PARITY_ERROR    = 0x08,
	MODBUS_EXCEPTION_GATEWAY_PATH           = 0x0A,
	MODBUS_EXCEPTION_GATEWAY_UNRESPONSIVE   = 0x0B,
	/* Internal signal indicating successful completion and that the proper
	 * response/acknowledgment should be sent */
	MODBUS_EXCEPTION_SUCCESS                = 0x00,
	/* Internal flow control signal indicating that the client needs to be
	   stalled until the register becomes available. This is not communicated
	   externally */
	MODBUS_EXCEPTION_NOT_READY              = 0xFF
}
Modbus_Exception_t;


/* Supported types of conversion from RAM values to Modbus registers */
enum
{
	//UINT8_TO_UINT16, 
    //UINT8_TO_UINT8,   //Have to test
	UINT16_TO_UINT16,
    UINT64_TO_UINT64, 
	INT16_TO_INT16,
	//INT32_TO_INT16,
	//INT32_TO_INT32,
	//INT64_TO_INT64,
	//INT16_TO_INT32,
    BOOL,
	//STRING,
};
			  	
	#endif /* _EXAMPLE_FILE_NAME_H */

/* *****************************************************************************
 End of File
 */
