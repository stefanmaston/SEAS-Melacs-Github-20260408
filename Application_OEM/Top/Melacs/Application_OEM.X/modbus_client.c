#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING


#include <stdint.h>

#include "modbus_format.h"
#include "modbus_export.h"
#include "modbus_client.h"
#include "modbus.h"
#include "modbus_data_storage.h"
#include "UART.h"
#include "delay.h"
#include <string.h>
#include <proc/p32mx795f512l.h>
#define countof(x) (sizeof(x) / sizeof(x[0]))


//Storage
Device_info_t Device_info;
Discrete_Inputs_t Discrete_Inputs;
Calib_info_t Calib_info;
Relay_Output_t Relay_Output;
System_Status_t System_Status;
Reset_Source_t Reset_Source;
Adc_Reading_t Adc_Reading;
Mode_Reading_t Mode_Reading;
DDS_Reading_t DDS_Reading;
ITRIP_Reading_t ITRIP_Reading;
DPLL_Reading_t DPLL_Reading;
//SM_Reading_t SM_Reading;



extern Serial_Instance_t Serial_Instance;
Serial_Instance_t ModbusClient_Instance;
ModbusClient_t ModbusClient;

void ModbusClient_RunTransmit(Serial_Instance_t *serial, ModbusClient_t *modbus);
void ModbusClient_HandleMessage(uint8_t receive[MODBUS_BUFFER_SIZE], uint16_t register_address);
bool Modbus_Receive(Serial_Instance_t *serial, ModbusClient_t *modbus);
bool Modbus_ReadWriteRegister(
	const ModbusRegister_t *registers, 
	int32_t register_count, 
	uint16_t address, 
	uint8_t *ptr, bool write);
bool Modbus_ReadMultiRegCoil_Write_SingleRegCoil(uint8_t device_address, 
    uint8_t function_code,
    uint16_t register_address, 
    uint16_t count);
    //uint8_t expected_response_length);
bool Modbus_WriteMulti_RegCoil(uint8_t device_address, 
    uint8_t function_code,
    uint16_t register_address, 
    uint16_t count,
    uint8_t num_data_bytes,
    uint16_t written_data[12]);

void Modbus_Client_Run();
uint8_t Excepted_Response_Calc(uint8_t function_code ,uint8_t register_count);

static const ModbusRegister_t ModbusRegisters[] =
{
	#undef MODBUS_GROUP
	#undef MODBUS_DATA
	#define MODBUS_GROUP(...) 
	#define MODBUS_DATA(address_, ident_, type_, value_, ...)\
  	{ \
	  	.address = address_, \
		.type = type_, \
		.value = &value_, \
        .ptr = NULL, \
        .count = 1, \
		.write = 1, \
		__VA_ARGS__ \
	},
	#include "modbus_data_client.h"
	#undef MODBUS_GROUP
	#undef MODBUS_DATA
};
/***********************************Modbus Transmitt Function *********************************************************************/
void ModbusClient_SendReadRequest(
    Serial_Instance_t *serial, 
    ModbusClient_t *modbus)
{	
    ModbusRequest_t *request = &modbus->request;
    uint8_t *transmit = serial->transmit.buffer;
	// Compile a message
	int32_t index = 0;
    MEMLED2 = ~MEMLED2;
    switch(request->function_code)
    {
        
        case MODBUS_FUNCTION_READ_HOLDING_REGS:
        case MODBUS_FUNCTION_READ_INPUT_REGS:
        case MODBUS_FUNCTION_WRITE_SINGLE_REG:
        case MODBUS_FUNCTION_READ_COILS:
        case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:    
        {
            transmit[index++] = request->device_address;//device_address;
            transmit[index++] = request->function_code;
            transmit[index++] = request->register_address >> 8;//register_address >> 8;
            transmit[index++] = request->register_address >> 0;
            transmit[index++] = request->register_count >> 8;//
            transmit[index++] = request->register_count >>0; //
        }
        break;
        case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
        {
            transmit[index++] = request->device_address;//device_address;
            transmit[index++] = request->function_code;
            transmit[index++] = request->register_address >> 8;//register_address >> 8;
            transmit[index++] = request->register_address >> 0;
            if(request->register_count == 1)
            {
                transmit[index++] = 0xFF;//Written data to this single coil >> 8;
                transmit[index++] = 0x00; //Written data >> 0;
            }
            else
            {   transmit[index++] = 0x00;//Written data to this single coil >> 8;
                transmit[index++] = 0x00; //Written data >> 0;                
            }
        }
        break;
        case MODBUS_FUNCTION_WRITE_MULTI_COILS:
        case MODBUS_FUNCTION_WRITE_MULTI_REGS:// 11 Byte 01 0F 07D0 0004 01 00 FE F3 
        {   
            uint8_t i;
            transmit[index++] = request->device_address;//device_address; 
            transmit[index++] = request->function_code; 
            transmit[index++] = request->register_address >> 8;//register_address >> 8; 
            transmit[index++] = request->register_address >> 0; 
            transmit[index++] = request->register_count >> 8;//Written data to this single coil >> 8;  
            transmit[index++] = request->register_count >>0; //Written data >> 0; 
            transmit[index++] = request->num_data_bytes;
            for (i = 0; i<request->num_data_bytes; i++)
                transmit[index++] = request->written_data[i];
            
        }
        break;
        default:
        {
            transmit[index++] = 0x00;       //request->device_address;//device_address;
            transmit[index++] = 0x01;       //request->function_code;
            transmit[index++] = 0x02;       //request->register_address >> 8;//register_address >> 8;
            transmit[index++] = 0x03;       //request->register_address >> 0;
            transmit[index++] = 0x04;       //request->register_count >> 8;//Written data to this single coil >> 8;
            transmit[index++] = 0x05;       //request->register_count >>0; //Written data >> 0;
        }
        break;
    }        
	/* Calculate the number of bytes that were added */
	uint8_t length = index;
	
	/* Update the CRC in the message to transmit */
    uint16_t crc = 0xFFFFu;
    crc = CalcCRC(transmit, index);
    
	/* Notice the CRC is in LSB format */
	Modbus_PutLSBValue(&transmit[index], crc);
	length += sizeof(uint16_t);
	
	
	// Send the request
	Serial_SendPacket(transmit, length);
}
/*********************************** END OF Modbus Transmitt Function *********************************************************************/



/***********************************Modbus Write Multiple registers and coils ********************************************************************************/
bool Modbus_WriteMulti_RegCoil(uint8_t device_address, 
    uint8_t function_code,
    uint16_t register_address, 
    uint16_t count,
    uint8_t num_data_bytes,
    uint16_t written_data[12])
{
     
    ModbusClient_t *c = &ModbusClient; 
    memset(&Serial_Instance, 0, sizeof(Serial_Instance_t));
    switch(function_code)
    {
        case MODBUS_FUNCTION_WRITE_MULTI_COILS:
        
        {
            uint8_t i;
            c->request.device_address = device_address;
            c->request.function_code = function_code;
            //c->request.expected_response_length = expected_response_length;
            c->request.register_count = count;
            c->request.register_address = register_address;
            c->request.num_data_bytes = num_data_bytes;
            for (i = 0; i<c->request.num_data_bytes; i++)
                c->request.written_data[i] = written_data[i]; 
        }
        break;
        case MODBUS_FUNCTION_WRITE_MULTI_REGS:
        {
            uint8_t i;
            c->request.device_address = device_address;
            c->request.function_code = function_code;
            c->request.register_count = count;
            c->request.register_address = register_address;
            c->request.num_data_bytes = num_data_bytes;
            for (i = 0; i<c->request.num_data_bytes; i++)
            {
                //uint16_t value = ;
                c->request.written_data[i] = (uint8_t)(written_data[i/2] >> 8);//Writes as 15 for all four
                i++;
                c->request.written_data[i] = (uint8_t)(written_data[i/2] >> 0);
            }
        }
        break;
    }
    ModbusClient_SendReadRequest(
        &ModbusClient_Instance, 
        &ModbusClient);
   
    Timer_t timer_timeout = Timer_Reset();
    Timer_t timer_idle = Timer_Reset();
    Serial_Buffer_t *receive = &Serial_Instance.receive;            
    
    while(true)
    {
        if(Timer_GetMS(&timer_timeout) > 1000)
            return false;        
        if(receive->head == 0)
            continue;
        if(receive->head < 8)
            continue;
        if(Timer_GetUS(&receive->timer_receive) < 100)
            continue;
        break;
    }
    if(!Modbus_Receive(&Serial_Instance, &ModbusClient))
    {
        return false;
    }
    return true;    
}
/***********************************ENDOF Modbus Write Multiple registers and coils ********************************************************************************/


/***********************************Modbus Read Multiple Coils and write Single coil and register *********************************************************************/
bool Modbus_ReadMultiRegCoil_WriteSingleRegCoil(
    uint8_t device_address, 
    uint8_t function_code,
    uint16_t register_address, 
    uint16_t count)
    
{
    ModbusClient_t *c = &ModbusClient; 
    memset(&Serial_Instance, 0, sizeof(Serial_Instance_t));
    c->request.device_address = device_address;
    c->request.function_code = function_code;
    c->request.register_count = count;
    c->request.register_address = register_address;
    c->request.expected_response_length = Excepted_Response_Calc(function_code, count);
    
    ModbusClient_SendReadRequest(
        &ModbusClient_Instance, 
        &ModbusClient);
   // uint8_t excepted = expected_response_length;
    Timer_t timer_timeout = Timer_Reset();
    Timer_t timer_idle = Timer_Reset();
    Serial_Buffer_t *receive = &Serial_Instance.receive;            
    
    while(true)
    {
        if(Timer_GetMS(&timer_timeout) > 1000)
            return false;        
        if(receive->head == 0)
            continue;
        if(receive->head < c->request.expected_response_length)
            continue;
        if(Timer_GetUS(&receive->timer_receive) < 100)
            continue;
        break;
    }
    if(!Modbus_Receive(&Serial_Instance, &ModbusClient))
    {
        return false;
    }
    usleep(100000);
    return true;
}

/*********************************** END OF Modbus Read Multiple Coils and write Single coil and register *********************************************************************/


/***********************************Modbus Receive function *********************************************************************/
bool Modbus_Receive(Serial_Instance_t *serial, ModbusClient_t *modbus)
{
    Serial_Buffer_t* receive = &serial->receive;
    uint8_t function_code = receive->buffer[1];
    ModbusRequest_t* request = &modbus->request;
    uint8_t index = 2;
    uint8_t length;
    switch(function_code)
    {
        case MODBUS_FUNCTION_READ_HOLDING_REGS:
        case MODBUS_FUNCTION_READ_INPUT_REGS:
        case MODBUS_FUNCTION_READ_COILS:
        case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
        {
            length = request->expected_response_length;
            if(receive->buffer[index] != request->expected_response_length-5)
            return false;
        }
        break;
        
        case MODBUS_FUNCTION_WRITE_MULTI_COILS:
        case MODBUS_FUNCTION_WRITE_MULTI_REGS:
        case MODBUS_FUNCTION_WRITE_SINGLE_COIL:  // Have to 
        case MODBUS_FUNCTION_WRITE_SINGLE_REG : 
        {
            Serial_Buffer_t* transmit = &ModbusClient_Instance.transmit;
            uint8_t i;
            for(i = 0; i < 6; i++)
            {   //strcmp(receive->buffer, transmit->buffer);asdasda
                if(receive->buffer[i] != transmit->buffer[i])
                {
                    //MEMLED = 0;
                    return false; 
                }
            }
            return true;
            //length = 8;
            //receive->buffer[length] = transmit->buffer[length-1]; //The written data stores here for local handle
        }
        break;
        
        default:
        {
            return false;
        }
        break;

    }
    //length -=sizeof(uint16_t); 
    if(CalcCRC(receive->buffer, length) != 0)
         return false;
    
    ModbusClient_HandleMessage(receive->buffer, request->register_address);
    return true; 
    
}
/*********************************** END OF Modbus Receive function *********************************************************************/


/***********************************Modbus Message Handler function *********************************************************************/
void ModbusClient_HandleMessage(uint8_t receive[MODBUS_BUFFER_SIZE], uint16_t register_address)
{
  uint8_t index = 1;
  uint8_t function_code = receive[index]; 
  uint16_t reg = register_address;
  index++;
	switch(function_code)
	{   case MODBUS_FUNCTION_READ_COILS:
        {
            uint8_t i;
			uint16_t count = receive[index];
			index += 1;
            
			for( i = 0; i < count; i++)
			{
				if(!Modbus_ReadWriteRegister(ModbusRegisters, countof(ModbusRegisters), reg, &receive[index], true))
				  	return;
                index += 1;
				reg = reg+8;
			}
        }
        break;
        
        case MODBUS_FUNCTION_READ_HOLDING_REGS:
        case MODBUS_FUNCTION_READ_INPUT_REGS:
        {   
            uint8_t i;
			uint16_t count = receive[index];
			index += 1;

			// The count must be even
			if(count & 1)
			  	return;			
			count >>= 1;
			
			for( i = 0; i < count; i++)
			{
				if(!Modbus_ReadWriteRegister(ModbusRegisters, countof(ModbusRegisters), reg, &receive[index], true))
				  	return;
				index += 2;
				reg++;
			}
		}
        case MODBUS_FUNCTION_WRITE_MULTI_COILS:
        {
			index = 8;
				if(!Modbus_ReadWriteRegister(ModbusRegisters, countof(ModbusRegisters), reg, &receive[index], true))
				  	return;
        }
		break;
	}
}
/*********************************** END OF Modbus Message Handler function *********************************************************************/



/***********************************Modbus Saver function *********************************************************************/
bool Modbus_ReadWriteRegister(const ModbusRegister_t *registers, int32_t register_count, uint16_t address, uint8_t *ptr, bool write)
{
    uint16_t i; 
    for(i = 0; i<register_count; i++)
    {   const ModbusRegister_t *reg = &registers[i];
        uint16_t start_address = reg->address;
        uint16_t end_address = reg->address + reg->count;
        if((address< start_address)||(address>= end_address))
            continue;
        void *reg_value = (void*)reg->value;
        if(reg->ptr)
        {
            reg_value = (void*)*reg->ptr;
        }
        if(write && (!reg->write))
		{
			return false;
		}
        uint16_t index = address - reg->address;
		int32_t value = 0x00000000;
        if((((uint64_t)reg->value) & 1U) != 0U)
            return false;
        /*switch(reg->type)
		{
			case UINT8_TO_UINT16:
			break;
			default:
			{   
				if((((uint64_t)reg->value) & 1U) != 0U)
                //if ((reg->value && 1u) != 0u)
				{
					return false;
				}
			}
			break;
		}*/
		/* Normally registers need to be inserted MSB, but strings should not be swizzled... */
		switch(reg->type)
		{
			case UINT16_TO_UINT16:
			{
				if(write)
				{
					/* Read a word from the received packet */
					value = (int32_t)(uint16_t)Modbus_GetMSBValue(ptr);
					/* Perform any scaling */
					//value = Modbus_Scale(value, -reg->reg_exp);
					/* Write to the value that is pointed to by the reg struct */
					Modbus_WriteUInt16((uint16_t*)reg_value, index, value);
				}
				else
				{
					value = Modbus_ReadUInt16((uint16_t*)reg_value, index);
					//value = Modbus_Scale(value, reg->reg_exp);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}					  
			}
			break;
			/*case UINT8_TO_UINT16:
			{
				if(write)
				{
					value = (int32_t)(uint8_t)Modbus_GetMSBValue(ptr);
					//value = Modbus_Scale(value, -reg->reg_exp);
					Modbus_WriteUInt8((uint8_t*)reg_value, index, value);
				}
				else
				{
					value = Modbus_ReadUInt8((uint8_t*)reg_value, index);
					//value = Modbus_Scale(value, reg->reg_exp);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}					  
			}*/
			break;
			case INT16_TO_INT16: 
			{
				if(write)
				{
					value = (int16_t)Modbus_GetMSBValue(ptr);
					//value = Modbus_Scale(value, -reg->reg_exp);
					Modbus_WriteInt16((int16_t*)reg_value, index, value);
				}
				else
				{
					value = Modbus_ReadInt16((int16_t*)reg_value, index);
					//value = Modbus_Scale(value, reg->reg_exp);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}
			}
			break;
			/*case INT16_TO_INT32:
			{
				if(index != 1u)
				{
					Modbus_PutMSBValue(ptr, 0u);
					break;
				}
				if(write)
				{
					value = (int16_t)Modbus_GetMSBValue(ptr);
					Modbus_WriteInt16((int16_t*)reg_value, 0, value);
				}
				else
				{
					value = Modbus_ReadInt32((int32_t*)reg_value, 0);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}
			}
			break;		*/	
			/*case INT32_TO_INT16: 
			{
				if(write)
				{
					value = (int32_t)Modbus_GetMSBValue(ptr);
					//value = Modbus_Scale(value, -reg->reg_exp);
					Modbus_WriteInt32((int32_t*)reg_value, index, value);
				}
				else
				{
					value = Modbus_ReadInt32((int32_t*)reg_value, index);
					//value = Modbus_Scale(value, reg->reg_exp);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}
			}
			break;*/
			/*case INT32_TO_INT32: 
			case INT64_TO_INT64: 
			{
				uint8_t swizzled_index = (uint8_t)(reg->count-1u-index);
				if(write)
				{
					value = (int16_t)Modbus_GetMSBValue(ptr);
					/* Swizzle the words 
					Modbus_WriteInt16((int16_t*)reg_value, swizzled_index, value);
				}
				else
				{
					value = Modbus_ReadInt16((int16_t*)reg_value, swizzled_index);
					Modbus_PutMSBValue(ptr, (uint16_t)value);
				}
			}
			break;*/
            case UINT64_TO_UINT64:
            {   
                uint8_t swizzled_index = (uint8_t)(reg->count-1u-index);
                
                value = (int16_t)Modbus_GetMSBValue(ptr);
				Modbus_WriteInt16((int16_t*)reg_value, swizzled_index, value);
                
            }break;
            case BOOL:
            { 
                if(write)
				{
                    value = (int32_t)(uint16_t)Modbus_GetLSBValue(ptr);
                    Modbus_WriteBool((uint8_t*)reg_value, index, value);
                }      
            }break;
			/*case STRING: 
			{
				/* Retrieve two characters as a word *
				if(write)
				{
					value = (int32_t)(uint16_t)Modbus_GetLSBValue(ptr);
					Modbus_WriteUInt16((uint16_t*)reg_value, index, value);
				}
				else
				{
					value = Modbus_ReadUInt16((uint16_t*)reg_value, index);
					Modbus_PutLSBValue(ptr, (uint16_t)value);
				}
			}
			break;*/
			default:
			break;
		}
		return true;		  	
	}
	return false;
    }

/***********************************END OF Modbus Save function *********************************************************************/

/***********************************Modbus RUN*********************************************************************/

void Modbus_Client_Run(uint16_t RLY[1], uint16_t DDS_READING_CHANGE_VALUE[6])
{
   //Timer_t time_timeout;
    ModbusClientState_t state = 0; 
   // bool datachanged = true;
    while(true)
    {
        switch(state)
        {
            case MODBUS_STARTUP: //Handshake
            {   
              if(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4100, 4))
                  continue;

              state = MODBUS_SET;
            }
            break;
            case MODBUS_SET: 
            {   
                if(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 5, 2102,1)) //Calib
                    continue;
                sleep(5);
                /*(Slave Address|Function code|Start adress| Number of Coils| State of Bool TRUE = 1 OR FALSE = 0| Expected Response = 0) Expected will always be equal to 0. */
                if(!Modbus_WriteMulti_RegCoil(Inverter_01, 15,2000,4,1,RLY))
                    continue;
                /*(Slave Address|Function code|Start adress| Value| Expected Response = 0) Expected will always be equal to 0. */
                if(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 6, 4202,1))
                    continue;
                sleep(5);
                 /*(Slave Address|Function code|Start adress| Number of register|Number Byte| actual value). 2 byte per register */
                if(!Modbus_WriteMulti_RegCoil(Inverter_01, 16,4300, 6,12, DDS_READING_CHANGE_VALUE))
                    continue;

                    state = MODBUS_READ;
            }
            break;
            case MODBUS_READ:
            {   
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 1, 2000, 4)); 
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 1, 2100, 16));
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 1, 2200, 16));
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 2, 1000, 6));
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4000, 30));

                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4200, 3));
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4300, 6)); //OBSERVERA
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4400, 2)); //OBSERVERA
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 3, 4500, 5));
                while(!Modbus_ReadMultiRegCoil_WriteSingleRegCoil(Inverter_01, 4, 3000, 80));
               
            }
            break;

        }
    }
}

/***********************************Modbus Excepted Response Not done yet and not used *********************************************************************/

uint8_t Excepted_Response_Calc(uint8_t function_code, uint8_t count)//, uint8_t *ptr, bool write)
{
    uint8_t length = 0;
    switch(function_code)
    {
            case MODBUS_FUNCTION_READ_COILS:
            {
                if(count<8)
                    length = 6;
                else
                    length = 7; 
            }break;
            case MODBUS_FUNCTION_READ_DISCRETE_INPUTS:
            {
                if(count<8)
                    length = 6;
                else
                    length = 7; 
                
            }
            break;
            case MODBUS_FUNCTION_READ_HOLDING_REGS:
            {
                length = count*2 + 5;
            }
            break;  
            case MODBUS_FUNCTION_READ_INPUT_REGS: 
            {
                 length = count*2 + 5;
            }
            break;
            case MODBUS_FUNCTION_WRITE_SINGLE_COIL:
            case MODBUS_FUNCTION_WRITE_SINGLE_REG:
            {
                length = 8;
            }
            break;
            default: 
                break;
    }
    return length;

}

