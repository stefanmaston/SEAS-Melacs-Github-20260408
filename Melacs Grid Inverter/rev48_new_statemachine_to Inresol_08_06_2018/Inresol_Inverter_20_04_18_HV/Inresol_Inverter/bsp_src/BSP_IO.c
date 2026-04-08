/*
 *  File name: BSP_IO.c
 *
 *  Description: Board Support Package function implementations for IO processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

void BSP_IO_Pins_DeInit(void)
{
	// Configure all analog ports as digital I/O
	ANSELA = 0x0;
	ANSELB = 0x0;
#ifdef DSPIC_7XX_FAMILY
	ANSELC = 0x0;
	ANSELD = 0x0;
#endif

#if 1
	ODCA = 0x0;
	ODCB = 0x0;
	ODCC = 0x0;
	ODCD = 0x0;

	CNENA = 0x0;
	CNENB = 0x0;
	CNENC = 0x0;
	CNEND = 0x0;
	CNPDA = 0x0;
	CNPDB = 0x0;
	CNPDC = 0x0;
	CNPDD = 0x0;
	CNPUA = 0x0;
	CNPUB = 0x0;
	CNPUC = 0x0;
	CNPUD = 0x0;
#endif

	// Configure all PWM ports as digital I/O
	IOCON1bits.PENH = 0;		// PWM1H pin is controlled by GPIO module
	IOCON1bits.PENL = 0;		// PWM1L pin is controlled by GPIO module
	IOCON2bits.PENH = 0;		// PWM2H pin is controlled by GPIO module
	IOCON2bits.PENL = 0;		// PWM2L pin is controlled by GPIO module
	IOCON3bits.PENH = 0;		// PWM3H pin is controlled by GPIO module
	IOCON3bits.PENL = 0;		// PWM3L pin is controlled by GPIO module
	IOCON4bits.PENH = 0;		// PWM4H pin is controlled by GPIO module
	IOCON4bits.PENL = 0;		// PWM4L pin is controlled by GPIO module
	IOCON5bits.PENH = 0;		// PWM5H pin is controlled by GPIO module
	IOCON5bits.PENL = 0;		// PWM5L pin is controlled by GPIO module
	IOCON6bits.PENH = 0;		// PWM6H pin is controlled by GPIO module
	IOCON6bits.PENL = 0;		// PWM6L pin is controlled by GPIO module

	// Configure all digital I/O pins as inputs
	TRISA = 0xFFFF;
	TRISB = 0xFFFF;
#ifdef DSPIC_7XX_FAMILY
	TRISC = 0xFFFF;
	TRISD = 0xFFFF;
#endif
}

void BSP_IO_Pins_Init(void)
{
	// Configure pins as inputs or outputs
#ifdef GPIO_LED_1_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_LED_1_PORTPIN);	// Configures pin LED_1 as output
	BSP_IO_GPIO_SET(GPIO_LED_1_PORTPIN);		// LED_1 Off
#endif
#ifdef GPIO_LED_2_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_LED_2_PORTPIN);	// Configures pin LED_2 as output
	BSP_IO_GPIO_SET(GPIO_LED_2_PORTPIN);		// LED_2 Off
#endif
#ifdef GPIO_LED_3_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_LED_3_PORTPIN);	// Configures pin LED_3 as output
	BSP_IO_GPIO_SET(GPIO_LED_3_PORTPIN);		// LED_3 Off
#endif
#ifdef GPIO_LED_4_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_LED_4_PORTPIN);	// Configures pin LED_4 as output
	BSP_IO_GPIO_SET(GPIO_LED_4_PORTPIN);		// LED_4 Off
#endif
#ifdef GPIO_LED_HB_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_LED_HB_PORTPIN);	// Configures pin LED_HB as output
	BSP_IO_GPIO_SET(GPIO_LED_HB_PORTPIN);		// LED_HB Off
#endif
#ifdef GPIO_TST1_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_TST1_PORTPIN);		// Configures pin TST1 as output
	BSP_IO_GPIO_CLR(GPIO_TST1_PORTPIN);			// TST1 Low
#endif
#ifdef GPIO_TST2_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_TST2_PORTPIN);		// Configures pin TST2 as output
	BSP_IO_GPIO_CLR(GPIO_TST2_PORTPIN);			// TST2 Low
#endif
#ifdef GPIO_TST3_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_TST3_PORTPIN);		// Configures pin TST3 as output
	BSP_IO_GPIO_CLR(GPIO_TST3_PORTPIN);			// TST3 Low
#endif
}