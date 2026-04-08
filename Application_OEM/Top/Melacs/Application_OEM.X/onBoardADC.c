/******************************************************************************
 *                                                                      	  *
 *        	AD-Converter Protocol for Access Microchip MCP3208 Device     	  *
 *                                                                      	  *
 *              		   Author: Finsun Inresol AB			              *
 ******************************************************************************
 * FileName:        AD_conveter.c											  *
 * Dependencies:	Real_time_clock.h spi.h inttypes.h						  *
 * Processor:       PIC18													  *
 * Complier:        MCC18 v3.13												  *
 * Description: 	Handles AD-Converter IC									  *
 *              		- AD-Converter (MCP3208)							  *
 ******************************************************************************/

//It is possible to sample faster by reducing the delay
#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _ONBOARD_ADC_FUNC_

#include <p32xxxx.h>
#include <time.h>
#include <stdint.h>
#include "delay.h"
#include <pthread.h>
#include "sd_spi.h"

//#include "inttypes.h"
//#include "OnboardADC.h"

#define CS_AD			LATGbits.LATG0
#define CS_AD_DIR		TRISGbits.TRISG0
#define SPICLK  		LATDbits.LATD15
#define SPICLK_DIR  		TRISDbits.TRISD15
#define SPIMISO 		PORTFbits.RF2
#define SPIMISO_DIR		TRISFbits.TRISF2
#define SPIMOSI 		PORTFbits.RF8
#define SPIMOSI_DIR 		TRISFbits.TRISF8

//** V A R I A B L E S ********************************************************/
uint16_t adcresult[8];

void ADC_SPIinit(void)
{
    AD1PCFG = 0;
    CS_AD = 1; 			CS_AD_DIR = 0;		// Standby mode

    SPICLK = 0;			SPICLK_DIR = 0;

    SPIMISO = 0;		SPIMISO_DIR = 1;
    SPIMOSI = 0;		SPIMOSI_DIR = 0;
}

//Test the DelayADC function
/*
void testADC()
{
    while(1)
    {
        SPICLK = 0;
        DelayADC(); //DelayUs(1);
        SPICLK = 1;
        DelayADC(); //DelayUs(1);
    }
}
*/

//** F U N C T I O N S ********************************************************/
// Write the channel channel, stopping just short of then next clock transition
// latching in a new A/D value
void ADCreadprepare(uint8_t channel)
{
	uint8_t i = 5 + 1;
	channel |= 0x18;

	do
	{
		// MSB first
		SPIMOSI = 0;
		if(channel & 0x10)
			SPIMOSI = 1;
		channel <<= 1;

		SPICLK = 0;
		DelayADC(); //DelayUs(1);
		CS_AD = 0;
		SPICLK = 1;
		DelayADC();
	}
	while(--i);
}

// Now clock out the 12 sampled bits from the pre-selected channel
uint16_t ADCreadextract(void)
{
	uint8_t i = 12 + 1;
	uint16_t result = 0;
	
	do
	{
        
		SPICLK = 0;
		DelayADC();
		SPICLK = 1;
		DelayADC();

		// MSB first
		result <<= 1;
		if(SPIMISO)
			result |= 1;
	}
	while(--i);

	CS_AD = 1;
	return result;
}

uint16_t ADCread(uint8_t channel)
{
	ADCreadprepare(channel);
	return ADCreadextract();
}

void ADCreadall(uint16_t all[8])
{
	int8_t i;

	for(i = 0; i < 8; ++i)
    {
        SPI_Clear();
		*all++ = ADCread(i);
    }
	
}

#ifdef UNUSED
void ReadExternalADC(void)
{
	uint8_t channel;
	
	for(channel = 0; channel < 8; ++channel)
	{
		ADCreadprepare(channel);
		adcresult[channel] = ADCreadextract();
	}
}
#endif

//*****************************************************************************/

#endif