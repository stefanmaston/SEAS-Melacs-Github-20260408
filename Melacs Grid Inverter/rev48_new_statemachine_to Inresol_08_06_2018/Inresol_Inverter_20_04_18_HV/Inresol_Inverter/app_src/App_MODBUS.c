/*
 *  File name: App_MODBUS.c
 *
 *  Description: High level function implementations for MODBUS RTU
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

// ----------------------- Modbus includes ----------------------------------
#include "mb.h"
#include "mbport.h"

// ----------------------- Defines ------------------------------------------
#define BIT_CHECK_ANY						0xFF

// Bit access -	Physical Discrete Inputs:
//					Function: Read Discrete Inputs (02)
#define MB_BIT_INPUT_OCP_ADDR_START			1000

// Bit access -	Internal Bits or Physical Coils:
//					Function: Read Coils (01)
#define MB_BIT_INPUT_RLY_ADDR_START			2000
#define MB_BIT_INPUT_STATUS_ADDR_START		2100		// SYS, REC, SM
#define MB_BIT_INPUT_SYS_ADDR_START			MB_BIT_INPUT_STATUS_ADDR_START
#define MB_BIT_INPUT_REC_ADDR_START			MB_BIT_OUTPUT_SYS_ADDR_START + 8
#define MB_BIT_INPUT_SM_ADDR_START			MB_BIT_INPUT_REC_ADDR_START + 8
#define MB_BIT_INPUT_RST_ADDR_START			2200
//					Function: Write Single Coil (05)
//					Function: Write Multiple Coils (15)
#define MB_BIT_OUTPUT_RLY_ADDR_START		MB_BIT_INPUT_RLY_ADDR_START
#define MB_BIT_OUTPUT_SYS_ADDR_START		MB_BIT_INPUT_STATUS_ADDR_START
#define MB_BIT_OUTPUT_REC_ADDR_START		MB_BIT_OUTPUT_SYS_ADDR_START + 8

// 16-Bits access -	Physical Input Registers:
//					Function: Read Input Register(s) (04)
#define MB_REG_INPUT_ADC_ADDR_START			3000

// 16-Bits access -	Internal Registers or Physical Output Registers:
//					Function: Read Holding Register(s) (03)
#define MB_REG_INPUT_CALIB_ADDR_START		4000
#define MB_REG_INPUT_HW_FW_ADDR_START		4100
#define MB_REG_INPUT_MODE_ADDR_START		4200
#define MB_REG_INPUT_DDS_ADDR_START			4300
#define MB_REG_INPUT_ITRIP_ADDR_START		4400
#define MB_REG_INPUT_DPLL_ADDR_START		4500
#define MB_REG_INPUT_SM_ADDR_START			9000
#define MB_REG_INPUT_REC_INFO_ADDR_START	9100
#define MB_REG_INPUT_REC_DATA_ADDR_START	9200
//					Function: Write Single Register (06)
//					Function: Write Multiple Registers (16)
#define MB_REG_OUTPUT_MODE_ADDR_START		MB_REG_INPUT_MODE_ADDR_START + 2	// Skip UpTime
#define MB_REG_OUTPUT_DDS_ADDR_START		MB_REG_INPUT_DDS_ADDR_START
#define MB_REG_OUTPUT_ITRIP_ADDR_START		MB_REG_INPUT_ITRIP_ADDR_START
#define MB_REG_OUTPUT_DPLL_ADDR_START		MB_REG_INPUT_DPLL_ADDR_START

// ----------------------- Types --------------------------------------------
typedef void (*load_bit_cb_t)(uint8_t **Output_Buffer, uint8_t *Out_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos);
typedef void (*load_reg_cb_t)(uint8_t **Output_Buffer, void *Value_Ptr);
typedef void (*conv_reg_cb_t)(void *Output, void *Input);
typedef void (*store_bit_cb_t)(uint8_t **Input_Buffer, uint8_t *Inp_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos);
typedef void (*store_reg_cb_t)(uint8_t **Input_Buffer, void *Value_Ptr);

typedef struct Bit_Read_s {
	void*			data_ptr;
	uint8_t			bit_pos;
	load_bit_cb_t	load_cb;
} Bit_Read_t;

typedef struct Reg_Read_s {
	void*			data_ptr;
	uint8_t			data_size;
	conv_reg_cb_t	conv_cb;
	load_reg_cb_t	load_cb;
} Reg_Read_t;

typedef struct Bit_Write_s {
	void*			data_ptr;
	uint8_t			bit_pos;
	store_bit_cb_t	store_cb;
} Bit_Write_t;

typedef struct Reg_Write_s {
	void*			data_ptr;
	uint8_t			data_size;
	conv_reg_cb_t	conv_cb;
	store_reg_cb_t	store_cb;
} Reg_Write_t;

// ----------------------- Static variables ---------------------------------

// ----------------------- Start implementation -----------------------------

void App_MODBUS_Init(void *Parameters)
{
	const UCHAR		ucSlaveID[] = {APP_SETTINGS_MODBUS_SLAVE_ID_ADDITIONAL};
	eMBErrorCode	eStatus;

	(void)Parameters;
	// Initialize the Modbus Protocol Stack.
	eStatus = eMBInit(MB_RTU, APP_SETTINGS_MODBUS_SLAVE_ADDR, 0, APP_SETTINGS_MODBUS_BAUDRATE, APP_SETTINGS_MODBUS_PARITY);
	// Set the Modbus Slave ID.
	eStatus = eMBSetSlaveID(APP_SETTINGS_MODBUS_SLAVE_ID_MAIN, TRUE, ucSlaveID, sizeof(ucSlaveID));
	// Enable the Modbus Protocol Stack.
	eStatus = eMBEnable();
}

void App_MODBUS_Process(void *Parameters)
{
	(void)Parameters;
	(void)eMBPoll();
}

static void load_bit(uint8_t **Output_Buffer, uint8_t *Out_Bit_Pos, bool Value_Bit_State)
{
	uint8_t out_bit_mask = (1 << *Out_Bit_Pos);

	if(*Out_Bit_Pos == 0) {
		*(*Output_Buffer) = 0x00;
	}
	if(Value_Bit_State)
		*(*Output_Buffer) |= out_bit_mask;
	else
		*(*Output_Buffer) &= ~out_bit_mask;
	(*Out_Bit_Pos)++;
	if((*Out_Bit_Pos) > 7) {
		*Out_Bit_Pos = 0;
		(*Output_Buffer)++;
	}
}

static void load_bit_bool(uint8_t **Output_Buffer, uint8_t *Out_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	bool value_bit_state = *(bool*)Value_Ptr;

	(void)Value_Bit_Pos;
	if(Value_Ptr != NULL) {
		load_bit(Output_Buffer, Out_Bit_Pos, value_bit_state);
	} else {
		load_bit(Output_Buffer, Out_Bit_Pos, false);
	}
}

static void load_bit_uint8(uint8_t **Output_Buffer, uint8_t *Out_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	uint8_t *value_data = (uint8_t*)Value_Ptr;
	bool value_bit_state;

	if(Value_Ptr != NULL) {
		if(Value_Bit_Pos != BIT_CHECK_ANY)
			value_bit_state = *value_data & (1 << Value_Bit_Pos);
		else
			value_bit_state = *value_data & 0xFF;
		load_bit(Output_Buffer, Out_Bit_Pos, value_bit_state);
	} else {
		load_bit(Output_Buffer, Out_Bit_Pos, false);
	}
}

static void load_bit_uint16(uint8_t **Output_Buffer, uint8_t *Out_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	uint16_t *value_data = (uint16_t*)Value_Ptr;
	bool value_bit_state;

	if(Value_Ptr != NULL) {
		if(Value_Bit_Pos != BIT_CHECK_ANY)
			value_bit_state = *value_data & (1 << Value_Bit_Pos);
		else
			value_bit_state = *value_data & 0xFFFF;
		load_bit(Output_Buffer, Out_Bit_Pos, value_bit_state);
	} else {
		load_bit(Output_Buffer, Out_Bit_Pos, false);
	}
}

static void load_reg_uint8(uint8_t **Output_Buffer, void *Value_Ptr)
{
	uint8_t *value_data = (uint8_t*)Value_Ptr;

	*(*Output_Buffer)++ = 0;
	*(*Output_Buffer)++ = *value_data;
}

static void load_reg_uint16(uint8_t **Output_Buffer, void *Value_Ptr)
{
	uint16_t *value_data = (uint16_t*)Value_Ptr;

	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 8);
	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 0);
}

static void load_reg_uint32(uint8_t **Output_Buffer, void *Value_Ptr)
{
	uint32_t *value_data = (uint32_t*)Value_Ptr;

	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 24);
	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 16);
	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 8);
	*(*Output_Buffer)++ = (uint8_t)(*value_data >> 0);
}

static bool store_bit(uint8_t **Input_Buffer, uint8_t *Inp_Bit_Pos)
{
	bool inp_bit_state;
	uint8_t inp_bit_mask = (1 << *Inp_Bit_Pos);
	
	inp_bit_state = *(*Input_Buffer) & inp_bit_mask;
	(*Inp_Bit_Pos)++;
	if((*Inp_Bit_Pos) > 7) {
		*Inp_Bit_Pos = 0;
		(*Input_Buffer)++;
	}
	return inp_bit_state;
}

static void store_bit_bool(uint8_t **Input_Buffer, uint8_t *Inp_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	bool *value_data = (bool*)Value_Ptr;
	bool value_bit_state = store_bit(Input_Buffer, Inp_Bit_Pos);

	(void)Value_Bit_Pos;
	if(Value_Ptr != NULL) {
		*value_data = value_bit_state;
	}
}

static void store_bit_uint8(uint8_t **Input_Buffer, uint8_t *Inp_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	uint8_t *value_data = (uint8_t*)Value_Ptr;
	bool value_bit_state = store_bit(Input_Buffer, Inp_Bit_Pos);
	uint8_t value_bit_mask = (1 << Value_Bit_Pos);

	if(Value_Ptr != NULL) {
		if(value_bit_state)
			*value_data |= value_bit_mask;
		else
			*value_data &= ~value_bit_mask;
	}
}

static void store_bit_uint16(uint8_t **Input_Buffer, uint8_t *Inp_Bit_Pos, void *Value_Ptr, uint8_t Value_Bit_Pos)
{
	uint16_t *value_data = (uint16_t*)Value_Ptr;
	bool value_bit_state = store_bit(Input_Buffer, Inp_Bit_Pos);
	uint16_t value_bit_mask = (1 << Value_Bit_Pos);

	if(Value_Ptr != NULL) {
		if(value_bit_state)
			*value_data |= value_bit_mask;
		else
			*value_data &= ~value_bit_mask;
	}
}

static void store_reg_uint8(uint8_t **Input_Buffer, void *Value_Ptr)
{
	uint8_t inp_byte;
	
	inp_byte = *(*Input_Buffer)++;	// Skip MSB Byte
	inp_byte = *(*Input_Buffer)++;
	*((uint8_t*)Value_Ptr) = inp_byte;
}

static void store_reg_uint16(uint8_t **Input_Buffer, void *Value_Ptr)
{
	uint16_t value_data = 0;
	uint16_t inp_byte;
	
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 8;
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 0;
	*((uint16_t*)Value_Ptr) = value_data;
}

static void store_reg_uint32(uint8_t **Input_Buffer, void *Value_Ptr)
{
	uint32_t value_data = 0;
	uint32_t inp_byte;
	
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 24;
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 16;
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 8;
	inp_byte = *(*Input_Buffer)++;
	value_data |= inp_byte << 0;
	*((uint32_t*)Value_Ptr) = value_data;
}


static void convert_u_udc_adc_to_volt(void *Output, void *Input)
{
	uint32_t ADC_Value = *((uint16_t*)Input);
	*((uint16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_U_DC_SCALING;
}

static void convert_u_inv_adc_to_volt(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_U_INV_SCALING;
}

static void convert_u_mid_adc_to_volt(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_U_MID_SCALING;
}

static void convert_u_grid_adc_to_volt(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_U_GRID_SCALING;
}

static void convert_i_inv_adc_to_ampere(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_I_INV_SCALING;
}

static void convert_i_grid_adc_to_ampere(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_I_GRID_SCALING;
}

static void convert_t_adc_to_celsius(void *Output, void *Input)
{
	int32_t ADC_Value = *((int16_t*)Input);
	if((ADC_Value != INT16_MIN) && (ADC_Value != INT16_MAX))
		*((int16_t*)Output) = ADC_Value * BSP_SETTINGS_ADC_T_SCALING;
	else
		*((int16_t*)Output) = ADC_Value;
}

// OCP Info List
static const Bit_Read_t bit_input_ocp_list[] = {
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L1_INV, load_bit_uint8},
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L2_INV, load_bit_uint8},
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L3_INV, load_bit_uint8},
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L1_GRID, load_bit_uint8},
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L2_GRID, load_bit_uint8},
	{(void*)&App_OCP_OC_Status, APP_OCP_OC_L3_GRID, load_bit_uint8},
	{NULL, 0, load_bit_uint8},
	{NULL, 0, load_bit_uint8}
};
#define MB_BIT_INPUT_OCP_NREGS		ARRAY_SIZE(bit_input_ocp_list)

// RLY Info List
static const Bit_Read_t bit_input_rly_list[] = {
	{(void*)&RelaysState, APP_RELAY_INV_PHASE, load_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_INV_NEUTRAL, load_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_GRID_PHASE, load_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_GRID_NEUTRAL, load_bit_uint8},
	{NULL, 0, load_bit_uint8},
	{NULL, 0, load_bit_uint8},
	{NULL, 0, load_bit_uint8},
	{NULL, 0, load_bit_uint8}
};
#define MB_BIT_INPUT_RLY_NREGS		ARRAY_SIZE(bit_input_rly_list)

// Status Info List (SYS, REC, SM)
static const Bit_Read_t bit_input_status_list[] = {
	{(void*)&Sys_Reloaded, 0, load_bit_bool},
	{(void*)&Sys_Shutdown, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{(void*)&DataRecState, REC_DATA_READY, load_bit_uint8},
	{(void*)&DataRecState, REC_DATA_REREAD, load_bit_uint8},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{(void*)&SMRecState, BIT_CHECK_ANY, load_bit_uint8},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool},
	{NULL, 0, load_bit_bool}
};
#define MB_BIT_INPUT_STATUS_NREGS		ARRAY_SIZE(bit_input_status_list)

// RST Info List
static const Bit_Read_t bit_input_rst_list[] = {
	{(void*)&BSP_System_Reset_State, RST_POR, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_BOR, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_IDLE, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_SLEEP, load_bit_uint16},

	{(void*)&BSP_System_Reset_State, RST_WDTO, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_SWDTEN, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_SWR, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_EXTR, load_bit_uint16},

	{(void*)&BSP_System_Reset_State, RST_VREGS, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_CM, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_UNIMPLEMENTED0, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_VREGSF, load_bit_uint16},

	{(void*)&BSP_System_Reset_State, RST_UNIMPLEMENTED1, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_UNIMPLEMENTED2, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_IOPUWR, load_bit_uint16},
	{(void*)&BSP_System_Reset_State, RST_TRAPR, load_bit_uint16}
};
#define MB_BIT_INPUT_RST_NREGS		ARRAY_SIZE(bit_input_rst_list)

// ADC Voltage, Current & Temperature Values List
static const Reg_Read_t reg_input_adc_list[] = {
	// L1_U_INV
	{(void*)&ADC_L1_U_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L1_U_Inv_Mean, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Inv_PkPk, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Inv_RMS, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	// L1_I_INV
	{(void*)&ADC_L1_I_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L1_I_Inv_Mean, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L1_I_Inv_PkPk, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L1_I_Inv_RMS, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	// L2_U_INV
	{(void*)&ADC_L2_U_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L2_U_Inv_Mean, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Inv_PkPk, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Inv_RMS, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	// L2_I_INV
	{(void*)&ADC_L2_I_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L2_I_Inv_Mean, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L2_I_Inv_PkPk, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L2_I_Inv_RMS, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	// L3_U_INV
	{(void*)&ADC_L3_U_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L3_U_Inv_Mean, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Inv_PkPk, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Inv_RMS, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	// L3_I_INV
	{(void*)&ADC_L3_I_Inv_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L3_I_Inv_Mean, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L3_I_Inv_PkPk, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L3_I_Inv_RMS, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	// L1_U_MID
	{(void*)&ADC_L1_U_Mid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L1_U_Mid_Mean, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Mid_PkPk, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Mid_RMS, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	// L2_U_MID
	{(void*)&ADC_L2_U_Mid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L2_U_Mid_Mean, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Mid_PkPk, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Mid_RMS, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	// L3_U_MID
	{(void*)&ADC_L3_U_Mid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L3_U_Mid_Mean, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Mid_PkPk, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Mid_RMS, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	// L1_U_GRID
	{(void*)&ADC_L1_U_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L1_U_Grid_Mean, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Grid_PkPk, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L1_U_Grid_RMS, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	// L1_I_GRID
	{(void*)&ADC_L1_I_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L1_I_Grid_Mean, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L1_I_Grid_PkPk, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L1_I_Grid_RMS, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	// L2_U_GRID
	{(void*)&ADC_L2_U_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L2_U_Grid_Mean, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Grid_PkPk, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L2_U_Grid_RMS, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	// L2_I_GRID
	{(void*)&ADC_L2_I_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L2_I_Grid_Mean, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L2_I_Grid_PkPk, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L2_I_Grid_RMS, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	// L3_U_GRID
	{(void*)&ADC_L3_U_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L3_U_Grid_Mean, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Grid_PkPk, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_L3_U_Grid_RMS, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	// L3_I_GRID
	{(void*)&ADC_L3_I_Grid_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_L3_I_Grid_Mean, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L3_I_Grid_PkPk, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&ADC_L3_I_Grid_RMS, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	// P_U_DC
	{(void*)&ADC_P_U_DC_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_P_U_DC_Mean, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_P_U_DC_PkPk, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_P_U_DC_RMS, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	// N_U_DC
	{(void*)&ADC_N_U_DC_RAW, 1, NULL, load_reg_uint16},
	{(void*)&ADC_N_U_DC_Mean, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_N_U_DC_PkPk, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	{(void*)&ADC_N_U_DC_RMS, 1, convert_u_udc_adc_to_volt, load_reg_uint16},
	// T1
	{(void*)&ADC_T1_RAW, 1, NULL, load_reg_uint16},
	{(void*)&TempSens_T_Ch1, 1, convert_t_adc_to_celsius, load_reg_uint16},
	{(void*)&TempSens_R_Ch1, 2, NULL, load_reg_uint32},
	{(void*)&TempSens_R_Ch1, 0, NULL, NULL},
	// T2
	{(void*)&ADC_T2_RAW, 1, NULL, load_reg_uint16},
	{(void*)&TempSens_T_Ch2, 1, convert_t_adc_to_celsius, load_reg_uint16},
	{(void*)&TempSens_R_Ch2, 2, NULL, load_reg_uint32},
	{(void*)&TempSens_R_Ch2, 0, NULL, NULL},
	// T3
	{(void*)&ADC_T3_RAW, 1, NULL, load_reg_uint16},
	{(void*)&TempSens_T_Ch3, 1, convert_t_adc_to_celsius, load_reg_uint16},
	{(void*)&TempSens_R_Ch3, 2, NULL, load_reg_uint32},
	{(void*)&TempSens_R_Ch3, 0, NULL, NULL}
};
#define MB_REG_INPUT_ADC_NREGS		ARRAY_SIZE(reg_input_adc_list)

// ADC Calibration Values List
static const Reg_Read_t reg_input_calib_list[] = {
	{(void*)&NVMemory.ADC.L1_I_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_I_Inv_Error, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_I_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_I_Inv_Error, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_I_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_I_Inv_Error, 1, convert_i_inv_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_I_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_I_Grid_Error, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_I_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_I_Grid_Error, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_I_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_I_Grid_Error, 1, convert_i_grid_adc_to_ampere, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Inv_Error, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Inv_Error, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Inv_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Inv_Error, 1, convert_u_inv_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Mid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Mid_Error, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Mid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Mid_Error, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Mid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Mid_Error, 1, convert_u_mid_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L1_U_Grid_Error, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L2_U_Grid_Error, 1, convert_u_grid_adc_to_volt, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Grid_Error, 1, NULL, load_reg_uint16},
	{(void*)&NVMemory.ADC.L3_U_Grid_Error, 1, convert_u_grid_adc_to_volt, load_reg_uint16}
};
#define MB_REG_INPUT_CALIB_NREGS		ARRAY_SIZE(reg_input_calib_list)

// VER HW & SW Info List
static const Reg_Read_t reg_input_hw_fw_list[] = {
	{(void*)&Sys_HW_Info, 1, NULL, load_reg_uint16},
	{(void*)&Sys_FW_Version, 1, NULL, load_reg_uint16},
	{(void*)&Sys_FW_Date_Year, 1, NULL, load_reg_uint16},
	{(void*)&Sys_FW_Date_Month_and_Day, 1, NULL, load_reg_uint16},
};
#define MB_REG_INPUT_HW_FW_NREGS		ARRAY_SIZE(reg_input_hw_fw_list)

// MODE Info List
static const Reg_Read_t reg_input_mode_list[] = {
	{(void*)&App_RTC_Counter_s, 2, NULL, load_reg_uint32},
	{(void*)&App_RTC_Counter_s, 0, NULL, NULL},
	{(void*)&App_SM_System_Mode, 1, NULL, load_reg_uint8}
};
#define MB_REG_INPUT_MODE_NREGS		ARRAY_SIZE(reg_input_mode_list)

// DDS Info List
static const Reg_Read_t reg_input_dds_list[] = {
	{(void*)&App_DDS_Waves_Freq, 1, NULL, load_reg_uint16},
	{(void*)&App_DDS_Shift_Phase_Chn2, 1, NULL, load_reg_uint16},
	{(void*)&App_DDS_Shift_Phase_Chn3, 1, NULL, load_reg_uint16},
	{(void*)&App_DDS_Gain_Chn1, 1, NULL, load_reg_uint16},
	{(void*)&App_DDS_Gain_Chn2, 1, NULL, load_reg_uint16},
	{(void*)&App_DDS_Gain_Chn3, 1, NULL, load_reg_uint16}
};
#define MB_REG_INPUT_DDS_NREGS		ARRAY_SIZE(reg_input_dds_list)

// ITRIP Info List
static const Reg_Read_t reg_input_itrip_list[] = {
	{(void*)&App_OCP_ITrip_Inv, 1, NULL, load_reg_uint16},
	{(void*)&App_OCP_ITrip_Grid, 1, NULL, load_reg_uint16}
};
#define MB_REG_INPUT_ITRIP_NREGS		ARRAY_SIZE(reg_input_itrip_list)

static int16_t loc_id_set;
static int16_t loc_iq_set;
static int16_t loc_vd_set;
static int16_t loc_vq_set;
static int16_t loc_omegaL;

// DPLL Info List
static const Reg_Read_t reg_input_dpll_list[] = {
	{(void*)&loc_id_set, 1, NULL, load_reg_uint16},
	{(void*)&loc_iq_set, 1, NULL, load_reg_uint16},
	{(void*)&loc_vd_set, 1, NULL, load_reg_uint16},
	{(void*)&loc_vq_set, 1, NULL, load_reg_uint16},
	{(void*)&loc_omegaL, 1, NULL, load_reg_uint16}
};
#define MB_REG_INPUT_DPLL_NREGS		ARRAY_SIZE(reg_input_dpll_list)

static void load_reg_uint16_ex_rec(uint8_t **Output_Buffer, void *Value_Ptr)
{
	uint16_t data_word;

	(void)Value_Ptr;
	App_DataRec_Load_Word((void*)&data_word);
	load_reg_uint16(Output_Buffer, &data_word);
}

// REC DATA List
static const Reg_Read_t reg_input_rec_data_list[] = {	// 2 + 123 regs = 125 in total (max for RTU)
	{(void*)&DataRecAddr, 2, NULL, load_reg_uint32},	// 2 regs
	{(void*)&DataRecAddr, 0, NULL, NULL},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},		// 123 regs
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec},
	{(void*)NULL, 1, NULL, load_reg_uint16_ex_rec}
};
#define MB_REG_INPUT_REC_DATA_NREGS		ARRAY_SIZE(reg_input_rec_data_list)

static void load_reg_uint32_ex_rec(uint8_t **Output_Buffer, void *Value_Ptr)
{
	uint32_t buffer_length = App_DataRec_Get_Length();
	
	load_reg_uint32(Output_Buffer, &buffer_length);
}

static uint16_t loc_Packet_Length = (MB_REG_INPUT_REC_DATA_NREGS * 2);	// 125 * 2 = 250 bytes or 125 regs

// REC INFO List
static const Reg_Read_t reg_input_rec_info_list[] = {
	{(void*)NULL, 2, NULL, load_reg_uint32_ex_rec},
	{(void*)NULL, 0, NULL, NULL},
	{(void*)&loc_Packet_Length, 1, NULL, load_reg_uint16}
};
#define MB_REG_INPUT_REC_INFO_NREGS		ARRAY_SIZE(reg_input_rec_info_list)

static uint8_t loc_State;
static uint8_t loc_Error;
static uint16_t loc_State_Error;
static uint16_t loc_TimeStamp_ms;
static uint32_t loc_TimeStamp_s;

// SM Info List
static const Reg_Read_t reg_input_sm_list[] = {
	{(void*)&SMRecState, 1, NULL, load_reg_uint8},
	{(void*)&loc_State_Error, 1, NULL, load_reg_uint16},
	{(void*)&loc_TimeStamp_ms, 1, NULL, load_reg_uint16},
	{(void*)&loc_TimeStamp_s, 2, NULL, load_reg_uint32},
	{(void*)&loc_TimeStamp_s, 0, NULL, NULL}
};
#define MB_REG_INPUT_SM_NREGS		ARRAY_SIZE(reg_input_sm_list)

// RLY Info List
static const Bit_Write_t bit_output_rly_list[] = {
	{(void*)&RelaysState, APP_RELAY_INV_PHASE, store_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_INV_NEUTRAL, store_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_GRID_PHASE, store_bit_uint8},
	{(void*)&RelaysState, APP_RELAY_GRID_NEUTRAL, store_bit_uint8},
	{NULL, 0, store_bit_uint8},
	{NULL, 0, store_bit_uint8},
	{NULL, 0, store_bit_uint8},
	{NULL, 0, store_bit_uint8}
};
#define MB_BIT_OUTPUT_RLY_NREGS		ARRAY_SIZE(bit_output_rly_list)

// SYS Info List
static const Bit_Write_t bit_output_sys_list[] = {
	{(void*)&Sys_Reloaded, 0, store_bit_bool},
	{(void*)&Sys_Shutdown, 0, store_bit_bool},
	{(void*)&Sys_Calib, 0, store_bit_bool},
	{(void*)&Sys_Reset, 0, store_bit_bool},
	{NULL, 0, store_bit_bool},
	{NULL, 0, store_bit_bool},
	{NULL, 0, store_bit_bool},
	{NULL, 0, store_bit_bool}
};
#define MB_BIT_OUTPUT_SYS_NREGS		ARRAY_SIZE(bit_output_sys_list)

static bool loc_rec_reinit;
static bool loc_rec_reread;

static void store_bits_rec(void)
{
	uint8_t data = 0;
	
	if(loc_rec_reinit)
		data |= (1 << REC_CONTROL_REINIT);		// Reload Everything
	if(loc_rec_reread)
		data |= (1 << REC_CONTROL_REREAD);		// Set Load Pointer
	App_DataRec_Set(data);
}

// REC Info List
static const Bit_Write_t bit_output_rec_list[] = {
	{(void*)&loc_rec_reinit, 0, store_bit_bool},
	{(void*)&loc_rec_reread, 0, store_bit_bool}
};
#define MB_BIT_OUTPUT_REC_NREGS		ARRAY_SIZE(bit_output_rec_list)

// MODE Info List
static const Reg_Write_t reg_output_mode_list[] = {
	{(void*)&App_SM_System_Mode, 1, NULL, store_reg_uint8}
};
#define MB_REG_OUTPUT_MODE_NREGS		ARRAY_SIZE(reg_output_mode_list)

static volatile uint16_t	loc_App_DDS_Waves_Freq;			// Frequency of waveforms
static volatile int16_t		loc_App_DDS_Shift_Phase_Chn2;	// Phase shift tuning word for channel 2
static volatile int16_t		loc_App_DDS_Shift_Phase_Chn3;	// Phase shift tuning word for channel 3
static volatile uint16_t	loc_App_DDS_Gain_Chn1;			// Magnitude for channel 1
static volatile uint16_t	loc_App_DDS_Gain_Chn2;			// Magnitude for channel 2
static volatile uint16_t	loc_App_DDS_Gain_Chn3;			// Magnitude for channel 3

static void copy_regs_dds(void)
{
	loc_App_DDS_Waves_Freq = App_DDS_Waves_Freq;				// Frequency of waveforms
	loc_App_DDS_Shift_Phase_Chn2 = App_DDS_Shift_Phase_Chn2;	// Phase shift tuning word for channel 2
	loc_App_DDS_Shift_Phase_Chn3 = App_DDS_Shift_Phase_Chn3;	// Phase shift tuning word for channel 3
	loc_App_DDS_Gain_Chn1 = App_DDS_Gain_Chn1;					// Magnitude for channel 1
	loc_App_DDS_Gain_Chn2 = App_DDS_Gain_Chn2;					// Magnitude for channel 2
	loc_App_DDS_Gain_Chn3 = App_DDS_Gain_Chn3;					// Magnitude for channel 3
}

static void store_reg_uint16_ex_dds(uint8_t **Input_Buffer, void *Value_Ptr)
{
	store_reg_uint16(Input_Buffer, Value_Ptr);
	if(loc_App_DDS_Waves_Freq != App_DDS_Waves_Freq)				// Frequency of waveforms
		App_DDS_Set_Freq(loc_App_DDS_Waves_Freq);
	if(loc_App_DDS_Shift_Phase_Chn2 != App_DDS_Shift_Phase_Chn2)	// Phase shift tuning word for channel 2
		App_DDS_Set_Phase_Ch2(loc_App_DDS_Shift_Phase_Chn2);
	if(loc_App_DDS_Shift_Phase_Chn3 != App_DDS_Shift_Phase_Chn3)	// Phase shift tuning word for channel 3
		App_DDS_Set_Phase_Ch3(loc_App_DDS_Shift_Phase_Chn3);
	if(loc_App_DDS_Gain_Chn1 != App_DDS_Gain_Chn1)					// Magnitude for channel 1
		App_DDS_Set_Gain_Ch1(loc_App_DDS_Gain_Chn1);
	if(loc_App_DDS_Gain_Chn2 != App_DDS_Gain_Chn2)					// Magnitude for channel 2
		App_DDS_Set_Gain_Ch2(loc_App_DDS_Gain_Chn2);
	if(loc_App_DDS_Gain_Chn3 != App_DDS_Gain_Chn3)					// Magnitude for channel 3
		App_DDS_Set_Gain_Ch3(loc_App_DDS_Gain_Chn3);
}

// DDS Info List
static const Reg_Write_t reg_output_dds_list[] = {
	{(void*)&loc_App_DDS_Waves_Freq, 1, NULL, store_reg_uint16_ex_dds},
	{(void*)&loc_App_DDS_Shift_Phase_Chn2, 1, NULL, store_reg_uint16_ex_dds},
	{(void*)&loc_App_DDS_Shift_Phase_Chn3, 1, NULL, store_reg_uint16_ex_dds},
	{(void*)&loc_App_DDS_Gain_Chn1, 1, NULL, store_reg_uint16_ex_dds},
	{(void*)&loc_App_DDS_Gain_Chn2, 1, NULL, store_reg_uint16_ex_dds},
	{(void*)&loc_App_DDS_Gain_Chn3, 1, NULL, store_reg_uint16_ex_dds}
};
#define MB_REG_OUTPUT_DDS_NREGS		ARRAY_SIZE(reg_output_dds_list)

// ITRIP Info List
static const Reg_Write_t reg_output_itrip_list[] = {
	{(void*)&App_OCP_ITrip_Inv, 1, NULL, store_reg_uint16},
	{(void*)&App_OCP_ITrip_Grid, 1, NULL, store_reg_uint16}
};
#define MB_REG_OUTPUT_ITRIP_NREGS		ARRAY_SIZE(reg_output_itrip_list)

static void copy_regs_dpll(void)
{
	loc_id_set = App_DPLL_Param_Vd_Get();
	loc_iq_set = App_DPLL_Param_Vq_Get();
	loc_vd_set = App_DPLL_Param_Id_Get();
	loc_vq_set = App_DPLL_Param_Iq_Get();
	loc_omegaL = App_DPLL_Param_Omega_Get();
}

static void store_reg_uint16_ex_dpll(uint8_t **Input_Buffer, void *Value_Ptr)
{
	store_reg_uint16(Input_Buffer, Value_Ptr);
	if(loc_id_set != App_DPLL_Param_Vd_Get())
		App_DPLL_Param_Vd_Set(loc_id_set);
	if(loc_iq_set != App_DPLL_Param_Vq_Get())
		App_DPLL_Param_Vq_Set(loc_iq_set);
	if(loc_vd_set != App_DPLL_Param_Id_Get())
		App_DPLL_Param_Id_Set(loc_vd_set);
	if(loc_vq_set != App_DPLL_Param_Iq_Get())
		App_DPLL_Param_Iq_Set(loc_vq_set);
	if(loc_omegaL != App_DPLL_Param_Omega_Get())
		App_DPLL_Param_Omega_Set(loc_omegaL);
}

// DPLL Info List
static const Reg_Write_t reg_output_dpll_list[] = {
	{(void*)&loc_id_set, 1, NULL, store_reg_uint16_ex_dpll},
	{(void*)&loc_iq_set, 1, NULL, store_reg_uint16_ex_dpll},
	{(void*)&loc_vd_set, 1, NULL, store_reg_uint16_ex_dpll},
	{(void*)&loc_vq_set, 1, NULL, store_reg_uint16_ex_dpll},
	{(void*)&loc_omegaL, 1, NULL, store_reg_uint16_ex_dpll}
};
#define MB_REG_OUTPUT_DPLL_NREGS		ARRAY_SIZE(reg_output_dpll_list)

static void bit_input_processing(const Bit_Read_t *list, UCHAR **pucRegBuffer, USHORT usNDiscrete)
{
	unsigned char	Out_Bit_Pos;

	Out_Bit_Pos = 0;
	while(usNDiscrete > 0) {
		if(list->load_cb != NULL) {
			list->load_cb(pucRegBuffer, &Out_Bit_Pos, list->data_ptr, list->bit_pos);
		}
		usNDiscrete--;
		list++;
	}
}

static void reg_input_processing(const Reg_Read_t *list, UCHAR **pucRegBuffer, USHORT usNRegs)
{
	unsigned long	Data;

	while(usNRegs > 0) {
		if(list->conv_cb != NULL) {
			list->conv_cb(&Data, list->data_ptr);
			list->load_cb(pucRegBuffer, &Data);
		} else {
			if(list->load_cb != NULL) {
				list->load_cb(pucRegBuffer, list->data_ptr);
			}
		}
		usNRegs -= list->data_size;
		list++;
	}
}

static void bit_output_processing(const Bit_Write_t *list, UCHAR **pucRegBuffer, USHORT usNDiscrete)
{
	unsigned char	Inp_Bit_Pos;

	Inp_Bit_Pos = 0;
	while(usNDiscrete > 0) {
		if(list->store_cb != NULL) {
			list->store_cb(pucRegBuffer, &Inp_Bit_Pos, list->data_ptr, list->bit_pos);
		}
		usNDiscrete--;
		list++;
	}
}

static void reg_output_processing(const Reg_Write_t *list, UCHAR **pucRegBuffer, USHORT usNRegs)
{
	unsigned long	Data;

	while(usNRegs > 0) {
		if(list->conv_cb != NULL) {
			list->conv_cb(&Data, list->data_ptr);
			list->store_cb(pucRegBuffer, &Data);
		} else {
			if(list->store_cb != NULL) {
				list->store_cb(pucRegBuffer, list->data_ptr);
			}
		}
		usNRegs -= list->data_size;
		list++;
	}
}

eMBErrorCode eMBRegDiscreteCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{
	eMBErrorCode	eStatus = MB_ENOERR;
	int				iBitIndex;

	if((usAddress >= (MB_BIT_INPUT_OCP_ADDR_START +1)) &&
		(usAddress + usNDiscrete <= (MB_BIT_INPUT_OCP_ADDR_START + 1) + MB_BIT_INPUT_OCP_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_INPUT_OCP_ADDR_START + 1));
		bit_input_processing(&(bit_input_ocp_list[iBitIndex]), &pucRegBuffer, usNDiscrete);
	} else {
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

eMBErrorCode eMBRegCoilsCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
	eMBErrorCode	eStatus = MB_ENOERR;
	int				iBitIndex;

	if((usAddress >= (MB_BIT_INPUT_RLY_ADDR_START +1)) &&
		(usAddress + usNCoils <= (MB_BIT_INPUT_RLY_ADDR_START + 1) + MB_BIT_INPUT_RLY_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_INPUT_RLY_ADDR_START + 1));
		if(eMode == MB_REG_READ) {
			bit_input_processing(&(bit_input_rly_list[iBitIndex]), &pucRegBuffer, usNCoils);
		} else if(eMode == MB_REG_WRITE) {
			bit_output_processing(&(bit_output_rly_list[iBitIndex]), &pucRegBuffer, usNCoils);
		} else {
			eStatus = MB_ENOREG;
		}
	} else
	if((usAddress >= (MB_BIT_OUTPUT_SYS_ADDR_START +1)) &&
		(usAddress + usNCoils <= (MB_BIT_OUTPUT_SYS_ADDR_START + 1) + MB_BIT_OUTPUT_SYS_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_OUTPUT_SYS_ADDR_START + 1));
		if(eMode == MB_REG_WRITE) {
			bit_output_processing(&(bit_output_sys_list[iBitIndex]), &pucRegBuffer, usNCoils);
		} else {
			eStatus = MB_ENOREG;
		}
	} else
	if((usAddress >= (MB_BIT_OUTPUT_REC_ADDR_START +1)) &&
		(usAddress + usNCoils <= (MB_BIT_OUTPUT_REC_ADDR_START + 1) + MB_BIT_OUTPUT_REC_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_OUTPUT_REC_ADDR_START + 1));
		if(eMode == MB_REG_WRITE) {
			bit_output_processing(&(bit_output_rec_list[iBitIndex]), &pucRegBuffer, usNCoils);
			store_bits_rec();
		} else {
			eStatus = MB_ENOREG;
		}
	} else
	if((usAddress >= (MB_BIT_INPUT_STATUS_ADDR_START +1)) &&
		(usAddress + usNCoils <= (MB_BIT_INPUT_STATUS_ADDR_START + 1) + MB_BIT_INPUT_STATUS_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_INPUT_STATUS_ADDR_START + 1));
		if(eMode == MB_REG_READ) {
			bit_input_processing(&(bit_input_status_list[iBitIndex]), &pucRegBuffer, usNCoils);
		} else {
			eStatus = MB_ENOREG;
		}
	} else
	if((usAddress >= (MB_BIT_INPUT_RST_ADDR_START +1)) &&
		(usAddress + usNCoils <= (MB_BIT_INPUT_RST_ADDR_START + 1) + MB_BIT_INPUT_RST_NREGS)) {
		iBitIndex = (int)(usAddress - (MB_BIT_INPUT_RST_ADDR_START + 1));
		if(eMode == MB_REG_READ) {
			bit_input_processing(&(bit_input_rst_list[iBitIndex]), &pucRegBuffer, usNCoils);
		} else {
			eStatus = MB_ENOREG;
		}
	} else {
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

eMBErrorCode eMBRegInputCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{
	eMBErrorCode	eStatus = MB_ENOERR;
	int				iRegIndex;

	if((usAddress >= (MB_REG_INPUT_ADC_ADDR_START +1)) &&
		(usAddress + usNRegs <= (MB_REG_INPUT_ADC_ADDR_START + 1) + MB_REG_INPUT_ADC_NREGS)) {
		iRegIndex = (int)(usAddress - (MB_REG_INPUT_ADC_ADDR_START + 1));
		reg_input_processing(&(reg_input_adc_list[iRegIndex]), &pucRegBuffer, usNRegs);
	} else {
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

eMBErrorCode eMBRegHoldingCB(UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{
	eMBErrorCode	eStatus = MB_ENOERR;
	int				iRegIndex;
	
	if(eMode == MB_REG_READ) {
		if((usAddress >= (MB_REG_INPUT_CALIB_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_CALIB_ADDR_START + 1) + MB_REG_INPUT_CALIB_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_CALIB_ADDR_START + 1));
			reg_input_processing(&(reg_input_calib_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_HW_FW_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_HW_FW_ADDR_START + 1) + MB_REG_INPUT_HW_FW_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_HW_FW_ADDR_START + 1));
			reg_input_processing(&(reg_input_hw_fw_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_MODE_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_MODE_ADDR_START + 1) + MB_REG_INPUT_MODE_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_MODE_ADDR_START + 1));
			reg_input_processing(&(reg_input_mode_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_DDS_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_DDS_ADDR_START + 1) + MB_REG_INPUT_DDS_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_DDS_ADDR_START + 1));
			reg_input_processing(&(reg_input_dds_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_ITRIP_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_ITRIP_ADDR_START + 1) + MB_REG_INPUT_ITRIP_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_ITRIP_ADDR_START + 1));
			reg_input_processing(&(reg_input_itrip_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_DPLL_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_DPLL_ADDR_START + 1) + MB_REG_INPUT_DPLL_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_DPLL_ADDR_START + 1));
			copy_regs_dpll();
			reg_input_processing(&(reg_input_dpll_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_SM_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_SM_ADDR_START + 1) + MB_REG_INPUT_SM_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_SM_ADDR_START + 1));
			App_SM_Status_Get(&loc_State, &loc_Error, &loc_TimeStamp_ms, &loc_TimeStamp_s);
			loc_State_Error = ((uint16_t)loc_State << 8) | ((uint16_t)loc_Error << 0);
			reg_input_processing(&(reg_input_sm_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_REC_INFO_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_REC_INFO_ADDR_START + 1) + MB_REG_INPUT_REC_INFO_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_REC_INFO_ADDR_START + 1));
			reg_input_processing(&(reg_input_rec_info_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_INPUT_REC_DATA_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_INPUT_REC_DATA_ADDR_START + 1) + MB_REG_INPUT_REC_DATA_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_INPUT_REC_DATA_ADDR_START + 1));
			reg_input_processing(&(reg_input_rec_data_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else {
			eStatus = MB_ENOREG;
		}
	} else if(eMode == MB_REG_WRITE) {
		if((usAddress >= (MB_REG_OUTPUT_MODE_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_OUTPUT_MODE_ADDR_START + 1) + MB_REG_OUTPUT_MODE_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_OUTPUT_MODE_ADDR_START + 1));
			reg_output_processing(&(reg_output_mode_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_OUTPUT_DDS_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_OUTPUT_DDS_ADDR_START + 1) + MB_REG_OUTPUT_DDS_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_OUTPUT_DDS_ADDR_START + 1));
			copy_regs_dds();
			reg_output_processing(&(reg_output_dds_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_OUTPUT_ITRIP_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_OUTPUT_ITRIP_ADDR_START + 1) + MB_REG_OUTPUT_ITRIP_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_OUTPUT_ITRIP_ADDR_START + 1));
			reg_output_processing(&(reg_output_itrip_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else
		if((usAddress >= (MB_REG_OUTPUT_DPLL_ADDR_START +1)) &&
			(usAddress + usNRegs <= (MB_REG_OUTPUT_DPLL_ADDR_START + 1) + MB_REG_OUTPUT_DPLL_NREGS)) {
			iRegIndex = (int)(usAddress - (MB_REG_OUTPUT_DPLL_ADDR_START + 1));
			copy_regs_dpll();
			reg_output_processing(&(reg_output_dpll_list[iRegIndex]), &pucRegBuffer, usNRegs);
		} else {
			eStatus = MB_ENOREG;
		}
	}
	return eStatus;
}

