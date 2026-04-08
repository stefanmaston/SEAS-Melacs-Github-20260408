/*
 *  File name: App_NVMemory.h
 *
 *  Description: High level function declarations for Non Volatile Memory processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_NVMEMORY_H
#define APP_NVMEMORY_H

typedef struct __attribute__((packed)) NVMemoryAdcParams_s
{
	int16_t		L1_I_Inv_Error;
	int16_t		L2_I_Inv_Error;
	int16_t		L3_I_Inv_Error;
	int16_t		L1_I_Grid_Error;
	int16_t		L2_I_Grid_Error;
	int16_t		L3_I_Grid_Error;
	int16_t		L1_U_Inv_Error;
	int16_t		L2_U_Inv_Error;
	int16_t		L3_U_Inv_Error;
	int16_t		L1_U_Mid_Error;
	int16_t		L2_U_Mid_Error;
	int16_t		L3_U_Mid_Error;
	int16_t		L1_U_Grid_Error;
	int16_t		L2_U_Grid_Error;
	int16_t		L3_U_Grid_Error;
	bool		Do_Calibration;
} NVMemoryAdcParams_t;

typedef struct __attribute__((packed)) NVMemoryMainParams_s
{
	NVMemoryAdcParams_t		ADC;
	uint32_t				CRC;
} NVMemoryMainParams_t;

extern NVMemoryMainParams_t NVMemory;
extern volatile bool NVMemoryDoUpdate;

void App_NVMemory_Init(void *Parameters);
void App_NVMemory_Process(void *Parameters);

#endif // APP_NVMemory_H
