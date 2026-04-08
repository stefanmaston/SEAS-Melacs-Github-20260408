/*
 *  File name: App_NVMemory.c
 *
 *  Description: High level function implementations for Non Volatile Memory
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

static const NVMemoryMainParams_t Default_NVMemory = {
	.ADC.L1_I_Inv_Error = 0,
	.ADC.L2_I_Inv_Error = 0,
	.ADC.L3_I_Inv_Error = 0,
	.ADC.L1_I_Grid_Error = 0,
	.ADC.L2_I_Grid_Error = 0,
	.ADC.L3_I_Grid_Error = 0,
	.ADC.L1_U_Inv_Error = 0,
	.ADC.L2_U_Inv_Error = 0,
	.ADC.L3_U_Inv_Error = 0,
	.ADC.L1_U_Mid_Error = 0,
	.ADC.L2_U_Mid_Error = 0,
	.ADC.L3_U_Mid_Error = 0,
	.ADC.L1_U_Grid_Error = 0,
	.ADC.L2_U_Grid_Error = 0,
	.ADC.L3_U_Grid_Error = 0,
	.ADC.Do_Calibration = false,
	.CRC = 0xDEADBEEF
};

volatile bool NVMemoryDoUpdate = false;
NVMemoryMainParams_t NVMemory;

static uint32_t App_NVMemory_CRC_Make(void *start_addr, uint16_t length)
{
	uint8_t *start_ptr;
	uint32_t crc;

	start_ptr = start_addr;
	CRC32_InitChecksum(&crc);
	CRC32_UpdateChecksum(&crc, start_ptr, length);
	CRC32_FinishChecksum(&crc);
	return crc;
}

static bool App_NVMemory_CRC_Ok(void *start_addr, uint16_t length, uint32_t crc)
{
	uint32_t local_crc;

	local_crc = App_NVMemory_CRC_Make(start_addr, length);
	if (local_crc != crc)
		return false;
	else
		return true;
}

static void App_NVMemory_Create_Default(void)
{
	// Copy Default Configuration
	memcpy((void*)&NVMemory, (void*)&Default_NVMemory, sizeof(NVMemory) - 4);
}

static bool App_NVMemory_Read(void)
{
	uint16_t DEEaddr, DEEdata;
	uint8_t *DEEptr;
	bool	DEEerror = false;
	
	dataEEFlags.val = 0;
	DEEptr = (uint8_t*)&NVMemory;
	for(DEEaddr = 0; DEEaddr < sizeof(NVMemory); DEEaddr++) {
		DEEdata = DataEERead(DEEaddr);
		if(dataEEFlags.IllegalAddress)
			DEEerror = true;
		if(dataEEFlags.pageCorrupt)
			DEEerror = true;
		if(dataEEFlags.addrNotFound)
			DEEerror = true;
		if(DEEerror == true) {
			break;
		} else {
			*DEEptr = (uint8_t)DEEdata;
			DEEptr++;
		}
	}
	return DEEerror;
}

static bool App_NVMemory_Check(void)
{
	// Check CRC
	if(App_NVMemory_CRC_Ok((void*)&NVMemory, sizeof(NVMemory) - 4, NVMemory.CRC))
		return false;	// CRC OK
	else
		return true;	// CRC Error
}

static bool App_NVMemory_Write(void)
{
	uint16_t DEEaddr;
	uint8_t *DEEptr;
	bool	DEEerror = false;
	
	// Make CRC
	NVMemory.CRC = App_NVMemory_CRC_Make((void*)&NVMemory, sizeof(NVMemory) - 4);
	dataEEFlags.val = 0;
	DEEptr = (uint8_t*)&NVMemory;
	for(DEEaddr = 0; DEEaddr < sizeof(NVMemory); DEEaddr++) {
		DataEEWrite(*DEEptr, DEEaddr);
		if(dataEEFlags.IllegalAddress)
			DEEerror = true;
		if(dataEEFlags.packBeforeInit)
			DEEerror = true;
		if(dataEEFlags.packSkipped)
			DEEerror = true;
		if(dataEEFlags.writeError)
			DEEerror = true;
		if(DEEerror == true) {
			break;
		} else {
			DEEptr++;
		}
	}
	return DEEerror;
}

void App_NVMemory_Init(void *Parameters)
{
	(void)Parameters;
	DataEEInit();
	dataEEFlags.val = 0;
	if(App_NVMemory_Read() == true) {		// Addr or Page Error
		App_NVMemory_Create_Default();
		App_NVMemory_Write();
	} else {
		if(App_NVMemory_Check() == true) {	// CRC Error
			App_NVMemory_Create_Default();
			App_NVMemory_Write();
		}
	}
	if(NVMemory.ADC.Do_Calibration == true) {
		NVMemory.ADC.Do_Calibration = false;
		ADC_Calib = true;
		App_NVMemory_Write();
	}
}

void App_NVMemory_Process(void *Parameters)
{
	(void)Parameters;
	if(NVMemoryDoUpdate == true) {
		App_NVMemory_Write();
		NVMemoryDoUpdate = false;
		if((ADC_Calib == true) && (ADC_Ready == true))
			BSP_System_SW_Reset();
	}
}
