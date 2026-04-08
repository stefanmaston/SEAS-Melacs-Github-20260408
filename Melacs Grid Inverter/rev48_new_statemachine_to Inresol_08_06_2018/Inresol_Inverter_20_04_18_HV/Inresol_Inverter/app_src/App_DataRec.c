/*
 *  File name: App_DataRec.c
 *
 *  Description: High level function implementations for Data Recording
 *
 *  Author: Future Electronics
 *
 */

#include "string.h"
#include "global_includes.h"

#ifdef APP_DATAREC_ENABLED
static volatile uint8_t	DataRecBuffer[APP_DATAREC_BUFFER_LENGTH];
#endif	// APP_DATAREC_ENABLED

volatile uint8_t		DataRecState = 0;
#ifdef APP_DATAREC_ENABLED
const	 uint32_t		DataRecLength = sizeof(DataRecBuffer);
#else	// APP_DATAREC_ENABLED
const	 uint32_t		DataRecLength = 0;
#endif	// APP_DATAREC_ENABLED
volatile uint32_t		DataRecAddr = 0;
volatile uint8_t		DataRecCfg1 = 0;

#ifdef APP_DATAREC_ENABLED
static volatile uint8_t		*DataRecStorePtr = &DataRecBuffer[0];
static volatile uint8_t		*DataRecLoadPtr = &DataRecBuffer[0];
/*
static const	uint8_t		*DataRecLimit8Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH];
static const	uint8_t		*DataRecLimit16Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH - 1];
static const	uint8_t		*DataRecLimit32Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH - 3];
*/
static const	uint8_t		*DataRecLimit8Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH - 1];
static const	uint8_t		*DataRecLimit16Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH - 2];
static const	uint8_t		*DataRecLimit32Ptr = (uint8_t*)&DataRecBuffer[APP_DATAREC_BUFFER_LENGTH - 4];
#endif	// APP_DATAREC_ENABLED

void App_DataRec_Init(void *Parameters)
{
	(void)Parameters;
#ifdef APP_DATAREC_ENABLED
	DataRecStorePtr = &DataRecBuffer[0];
	DataRecLoadPtr = &DataRecBuffer[0];
	DataRecState = 0;
#endif	// APP_DATAREC_ENABLED
}

void App_DataRec_Process(void *Parameters)
{
	(void)Parameters;
}

void App_DataRec_Set(uint8_t Parameters)
{
	if(Parameters & (1 << REC_CONTROL_REINIT)) {			// Reload Everything
		App_DataRec_Init(NULL);
		DPLL_Trigger = false;
	}
	if(Parameters & (1 << REC_CONTROL_REREAD)) {			// Set Load Pointer
		DataRecLoadPtr = &DataRecBuffer[0];
		DataRecState |= (1 << REC_DATA_REREAD);
	}
}

inline void App_DataRec_Store_8bit(uint8_t Data)
{
#ifdef APP_DATAREC_ENABLED
	if(DataRecStorePtr > DataRecLimit8Ptr) {
		DataRecState |= (1 << REC_DATA_READY);
		return;
	}
	*((uint8_t*)DataRecStorePtr) = Data;
	DataRecStorePtr += 1;
#endif	// APP_DATAREC_ENABLED
}

//uint16_t Test_Cnt = 0;

inline void App_DataRec_Store_16bit(uint16_t Data)
{
#ifdef APP_DATAREC_ENABLED
	if(DataRecStorePtr > DataRecLimit16Ptr) {
		DataRecState |= (1 << REC_DATA_READY);
		return;
	}
#if 1
	*((uint16_t*)DataRecStorePtr) = Data;
#else
	*((uint16_t*)DataRecStorePtr) = Test_Cnt;
	Test_Cnt++;
#endif
	DataRecStorePtr += 2;
#endif	// APP_DATAREC_ENABLED
}

inline void App_DataRec_Store_32bit(uint32_t Data)
{
#ifdef APP_DATAREC_ENABLED
	if(DataRecStorePtr > DataRecLimit32Ptr) {
		DataRecState |= (1 << REC_DATA_READY);
		return;
	}
	*((uint32_t*)DataRecStorePtr) = Data;
	DataRecStorePtr += 4;
#endif	// APP_DATAREC_ENABLED
}

uint32_t App_DataRec_Get_Length(void)
{
#ifdef APP_DATAREC_ENABLED
	DataRecLoadPtr = &DataRecBuffer[0];
#endif	// APP_DATAREC_ENABLED
	DataRecState &= ~(1 << REC_DATA_REREAD);
	DataRecAddr = 0;
	return DataRecLength;
}

// For Debug Interface
bool App_DataRec_Load_Buffer(void *Data, uint16_t Size)
{
	bool Result = true;

#ifdef APP_DATAREC_ENABLED
	memcpy((void*)Data, (void*)DataRecLoadPtr, Size);
	DataRecAddr = DataRecLoadPtr - &DataRecBuffer[0];
	DataRecLoadPtr += Size;
#endif	// APP_DATAREC_ENABLED
	return Result;
}

// For Modbus Interface
bool App_DataRec_Load_Word(void *Data)
{
	bool Result = true;

#ifdef APP_DATAREC_ENABLED
	memcpy((void*)Data, (void*)DataRecLoadPtr, 2);
	DataRecLoadPtr += 2;
	DataRecAddr += 2;
#endif	// APP_DATAREC_ENABLED
	return Result;
}
