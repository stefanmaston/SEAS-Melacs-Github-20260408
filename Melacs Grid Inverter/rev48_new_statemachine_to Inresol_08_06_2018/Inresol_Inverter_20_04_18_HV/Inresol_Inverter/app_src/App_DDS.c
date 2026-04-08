/*
 *  File name: App_DDS.c
 *
 *  Description: High level function implementations for for DDS (Direct Digital Synthesis) generator
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"
#include "sineTable512.h"

// DDS Macros
#define APP_MACRO_DDS_SAMP_FCTR		((uint32_t)1 << APP_SETTINGS_DDS_SAMP_BITS)						// Value 0x800 (2048)
#define APP_MACRO_DDS_SHFT_BITS		(APP_SETTINGS_DDS_ACC_BITS - APP_SETTINGS_DDS_SAMP_BITS)		// Used to shift result of frequency tuning word to the top bits (21))
#define APP_MACRO_DDS_SHFT_FCTR		((uint32_t)1 << APP_MACRO_DDS_SHFT_BITS)						// Value 0x200000 (2097152)

static volatile uint32_t	App_DDS_Acc_Phase_Chn1;		// Used to store phase accumulator for channel 1
static volatile uint32_t	App_DDS_Acc_Phase_Chn2;		// Used to store phase accumulator for channel 2
static volatile uint32_t	App_DDS_Acc_Phase_Chn3;		// Used to store phase accumulator for channel 3
static volatile uint32_t	App_DDS_Freq_Tune_Chn1;		// Frequency tuning word for channel 1
static volatile int32_t		App_DDS_Freq_Tune_Chn2;		// Frequency tuning word for channel 2
static volatile int32_t		App_DDS_Freq_Tune_Chn3;		// Frequency tuning word for channel 3
/*static*/ volatile uint16_t	App_DDS_Waves_Freq;			// Frequency of waveforms
/*static*/ volatile int16_t		App_DDS_Shift_Phase_Chn2;	// Phase shift tuning word for channel 2
/*static*/ volatile int16_t		App_DDS_Shift_Phase_Chn3;	// Phase shift tuning word for channel 3
/*static*/ volatile uint16_t	App_DDS_Gain_Chn1;			// Magnitude for channel 1
/*static*/ volatile uint16_t	App_DDS_Gain_Chn2;			// Magnitude for channel 2
/*static*/ volatile uint16_t	App_DDS_Gain_Chn3;			// Magnitude for channel 3

// This function adds the frequency tuning word to the phase accumulator
inline static void App_DDS_Acc_Inc(void)
{
	uint32_t	Base_Phase;

	Base_Phase = App_DDS_Acc_Phase_Chn1;
	App_DDS_Acc_Phase_Chn1 = Base_Phase + App_DDS_Freq_Tune_Chn1;
	App_DDS_Acc_Phase_Chn2 = Base_Phase + App_DDS_Freq_Tune_Chn2;
	App_DDS_Acc_Phase_Chn3 = Base_Phase + App_DDS_Freq_Tune_Chn3;
}

// This function resets the phase accumulator.
static void App_DDS_Acc_Reset(void)
{
	// Phase 0
	App_DDS_Acc_Phase_Chn1 = 0;
	App_DDS_Acc_Phase_Chn2 = 0;
	App_DDS_Acc_Phase_Chn3 = 0;
	// Shift 0
	App_DDS_Shift_Phase_Chn2 = 0;
	App_DDS_Shift_Phase_Chn3 = 0;
	// Magnitude max
	App_DDS_Gain_Chn1 = 0;
	App_DDS_Gain_Chn2 = 0;
	App_DDS_Gain_Chn3 = 0;
}

inline static void Calculate_Freq_Tune_Chn1(void)
{
//	App_DDS_Freq_Tune_Chn1 = (uint64_t)(50) * (0x800) * (0x200000) / (16000);
//	App_DDS_Freq_Tune_Chn1 = (uint64_t)(500) * (0x800) * (0x200000) / (16000) / 10;
	App_DDS_Freq_Tune_Chn1 = (uint64_t)App_DDS_Waves_Freq * APP_MACRO_DDS_SAMP_FCTR * APP_MACRO_DDS_SHFT_FCTR / APP_SETTINGS_DDS_SAMP_FREQ / 10;
}

inline static void Calculate_Freq_Tune_Chn2(void)
{
	App_DDS_Freq_Tune_Chn2 = (int64_t)APP_MACRO_DDS_SAMP_FCTR * APP_MACRO_DDS_SHFT_FCTR * App_DDS_Shift_Phase_Chn2 / 32768;
}

inline static void Calculate_Freq_Tune_Chn3(void)
{
	App_DDS_Freq_Tune_Chn3 = (int64_t)APP_MACRO_DDS_SAMP_FCTR * APP_MACRO_DDS_SHFT_FCTR * App_DDS_Shift_Phase_Chn3 / 32768;
}

// This function calculates the frequency tuning words of the oscillator
static void Calculate_Freq_Tunes(void)
{
	Calculate_Freq_Tune_Chn1();
	Calculate_Freq_Tune_Chn2();
	Calculate_Freq_Tune_Chn3();
}

// This function sets the frequency of the oscillator in the tenths of Hz (0.1Hz).
// In addition, this function calculates the corresponding frequency tuning word.
void App_DDS_Set_Freq(uint16_t Freq)
{
	if(Freq > APP_SETTINGS_DDS_MAX_GEN_FREQ)
		App_DDS_Waves_Freq = APP_SETTINGS_DDS_MAX_GEN_FREQ;
	else if(Freq < APP_SETTINGS_DDS_MIN_GEN_FREQ)
		App_DDS_Waves_Freq = APP_SETTINGS_DDS_MIN_GEN_FREQ;
	else
		App_DDS_Waves_Freq = Freq;
	Calculate_Freq_Tunes();
}

inline void App_DDS_Set_Phase_Ch2(int16_t Phase_Shift)
{
	App_DDS_Shift_Phase_Chn2 = Phase_Shift;
	Calculate_Freq_Tune_Chn2();
}

inline void App_DDS_Set_Phase_Ch3(int16_t Phase_Shift)
{
	App_DDS_Shift_Phase_Chn3 = Phase_Shift;
	Calculate_Freq_Tune_Chn3();
}

// This function sets the phase shifts for channels 2 and 3.
// Input range: max: +32767 (+2PI or +360deg); min: -32768 (-2PI or -360deg)
void App_DDS_Set_Phase(uint8_t Channel, int16_t Phase_Shift)
{
	switch(Channel) {
		case APP_DDS_CHANNEL_NUMBER_2:
			App_DDS_Set_Phase_Ch2(Phase_Shift);
			break;
		case APP_DDS_CHANNEL_NUMBER_3:
			App_DDS_Set_Phase_Ch3(Phase_Shift);
			break;
	}
}

inline void App_DDS_Set_Gain_Ch1(uint16_t Gain)
{
	App_DDS_Gain_Chn1 = Gain;
}

inline void App_DDS_Set_Gain_Ch2(uint16_t Gain)
{
	App_DDS_Gain_Chn2 = Gain;
}

inline void App_DDS_Set_Gain_Ch3(uint16_t Gain)
{
	App_DDS_Gain_Chn3 = Gain;
}

// This function sets the magnitudes for all channels 1 to 3.
void App_DDS_Set_Gain(uint8_t Channel, uint16_t Gain)
{
	switch(Channel) {
		case APP_DDS_CHANNEL_NUMBER_1:
			App_DDS_Set_Gain_Ch1(Gain);
			break;
		case APP_DDS_CHANNEL_NUMBER_2:
			App_DDS_Set_Gain_Ch2(Gain);
			break;
		case APP_DDS_CHANNEL_NUMBER_3:
			App_DDS_Set_Gain_Ch3(Gain);
			break;
	}
}

inline static uint16_t App_DDS_Look_Up_Table(uint16_t sample_index)
{
	uint16_t	sample_value;

	if(sample_index < 512)
		sample_value = 32768 + sineTable512[sample_index];
	else if(sample_index < 1024)
		sample_value = 32768 + sineTable512[1023 - sample_index];
	else if(sample_index < 1536)
		sample_value = 32767 - sineTable512[sample_index - 1024];
	else
		sample_value = 32767 - sineTable512[2047 - sample_index];
	
	return sample_value;
}

inline uint16_t App_DDS_Get_Sample_Table_Ch1(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator

	sample_index = App_DDS_Acc_Phase_Chn1 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	return App_DDS_Look_Up_Table(sample_index);
}

inline uint16_t App_DDS_Get_Sample_Table_Ch2(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator

	sample_index = App_DDS_Acc_Phase_Chn2 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	return App_DDS_Look_Up_Table(sample_index);
}

inline uint16_t App_DDS_Get_Sample_Table_Ch3(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator

	sample_index = App_DDS_Acc_Phase_Chn3 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	return App_DDS_Look_Up_Table(sample_index);
}

uint16_t App_DDS_Get_Sample_Table(uint8_t Channel)
{
	uint16_t	sample_value;

	switch(Channel) {
		case APP_DDS_CHANNEL_NUMBER_1:
			sample_value = App_DDS_Get_Sample_Table_Ch1();
			break;
		case APP_DDS_CHANNEL_NUMBER_2:
			sample_value = App_DDS_Get_Sample_Table_Ch2();
			break;
		case APP_DDS_CHANNEL_NUMBER_3:
			sample_value = App_DDS_Get_Sample_Table_Ch3();
			break;
	}
	return sample_value;
}

// unsigned long __builtin_muluu(const unsigned int p0, const unsigned int p1);
// unsigned int __builtin_divud(const unsigned long num, const unsigned int den);

inline static uint16_t App_DDS_Look_Up_Table_Gain(uint16_t sample_index, uint16_t gain_value)
{
	uint16_t	sample_value;

	if(sample_index < 512)
		sample_value = 32768 + __builtin_divud(__builtin_muluu(sineTable512[sample_index], gain_value), 65535);
	else if(sample_index < 1024)
		sample_value = 32768 + __builtin_divud(__builtin_muluu(sineTable512[1023 - sample_index], gain_value), 65535);
	else if(sample_index < 1536)
		sample_value = 32767 - __builtin_divud(__builtin_muluu(sineTable512[sample_index - 1024], gain_value), 65535);
	else
		sample_value = 32767 - __builtin_divud(__builtin_muluu(sineTable512[2047 - sample_index], gain_value), 65535);
	
	return sample_value;
}

inline uint16_t App_DDS_Get_Sample_Scaled_Ch1(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator
	uint16_t	gain_value;

	sample_index = App_DDS_Acc_Phase_Chn1 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	gain_value = App_DDS_Gain_Chn1;
	return App_DDS_Look_Up_Table_Gain(sample_index, gain_value);
}

inline uint16_t App_DDS_Get_Sample_Scaled_Ch2(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator
	uint16_t	gain_value;

	sample_index = App_DDS_Acc_Phase_Chn2 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	gain_value = App_DDS_Gain_Chn2;
	return App_DDS_Look_Up_Table_Gain(sample_index, gain_value);
}

inline uint16_t App_DDS_Get_Sample_Scaled_Ch3(void)
{
	uint16_t	sample_index;											// Top 11 bits of phase accumulator
	uint16_t	gain_value;

	sample_index = App_DDS_Acc_Phase_Chn3 >> APP_MACRO_DDS_SHFT_BITS;	// Get address into wavetable
	gain_value = App_DDS_Gain_Chn3;
	return App_DDS_Look_Up_Table_Gain(sample_index, gain_value);
}

uint16_t App_DDS_Get_Sample_Scaled(uint8_t Channel)
{
	uint16_t	sample_value;

	switch(Channel) {
		case APP_DDS_CHANNEL_NUMBER_1:
			sample_value = App_DDS_Get_Sample_Scaled_Ch1();
			break;
		case APP_DDS_CHANNEL_NUMBER_2:
			sample_value = App_DDS_Get_Sample_Scaled_Ch2();
			break;
		case APP_DDS_CHANNEL_NUMBER_3:
			sample_value = App_DDS_Get_Sample_Scaled_Ch3();
			break;
	}
	return sample_value;
}

#define APP_MACRO_DDS_DEF_GEN_FREQ			(APP_SETTINGS_DDS_DEF_GEN_FREQ * 10)		// 50Hz * 10 = 500 (in 0.1Hz)

void App_DDS_Init(void *Parameters)
{
#if 0
	(void)Parameters;
	App_DDS_Acc_Reset();			// Set accumulator to 0 initially
	App_DDS_Set_Freq(APP_MACRO_DDS_DEF_GEN_FREQ);			// 50Hz
	App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_2, 10922);		// 120deg
	App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_3, 21844);		// 240deg
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_1, 49151);		// 3/4
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_2, 65535);		// 1
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_3, 32767);		// 1/2
#else
	int32_t		Value;
	
	(void)Parameters;
	App_DDS_Acc_Reset();			// Set accumulator to 0 initially
	App_DDS_Set_Freq(APP_MACRO_DDS_DEF_GEN_FREQ);			// 50Hz
	if(APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH2 < 0)
		Value = (int32_t)32768 * APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH2 / 360;
	else
		Value = (int32_t)32767 * APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH2 / 360;
	App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_2, Value);		// 120deg
	if(APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH3 < 0)
		Value = (int32_t)32768 * APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH3 / 360;
	else
		Value = (int32_t)32767 * APP_SETTINGS_DDS_DEF_PHASE_SHIFT_CH3 / 360;
	App_DDS_Set_Phase(APP_DDS_CHANNEL_NUMBER_3, Value);		// 240deg
	Value = (int32_t)65535 * APP_SETTINGS_DDS_DEF_MAGNITUDE_CH1 / 100;
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_1, Value);		// 3/4
	Value = (int32_t)65535 * APP_SETTINGS_DDS_DEF_MAGNITUDE_CH2 / 100;
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_2, Value);		// 1
	Value = (int32_t)65535 * APP_SETTINGS_DDS_DEF_MAGNITUDE_CH3 / 100;
	App_DDS_Set_Gain(APP_DDS_CHANNEL_NUMBER_3, Value);		// 1/2
#endif
}

inline void App_DDS_Process(void)
{
	App_DDS_Acc_Inc();				// Increment phase accumulator
}
