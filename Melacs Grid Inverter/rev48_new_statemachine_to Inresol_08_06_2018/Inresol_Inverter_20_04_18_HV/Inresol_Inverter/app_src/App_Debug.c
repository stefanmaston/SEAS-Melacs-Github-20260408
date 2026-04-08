/*
 *  File name: App_Debug.c
 *
 *  Description: High level function implementations for Debug
 *
 *  Author: Future Electronics
 *
 */
#include <string.h>
#include "global_includes.h"

#ifndef INT16_MIN
#define INT16_MIN (-32768)
#endif
#ifndef INT16_MAX
#define INT16_MAX (32767)
#endif

typedef enum DataTypes_e {
	DATA_2BYTES = 0,	// e.g. uint8_t
	DATA_4BYTES,		// e.g. uint16_t
	DATA_8BYTES,		// e.g. uint32_t
	DATA_NULL
} DataTypes_t;

typedef enum DebugRxCmdCode_e {
	DEBUG_RX_CMD_SET_RESPONSE = 0,
	DEBUG_RX_CMD_SET_ECHO_ON_OFF,
	DEBUG_RX_CMD_SET_DDS_PARAMS,
	DEBUG_RX_CMD_SET_RELAYS,
	DEBUG_RX_CMD_SET_ITRIP_PARAMS,
	DEBUG_RX_CMD_SET_REC,
	DEBUG_RX_CMD_SET_SYSTEM_PARAMS,
	DEBUG_RX_CMD_SET_DPLL_PARAMS,
	DEBUG_RX_CMD_SET_SYSTEM_RESET
} DebugRxCmdCode_t;

typedef enum DebugRxEchoTypes_e {
	DEBUG_TX_ECHO_OFF = 0,
	DEBUG_TX_ECHO_ON
} DebugRxEchoTypes_t;

typedef enum DebugTxResponseCode_e {
	DEBUG_TX_RSP_ACK = 0,		// Response ACK/nACK
	DEBUG_TX_RSP_FW_VER,		// Firmware Version
	DEBUG_TX_RSP_RESET,			// Reset Information
	DEBUG_TX_RSP_ADC_P_U_DC,	// Results from ADC Converter - P U DC
	DEBUG_TX_RSP_ADC_N_U_DC,	// Results from ADC Converter - N U DC
	DEBUG_TX_RSP_ADC_L1_U_INV,	// Results from ADC Converter - L1 U Inv
	DEBUG_TX_RSP_ADC_L1_I_INV,	// Results from ADC Converter - L1 I Inv
	DEBUG_TX_RSP_ADC_L2_U_INV,	// Results from ADC Converter - L2 U Inv
	DEBUG_TX_RSP_ADC_L2_I_INV,	// Results from ADC Converter - L2 I Inv
	DEBUG_TX_RSP_ADC_L3_U_INV,	// Results from ADC Converter - L3 U Inv
	DEBUG_TX_RSP_ADC_L3_I_INV,	// Results from ADC Converter - L3 I Inv
	DEBUG_TX_RSP_ADC_L1_U_MID,	// Results from ADC Converter - L1 U Mid
	DEBUG_TX_RSP_ADC_L2_U_MID,	// Results from ADC Converter - L2 U Mid
	DEBUG_TX_RSP_ADC_L3_U_MID,	// Results from ADC Converter - L3 U Mid
	DEBUG_TX_RSP_ADC_L1_U_GRID,	// Results from ADC Converter - L1 U Grid
	DEBUG_TX_RSP_ADC_L1_I_GRID,	// Results from ADC Converter - L1 I Grid
	DEBUG_TX_RSP_ADC_L2_U_GRID,	// Results from ADC Converter - L2 U Grid
	DEBUG_TX_RSP_ADC_L2_I_GRID,	// Results from ADC Converter - L2 I Grid
	DEBUG_TX_RSP_ADC_L3_U_GRID,	// Results from ADC Converter - L3 U Grid
	DEBUG_TX_RSP_ADC_L3_I_GRID,	// Results from ADC Converter - L3 I Grid
	DEBUG_TX_RSP_ADC_T1,		// Results from ADC Converter - T1
	DEBUG_TX_RSP_ADC_T2,		// Results from ADC Converter - T2
	DEBUG_TX_RSP_ADC_T3,		// Results from ADC Converter - T3
	DEBUG_TX_RSP_STATUS,		// Status (OCP, etc...)
	DEBUG_TX_RSP_REC_INFO,		// Results from Data Recording - Info
	DEBUG_TX_RSP_REC_DATA,		// Results from Data Recording - Data
	DEBUG_TX_RSP_SM_DATA		// Results from SM Recording  - Data
} DebugTxResponseCode_t;

typedef enum DebugTxAckTypes_e {
	DEBUG_TX_NACK = 0,
	DEBUG_TX_ACK
} DebugTxAckTypes_t;

typedef void (*rx_cmd_cb_t)(void *data);
typedef void (*tx_rsp_cb_t)(void *data);

typedef struct RxCmdList_s {
	uint8_t cmd_code;
	uint8_t cmd_length;
	uint8_t *param_types;
	rx_cmd_cb_t cmd_cb;
} RxCmdList_t;

typedef struct TxRspList_s {
	uint8_t rsp_code;
	uint8_t *param_types;
	tx_rsp_cb_t rsp_cb;
} TxRspList_t;

// Note: The MSBs of all values in frames are transmitted at the first position.

/* RX Command - Set Response - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 00 means: SET_RESPONSE)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Response Type (e.g. 00 means: RSP_OFF, 01 means: RSP_FW_VER etc...)
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set Response Type - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetResponse_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Response_Type[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetResponse_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetResponse_BIN_s {
	uint8_t		Response_Type;
	uint8_t		Frame_Counter;
} RxCmdSetResponse_BIN_t;

#define RX_CMD_SET_RESPONSE_TYPE		DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_RESPONSE_SIZE		sizeof(RxCmdSetResponse_ASCIIHEX_t)

/* RX Command - Set Echo On/Off - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 01 means: SET_ECHO_ON_OFF)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Echo On/Off state (e.g. 00 means: ECHO_OFF, 01 means: ECHO_ON)
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set Echo On/Off - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetEchoOnOff_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Echo_State[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetEchoOnOff_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetEchoOnOff_BIN_s {
	uint8_t		Echo_State;
	uint8_t		Frame_Counter;
} RxCmdSetEchoOnOff_BIN_t;

#define RX_CMD_SET_ECHO_ON_OFF_TYPE		DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_ECHO_ON_OFF_SIZE		sizeof(RxCmdSetEchoOnOff_ASCIIHEX_t)

/* RX Command - Set DDS Parameters - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 02 means: SET_DDS_PARAMS)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the Frequency in 0.1Hz (e.g. 01F4 means: 50.0 Hz)
Bytes 7, 8, 9, 10 - ASCII HEX representation of int16_t value - the Phase 2 Shift from -360deg to +360deg (-2Pi to +2Pi) (e.g. 2AAA means: +120deg)
Bytes 11, 12, 13, 14 - ASCII HEX representation of int16_t value - the Phase 3 Shift from -360deg to +360deg (-2Pi to +2Pi) (e.g. 5555 means: +240deg)
Bytes 15, 16, 17, 18 - ASCII HEX representation of uint16_t value - the Phase 1 Amplitude from 0 to 65535, 0% - 100% (e.g. 7FFF means: 50%)
Bytes 19, 20, 21, 22 - ASCII HEX representation of uint16_t value - the Phase 2 Amplitude from 0 to 65535, 0% - 100% (e.g. BFFF means: 75%)
Bytes 23, 24, 25, 26 - ASCII HEX representation of uint16_t value - the Phase 3 Amplitude from 0 to 65535, 0% - 100% (e.g. FFFF means: 100%)
Bytes 27, 28 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 29 - 'Z' ASCII character (End of Frame)
Byte 30 - <CR> control character (Carriage Return)
Byte 31 - <LF> control character (Line Feed)
*/

// RX Command - Set DDS Parameters - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetDdsParams_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Freq[4];
	char		Phase2_Shift[4];
	char		Phase3_Shift[4];
	char		Phase1_Amplitude[4];
	char		Phase2_Amplitude[4];
	char		Phase3_Amplitude[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetDdsParams_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetDdsParams_BIN_s {
	uint16_t	Freq;
	int16_t		Phase2_Shift;
	int16_t		Phase3_Shift;
	uint16_t	Phase1_Amplitude;
	uint16_t	Phase2_Amplitude;
	uint16_t	Phase3_Amplitude;
	uint8_t		Frame_Counter;
} RxCmdSetDdsParams_BIN_t;

#define RX_CMD_SET_DDS_PARAMS_TYPE		DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_DDS_PARAMS_SIZE		sizeof(RxCmdSetDdsParams_ASCIIHEX_t)

/* RX Command - Set Relays - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 03 means: SET_RELAYS)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Relays State (e.g. 00 means: All_OFF, 01 means: FIRST_ON etc...)
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set Relays Type - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetRelays_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Relays_State[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetRelays_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetRelays_BIN_s {
	uint8_t		Relays_State;
	uint8_t		Frame_Counter;
} RxCmdSetRelays_BIN_t;

#define RX_CMD_SET_RELAYS_TYPE			DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_RELAYS_SIZE			sizeof(RxCmdSetRelays_ASCIIHEX_t)

/* RX Command - Set I Trip Parameters - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 04 means: SET_ITRIP_PARAMS)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the I Trip  Inv Amplitude from 0 to 65535, 0% - 100% (e.g. 7FFF means: 50%)
Bytes 7, 8, 9, 10 - ASCII HEX representation of int16_t value - the I Trip Grid Amplitude from 0 to 65535, 0% - 100% (e.g. FFFF means: 100%)
Bytes 11, 12 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 13 - 'Z' ASCII character (End of Frame)
Byte 14 - <CR> control character (Carriage Return)
Byte 15 - <LF> control character (Line Feed)
*/

// RX Command - Set I Trip Parameters - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetITripParams_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		ITrip_Inv[4];
	char		ITrip_Grid[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetITripParams_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetITripParams_BIN_s {
	uint16_t	ITrip_Inv;
	uint16_t	ITrip_Grid;
	uint8_t		Frame_Counter;
} RxCmdSetITripParams_BIN_t;

#define RX_CMD_SET_ITRIP_PARAMS_TYPE	DATA_4BYTES, DATA_4BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_ITRIP_PARAMS_SIZE	sizeof(RxCmdSetITripParams_ASCIIHEX_t)

/* RX Command - Set Recordings - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 03 means: SET_REC)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Recordings Mode
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set Recordings Type - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetRec_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Mode[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetRec_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetRec_BIN_s {
	uint8_t		Mode;
	uint8_t		Frame_Counter;
} RxCmdSetRec_BIN_t;

#define RX_CMD_SET_REC_TYPE				DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_REC_SIZE				sizeof(RxCmdSetRec_ASCIIHEX_t)

/* RX Command - Set System Parameters - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 03 means: SET_SYSTEM_PARAMS)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the System Mode
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set System Parameters - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetSystemParams_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		System_Mode[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetSystemParams_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetSystemParams_BIN_s {
	uint8_t		System_Mode;
	uint8_t		Frame_Counter;
} RxCmdSetSystemParams_BIN_t;

#define RX_CMD_SET_SYSTEM_PARAMS_TYPE	DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_SYSTEM_PARAMS_SIZE	sizeof(RxCmdSetSystemParams_ASCIIHEX_t)

/* RX Command - Set DPLL Parameters - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 07 means: SET_DPLL_PARAMS)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the Ud value from 0 to 65535, 0% - 100% (e.g. 0 means: 0%)
Bytes 7, 8, 9, 10 - ASCII HEX representation of uint16_t value - the Uq value from 0 to 65535, 0% - 100% (e.g. 7FFF means: 50%)
Bytes 11, 12, 13, 14 - ASCII HEX representation of uint16_t value - the Id value from 0 to 65535, 0% - 100% (e.g. BFFF means: 75%)
Bytes 15, 16, 17, 18 - ASCII HEX representation of uint16_t value - the Iq value from 0 to 65535, 0% - 100% (e.g. FFFF means: 100%)
Bytes 19, 20, 21, 22 - ASCII HEX representation of uint16_t value - the Omega value from 0 to 65535, 0% - 100% (e.g. FFFF means: 100%)
Bytes 23, 24 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 25 - 'Z' ASCII character (End of Frame)
Byte 26 - <CR> control character (Carriage Return)
Byte 27 - <LF> control character (Line Feed)
*/

// RX Command - Set DPLL Parameters - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetDpllParams_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Ud_Value[4];
	char		Uq_Value[4];
	char		Id_Value[4];
	char		Iq_Value[4];
	char		Omega_Value[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetDpllParams_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetDpllParams_BIN_s {
	uint16_t	Ud_Value;
	uint16_t	Uq_Value;
	uint16_t	Id_Value;
	uint16_t	Iq_Value;
	uint16_t	Omega_Value;
	uint8_t		Frame_Counter;
} RxCmdSetDpllParams_BIN_t;

#define RX_CMD_SET_DPLL_PARAMS_TYPE		DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_DPLL_PARAMS_SIZE		sizeof(RxCmdSetDpllParams_ASCIIHEX_t)

/* RX Command - Set System Reset - Frame Description
Byte  0 - 'S' ASCII character (Start of Frame Cmd)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 08 means: SET_SYSTEM_RESET)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Reset type
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 7 - 'Z' ASCII character (End of Frame)
Byte 8 - <CR> control character (Carriage Return)
Byte 9 - <LF> control character (Line Feed)
*/

// RX Command - Set System Reset - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) RxCmdSetSystemReset_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Cmd_Code[2];
	char		Reset_Type[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} RxCmdSetSystemReset_ASCIIHEX_t;

typedef struct __attribute__((packed)) RxCmdSetSystemReset_BIN_s {
	uint8_t		Reset_Type;
	uint8_t		Frame_Counter;
} RxCmdSetSystemReset_BIN_t;

#define RX_CMD_SET_SYSTEM_RESET_TYPE	DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define RX_CMD_SET_SYSTEM_RESET_SIZE	sizeof(RxCmdSetSystemReset_ASCIIHEX_t)

/////
/* TX Response - Get ACK - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Command Code (e.g. 02 means: SET_DDS_PARAMS)
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the ACK State (e.g. 00 means NACK, 01 means: ACK)
Bytes 7, 8 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 9 - 'Z' ASCII character (End of Frame)
Byte 10 - <CR> control character (Carriage Return)
Byte 11 - <LF> control character (Line Feed)
*/

// TX Response - Get ACK - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetAck_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		Cmd_Code[2];
	char		State[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetAck_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetAck_BIN_s {
	uint8_t		Cmd_Code;
	uint8_t		State;
} TxRspGetAck_BIN_t;

#define TX_RSP_GET_ACK_TYPE				DATA_2BYTES, DATA_2BYTES, DATA_NULL

/* TX Response - Get FW VER - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the HW Info (e.g. 0100 means Inresol's Board subversion 00)
Bytes 7, 8, 9, 10 - ASCII HEX representation of uint16_t value - the FW Version (e.g. 0100)
Bytes 11, 12, 13, 14 - ASCII HEX representation of uint16_t value - the FW Date - Year (e.g. 2017)
Bytes 15, 16 - ASCII HEX representation of uint8_t value - the FW Date - Month (e.g. 01 means: January)
Bytes 17, 18 - ASCII HEX representation of uint8_t value - the FW Date - Day of Month (e.g. 01)
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get FW VER - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetFwVer_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		HW_Info[4];
	char		FW_Version[4];
	char		FW_Date_Year[4];
	char		FW_Date_Month[2];
	char		FW_Date_Day[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetFwVer_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetFwVer_BIN_s {
	uint16_t	HW_Info;
	uint16_t	FW_Version;
	uint16_t	FW_Date_Year;
	uint8_t		FW_Date_Month;
	uint8_t		FW_Date_Day;
} TxRspGetFwVer_BIN_t;

#define TX_RSP_GET_FW_VER_TYPE			DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_2BYTES, DATA_2BYTES, DATA_NULL

/* TX Response - Get RESET - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the Reset Info
Bytes 7, 8 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 9 - 'Z' ASCII character (End of Frame)
Byte 10 - <CR> control character (Carriage Return)
Byte 11 - <LF> control character (Line Feed)
*/

// TX Response - Get RESET - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetReset_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		Reset_Info[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetReset_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetReset_BIN_s {
	uint16_t	Reset_Info;
} TxRspGetReset_BIN_t;

#define TX_RSP_GET_RESET_TYPE			DATA_4BYTES, DATA_NULL

/* TX Response - Get ADC U Unsigned - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 02 means: RSP_ADC_1)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the ADC Reading RAW
Bytes 7, 8, 9, 10 - ASCII HEX representation of uint16_t value - the ADC Reading Mean
Bytes 11, 12, 13, 14 - ASCII HEX representation of uint16_t value - the ADC Reading PkPk
Bytes 15, 16, 17, 18 - ASCII HEX representation of uint16_t value - the ADC Reading RMS
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get ADC U Unsigned - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetAdcUU_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		RAW[4];
	char		Mean[4];
	char		PkPk[4];
	char		RMS[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetAdcUU_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetAdcUU_BIN_s {
	uint16_t	RAW;
	uint16_t	Mean;
	uint16_t	PkPk;
	uint16_t	RMS;
} TxRspGetAdcUU_BIN_t;

#define TX_RSP_GET_ADC_UU_TYPE			DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_NULL

/* TX Response - Get ADC U Signed - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 02 means: RSP_ADC_1)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the ADC Reading RAW
Bytes 7, 8, 9, 10 - ASCII HEX representation of int16_t value - the ADC Reading Mean
Bytes 11, 12, 13, 14 - ASCII HEX representation of int16_t value - the ADC Reading PkPk
Bytes 15, 16, 17, 18 - ASCII HEX representation of int16_t value - the ADC Reading RMS
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get ADC U Signed - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetAdcUS_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		RAW[4];
	char		Mean[4];
	char		PkPk[4];
	char		RMS[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetAdcUS_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetAdcUS_BIN_s {
	uint16_t	RAW;
	int16_t		Mean;
	int16_t		PkPk;
	int16_t		RMS;
} TxRspGetAdcUS_BIN_t;

#define TX_RSP_GET_ADC_US_TYPE			DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_NULL

/* TX Response - Get ADC I - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 02 means: RSP_ADC_1)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the ADC Reading RAW
Bytes 7, 8, 9, 10 - ASCII HEX representation of uint16_t value - the ADC Reading Mean
Bytes 11, 12, 13, 14 - ASCII HEX representation of uint16_t value - the ADC Reading PkPk
Bytes 15, 16, 17, 18 - ASCII HEX representation of uint16_t value - the ADC Reading RMS
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get ADC I - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetAdcI_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		RAW[4];
	char		Mean[4];
	char		PkPk[4];
	char		RMS[4];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetAdcI_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetAdcI_BIN_s {
	uint16_t	RAW;
	uint16_t	Mean;
	uint16_t	PkPk;
	uint16_t	RMS;
} TxRspGetAdcI_BIN_t;

#define TX_RSP_GET_ADC_I_TYPE			DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_4BYTES, DATA_NULL

/* TX Response - Get ADC T - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 02 means: RSP_ADC_1)
Bytes 3, 4, 5, 6 - ASCII HEX representation of uint16_t value - the ADC Reading RAW
Bytes 7, 8, 9, 10 - ASCII HEX representation of int16_t value - the Temperature
Bytes 11, 12, 13, 14, 15, 16, 17, 18 - ASCII HEX representation of uint32_t value - the Resistance
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get ADC T - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetAdcT_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		RAW[4];
	char		Temperature[4];
	char		Resistance[8];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetAdcT_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetAdcT_BIN_s {
	uint16_t	RAW;
	int16_t		Temperature;
	uint32_t	Resistance;
} TxRspGetAdcT_BIN_t;

#define TX_RSP_GET_ADC_T_TYPE			DATA_4BYTES, DATA_4BYTES, DATA_8BYTES, DATA_NULL

/* TX Response - Get Status - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the Over Current Protection
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the Data Recording Status
Bytes 7, 8 - ASCII HEX representation of uint8_t value - the SM Recording Status
Bytes 9, 10 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 11 - 'Z' ASCII character (End of Frame)
Byte 12 - <CR> control character (Carriage Return)
Byte 13 - <LF> control character (Line Feed)
*/

// TX Response - Get Status - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetStatus_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		OCP[2];
	char		DataRec[2];
	char		SMRec[2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetStatus_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetStatus_BIN_s {
	uint8_t		OCP;
	uint8_t		DataRec;
	uint8_t		SMRec;
} TxRspGetStatus_BIN_t;

#define TX_RSP_GET_STATUS_TYPE			DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_NULL

/* TX Response - Get Recording Info - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4, 5, 6, 7, 8, 9, 10 - ASCII HEX representation of uint32_t value - the Recording Length
Bytes 11, 12 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 13 - 'Z' ASCII character (End of Frame)
Byte 14 - <CR> control character (Carriage Return)
Byte 15 - <LF> control character (Line Feed)
*/

// TX Response - Get Recording Info - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetRecInfo_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		Length[8];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetRecInfo_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetRecInfo_BIN_s {
	uint32_t	Buffer_Length;
	uint16_t	Packet_Length;
} TxRspGetRecInfo_BIN_t;

#define TX_RSP_GET_REC_INFO_TYPE		DATA_8BYTES, DATA_4BYTES, DATA_NULL

/* TX Response - Get Recording Data - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4, 5, 6, 7, 8, 9, 10 - ASCII HEX representation of uint32_t value - the Recording Addr
Bytes 11, 12, 13, 14, 15, 16, 17, 18 - ASCII HEX representation of uint32_t value - the Recording Data
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get Recording Data - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetRecData_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		Addr[8];
	char		Data[APP_DATAREC_PACKET_LENGTH][2];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetRecData_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetRecData_BIN_s {
	uint32_t	Addr;
	uint8_t		Data[APP_DATAREC_PACKET_LENGTH];
} TxRspGetRecData_BIN_t;

//#define TX_RSP_GET_REC_DATA_TYPE		DATA_8BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_2BYTES, DATA_NULL
#define TX_RSP_GET_REC_DATA_TYPE		DATA_8BYTES, REP_DIG(0,1,2,DATA_2BYTES), DATA_NULL

/* TX Response - Get SM Data - Frame Description
Byte  0 - 'R' ASCII character (Start of Frame Rsp)
Bytes 1, 2 - ASCII HEX representation of uint8_t value - the Response Code (e.g. 00 means: RSP_ACK)
Bytes 3, 4 - ASCII HEX representation of uint8_t value - the SM State
Bytes 5, 6 - ASCII HEX representation of uint8_t value - the SM Error
Bytes 7, 8, 9, 10 - ASCII HEX representation of uint16_t value - the TimeStamp
Bytes 11, 12, 13, 14, 15, 16, 17, 18 - ASCII HEX representation of uint32_t value - the TimeStamp
Bytes 19, 20 - ASCII HEX representation of uint8_t value - the Incremented Frame Counter
Byte 21 - 'Z' ASCII character (End of Frame)
Byte 22 - <CR> control character (Carriage Return)
Byte 23 - <LF> control character (Line Feed)
*/

// TX Response - Get Recording Data - ASCIIHEX & BIN Structures
typedef struct __attribute__((packed)) TxRspGetSMData_ASCIIHEX_s {
	char		Start_of_Frame;
	char		Rsp_Code[2];
	char		State[2];
	char		Error[2];
	char		TimeStamp_ms[4];
	char		TimeStamp_s[8];
	char		Frame_Counter[2];
	char		End_of_Frame;
} TxRspGetSMData_ASCIIHEX_t;

typedef struct __attribute__((packed)) TxRspGetSMData_BIN_s {
	uint8_t		State;
	uint8_t		Error;
	uint16_t	TimeStamp_ms;
	uint32_t	TimeStamp_s;
} TxRspGetSMData_BIN_t;

#define TX_RSP_GET_SM_DATA_TYPE		DATA_2BYTES, DATA_2BYTES, DATA_4BYTES, DATA_8BYTES, DATA_NULL
/////

// RX Command - Set Response - Types Table
static const uint8_t RxCmdSetResponseTypesTable[] = {RX_CMD_SET_RESPONSE_TYPE};
// RX Command - Set Echo On/Off - Types Table
static const uint8_t RxCmdSetEchoOnOffTypesTable[] = {RX_CMD_SET_ECHO_ON_OFF_TYPE};
// RX Command - Set DDS Parameters - Types Table
static const uint8_t RxCmdSetDdsParamsTypesTable[] = {RX_CMD_SET_DDS_PARAMS_TYPE};
// RX Command - Set Relays - Types Table
static const uint8_t RxCmdSetRelaysTypesTable[] = {RX_CMD_SET_RELAYS_TYPE};
// RX Command - Set I Trip Parameters - Types Table
static const uint8_t RxCmdSetITripParamsTypesTable[] = {RX_CMD_SET_ITRIP_PARAMS_TYPE};
// RX Command - Set Recordings - Types Table
static const uint8_t RxCmdSetRecTypesTable[] = {RX_CMD_SET_REC_TYPE};
// RX Command - Set System Parameters - Types Table
static const uint8_t RxCmdSetSystemParamsTypesTable[] = {RX_CMD_SET_SYSTEM_PARAMS_TYPE};
// RX Command - Set DPLL Parameters - Types Table
static const uint8_t RxCmdSetDpllParamsTypesTable[] = {RX_CMD_SET_DPLL_PARAMS_TYPE};
// RX Command - Set System Reset - Types Table
static const uint8_t RxCmdSetSystemResetTypesTable[] = {RX_CMD_SET_SYSTEM_RESET_TYPE};

/////
// TX Response - Get ACK - Types Table
static const uint8_t TxRspGetAckTypesTable[] = {TX_RSP_GET_ACK_TYPE};
// TX Response - Get FW VER - Types Table
static const uint8_t TxRspGetFwVerTypesTable[] = {TX_RSP_GET_FW_VER_TYPE};
// TX Response - Get RESET - Types Table
static const uint8_t TxRspGetResetTypesTable[] = {TX_RSP_GET_RESET_TYPE};
// TX Response - Get ADC U Unsigned - Types Table
static const uint8_t TxRspGetAdcUUTypesTable[] = {TX_RSP_GET_ADC_UU_TYPE};
// TX Response - Get ADC U Signed - Types Table
static const uint8_t TxRspGetAdcUSTypesTable[] = {TX_RSP_GET_ADC_US_TYPE};
// TX Response - Get ADC I - Types Table
static const uint8_t TxRspGetAdcITypesTable[] = {TX_RSP_GET_ADC_I_TYPE};
// TX Response - Get ADC T - Types Table
static const uint8_t TxRspGetAdcTTypesTable[] = {TX_RSP_GET_ADC_T_TYPE};
// TX Response - Get Status - Types Table
static const uint8_t TxRspGetStatusTypesTable[] = {TX_RSP_GET_STATUS_TYPE};
// TX Response - Get Recording Info - Types Table
static const uint8_t TxRspGetRecInfoTypesTable[] = {TX_RSP_GET_REC_INFO_TYPE};
// TX Response - Get Recording Data - Types Table
static const uint8_t TxRspGetRecDataTypesTable[] = {TX_RSP_GET_REC_DATA_TYPE};
// TX Response - Get SM Data - Types Table
static const uint8_t TxRspGetSMDataTypesTable[] = {TX_RSP_GET_SM_DATA_TYPE};

/////

// RX Command's Binary Buffer
static uint8_t RxCmdBinBuffer[APP_SETTINGS_DEBUG_RX_BIN_BUFFER_SIZE];
// TX Respond's ASCII Buffer
static uint8_t TxRspAsciiBuffer[APP_SETTINGS_DEBUG_TX_ASCIIHEX_BUFFER_SIZE];
// TX Respond's Binary Buffer
static uint8_t TxRspBinBuffer[APP_SETTINGS_DEBUG_TX_BIN_BUFFER_SIZE];
// Echo On/Off State
static uint8_t EchoState = DEBUG_TX_ECHO_ON;
// Response Type
static uint8_t ResponseType = DEBUG_TX_RSP_ACK;
// Tx Frame Counter
static uint8_t TxFrameCounter = 0;
// ACK Response
static uint8_t ACKRsp = DEBUG_RX_CMD_SET_RESPONSE;
// ACK State
static uint8_t ACKState = DEBUG_TX_ACK;

static void debug_rx_cmd_set_response(void *data)
{
	RxCmdSetResponse_BIN_t	*cmd_ptr = (RxCmdSetResponse_BIN_t*)data;

	ResponseType = cmd_ptr->Response_Type;					// Response Type
}

static void debug_rx_cmd_set_echo_on_off(void *data)
{
	RxCmdSetEchoOnOff_BIN_t	*cmd_ptr = (RxCmdSetEchoOnOff_BIN_t*)data;

	EchoState = cmd_ptr->Echo_State;						// Echo State
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_dds_params(void *data)
{
	RxCmdSetDdsParams_BIN_t	*cmd_ptr = (RxCmdSetDdsParams_BIN_t*)data;

//	BSP_UART_1_Send_Data_NoBlocking(data, strlen((char*)data));
	if(cmd_ptr->Freq != App_DDS_Waves_Freq)					// Frequency of waveforms
		App_DDS_Set_Freq(cmd_ptr->Freq);
	if(cmd_ptr->Phase2_Shift != App_DDS_Shift_Phase_Chn2)	// Phase shift tuning word for channel 2
		App_DDS_Set_Phase_Ch2(cmd_ptr->Phase2_Shift);
	if(cmd_ptr->Phase3_Shift != App_DDS_Shift_Phase_Chn3)	// Phase shift tuning word for channel 3
		App_DDS_Set_Phase_Ch3(cmd_ptr->Phase3_Shift);
	if(cmd_ptr->Phase1_Amplitude != App_DDS_Gain_Chn1)		// Magnitude for channel 1
		App_DDS_Set_Gain_Ch1(cmd_ptr->Phase1_Amplitude);
	if(cmd_ptr->Phase2_Amplitude != App_DDS_Gain_Chn2)		// Magnitude for channel 2
		App_DDS_Set_Gain_Ch2(cmd_ptr->Phase2_Amplitude);
	if(cmd_ptr->Phase3_Amplitude != App_DDS_Gain_Chn3)		// Magnitude for channel 3
		App_DDS_Set_Gain_Ch3(cmd_ptr->Phase3_Amplitude);
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_relays(void *data)
{
	RxCmdSetRelays_BIN_t	*cmd_ptr = (RxCmdSetRelays_BIN_t*)data;

	RelaysState = cmd_ptr->Relays_State;					// Relays State
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_itrip_params(void *data)
{
	RxCmdSetITripParams_BIN_t	*cmd_ptr = (RxCmdSetITripParams_BIN_t*)data;

	App_OCP_ITrip_Inv = cmd_ptr->ITrip_Inv;
	App_OCP_ITrip_Grid = cmd_ptr->ITrip_Grid;
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_rec(void *data)
{
	RxCmdSetRec_BIN_t	*cmd_ptr = (RxCmdSetRec_BIN_t*)data;

	App_DataRec_Set(cmd_ptr->Mode);
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_system_params(void *data)
{
	RxCmdSetSystemParams_BIN_t	*cmd_ptr = (RxCmdSetSystemParams_BIN_t*)data;

	App_SM_System_Mode = cmd_ptr->System_Mode;
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_dpll_params(void *data)
{
	RxCmdSetDpllParams_BIN_t	*cmd_ptr = (RxCmdSetDpllParams_BIN_t*)data;

	App_DPLL_Param_Vd_Set(cmd_ptr->Ud_Value);
	App_DPLL_Param_Vq_Set(cmd_ptr->Uq_Value);
	App_DPLL_Param_Id_Set(cmd_ptr->Id_Value);
	App_DPLL_Param_Iq_Set(cmd_ptr->Iq_Value);
	App_DPLL_Param_Omega_Set(cmd_ptr->Omega_Value);
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

static void debug_rx_cmd_set_system_reset(void *data)
{
	RxCmdSetSystemReset_BIN_t	*cmd_ptr = (RxCmdSetSystemReset_BIN_t*)data;
	uint8_t Reset_Type;

	Reset_Type = cmd_ptr->Reset_Type;
	/*
	if(Reset_Type != 0) {
		NVMemory.ADC.Do_Calibration = true;
		NVMemoryDoUpdate = true;
		App_NVMemory_Process(NULL);
	}
	BSP_System_SW_Reset();
	*/
	ACKState = DEBUG_TX_ACK;
	ResponseType = DEBUG_TX_RSP_ACK;
}

// RX Commands List
static const RxCmdList_t rx_cmd_list[] = {
	{DEBUG_RX_CMD_SET_RESPONSE, RX_CMD_SET_RESPONSE_SIZE, (uint8_t*)&RxCmdSetResponseTypesTable[0], debug_rx_cmd_set_response},
	{DEBUG_RX_CMD_SET_ECHO_ON_OFF, RX_CMD_SET_ECHO_ON_OFF_SIZE, (uint8_t*)&RxCmdSetEchoOnOffTypesTable[0], debug_rx_cmd_set_echo_on_off},
	{DEBUG_RX_CMD_SET_DDS_PARAMS, RX_CMD_SET_DDS_PARAMS_SIZE, (uint8_t*)&RxCmdSetDdsParamsTypesTable[0], debug_rx_cmd_set_dds_params},
	{DEBUG_RX_CMD_SET_RELAYS, RX_CMD_SET_RELAYS_SIZE, (uint8_t*)&RxCmdSetRelaysTypesTable[0], debug_rx_cmd_set_relays},
	{DEBUG_RX_CMD_SET_ITRIP_PARAMS, RX_CMD_SET_ITRIP_PARAMS_SIZE, (uint8_t*)&RxCmdSetITripParamsTypesTable[0], debug_rx_cmd_set_itrip_params},
	{DEBUG_RX_CMD_SET_REC, RX_CMD_SET_REC_SIZE, (uint8_t*)&RxCmdSetRecTypesTable[0], debug_rx_cmd_set_rec},
	{DEBUG_RX_CMD_SET_SYSTEM_PARAMS, RX_CMD_SET_SYSTEM_PARAMS_SIZE, (uint8_t*)&RxCmdSetSystemParamsTypesTable[0], debug_rx_cmd_set_system_params},
	{DEBUG_RX_CMD_SET_DPLL_PARAMS, RX_CMD_SET_DPLL_PARAMS_SIZE, (uint8_t*)&RxCmdSetDpllParamsTypesTable[0], debug_rx_cmd_set_dpll_params},
	{DEBUG_RX_CMD_SET_SYSTEM_RESET, RX_CMD_SET_SYSTEM_RESET_SIZE, (uint8_t*)&RxCmdSetSystemResetTypesTable[0], debug_rx_cmd_set_system_reset}
};
#define RX_CMD_MAX_ARGS			ARRAY_SIZE(rx_cmd_list)

/////
static void debug_tx_rsp_get_ack(void *data)
{
	TxRspGetAck_BIN_t	*rsp_ptr = (TxRspGetAck_BIN_t*)data;

	rsp_ptr->Cmd_Code = ACKRsp;
	rsp_ptr->State = ACKState;
}

static void debug_tx_rsp_get_fw_ver(void *data)
{
	TxRspGetFwVer_BIN_t	*rsp_ptr = (TxRspGetFwVer_BIN_t*)data;

	rsp_ptr->HW_Info = APP_SETTINGS_VERSION_HW_INFO;
	rsp_ptr->FW_Version = APP_SETTINGS_VERSION_FW_VERSION;
	rsp_ptr->FW_Date_Year = APP_SETTINGS_VERSION_FW_DATE_YEAR;
	rsp_ptr->FW_Date_Month = APP_SETTINGS_VERSION_FW_DATE_MONTH;
	rsp_ptr->FW_Date_Day = APP_SETTINGS_VERSION_FW_DATE_DAY;
}

static void debug_tx_rsp_get_reset(void *data)
{
	TxRspGetReset_BIN_t	*rsp_ptr = (TxRspGetReset_BIN_t*)data;

	rsp_ptr->Reset_Info = BSP_System_Reset_State;
}

static uint16_t convert_u_udc_adc_to_volt(uint16_t ADC_Value)
{
	uint32_t Result;

	Result = (uint32_t)ADC_Value * BSP_SETTINGS_ADC_U_DC_SCALING;
	return Result;
}

static int16_t convert_u_inv_adc_to_volt(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_U_INV_SCALING;
	return Result;
}

static int16_t convert_u_mid_adc_to_volt(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_U_MID_SCALING;
	return Result;
}

static int16_t convert_u_grid_adc_to_volt(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_U_GRID_SCALING;
	return Result;
}

static int16_t convert_i_inv_adc_to_ampere(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_I_INV_SCALING;
	return Result;
}

static int16_t convert_i_grid_adc_to_ampere(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_I_GRID_SCALING;
	return Result;
}

static int16_t convert_t_adc_to_celsius(int16_t ADC_Value)
{
	int32_t Result;

	Result = (int32_t)ADC_Value * BSP_SETTINGS_ADC_T_SCALING;
	return Result;
}

static void debug_tx_rsp_get_adc_p_u_dc(void *data)
{
	TxRspGetAdcUU_BIN_t	*rsp_ptr = (TxRspGetAdcUU_BIN_t*)data;

	rsp_ptr->RAW = ADC_P_U_DC_RAW;
	rsp_ptr->Mean = convert_u_udc_adc_to_volt(ADC_P_U_DC_Mean);
	rsp_ptr->PkPk = convert_u_udc_adc_to_volt(ADC_P_U_DC_PkPk);
	rsp_ptr->RMS = convert_u_udc_adc_to_volt(ADC_P_U_DC_RMS);
}

static void debug_tx_rsp_get_adc_n_u_dc(void *data)
{
	TxRspGetAdcUU_BIN_t	*rsp_ptr = (TxRspGetAdcUU_BIN_t*)data;

	rsp_ptr->RAW = ADC_N_U_DC_RAW;
	rsp_ptr->Mean = convert_u_udc_adc_to_volt(ADC_N_U_DC_Mean);
	rsp_ptr->PkPk = convert_u_udc_adc_to_volt(ADC_N_U_DC_PkPk);
	rsp_ptr->RMS = convert_u_udc_adc_to_volt(ADC_N_U_DC_RMS);
}

static void debug_tx_rsp_get_adc_l1_u_inv(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L1_U_Inv_RAW;
	rsp_ptr->Mean = convert_u_inv_adc_to_volt(ADC_L1_U_Inv_Mean);
	rsp_ptr->PkPk = convert_u_inv_adc_to_volt(ADC_L1_U_Inv_PkPk);
	rsp_ptr->RMS = convert_u_inv_adc_to_volt(ADC_L1_U_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l1_i_inv(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L1_I_Inv_RAW;
	rsp_ptr->Mean = convert_i_inv_adc_to_ampere(ADC_L1_I_Inv_Mean);
	rsp_ptr->PkPk = convert_i_inv_adc_to_ampere(ADC_L1_I_Inv_PkPk);
	rsp_ptr->RMS = convert_i_inv_adc_to_ampere(ADC_L1_I_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l2_u_inv(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L2_U_Inv_RAW;
	rsp_ptr->Mean = convert_u_inv_adc_to_volt(ADC_L2_U_Inv_Mean);
	rsp_ptr->PkPk = convert_u_inv_adc_to_volt(ADC_L2_U_Inv_PkPk);
	rsp_ptr->RMS = convert_u_inv_adc_to_volt(ADC_L2_U_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l2_i_inv(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L2_I_Inv_RAW;
	rsp_ptr->Mean = convert_i_inv_adc_to_ampere(ADC_L2_I_Inv_Mean);
	rsp_ptr->PkPk = convert_i_inv_adc_to_ampere(ADC_L2_I_Inv_PkPk);
	rsp_ptr->RMS = convert_i_inv_adc_to_ampere(ADC_L2_I_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l3_u_inv(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L3_U_Inv_RAW;
	rsp_ptr->Mean = convert_u_inv_adc_to_volt(ADC_L3_U_Inv_Mean);
	rsp_ptr->PkPk = convert_u_inv_adc_to_volt(ADC_L3_U_Inv_PkPk);
	rsp_ptr->RMS = convert_u_inv_adc_to_volt(ADC_L3_U_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l3_i_inv(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L3_I_Inv_RAW;
	rsp_ptr->Mean = convert_i_inv_adc_to_ampere(ADC_L3_I_Inv_Mean);
	rsp_ptr->PkPk = convert_i_inv_adc_to_ampere(ADC_L3_I_Inv_PkPk);
	rsp_ptr->RMS = convert_i_inv_adc_to_ampere(ADC_L3_I_Inv_RMS);
}

static void debug_tx_rsp_get_adc_l1_u_mid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L1_U_Mid_RAW;
	rsp_ptr->Mean = convert_u_mid_adc_to_volt(ADC_L1_U_Mid_Mean);
	rsp_ptr->PkPk = convert_u_mid_adc_to_volt(ADC_L1_U_Mid_PkPk);
	rsp_ptr->RMS = convert_u_mid_adc_to_volt(ADC_L1_U_Mid_RMS);
}

static void debug_tx_rsp_get_adc_l2_u_mid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L2_U_Mid_RAW;
	rsp_ptr->Mean = convert_u_mid_adc_to_volt(ADC_L2_U_Mid_Mean);
	rsp_ptr->PkPk = convert_u_mid_adc_to_volt(ADC_L2_U_Mid_PkPk);
	rsp_ptr->RMS = convert_u_mid_adc_to_volt(ADC_L2_U_Mid_RMS);
}

static void debug_tx_rsp_get_adc_l3_u_mid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L3_U_Mid_RAW;
	rsp_ptr->Mean = convert_u_mid_adc_to_volt(ADC_L3_U_Mid_Mean);
	rsp_ptr->PkPk = convert_u_mid_adc_to_volt(ADC_L3_U_Mid_PkPk);
	rsp_ptr->RMS = convert_u_mid_adc_to_volt(ADC_L3_U_Mid_RMS);
}

static void debug_tx_rsp_get_adc_l1_u_grid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L1_U_Grid_RAW;
	rsp_ptr->Mean = convert_u_grid_adc_to_volt(ADC_L1_U_Grid_Mean);
	rsp_ptr->PkPk = convert_u_grid_adc_to_volt(ADC_L1_U_Grid_PkPk);
	rsp_ptr->RMS = convert_u_grid_adc_to_volt(ADC_L1_U_Grid_RMS);
}

static void debug_tx_rsp_get_adc_l1_i_grid(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L1_I_Grid_RAW;
	rsp_ptr->Mean = convert_i_grid_adc_to_ampere(ADC_L1_I_Grid_Mean);
	rsp_ptr->PkPk = convert_i_grid_adc_to_ampere(ADC_L1_I_Grid_PkPk);
	rsp_ptr->RMS = convert_i_grid_adc_to_ampere(ADC_L1_I_Grid_RMS);
}

static void debug_tx_rsp_get_adc_l2_u_grid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L2_U_Grid_RAW;
	rsp_ptr->Mean = convert_u_grid_adc_to_volt(ADC_L2_U_Grid_Mean);
	rsp_ptr->PkPk = convert_u_grid_adc_to_volt(ADC_L2_U_Grid_PkPk);
	rsp_ptr->RMS = convert_u_grid_adc_to_volt(ADC_L2_U_Grid_RMS);
}

static void debug_tx_rsp_get_adc_l2_i_grid(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L2_I_Grid_RAW;
	rsp_ptr->Mean = convert_i_grid_adc_to_ampere(ADC_L2_I_Grid_Mean);
	rsp_ptr->PkPk = convert_i_grid_adc_to_ampere(ADC_L2_I_Grid_PkPk);
	rsp_ptr->RMS = convert_i_grid_adc_to_ampere(ADC_L2_I_Grid_RMS);
}

static void debug_tx_rsp_get_adc_l3_u_grid(void *data)
{
	TxRspGetAdcUS_BIN_t	*rsp_ptr = (TxRspGetAdcUS_BIN_t*)data;

	rsp_ptr->RAW = ADC_L3_U_Grid_RAW;
	rsp_ptr->Mean = convert_u_grid_adc_to_volt(ADC_L3_U_Grid_Mean);
	rsp_ptr->PkPk = convert_u_grid_adc_to_volt(ADC_L3_U_Grid_PkPk);
	rsp_ptr->RMS = convert_u_grid_adc_to_volt(ADC_L3_U_Grid_RMS);
}

static void debug_tx_rsp_get_adc_l3_i_grid(void *data)
{
	TxRspGetAdcI_BIN_t	*rsp_ptr = (TxRspGetAdcI_BIN_t*)data;

	rsp_ptr->RAW = ADC_L3_I_Grid_RAW;
	rsp_ptr->Mean = convert_i_grid_adc_to_ampere(ADC_L3_I_Grid_Mean);
	rsp_ptr->PkPk = convert_i_grid_adc_to_ampere(ADC_L3_I_Grid_PkPk);
	rsp_ptr->RMS = convert_i_grid_adc_to_ampere(ADC_L3_I_Grid_RMS);
}

static void debug_tx_rsp_get_adc_t1(void *data)
{
	TxRspGetAdcT_BIN_t	*rsp_ptr = (TxRspGetAdcT_BIN_t*)data;
	int16_t Temp;

	if(TempSens_State[APP_TEMP_SENS_CHANNEL_1] & APP_TEMP_SENS_FAILURE_OPEN)
		Temp = INT16_MIN;
	else if (TempSens_State[APP_TEMP_SENS_CHANNEL_1] & APP_TEMP_SENS_FAILURE_SHORT)
		Temp = INT16_MAX;
	else
		Temp = convert_t_adc_to_celsius(TempSens_T_Ch1);
	rsp_ptr->RAW = ADC_T1_RAW;
	rsp_ptr->Temperature = Temp;
	rsp_ptr->Resistance = TempSens_R_Ch1;
}

static void debug_tx_rsp_get_adc_t2(void *data)
{
	TxRspGetAdcT_BIN_t	*rsp_ptr = (TxRspGetAdcT_BIN_t*)data;
	int16_t Temp;

	if(TempSens_State[APP_TEMP_SENS_CHANNEL_2] & APP_TEMP_SENS_FAILURE_OPEN)
		Temp = INT16_MIN;
	else if (TempSens_State[APP_TEMP_SENS_CHANNEL_2] & APP_TEMP_SENS_FAILURE_SHORT)
		Temp = INT16_MAX;
	else
		Temp = convert_t_adc_to_celsius(TempSens_T_Ch2);

	rsp_ptr->RAW = ADC_T2_RAW;
	rsp_ptr->Temperature = Temp;
	rsp_ptr->Resistance = TempSens_R_Ch2;
}

static void debug_tx_rsp_get_adc_t3(void *data)
{
	TxRspGetAdcT_BIN_t	*rsp_ptr = (TxRspGetAdcT_BIN_t*)data;
	int16_t Temp;

	if(TempSens_State[APP_TEMP_SENS_CHANNEL_3] & APP_TEMP_SENS_FAILURE_OPEN)
		Temp = INT16_MIN;
	else if (TempSens_State[APP_TEMP_SENS_CHANNEL_3] & APP_TEMP_SENS_FAILURE_SHORT)
		Temp = INT16_MAX;
	else
		Temp = convert_t_adc_to_celsius(TempSens_T_Ch3);

	rsp_ptr->RAW = ADC_T3_RAW;
	rsp_ptr->Temperature = Temp;
	rsp_ptr->Resistance = TempSens_R_Ch3;
}

static void debug_tx_rsp_get_status(void *data)
{
	TxRspGetStatus_BIN_t	*rsp_ptr = (TxRspGetStatus_BIN_t*)data;

	rsp_ptr->OCP = App_OCP_OC_Status;
	rsp_ptr->DataRec = DataRecState;
	rsp_ptr->SMRec = SMRecState;
}

static void debug_tx_rsp_get_rec_info(void *data)
{
	TxRspGetRecInfo_BIN_t	*rsp_ptr = (TxRspGetRecInfo_BIN_t*)data;

	rsp_ptr->Buffer_Length = App_DataRec_Get_Length();
	rsp_ptr->Packet_Length = APP_DATAREC_PACKET_LENGTH;
}

static void debug_tx_rsp_get_rec_data(void *data)
{
	TxRspGetRecData_BIN_t	*rsp_ptr = (TxRspGetRecData_BIN_t*)data;

	App_DataRec_Load_Buffer((void*)&(rsp_ptr->Data[0]), APP_DATAREC_PACKET_LENGTH);
	rsp_ptr->Addr = DataRecAddr;
}

static void debug_tx_rsp_get_sm_data(void *data)
{
	TxRspGetSMData_BIN_t	*rsp_ptr = (TxRspGetSMData_BIN_t*)data;

	App_SM_Status_Get(&(rsp_ptr->State), &(rsp_ptr->Error), &(rsp_ptr->TimeStamp_ms), &(rsp_ptr->TimeStamp_s));
}

// TX Responses List
static const TxRspList_t tx_rsp_list[] = {
	{DEBUG_TX_RSP_ACK,				(uint8_t*)&TxRspGetAckTypesTable[0],		debug_tx_rsp_get_ack},
	{DEBUG_TX_RSP_FW_VER,			(uint8_t*)&TxRspGetFwVerTypesTable[0],		debug_tx_rsp_get_fw_ver},
	{DEBUG_TX_RSP_RESET,			(uint8_t*)&TxRspGetResetTypesTable[0],		debug_tx_rsp_get_reset},
	{DEBUG_TX_RSP_ADC_P_U_DC,		(uint8_t*)&TxRspGetAdcUUTypesTable[0],		debug_tx_rsp_get_adc_p_u_dc},
	{DEBUG_TX_RSP_ADC_N_U_DC,		(uint8_t*)&TxRspGetAdcUUTypesTable[0],		debug_tx_rsp_get_adc_n_u_dc},
	{DEBUG_TX_RSP_ADC_L1_U_INV,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l1_u_inv},
	{DEBUG_TX_RSP_ADC_L1_I_INV,		(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l1_i_inv},
	{DEBUG_TX_RSP_ADC_L2_U_INV,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l2_u_inv},
	{DEBUG_TX_RSP_ADC_L2_I_INV,		(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l2_i_inv},
	{DEBUG_TX_RSP_ADC_L3_U_INV,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l3_u_inv},
	{DEBUG_TX_RSP_ADC_L3_I_INV,		(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l3_i_inv},
	{DEBUG_TX_RSP_ADC_L1_U_MID,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l1_u_mid},
	{DEBUG_TX_RSP_ADC_L2_U_MID,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l2_u_mid},
	{DEBUG_TX_RSP_ADC_L3_U_MID,		(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l3_u_mid},
	{DEBUG_TX_RSP_ADC_L1_U_GRID,	(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l1_u_grid},
	{DEBUG_TX_RSP_ADC_L1_I_GRID,	(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l1_i_grid},
	{DEBUG_TX_RSP_ADC_L2_U_GRID,	(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l2_u_grid},
	{DEBUG_TX_RSP_ADC_L2_I_GRID,	(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l2_i_grid},
	{DEBUG_TX_RSP_ADC_L3_U_GRID,	(uint8_t*)&TxRspGetAdcUSTypesTable[0],		debug_tx_rsp_get_adc_l3_u_grid},
	{DEBUG_TX_RSP_ADC_L3_I_GRID,	(uint8_t*)&TxRspGetAdcITypesTable[0],		debug_tx_rsp_get_adc_l3_i_grid},
	{DEBUG_TX_RSP_ADC_T1,			(uint8_t*)&TxRspGetAdcTTypesTable[0],		debug_tx_rsp_get_adc_t1},
	{DEBUG_TX_RSP_ADC_T2,			(uint8_t*)&TxRspGetAdcTTypesTable[0],		debug_tx_rsp_get_adc_t2},
	{DEBUG_TX_RSP_ADC_T3,			(uint8_t*)&TxRspGetAdcTTypesTable[0],		debug_tx_rsp_get_adc_t3},
	{DEBUG_TX_RSP_STATUS,			(uint8_t*)&TxRspGetStatusTypesTable[0],		debug_tx_rsp_get_status},
	{DEBUG_TX_RSP_REC_INFO,			(uint8_t*)&TxRspGetRecInfoTypesTable[0],	debug_tx_rsp_get_rec_info},
	{DEBUG_TX_RSP_REC_DATA,			(uint8_t*)&TxRspGetRecDataTypesTable[0],	debug_tx_rsp_get_rec_data},
	{DEBUG_TX_RSP_SM_DATA,			(uint8_t*)&TxRspGetSMDataTypesTable[0],		debug_tx_rsp_get_sm_data}
};
#define TX_RSP_MAX_ARGS			ARRAY_SIZE(tx_rsp_list)
/////

int io_puts(const char * str)
{
	if (BSP_UART_1_Send_Data_NoBlocking((const void*)str, strlen(str)) != 1)
		return 1;
	return 0;
}

int io_putchar(char c)
{
	if (BSP_UART_1_Send_Data_NoBlocking((const void*)&c, 1) != 1)
		return 1;
	return 0;
}

int io_getc(char *c)
{
	char rcvd_char;
	int bytes;

	bytes = BSP_UART_1_Receive_Data(&rcvd_char, 1);
	if (bytes <= 0)
		return 1;
	if(EchoState != DEBUG_TX_ECHO_OFF) {
#if 0
		if (rcvd_char == '\r') {
			io_putchar('\n');
		// Echo char.
		} else if (rcvd_char == '\b') {
#else
		if (rcvd_char == '\b') {
#endif
			io_putchar(rcvd_char);
			io_putchar(' ');
			io_putchar(rcvd_char);
		} else {
			io_putchar(rcvd_char);
		}
	}
	*c = rcvd_char;
	return 0;
}

char* console_gets(void)
{
	static char buff[APP_SETTINGS_DEBUG_RX_ASCIIHEX_BUFFER_SIZE];
	static int pos = 0;
	char c;

	for (;;) {
		if (io_getc(&c))
			return NULL;
#if 0
		if (c == '\r' || c == '\n') {
#else
		if (c == '\r') {		// Carriage Return
			return NULL;
		} else if (c == '\n') {	// Line Feed
#endif
			buff[pos] = '\0';
			pos = 0;
			return buff;
		}
		if (c == 'S') {			// Start sequence
			pos = 0;
			buff[pos] = c;
			if (pos < (sizeof(buff) - 1))
				pos++;
		} else
		if (c == '\b') {		// Backspace
			pos--;
			if (pos < 0)
				pos = 0;
			buff[pos] = 0;
		} else {
			buff[pos] = c;
			if (pos < (sizeof(buff) - 1))
				pos++;
		}
	}
	return NULL;
}

void debug_rx_cmd_conv_data(uint8_t *types_ptr, char *asciihex_ptr, uint8_t *bin_ptr)
{
	uint8_t	type;

	do {
		type = *types_ptr++;
		switch(type) {
			case DATA_2BYTES:
				asciihex_2_to_uint8_inc2ptrs(&asciihex_ptr, &bin_ptr);
				break;
			case DATA_4BYTES:
				asciihex_4_to_uint16_inc2ptrs(&asciihex_ptr, &bin_ptr);
				break;
			case DATA_8BYTES:
				asciihex_8_to_uint32_inc2ptrs(&asciihex_ptr, &bin_ptr);
				break;
		}
	} while(type != DATA_NULL);
}

void debug_tx_rsp_conv_data(uint8_t *types_ptr, uint8_t *bin_ptr, char **asciihex_ptr)
{
	uint8_t	type;

	do {
		type = *types_ptr++;
		switch(type) {
			case DATA_2BYTES:
				uint8_to_asciihex_2_inc2ptrs(&bin_ptr, asciihex_ptr);
				break;
			case DATA_4BYTES:
				uint16_to_asciihex_4_inc2ptrs(&bin_ptr, asciihex_ptr);
				break;
			case DATA_8BYTES:
				uint32_to_asciihex_8_inc2ptrs(&bin_ptr, asciihex_ptr);
				break;
		}
	} while(type != DATA_NULL);
}

int console_schedule_cmd(char *cmd)
{
	int i;
	char start_seq, end_seq;
	uint8_t code;

	if(cmd != NULL) {
		start_seq = *cmd++;
		if((start_seq != 'S') && (start_seq != 's'))
			return 0;
		code = asciihex_2_to_uint8_incptr(&cmd);
		for (i = 0; i < RX_CMD_MAX_ARGS; i++) {
			if (rx_cmd_list[i].cmd_code == code) {
				ACKRsp = code;
				end_seq = *(cmd + rx_cmd_list[i].cmd_length - 4);	// Skip Start_of_Frame and Cmd_Code
				if((end_seq != 'Z') && (end_seq != 'z'))
					return 0;
				debug_rx_cmd_conv_data(rx_cmd_list[i].param_types, cmd, &RxCmdBinBuffer[0]);
				rx_cmd_list[i].cmd_cb(&RxCmdBinBuffer[0]);
				return 1;
			}
		}
 	}
	return 0;
}

int console_prepare_rsp(unsigned char rsp)
{
	int i;
	char *p_str_out;

	p_str_out = (char*)&TxRspAsciiBuffer[0];
	for (i = 0; i < TX_RSP_MAX_ARGS; i++) {
		if (tx_rsp_list[i].rsp_code == rsp) {
//			end_seq = *(cmd + rx_cmd_list[i].cmd_length);
//			if((end_seq != 'E') && (end_seq != 'e'))
//				continue;
			tx_rsp_list[i].rsp_cb(&TxRspBinBuffer[0]);
			*p_str_out++ = 'R';
			uint8_to_asciihex_2_incptr(rsp, &p_str_out);
			debug_tx_rsp_conv_data(tx_rsp_list[i].param_types, &TxRspBinBuffer[0], &p_str_out);
			uint8_to_asciihex_2_incptr(TxFrameCounter, &p_str_out);
			*p_str_out++ = 'Z';
			*p_str_out++ = '\r';
			*p_str_out++ = '\n';
			*p_str_out = '\0';
			return 1;
		}
	}
	return 0;
}

void App_Debug_Init(void *Parameters)
{
	(void)Parameters;
	BSP_UART_1_Config_Pins();
//	BSP_UART_1_DeInit();
//	BSP_UART_1_Set_Int(APP_SETTINGS_UART_1_INT);
//	BSP_UART_1_Init(APP_SETTINGS_UART_1_MODE, APP_SETTINGS_UART_1_STA, APP_SETTINGS_UART_1_BAUDRATE);
}

void App_Debug_Process(void *Parameters)
{
	char *buf;

	(void)Parameters;
	buf = console_gets();
	if(console_schedule_cmd(buf))
		if(console_prepare_rsp(ResponseType))
			if(io_puts((char*)&TxRspAsciiBuffer[0]))
				TxFrameCounter++;
}
