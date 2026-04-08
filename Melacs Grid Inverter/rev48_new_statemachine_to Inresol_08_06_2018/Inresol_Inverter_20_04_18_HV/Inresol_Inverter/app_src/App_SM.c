/*
 *  File name: App_SM.c
 *
 *  Description: High level function implementations for Main State Machine
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"
#include "ring_buffer.h"

bool	Sys_Reloaded = true;
bool	Sys_Reset = false;
bool	Sys_Calib = false;
bool	Sys_Shutdown = false;
const uint16_t	Sys_HW_Info = APP_SETTINGS_VERSION_HW_INFO;
const uint16_t	Sys_FW_Version = APP_SETTINGS_VERSION_FW_VERSION;
const uint16_t	Sys_FW_Date_Year = APP_SETTINGS_VERSION_FW_DATE_YEAR;
const uint16_t	Sys_FW_Date_Month_and_Day = ((APP_SETTINGS_VERSION_FW_DATE_MONTH << 8) | APP_SETTINGS_VERSION_FW_DATE_DAY);

volatile uint8_t	App_SM_System_Mode = APP_SM_SYSTEM_MODE_IDLE;
volatile uint8_t	SMRecState = 0;

#if defined(APP_SM_RB_SIZE)
//
typedef struct __attribute__((packed)) SM_Item_s {
	uint8_t		State;
	uint8_t		Error;
	uint16_t	TimeStamp_ms;
	uint32_t	TimeStamp_s;
} SM_Item_t;
#define SM_ITEM_SIZE	(sizeof(SM_Item_t))
// SM ring buffer structure
static RINGBUFF_T SM_Ring;
// SM data buffer
static SM_Item_t SM_Buff[APP_SM_RB_SIZE];
#else
#error Please define APP_SM_RB_SIZE !!!
#endif

void App_SM_Status_Update(void)
{
#if (APP_SM_RB_SIZE != 0)
	SMRecState = RingBuffer_GetCount(&SM_Ring);
#else
	SMRecState = 0;
#endif
}


void App_SM_Status_Store(void)
{
	static SM_Main_t sm_state_old = (SM_Main_t)0xFF;
	static System_Error_t system_ERROR_old = (System_Error_t)0xFF;
	
	if((sm_state != sm_state_old) || (system_ERROR != system_ERROR_old)) {
#if (APP_SM_RB_SIZE != 0)
		SM_Item_t Item;
		Item.State = sm_state;
		Item.Error = system_ERROR;
		Item.TimeStamp_ms = App_RTC_Counter_ms;
		Item.TimeStamp_s = App_RTC_Counter_s;
		RingBuffer_Insert(&SM_Ring, &Item);
#endif
		sm_state_old = sm_state;
		system_ERROR_old = system_ERROR;
		App_SM_Status_Update();
	}
}

void App_SM_Status_Get(uint8_t *State, uint8_t *Error, uint16_t *TimeStamp_ms, uint32_t *TimeStamp_s)
{
#if (APP_SM_RB_SIZE != 0)
	SM_Item_t Item;

	if(!(RingBuffer_IsEmpty(&SM_Ring)) && RingBuffer_Pop(&SM_Ring, &Item)) {
		*State = Item.State;
		*Error = Item.Error;
		*TimeStamp_ms = Item.TimeStamp_ms;
		*TimeStamp_s = Item.TimeStamp_s;
	} else {
		*State = (uint8_t)sm_state;
		*Error = (uint8_t)system_ERROR;
		*TimeStamp_ms = App_RTC_Counter_ms;
		*TimeStamp_s = App_RTC_Counter_s;
	}
#else
	*State = (uint8_t)sm_state;
	*Error = (uint8_t)system_ERROR;
	*TimeStamp_ms = App_RTC_Counter_ms;
	*TimeStamp_s = App_RTC_Counter_s;
#endif
	App_SM_Status_Update();
}

void App_SM_Init(void *Parameters)
{
	(void)Parameters;

	SMRecState = 0;
#if (APP_SM_RB_SIZE != 0)
	RingBuffer_Init(&SM_Ring, &SM_Buff, SM_ITEM_SIZE, APP_SM_RB_SIZE);
#endif
#if 0
	sm_state = 1; system_ERROR = 9; App_SM_Status_Store();
	sm_state = 2; system_ERROR = 8; App_SM_Status_Store();
	sm_state = 3; system_ERROR = 7; App_SM_Status_Store();
	sm_state = 4; system_ERROR = 6; App_SM_Status_Store();
	sm_state = 5; system_ERROR = 5; App_SM_Status_Store();
	sm_state = 6; system_ERROR = 4; App_SM_Status_Store();
	sm_state = 7; system_ERROR = 3; App_SM_Status_Store();
	sm_state = 8; system_ERROR = 2; App_SM_Status_Store();
	sm_state = 9; system_ERROR = 1; App_SM_Status_Store();
	sm_state = 10; system_ERROR = 0; App_SM_Status_Store();
	sm_state = 11; system_ERROR = 9; App_SM_Status_Store();
	sm_state = 12; system_ERROR = 8; App_SM_Status_Store();
#endif
	if (ADC_Calib == false)
		App_Main_SM_Init();
}

#define APP_SM_RESET_DELAY_TIME		1000	// 1000ms delay (Delay is needed against multiple resets in Modbus mode)

void App_SM_Process(void *Parameters)
{
	static uint16_t Timer_Last_Value = 0;
	uint16_t Timer_Current_Value = *(uint16_t*)Parameters;
	static uint16_t Delay_Reset_Value = APP_SM_RESET_DELAY_TIME;					

	if(Timer_Last_Value != Timer_Current_Value) {				// Enter each 1ms Tick
		Timer_Last_Value = Timer_Current_Value;
		if (Sys_Calib == true) {
			if(Delay_Reset_Value > 0) {
				if(Delay_Reset_Value == (APP_SM_RESET_DELAY_TIME / 2)) {
					NVMemory.ADC.Do_Calibration = true;
					NVMemoryDoUpdate = true;
					App_NVMemory_Process(NULL);
				}
				Delay_Reset_Value--;
			} else {
				BSP_System_SW_Reset();
			}
		}
		if (Sys_Reset == true) {
			if(Delay_Reset_Value > 0)
				Delay_Reset_Value--;
			else
				BSP_System_SW_Reset();
		}
		if(App_OCP_OC_Status != 0) {
			Sys_Shutdown = true;
		}
		if (ADC_Calib == false)
			main_state_machine();
		App_SM_Status_Store();
	}
}
