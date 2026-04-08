/*
 *  File name: App_PWM.c
 *
 *  Description: High level function implementations for PWM processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

static bool App_PWM_IGBTs_Are_On = false;

void App_PWM_All_IGBTs_Off(bool all_channels)
{
	BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_1, 3, 3);		// Both pins PWM; Both pins Active-High
	if(all_channels) {
		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_2, 3, 3);	// Both pins PWM; Both pins Active-High
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 3, 3);	// Both pins PWM; Both pins Active-High
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
//		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 3, 3);	// Both pins PWM; Both pins Active-High
#else
// 28-pins Starter Board
//		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 2, 1);	// H pin PWM; H pins Active-Low
#endif
	}
	App_PWM_IGBTs_Are_On = false;
}

void App_PWM_All_IGBTs_On(bool all_channels)
{
	BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_1, 3);			// Both pins PWM
	if(all_channels) {
		BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_2, 3);		// Both pins PWM
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
		BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 3);		// Both pins PWM
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
//		BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 3);		// Both pins PWM
#else
// 28-pins Starter Board
//		BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_3, 2, 1);		// H pin PWM
#endif
	}
	App_PWM_IGBTs_Are_On = true;
}

void App_PWM_Gate_Drivers_Off(void)
{
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_4, 3, 0);	// Both pins PWM; Both pins Active-Low
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
		BSP_PWM_Channel_Off_Outputs(BSP_PWM_CHANNEL_NUMBER_4, 3, 0);	// Both pins PWM; Both pins Active-Low
#else
// 28-pins Starter Board
#endif
}

void App_PWM_Gate_Drivers_On(void)
{
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
	BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_4, 3);		// Both pins PWM
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
	BSP_PWM_Channel_On_Outputs(BSP_PWM_CHANNEL_NUMBER_4, 3);		// Both pins PWM
#else
// 28-pins Starter Board
#endif  
}

void App_PWM_Init(void *Parameters)
{
	(void)Parameters;
	BSP_PWM_Core_Init();
	BSP_PWM_Set_TimeBase(BSP_PWM_MASTER_TIME_BASE_PRIMARY, APP_SETTINGS_PWM_IGBT_SW_FREQ);
	BSP_PWM_Set_TimeBase(BSP_PWM_MASTER_TIME_BASE_SECONDARY, APP_SETTINGS_PWM_GATE_DRV_SW_FREQ);
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_1, 3, 3, 0, 0);		// Both pins PWM; Both pins Active-High; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_1, 32767);	// 50% duty cycle
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_2, 3, 3, 0, 0);		// Both pins PWM; Both pins Active-High; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_2, 32767);	// 50% duty cycle
//	BSP_PWM_Channel_Set_Trigger(BSP_PWM_CHANNEL_NUMBER_2, 1200/*2400*/, /*2*/0, 0);	// Trigger generated at beginning of PWM active period; Trigger interrupt generated every 3 PWM cycles; Trigger generated after waiting 1 PWM cycles
#ifndef ADC_TIME_SHIFT_ENABLED										// Enable time shift between conversion of ADC Dedicated and Shared cores
	BSP_PWM_Channel_Set_Trigger(BSP_PWM_CHANNEL_NUMBER_2, APP_SETTINGS_PWM_PRIMARY_TRIGGER_DELAY, APP_SETTINGS_PWM_SECONDARY_TRIGGER_DELAY, /*2*/0, 0, 1);	// Trigger generated at beginning of PWM active period; Trigger interrupt generated every 3 PWM cycles; Trigger generated after waiting 1 PWM cycles
#else	// ADC_TIME_SHIFT_ENABLED
	BSP_PWM_Channel_Set_Trigger(BSP_PWM_CHANNEL_NUMBER_1, APP_SETTINGS_PWM_PRIMARY_TRIGGER_DELAY_ADC_S, APP_SETTINGS_PWM_SECONDARY_TRIGGER_DELAY_ADC_S, /*2*/0, 0, 1);	// Trigger generated at beginning of PWM active period; Trigger interrupt generated every 3 PWM cycles; Trigger generated after waiting 1 PWM cycles
	BSP_PWM_Channel_Set_Trigger(BSP_PWM_CHANNEL_NUMBER_2, APP_SETTINGS_PWM_PRIMARY_TRIGGER_DELAY_ADC_D, APP_SETTINGS_PWM_SECONDARY_TRIGGER_DELAY_ADC_D, /*2*/0, 0, 1);	// Trigger generated at beginning of PWM active period; Trigger interrupt generated every 3 PWM cycles; Trigger generated after waiting 1 PWM cycles
#endif	// ADC_TIME_SHIFT_ENABLED
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_3, 3, 3, 0, 0);		// Both pins PWM; Both pins Active-High; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_3, 32767);	// 50% duty cycle
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_4, 3, 0, 0, 0);		// Both pins PWM; Both pins Active-Low; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_4, 32767);	// 50% duty cycle
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_5, 3, 3, 3, 0);		// Both pins PWM; Both pins Active-High; True Independent mode; Positive dead time is actively applied for all Output modes
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
////	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_3, 3, 3, 0, 0);	// Both pins PWM; Both pins Active-High; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_4, 3, 0, 0, 0);		// Both pins PWM; Both pins Active-Low; Complementary mode; Positive dead time is actively applied for all Output modes
	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_4, 32767);	// 50% duty cycle
	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_5, 3, 3, 3, 0);		// Both pins PWM; Both pins Active-High; True Independent mode; Positive dead time is actively applied for all Output modes
#else
// 28-pins Starter Board
//	BSP_PWM_Channel_Init(BSP_PWM_CHANNEL_NUMBER_3, 2, 1, 3, 0);		// H pin PWM; H pins Active-Low; True Independent Mode; Dead-time function is disabled
//	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_3, 32767);	// 50% duty cycle
#endif

	App_DDS_Init(NULL);
	App_OCP_Init(NULL);

#ifndef	APP_SETTINGS_PWM_DELAYS_ENABLED
	BSP_PWM_Interrupt_Enable(BSP_PWM_INTERRUPT_CHANNEL, BSP_PWM_INTERRUPT_LEVEL);
	BSP_PWM_Core_Enable();											// Enable the PWM
#else	// APP_SETTINGS_PWM_DELAYS_ENABLED
	App_PWM_All_IGBTs_Off(true);
	BSP_PWM_Core_Enable();											// Enable the PWM
	App_SysTick_Delay(APP_SETTINGS_PWM_DELAY_BEFORE_GATE_DRV);		// 100ms Delay before 250kHz Gate-Driver PWM Oscillator Start
	App_PWM_Gate_Drivers_On();
	App_SysTick_Delay(APP_SETTINGS_PWM_DELAY_BEFORE_IGBTS);			// 100ms Delay before 16kHz IGBTs PWM Start
//	App_PWM_All_IGBTs_On(true);										// Now we starting in IDLE mode with all IGBTs Off
	BSP_PWM_Interrupt_Enable(BSP_PWM_INTERRUPT_CHANNEL, BSP_PWM_INTERRUPT_LEVEL);
#endif	// APP_SETTINGS_PWM_DELAYS_ENABLED
}

#if 1
inline void App_PWM_Process_IRQ(void)
{
	uint16_t sample_int;
//	float sample_float;
//	uint16_t sample_q15;

#if 0
	static int16_t phase = 0;
	static uint8_t dir = 0;
	static uint16_t cnt = 0;

	if(cnt < 10) {
		cnt++;
	} else {
		cnt = 0;
		if(dir == 0) {
			if(phase < 32767)
				phase++;
			else
				dir = 1;
		} else {
			if(phase > -32768)
				phase--;
			else
				dir = 0;
		}
		App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_2, phase);
//		App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_3, -1 - phase);
	}
#endif

	if(App_SM_System_Mode == APP_SM_SYSTEM_MODE_TEST) {

		App_DDS_Process();

#if 1
//		sample_int = App_DDS_Get_Sample_Table(APP_DDS_CHANNEL_NUMBER_1);
		sample_int = App_DDS_Get_Sample_Scaled(APP_DDS_CHANNEL_NUMBER_1);
//sample_int = App_DDS_Gain_Chn1;
//		sample_float = (float)sample_int / 65535.0;
//		BSP_PWM_Channel_Set_DutyCycle(2, sample_float);
//		BSP_PWM_Channel_Set_DutyCycle(2, Q15(0.5));
//		sample_q15 = sample_int / 2;
//		sample_q15 = sample_int;
//		BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_1, sample_int);
		BSP_PWM_Channel_1_Set_DutyCycle(sample_int);
//		sample_int = DDS_Get_Table_Value(APP_DDS_CHANNEL_NUMBER_2);
		sample_int = App_DDS_Get_Sample_Scaled(APP_DDS_CHANNEL_NUMBER_2);
//sample_int = App_DDS_Gain_Chn2;
//		BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_2, sample_int);
		BSP_PWM_Channel_2_Set_DutyCycle(sample_int);
//		LED4_OUT = 0;
#if (!defined PINS28_STARTER_BOARD)
		sample_int = App_DDS_Get_Sample_Scaled(APP_DDS_CHANNEL_NUMBER_3);
		BSP_PWM_Channel_3_Set_DutyCycle(sample_int);
#endif
#endif
	}
	
	App_OCP_Process();
	
#if 1
	sample_int = App_OCP_Get_Sample_Scaled(APP_OCP_ITRIP_CHANNEL_NUMBER_1);
	BSP_PWM_Channel_5_Set_DutyCycle(sample_int);
	sample_int = App_OCP_Get_Sample_Scaled(APP_OCP_ITRIP_CHANNEL_NUMBER_2);
	BSP_PWM_Channel_6_Set_DutyCycle(sample_int);
#else
	sample_int = App_DDS_Get_Sample_Scaled(APP_DDS_CHANNEL_NUMBER_1);
	BSP_PWM_Channel_5_Set_DutyCycle(sample_int);
	sample_int = App_DDS_Get_Sample_Scaled(APP_DDS_CHANNEL_NUMBER_2);
	BSP_PWM_Channel_6_Set_DutyCycle(sample_int);
#endif
}
#endif

#if 0	// Test Sawtooth signal 50Hz
inline void App_PWM_Process(void)
{
	static uint16_t cnt = 0;

	cnt += 50LL * 65536 / APP_SETTINGS_DDS_SAMP_FREQ;		// 50Hz * 65536 / 16000Hz
//	BSP_PWM_Channel_Set_DutyCycle(BSP_PWM_CHANNEL_NUMBER_2, cnt);
	BSP_PWM_Channel_2_Set_DutyCycle(cnt);
}
#endif

void App_PWM_Process_IDLE(void *Parameters)
{
	(void)Parameters;
	if((App_OCP_OC_Status != 0) || (Sys_Shutdown == true)) {
		App_PWM_All_IGBTs_Off(true);
		App_PWM_Gate_Drivers_Off();
	} else if ((App_SM_System_Mode == APP_SM_SYSTEM_MODE_TEST) && (App_PWM_IGBTs_Are_On == false)) {
		App_PWM_All_IGBTs_On(true);
	}
}
