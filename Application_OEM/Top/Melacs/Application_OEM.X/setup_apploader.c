/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2011 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
*                           ALL RIGHTS RESERVED
*
*   This computer program is the property of RoweBots Research Inc.,
*   Kitchener, Ontario Canada. and may not be copied or redistributed in any 
*   form or by any means, whether in part or in whole, except under license 
*   granted by RoweBots Research Inc.
*
*   All copies of this program, whether in part or in whole, and whether 
*   modified or not, must display this and all other embedded copyright and 
*   ownership notices in full.  This notice may not be modified.
*
*   All source code is protected by international copyright laws and license
*   agreements.  Do not break the law.  You can obtain a license and source
*   code at rowebots.com subject to licensing conditions and restrictions.
*   Free development, free source code and free non commercial licenses may
*   be obtained in a few seconds on line without any difficult process.
*
*   All demonstration programs may be redistributed as source code to others  
*   as a small part of a Unison or DSPnano application. 
*
* ******************************************************************************   
*
*
*   Save Time and Money.  If you need modifications to the software to support
*   specific processors or peripherals, RoweBots Research can do this for you
*   quickly and easily at low cost.  If you need help with application develop-
*   ment, again we can solve your embedded development problems quickly and 
*   easily at very attractive prices.  We are tiny tiny embedded Linux* experts,
*   let us reduce your risk, accelerate your development and slash your time 
*   to market.  See rowebots.com - contact us.
*
*
*******************************************************************************/

#include <sys.h>
#include <plib.h>
#include <p32xxxx.h>
#include "main.h"

#define DEBUG_TO_BUF	0 			// 1 - xprintf will printout debug information to 
						  			//     debug memory buffer “debug_buffer” 

						  			// 0 - xprintf will printout debug information to 
						  			//     serial port (UART). Do not use this options, when using TTY server in your demo!
#define DEBUG_BUFSIZE	128			// Size for “debug_buffer” in bytes

// Configuration Bit settings
// SYSCLK = 72 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 36 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_2

#define SYSCLK					(72000000)
#define PBCLK       			(SYSCLK/2)
#define DESIRED_BAUDRATE    	(115200)      		//The desired BaudRate 115200
#define BAUD_VALUE 	((PBCLK/16/DESIRED_BAUDRATE)-1) // calculate actual BAUD generate value.

#define CLOCK_TIME_PERIOD  2000000		// nanoseconds per tick - period 2ms
#define CORE_TIMER_PERIOD  72000		// PBCLK * 0.002s - tikcs per 2ms

#if DEBUG_TO_BUF == 0
void UART1Init();
#endif

void malloc_init();
void _isr_init();


#define SYSSTK	1024
char _isr_stack[SYSSTK] __attribute__(( __aligned__(8)));

/********************************************************************
 * Ethernet MII Enable bit [FMIIEN]
 * 
 * ON   - MII enabled, RMII disabled  
 * OFF  - MII disabled, RMII enabled  
 ********************************************************************/
#pragma config FMIIEN = OFF


/********************************************************************
 * Ethernet IO Pin Selection bit [FETHIO]
 * 
 * ON   - Default Ethernet IO Pins   
 * OFF  - Alternate Ethernet IO Pins  
 ********************************************************************/
#pragma config FETHIO = OFF


/* Never returns */
/**********************************************************************************
Function Name: 	main
Description:	setup hardware and start RTOS
Parameters: 	none
Return value: 	none
***********************************************************************************/
int main()
{
	/*disable all interrupt in interrupt controller */
	INTDisableInterrupts();

	DDPCONbits.JTAGEN = 1;		//Jtag Enable

	/* 1 - fill task stack by 'S' during initialization for debug purpose */
	pthreadStackFill = 1; 

	/* 1 - fill isr stack by 'I' during initialization for debug purpose*/
	_isrStackFill = 1; 

	/* initializes stack for interrupt */ 
	_isr_init(SYSSTK);

	// memory initialzation - uses xprintf, xpputchar
	malloc_init();

	/* all hardware initialization */
	hw_init();

	/* Start RTOS */
	Nano_Start();


	return 0;
}


/**********************************************************************************
Function Name: 	SysTickHandler
Description:	RTOS system timer with period = TICKS_PER_SEC
Parameters: 	arg - must be ignored
Return value: 	none
***********************************************************************************/
void T1InterruptBody (uint_32 arg)
{
	timer_tick(CLOCK_REALTIME); 			/******TIMER TICK******/
	mT1ClearIntFlag();                      // clear the interrupt flag

}


/**********************************************************************************
Function Name: 	hw_processor_init_cortexm3
Description:	Initializes RTOS clock and other hardware if need
Parameters: 	none
Return value: 	none
***********************************************************************************/
static void hw_processor_init_pic32()
{
	int iseterror; 
	clockid_t  my_timer_clockid; 
	struct timespec my_timespec;

	// processor specific initialization with clock
	// first setup the interrupt vector, clock parameters and then setup the timer hardware
	my_timespec.tv_sec = 0;
	my_timespec.tv_nsec = CLOCK_TIME_PERIOD; 
	my_timer_clockid = CLOCK_REALTIME;
	iseterror = clock_init(my_timer_clockid, &my_timespec);
	
	if(iseterror != 0) 
	{ 
		xprintf("clock_init error\n\r");
	}

    PORTSetPinsDigitalOut(IOPORT_D, BIT_2);
    PORTSetPinsDigitalOut(IOPORT_D, BIT_1);
    PORTClearBits(IOPORT_D, BIT_2);
    PORTSetBits(IOPORT_D, BIT_3);

}


void sd_pictail_init(void)
{
#if defined (SD_SPI1)
	//Card I/O's init
	TRISFbits.TRISF0 = 1;        // Card Detect input
	TRISFbits.TRISF1 = 1;        // Write Protect input

    _PCFG1 = 1;         	  // make Card select as digital pin
    TRISBbits.TRISB1 = 0;     // make Card select an output pin
	PORTBbits.RB1 = 1;
#elif defined (SD_SPI2)
	//Card I/O's init
	TRISGbits.TRISG0 = 1;        // Card Detect input
	TRISGbits.TRISG1 = 1;        // Write Protect input
   
    _PCFG9 = 1;         	  // make Card select as digital pin
	PORTBbits.RB9 = 1;
    TRISBbits.TRISB9 = 0;     // make Card select an output pin
#else
	#error You must define SPI for SD!
#endif
}


/**********************************************************************************
Function Name: 	hw_init
Description:This routine initializes the three aspects of the hardware
and enables interrupts.  The next immediate thing must be
to start the kernel so it can initialize before the first
timer interrupt occurs
Parameters: 	none
Return value: 	none
***********************************************************************************/
void hw_init(void)
{
   	// Set single vector mode
	INTEnableSystemSingleVectoredInt();
	INTDisableInterrupts();

	
	// Configure main timer
	i_set_interrupt(_TIMER_1_VECTOR, T1InterruptBody, 0);
	OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, 1125); //Set Interrupt interval 2ms 
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);

	#if DEBUG_TO_BUF == 0
	UART1Init();
	#endif

	sd_pictail_init();

	hw_processor_init_pic32();
}



/*****************************************************************************
 * Function: UART1Init
 * Precondition: None.
 * Overview: Setup UART1 module.
 * Input: None.
 * Output: None.
 *****************************************************************************/
#if DEBUG_TO_BUF == 0
void UART1Init()
{
 	// Open UART1 with Transmitter enable.
	OpenUART1(UART_EN, UART_TX_ENABLE, BAUD_VALUE);
}
#else
	uchar debug_buffer[DEBUG_BUFSIZE];
	static int debug_index=0;
#endif

void xputchar (const int c)
{
	#if DEBUG_TO_BUF == 0
		putcUART1(c);	/* Write data into Uart Tx. */
	#else
		debug_buffer[debug_index]=(uchar)c;
 		if (++debug_index >= DEBUG_BUFSIZE) debug_index = 0;
	#endif
}	



/*************************************/
/* Mandatory functions for tcpserver */
/*************************************/
// This function need for MII speed setup
unsigned long GetSystemClock(void)
{
	return SYSCLK;
}

int _ivfprintf()
{
	_nop();
}
