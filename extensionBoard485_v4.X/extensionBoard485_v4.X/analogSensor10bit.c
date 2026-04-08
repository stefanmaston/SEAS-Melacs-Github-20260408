/********************************************************************
Super simple Analog Input with POT.
********************************************************************/
#define _SUPPRESS_PLIB_WARNING
#include "main.h"
#ifdef _ANALOGSENSOR10BIT_FUNC_

#include <plib.h>

unsigned short int channel3;	// conversion result as read from result buffer

int analog_sensor_10bit_init(void)
{
	// configure and enable the ADC
	CloseADC10();	// ensure the ADC is off before setting the configuration

	// define setup parameters for OpenADC10
				// Turn module on | output in integer | trigger mode auto | enable  autosample
	#define PARAM1  ADC_MODULE_ON | ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON

	// define setup parameters for OpenADC10
			    // ADC ref external    | disable offset test    | enable scan mode | perform 2 samples | use one buffer | use MUXA mode
       // note: to read X number of pins you must set ADC_SAMPLES_PER_INT_X
	#define PARAM2  ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_ON | ADC_SAMPLES_PER_INT_10 | ADC_ALT_BUF_OFF | ADC_ALT_INPUT_OFF

	// define setup parameters for OpenADC10
	// 				  use ADC internal clock | set sample time
	#define PARAM3  ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15

	// define setup parameters for OpenADC10
				// set AN4 and AN5
	#define PARAM4	ENABLE_AN0_ANA | ENABLE_AN1_ANA | ENABLE_AN2_ANA | ENABLE_AN3_ANA | ENABLE_AN4_ANA | ENABLE_AN5_ANA | ENABLE_AN10_ANA | ENABLE_AN13_ANA | ENABLE_AN14_ANA | ENABLE_AN15_ANA

	// define setup parameters for OpenADC10
	// do not assign channels to scan
	//#define PARAM5	SKIP_SCAN_AN0 | SKIP_SCAN_AN1 | SKIP_SCAN_AN2 | SKIP_SCAN_AN4 | SKIP_SCAN_AN5    | SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN10 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12 | SKIP_SCAN_AN13 | SKIP_SCAN_AN14 | SKIP_SCAN_AN15
        #define PARAM5	  SKIP_SCAN_AN6 | SKIP_SCAN_AN7 | SKIP_SCAN_AN8 | SKIP_SCAN_AN9 | SKIP_SCAN_AN11 | SKIP_SCAN_AN12

	// use ground as neg ref for A
	SetChanADC10( ADC_CH0_NEG_SAMPLEA_NVREF); // use ground as the negative reference
	OpenADC10( PARAM1, PARAM2, PARAM3, PARAM4, PARAM5 ); // configure ADC using parameter define above

	EnableADC10(); // Enable the ADC

	while ( ! mAD1GetIntFlag() ) { } // wait for the first conversion to complete so there will be valid data in ADC result registers
}


unsigned int read_board_temperature()
{
    //return ReadADC10(0);  		// read the result of channel 3
    return ReadADC10(3);  		// read the result of channel 3
}

unsigned int read_analog_DIO7()
{
    return ReadADC10(2);  		// read the result of channel 2
}

unsigned int read_analog_DIO6()
{
    return ReadADC10(1);  		// read the result of channel 1
}

unsigned int read_analog_DIO5()
{
    return ReadADC10(0);  		// read the result of channel 0
}

unsigned int read_analog_M2CUR()
{
    return ReadADC10(4);  		// read the result of channel 4
}

unsigned int read_analog_M1CUR()
{
    return ReadADC10(5);  		// read the result of channel 5
}

unsigned int read_analog_M2VOLT()
{
    return ReadADC10(6);  		// read the result of channel 10
}

unsigned int read_analog_M1VOLT()
{
    return ReadADC10(7);  		// read the result of channel 13
}

unsigned int read_analog_M2CUR_H()
{
    return ReadADC10(8);  		// read the result of channel 14
}

unsigned int read_analog_M1CUR_H()
{
    return ReadADC10(9);  		// read the result of channel 15
}

#endif