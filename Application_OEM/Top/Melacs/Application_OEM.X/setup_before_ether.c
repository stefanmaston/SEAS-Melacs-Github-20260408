/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2012 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
#define _SUPPRESS_PLIB_WARNING
#include <sys.h>
#include <plib.h>
#include <p32xxxx.h>
#include "configurations.h"
#include "main.h"


#define DEBUG_TO_BUF	1 			// 1 - xprintf will printout debug information to
						  			//     debug memory buffer ?debug_buffer?

						  			// 0 - xprintf will printout debug information to
						  			//     serial port (UART). Do not use this options, when using TTY server in your demo!
#define DEBUG_BUFSIZE	128			// Size for ?debug_buffer? in bytes


#if DEBUG_TO_BUF == 0
void DBG_UARTInit();
#endif

#define SYSSTK	1024
char _isr_stack[SYSSTK] __attribute__(( __aligned__(8)));


#define VCCout_ON_DIR TRISAbits.TRISA0
#define VCCout_ON LATAbits.LATA0

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

	DDPCONbits.JTAGEN = 0;		//Disable JTAG

        // configure the proper PB frequency and the number of wait states
        SYSTEMConfigWaitStates(72000000L);
        CheKseg0CacheOn();// enable the cache for the best performance
        mBMXDisableDRMWaitState(); // no wait states for RAM
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
    //------ fat-fsys function  -------//
	sd_disk_timerproc();
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

 //led port init
#ifdef _USE_EXP16
	LATA = 0xFF00;
	TRISA = 0xFF00;
#endif
}



void sd_pictail_init(void)
{
    TRISFbits.TRISF5 = 0;     // make Card select an output pin
    PORTFbits.RF5 = 1;
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
	OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, CORE_TIMER_PERIOD); //Set Interrupt interval 2ms
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);


	#if DEBUG_TO_BUF == 0
	DBG_UARTInit();
	#endif

        VCCout_ON_DIR = 0;
        VCCout_ON = 1;

	sd_pictail_init();

	hw_processor_init_pic32();

}



/*****************************************************************************
 * Function: UARTInit
 * Precondition: None.
 * Overview: Setup UART module.
 * Input: None.
 * Output: None.
 *****************************************************************************/
#if DEBUG_TO_BUF == 0
void DBG_UARTInit()
{
#ifdef  _USE_ESK
 	// Open UART1 with Transmitter enable.
	OpenUART1(UART_EN, UART_TX_ENABLE, BAUD_VALUE);
#elif   _USE_EXP16
        OpenUART2(UART_EN, UART_TX_ENABLE, BAUD_VALUE);
#endif

}
#else
	uchar debug_buffer[DEBUG_BUFSIZE];
	static int debug_index=0;
#endif

//TODO writing printf to a file
void xputchar (const int c)
{
	#if DEBUG_TO_BUF == 0
            #ifdef _USE_ESK
                putcUART1(c);	/* Write data into Uart Tx. */
            #elif  _USE_EXP16
                putcUART2(c);	/* Write data into Uart Tx. */
            #endif
	#else
		debug_buffer[debug_index]=(uchar)c;
 		if (++debug_index >= DEBUG_BUFSIZE) debug_index = 0;
	#endif
}


