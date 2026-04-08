/*
 *  File name: App_TempSens.c
 *
 *  Description: High level function implementations for Temperature Sensors
 *
 *  Author: Future Electronics
 *
 */

#include <string.h>
#include "global_includes.h"

#define VARIABLE_FILTER_LENGTH

#define MEDIAN_FILTER_ENABLED		1
#define MEDIAN_FILTER_LENGTH		10
#define MEDIAN_FILTER_CHANNELS		APP_TEMP_SENS_CHANNELS_MAX

#define R_UPPER						5620UL		// 5k62 * 10
#define R_SCALER					10000UL
#define R_PREC						10			// Resistance Precision 0.1 Ohm

#define R_LOW_LIMIT					808			// Lowest value 161.5 Ohm - 50% = 80.8 Ohm * 10 = 808
#define R_HIGH_LIMIT				5014116UL	// Highest value 334274.4 Ohm + 50% = 501411.6 Ohm * 10 = 5014116
//#define R_HIGH_LIMIT				500000UL	// Highest value 334274.4 Ohm + 50% = 501411.6 Ohm * 10 = 5014116

#define	T_START						155			// Temperature Start 155*C
#define	T_STEP						1			// Temperature Step  1*C
#define T_PREC						100			// Temperature Precision 0.01 *C -> 0.1 *C after rounding at the end

#define ADC_MAX_VALUE				4095		// 12-bit
#define ADC_IMPEDANCE				1250000UL	// 125k Ohm * 10
#define ADC_FAILURE_CNT				250			// 250 * 1ms = 250ms

// Curve resistance to temperature table for Vishay NTCALUGE2C90169 (NTC 10k)
static const uint32_t NTC10000_R_table[] = { // [R*10]
	   1615, //  R =    161.5 ; T = +155 *C
	   1653, //  R =    165.3 ; T = +154 *C
	   1692, //  R =    169.2 ; T = +153 *C
	   1731, //  R =    173.1 ; T = +152 *C
	   1772, //  R =    177.2 ; T = +151 *C
	   1814, //  R =    181.4 ; T = +150 *C
	   1857, //  R =    185.7 ; T = +149 *C
	   1901, //  R =    190.1 ; T = +148 *C
	   1947, //  R =    194.7 ; T = +147 *C
	   1993, //  R =    199.3 ; T = +146 *C
	   2042, //  R =    204.2 ; T = +145 *C
	   2091, //  R =    209.1 ; T = +144 *C
	   2142, //  R =    214.2 ; T = +143 *C
	   2195, //  R =    219.5 ; T = +142 *C
	   2248, //  R =    224.8 ; T = +141 *C
	   2304, //  R =    230.4 ; T = +140 *C
	   2361, //  R =    236.1 ; T = +139 *C
	   2420, //  R =    242.0 ; T = +138 *C
	   2481, //  R =    248.1 ; T = +137 *C
	   2543, //  R =    254.3 ; T = +136 *C
	   2607, //  R =    260.7 ; T = +135 *C
	   2674, //  R =    267.4 ; T = +134 *C
	   2742, //  R =    274.2 ; T = +133 *C
	   2812, //  R =    281.2 ; T = +132 *C
	   2884, //  R =    288.4 ; T = +131 *C
	   2959, //  R =    295.9 ; T = +130 *C
	   3036, //  R =    303.6 ; T = +129 *C
	   3115, //  R =    311.5 ; T = +128 *C
	   3197, //  R =    319.7 ; T = +127 *C
	   3281, //  R =    328.1 ; T = +126 *C
	   3368, //  R =    336.8 ; T = +125 *C
	   3457, //  R =    345.7 ; T = +124 *C
	   3549, //  R =    354.9 ; T = +123 *C
	   3645, //  R =    364.5 ; T = +122 *C
	   3743, //  R =    374.3 ; T = +121 *C
	   3844, //  R =    384.4 ; T = +120 *C
	   3949, //  R =    394.9 ; T = +119 *C
	   4057, //  R =    405.7 ; T = +118 *C
	   4168, //  R =    416.8 ; T = +117 *C
	   4283, //  R =    428.3 ; T = +116 *C
	   4402, //  R =    440.2 ; T = +115 *C
	   4525, //  R =    452.5 ; T = +114 *C
	   4651, //  R =    465.1 ; T = +113 *C
	   4782, //  R =    478.2 ; T = +112 *C
	   4917, //  R =    491.7 ; T = +111 *C
	   5057, //  R =    505.7 ; T = +110 *C
	   5201, //  R =    520.1 ; T = +109 *C
	   5350, //  R =    535.0 ; T = +108 *C
	   5504, //  R =    550.4 ; T = +107 *C
	   5664, //  R =    566.4 ; T = +106 *C
	   5828, //  R =    582.8 ; T = +105 *C
	   5999, //  R =    599.9 ; T = +104 *C
	   6175, //  R =    617.5 ; T = +103 *C
	   6357, //  R =    635.7 ; T = +102 *C
	   6546, //  R =    654.6 ; T = +101 *C
	   6741, //  R =    674.1 ; T = +100 *C
	   6943, //  R =    694.3 ; T =  +99 *C
	   7152, //  R =    715.2 ; T =  +98 *C
	   7369, //  R =    736.9 ; T =  +97 *C
	   7593, //  R =    759.3 ; T =  +96 *C
	   7825, //  R =    782.5 ; T =  +95 *C
	   8065, //  R =    806.5 ; T =  +94 *C
	   8314, //  R =    831.4 ; T =  +93 *C
	   8572, //  R =    857.2 ; T =  +92 *C
	   8839, //  R =    883.9 ; T =  +91 *C
	   9116, //  R =    911.6 ; T =  +90 *C
	   9403, //  R =    940.3 ; T =  +89 *C
	   9700, //  R =    970.0 ; T =  +88 *C
	  10009, //  R =   1000.9 ; T =  +87 *C
	  10329, //  R =   1032.9 ; T =  +86 *C
	  10661, //  R =   1066.1 ; T =  +85 *C
	  11006, //  R =   1100.6 ; T =  +84 *C
	  11363, //  R =   1136.3 ; T =  +83 *C
	  11734, //  R =   1173.4 ; T =  +82 *C
	  12119, //  R =   1211.9 ; T =  +81 *C
	  12518, //  R =   1251.8 ; T =  +80 *C
	  12933, //  R =   1293.3 ; T =  +79 *C
	  13364, //  R =   1336.4 ; T =  +78 *C
	  13811, //  R =   1381.1 ; T =  +77 *C
	  14276, //  R =   1427.6 ; T =  +76 *C
	  14759, //  R =   1475.9 ; T =  +75 *C
	  15261, //  R =   1526.1 ; T =  +74 *C
	  15783, //  R =   1578.3 ; T =  +73 *C
	  16326, //  R =   1632.6 ; T =  +72 *C
	  16890, //  R =   1689.0 ; T =  +71 *C
	  17477, //  R =   1747.7 ; T =  +70 *C
	  18087, //  R =   1808.7 ; T =  +69 *C
	  18722, //  R =   1872.2 ; T =  +68 *C
	  19383, //  R =   1938.3 ; T =  +67 *C
	  20070, //  R =   2007.0 ; T =  +66 *C
	  20787, //  R =   2078.7 ; T =  +65 *C
	  21532, //  R =   2153.2 ; T =  +64 *C
	  22309, //  R =   2230.9 ; T =  +63 *C
	  23118, //  R =   2311.8 ; T =  +62 *C
	  23960, //  R =   2396.0 ; T =  +61 *C
	  24838, //  R =   2483.8 ; T =  +60 *C
	  25753, //  R =   2575.3 ; T =  +59 *C
	  26708, //  R =   2670.8 ; T =  +58 *C
	  27703, //  R =   2770.3 ; T =  +57 *C
	  28740, //  R =   2874.0 ; T =  +56 *C
	  29823, //  R =   2982.3 ; T =  +55 *C
	  30952, //  R =   3095.2 ; T =  +54 *C
	  32130, //  R =   3213.0 ; T =  +53 *C
	  33361, //  R =   3336.1 ; T =  +52 *C
	  34646, //  R =   3464.6 ; T =  +51 *C
	  35987, //  R =   3598.7 ; T =  +50 *C
	  37388, //  R =   3738.8 ; T =  +49 *C
	  38852, //  R =   3885.2 ; T =  +48 *C
	  40382, //  R =   4038.2 ; T =  +47 *C
	  41981, //  R =   4198.1 ; T =  +46 *C
	  43653, //  R =   4365.3 ; T =  +45 *C
	  45401, //  R =   4540.1 ; T =  +44 *C
	  47229, //  R =   4722.9 ; T =  +43 *C
	  49142, //  R =   4914.2 ; T =  +42 *C
	  51144, //  R =   5114.4 ; T =  +41 *C
	  53239, //  R =   5323.9 ; T =  +40 *C
	  55432, //  R =   5543.2 ; T =  +39 *C
	  57729, //  R =   5772.9 ; T =  +38 *C
	  60135, //  R =   6013.5 ; T =  +37 *C
	  62656, //  R =   6265.6 ; T =  +36 *C
	  65297, //  R =   6529.7 ; T =  +35 *C
	  68066, //  R =   6806.6 ; T =  +34 *C
	  70970, //  R =   7097.0 ; T =  +33 *C
	  74014, //  R =   7401.4 ; T =  +32 *C
	  77208, //  R =   7720.8 ; T =  +31 *C
	  80560, //  R =   8056.0 ; T =  +30 *C
	  84077, //  R =   8407.7 ; T =  +29 *C
	  87770, //  R =   8777.0 ; T =  +28 *C
	  91647, //  R =   9164.7 ; T =  +27 *C
	  95720, //  R =   9572.0 ; T =  +26 *C
	 100000, //  R =  10000.0 ; T =  +25 *C
	 104498, //  R =  10449.8 ; T =  +24 *C
	 109225, //  R =  10922.5 ; T =  +23 *C
	 114197, //  R =  11419.7 ; T =  +22 *C
	 119426, //  R =  11942.6 ; T =  +21 *C
	 124928, //  R =  12492.8 ; T =  +20 *C
	 130717, //  R =  13071.7 ; T =  +19 *C
	 136812, //  R =  13681.2 ; T =  +18 *C
	 143230, //  R =  14323.0 ; T =  +17 *C
	 149990, //  R =  14999.0 ; T =  +16 *C
	 157113, //  R =  15711.3 ; T =  +15 *C
	 164619, //  R =  16461.9 ; T =  +14 *C
	 172533, //  R =  17253.3 ; T =  +13 *C
	 180878, //  R =  18087.8 ; T =  +12 *C
	 189680, //  R =  18968.0 ; T =  +11 *C
	 198969, //  R =  19896.9 ; T =  +10 *C
	 208773, //  R =  20877.3 ; T =   +9 *C
	 219125, //  R =  21912.5 ; T =   +8 *C
	 230057, //  R =  23005.7 ; T =   +7 *C
	 241607, //  R =  24160.7 ; T =   +6 *C
	 253814, //  R =  25381.4 ; T =   +5 *C
	 266718, //  R =  26671.8 ; T =   +4 *C
	 280364, //  R =  28036.4 ; T =   +3 *C
	 294799, //  R =  29479.9 ; T =   +2 *C
	 310073, //  R =  31007.3 ; T =   +1 *C
	 326242, //  R =  32624.2 ; T =    0 *C
	 343363, //  R =  34336.3 ; T =   -1 *C
	 361498, //  R =  36149.8 ; T =   -2 *C
	 380714, //  R =  38071.4 ; T =   -3 *C
	 401082, //  R =  40108.2 ; T =   -4 *C
	 422679, //  R =  42267.9 ; T =   -5 *C
	 445586, //  R =  44558.6 ; T =   -6 *C
	 469891, //  R =  46989.1 ; T =   -7 *C
	 495690, //  R =  49569.0 ; T =   -8 *C
	 523084, //  R =  52308.4 ; T =   -9 *C
	 552181, //  R =  55218.1 ; T =  -10 *C
	 583099, //  R =  58309.9 ; T =  -11 *C
	 615964, //  R =  61596.4 ; T =  -12 *C
	 650911, //  R =  65091.1 ; T =  -13 *C
	 688086, //  R =  68808.6 ; T =  -14 *C
	 727646, //  R =  72764.6 ; T =  -15 *C
	 769760, //  R =  76976.0 ; T =  -16 *C
	 814609, //  R =  81460.9 ; T =  -17 *C
	 862390, //  R =  86239.0 ; T =  -18 *C
	 913315, //  R =  91331.5 ; T =  -19 *C
	 967611, //  R =  96761.1 ; T =  -20 *C
	1025525, //  R = 102552.5 ; T =  -21 *C
	1087322, //  R = 108732.2 ; T =  -22 *C
	1153290, //  R = 115329.0 ; T =  -23 *C
	1223737, //  R = 122373.7 ; T =  -24 *C
	1299000, //  R = 129900.0 ; T =  -25 *C
	1379441, //  R = 137944.1 ; T =  -26 *C
	1465451, //  R = 146545.1 ; T =  -27 *C
	1557456, //  R = 155745.6 ; T =  -28 *C
	1655915, //  R = 165591.5 ; T =  -29 *C
	1761325, //  R = 176132.5 ; T =  -30 *C
	1874227, //  R = 187422.7 ; T =  -31 *C
	1995206, //  R = 199520.6 ; T =  -32 *C
	2124897, //  R = 212489.7 ; T =  -33 *C
	2263988, //  R = 226398.8 ; T =  -34 *C
	2413229, //  R = 241322.9 ; T =  -35 *C
	2573431, //  R = 257343.1 ; T =  -36 *C
	2745480, //  R = 274548.0 ; T =  -37 *C
	2930336, //  R = 293033.6 ; T =  -38 *C
	3129044, //  R = 312904.4 ; T =  -39 *C
	3342744  //  R = 334274.4 ; T =  -40 *C
};

#define NTC10000_LENGTH sizeof NTC10000_R_table / sizeof(NTC10000_R_table[0])

// Temperature
volatile int16_t TempSens_T_Ch1;
volatile int16_t TempSens_T_Ch2;
volatile int16_t TempSens_T_Ch3;
// Resistance
volatile uint32_t TempSens_R_Ch1;
volatile uint32_t TempSens_R_Ch2;
volatile uint32_t TempSens_R_Ch3;
// State
volatile uint8_t TempSens_State[APP_TEMP_SENS_CHANNELS_MAX] = {0};

static uint8_t TempSens_Open_Cnt[APP_TEMP_SENS_CHANNELS_MAX] = {0};
static uint8_t TempSens_Short_Cnt[APP_TEMP_SENS_CHANNELS_MAX] = {0};

#ifdef VARIABLE_FILTER_LENGTH
static uint8_t actual_len[MEDIAN_FILTER_CHANNELS] = {0};
#endif	// VARIABLE_FILTER_LENGTH

#if MEDIAN_FILTER_ENABLED
static uint16_t Median_filter[MEDIAN_FILTER_CHANNELS][MEDIAN_FILTER_LENGTH];
static uint8_t Median_index[MEDIAN_FILTER_CHANNELS] = {0};
#endif

#if MEDIAN_FILTER_ENABLED
// calculate the median of a neighbour hood,
// the median is the middle value of a shell sorted list of numbers.
static void Median_sort(uint16_t *data, uint8_t channel)
{
	uint16_t value;
	uint8_t i, j;

#ifdef VARIABLE_FILTER_LENGTH
	// store new input value
	Median_filter[channel][Median_index[channel]] = *data;
	// modify qty of samples
	if(actual_len[channel] < MEDIAN_FILTER_LENGTH) {
		actual_len[channel]++;	// 0 - 10
	}
	// sort of all values
	for(i=0; i < actual_len[channel]; i++) {
		j = i;
		value = Median_filter[channel][i];
		while((j != 0) && (Median_filter[channel][j - 1] > value)) {
			Median_filter[channel][j] = Median_filter[channel][j - 1];
			j--;
		}
		Median_filter[channel][j] = value;
	}
	// get the middle value
	if (actual_len[channel] & 0x01)
		*data = Median_filter[channel][actual_len[channel] / 2];
	else
		*data = (Median_filter[channel][(actual_len[channel] / 2) - 1] + Median_filter[channel][(actual_len[channel] / 2)]) / 2;
	// modify index of median table
	Median_index[channel]++;
	if (Median_index[channel] >= MEDIAN_FILTER_LENGTH) {
		Median_index[channel] = 0;
	}
#else	// VARIABLE_FILTER_LENGTH
	// store new input value
	Median_filter[channel][Median_index[channel]] = *data;
	// sort of all values
	for(i=0; i < MEDIAN_FILTER_LENGTH; i++) {
		j = i;
		value = Median_filter[channel][i];
		while((j != 0) && (Median_filter[channel][j - 1] > value)) {
			Median_filter[channel][j] = Median_filter[channel][j - 1];
			j--;
		}
		Median_filter[channel][j] = value;
	}
	// get the middle value
#if (MEDIAN_FILTER_LENGTH & 0x01)
	*data = Median_filter[channel][MEDIAN_FILTER_LENGTH / 2];
#else
	*data = (Median_filter[channel][(MEDIAN_FILTER_LENGTH / 2) - 1] + Median_filter[channel][(MEDIAN_FILTER_LENGTH / 2)]) / 2;
#endif
	// modify index of median table
	Median_index[channel]++;
	if (Median_index[channel] >= MEDIAN_FILTER_LENGTH) {
		Median_index[channel] = 0;
	}
#endif	// VARIABLE_FILTER_LENGTH
}
#endif	// MEDIAN_FILTER_ENABLED

// Outputs round(int/10)
static int16_t SigIntRoundDiv_by10(int16_t value)
{
	int32_t rd;

	rd = (int32_t)value;
	if (rd < 0)
		rd = (rd-5)/10;
	else
		rd = (rd+5)/10;
	return rd;
}

void App_TempSens_Init(void *Parameters)
{
	uint8_t channel;

	(void)Parameters;
	for(channel = 0; channel < APP_TEMP_SENS_CHANNELS_MAX; channel++) {
		TempSens_State[channel] = 0;
		TempSens_Open_Cnt[channel] = 0;
		TempSens_Short_Cnt[channel] = 0;
	}
}

static int16_t Process_One_Channel(uint8_t channel, uint16_t adc_value)
{
	uint16_t median_value;
	uint32_t Rx, Rntc;
	uint8_t i, NTC_index;
	const uint32_t *pt_measure_table;
	int32_t T_coarse, T_fract, T_fine;

	median_value = adc_value;
#if MEDIAN_FILTER_ENABLED
	Median_sort(&median_value, channel);
#endif
	// Computing parallel resistance value of thermo-element and ADC input impedance
	// Rx = R_upper / ((4096 / x) - 1)
	Rx = (R_UPPER * R_SCALER * R_PREC) / ((((ADC_MAX_VALUE + 1) * R_SCALER) / median_value) - (1 * R_SCALER));
	// Computing thermo-element resistance value
#if 1	// Without needed OPAMP buffer on the ADC input
	// Rntc = (Rx * Rimp) / (Rimp - Rx)
	Rntc = ((uint64_t)Rx * ADC_IMPEDANCE) / (ADC_IMPEDANCE - Rx);
#else
	Rntc = Rx;
#endif
	switch(channel) {
		case APP_TEMP_SENS_CHANNEL_1:
			TempSens_R_Ch1 = Rntc;
			break;
		case APP_TEMP_SENS_CHANNEL_2:
			TempSens_R_Ch2 = Rntc;
			break;
		case APP_TEMP_SENS_CHANNEL_3:
			TempSens_R_Ch3 = Rntc;
			break;
	}
	// Checking of Short or Open Failures
	if(TempSens_State[channel] & APP_TEMP_SENS_READY) {	// Sensor is Ready
		if(Rntc < R_LOW_LIMIT) {		// Short ?
			if(!(TempSens_State[channel] & APP_TEMP_SENS_FAILURE_SHORT)) {
				if(TempSens_Short_Cnt[channel] < ADC_FAILURE_CNT) {
					if(TempSens_Short_Cnt[channel] == (ADC_FAILURE_CNT - 1)) {
						TempSens_State[channel] |= APP_TEMP_SENS_FAILURE_SHORT;
						// sendLog("Temperature sensor %d Short Failure - On\n", channel);
					}
					TempSens_Short_Cnt[channel]++;
				}
			}
		} else {			// Not short
			if(TempSens_State[channel] & APP_TEMP_SENS_FAILURE_SHORT) {
				if(TempSens_Short_Cnt[channel] > 0) {
					if(TempSens_Short_Cnt[channel] == 1) {
						TempSens_State[channel] &= ~APP_TEMP_SENS_FAILURE_SHORT;
						// sendLog("Temperature sensor %d Short Failure - Off\n", channel);
					}								
					TempSens_Short_Cnt[channel]--;
				}
			}
		}
		if(Rntc > R_HIGH_LIMIT) {	// Open ?
			if(!(TempSens_State[channel] & APP_TEMP_SENS_FAILURE_OPEN)) {
				if(TempSens_Open_Cnt[channel] < ADC_FAILURE_CNT) {
					if(TempSens_Open_Cnt[channel] == (ADC_FAILURE_CNT - 1)) {
						TempSens_State[channel] |= APP_TEMP_SENS_FAILURE_OPEN;
						// sendLog("Temperature sensor %d Open Failure - On\n", channel);
					}								
					TempSens_Open_Cnt[channel]++;
				}
			}
		} else {			// Not open
			if (TempSens_State[channel] & APP_TEMP_SENS_FAILURE_OPEN) {
				if(TempSens_Open_Cnt[channel] > 0) {
					if(TempSens_Open_Cnt[channel] == 1) {
						TempSens_State[channel] &= ~APP_TEMP_SENS_FAILURE_OPEN;
						// sendLog("Temperature sensor %d Open Failure - Off\n", channel);
					}								
					TempSens_Open_Cnt[channel]--;
				}
			}
		}
		// 
	}
	// Search the temperature index in the resistance table
	NTC_index = 0;
	pt_measure_table = NTC10000_R_table;
	for(i = 0; i < NTC10000_LENGTH; i++) {
		if (Rntc >= *pt_measure_table)
			NTC_index = i;
		else
			break;
		pt_measure_table++; 
	}
	// Compute the temperature value
	T_coarse = ((int32_t)T_START * T_PREC) - ((int32_t)NTC_index * (T_STEP * T_PREC));
	T_fract = ((Rntc - NTC10000_R_table[NTC_index]) * T_STEP * T_PREC
			/ (NTC10000_R_table[NTC_index + 1] - NTC10000_R_table[NTC_index]));
	T_fine = T_coarse - T_fract;
	T_fine = SigIntRoundDiv_by10(T_fine); // Div by 10 with Rounding
	return (int16_t)T_fine;
}

void App_TempSens_Process(void *Parameters)
{
	static uint8_t channel = APP_TEMP_SENS_CHANNEL_1;
	static uint16_t timeout = (MEDIAN_FILTER_LENGTH * 3 / 2);
	static uint16_t Timer_Last_Value = 0;
	uint16_t Timer_Current_Value = *(uint16_t*)Parameters; 
	uint16_t adc_value;
	int16_t Temp;

	if(Timer_Last_Value != Timer_Current_Value) {				// Enter each 1ms Tick
		Timer_Last_Value = Timer_Current_Value;
		switch(channel) {
			case APP_TEMP_SENS_CHANNEL_1:
				adc_value = ADC_T1_RAW;
				Temp = Process_One_Channel(channel, adc_value);
				if(TempSens_State[APP_TEMP_SENS_CHANNEL_1] & APP_TEMP_SENS_FAILURE_OPEN)
					Temp = INT16_MIN;
				else if (TempSens_State[APP_TEMP_SENS_CHANNEL_1] & APP_TEMP_SENS_FAILURE_SHORT)
					Temp = INT16_MAX;
				TempSens_T_Ch1 = Temp;
				break;
			case APP_TEMP_SENS_CHANNEL_2:
				adc_value = ADC_T2_RAW;
				Temp = Process_One_Channel(channel, adc_value);
				if(TempSens_State[APP_TEMP_SENS_CHANNEL_2] & APP_TEMP_SENS_FAILURE_OPEN)
					Temp = INT16_MIN;
				else if (TempSens_State[APP_TEMP_SENS_CHANNEL_2] & APP_TEMP_SENS_FAILURE_SHORT)
					Temp = INT16_MAX;
				TempSens_T_Ch2 = Temp;
				break;
			case APP_TEMP_SENS_CHANNEL_3:
				adc_value = ADC_T3_RAW;
				Temp = Process_One_Channel(channel, adc_value);
				if(TempSens_State[APP_TEMP_SENS_CHANNEL_3] & APP_TEMP_SENS_FAILURE_OPEN)
					Temp = INT16_MIN;
				else if (TempSens_State[APP_TEMP_SENS_CHANNEL_3] & APP_TEMP_SENS_FAILURE_SHORT)
					Temp = INT16_MAX;
				TempSens_T_Ch3 = Temp;
				if(timeout > 0)
					timeout--;
				break;
			default:
				adc_value = 0;
				break;
		}
		channel++;
		if(channel >= APP_TEMP_SENS_CHANNELS_MAX)
			channel = APP_TEMP_SENS_CHANNEL_1;
		if(timeout == 1) {
			TempSens_State[channel] |= APP_TEMP_SENS_READY;
		}
	} 
}
