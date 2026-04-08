/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2014 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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


#define DEBUG_TO_BUF	0	// 1 - xprintf will printout debug information to
							//     debug memory buffer “debug_buffer”
							// 0 - xprintf will printout debug information to
							//     serial port (UART). Do not use this options, when using TTY server in your demo!

#define DEBUG_BUFSIZE	1024	// Size for “debug_buffer” in bytes

#define _USE_CACHE 		1		// 1/0 enable/disable Pic32 cache


// Configuration Bit settings
// SYSCLK = 72 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 36 MHz
// Primary Osc w/PLL (OFF,RC+PLL)
// WDT OFF
// Other options are don't care
#pragma config FPLLMUL = MUL_18, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = OFF, FNOSC = FRCPLL, FPBDIV = DIV_2

#define SYSCLK				(72000000)
#define PBCLK				(SYSCLK/2)

#define CLOCK_TIME_PERIOD	2000000                  // nanoseconds per tick - period 2ms
#define CORE_TIMER_PERIOD	((PBCLK/64)/500)         // (PBCLK / 64) * 0.002s - ticks per 2ms

#define DESIRED_BAUDRATE	(115200)      		//The desired BaudRate 115200
#define BAUD_VALUE			((PBCLK/16/DESIRED_BAUDRATE)-1) // calculate actual BAUD generate value.


#if DEBUG_TO_BUF == 0
void DBG_UARTInit();
#endif

#define SYSSTK	1024
char _isr_stack[SYSSTK] __attribute__(( __aligned__(8)));

extern void encx24j600_int(uint_32 arg);
void enc424j600_init();
void Led_TOGGLE(char num);

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

#if _USE_CACHE  > 0
	// configure the proper PB frequency and the number of wait states
	SYSTEMConfigWaitStates(72000000L);
	CheKseg0CacheOn();// enable the cache for the best performance
	mBMXDisableDRMWaitState(); // no wait states for RAM
#endif

	/* 1 - fill task stack by 'S' during initialization for debug purpose */
	pthreadStackFill = 1; 

	/* 1 - fill isr stack by 'I' during initialization for debug purpose*/
	_isrStackFill = 1;

	/* initializes stack for interrupt */ 
	_isr_init(SYSSTK);

	// memory initialzation - uses xprintf, xputchar
	malloc_init();

	/* all hardware initialization */
	hw_init();

	/* Start RTOS */
	Nano_Start();

	return 0;
}

int led = 0;
int encint = 0;
/**********************************************************************************
Function Name: 	SysTickHandler
Description:	RTOS system timer with period = TICKS_PER_SEC
Parameters: 	arg - must be ignored
Return value: 	none
***********************************************************************************/
void TInterruptBody (uint_32 arg)
{
	timer_tick(CLOCK_REALTIME); 			/******TIMER TICK******/

	// clear the interrupt flag
	mT1ClearIntFlag();
	if(led == (1000000000ul / CLOCK_TIME_PERIOD) / 2) {		//Every 500 ms
		led = 0;
		Led_TOGGLE(2);
	}
	else
		led++;
	if(encint >= (1000000000ul / CLOCK_TIME_PERIOD) / 50) {	//Every 10 ms
		encint = 0;
		encx24j600_int(0);
	}
	else
		encint++;
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
	LATF = 0xFFFD;
	TRISF = 0xFFFD;
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
	i_set_interrupt(_TIMER_1_VECTOR, TInterruptBody, 0);
	OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, CORE_TIMER_PERIOD); //Set Interrupt interval 2ms
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);

	#if DEBUG_TO_BUF == 0
	DBG_UARTInit();
	#endif

	hw_processor_init_pic32();

	enc424j600_init();
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
    // Open UART1 with Transmitter enable.
	UARTSetLineControl(UART3, (UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1));
	UARTSetFifoMode(UART3, UART_INTERRUPT_ON_TX_DONE);
	UARTSetDataRate(UART3, PBCLK, DESIRED_BAUDRATE);
	UARTEnable(UART3, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_TX));
}
#else
	uchar debug_buffer[DEBUG_BUFSIZE];
	static int debug_index=0;
#endif

void xputchar (const int c)
{
#if DEBUG_TO_BUF == 0
	while(!UARTTransmitterIsReady(UART3)) ;
	UARTSendDataByte(UART3, c);
#else
    debug_buffer[debug_index]=(uchar)c;
    if (++debug_index >= DEBUG_BUFSIZE) debug_index = 0;
#endif
}	

void Led_TOGGLE(char num)
{
    if(num) {
            PORTF ^= (1 << (num-1));
    }
}

/*************************************/
/* Mandatory functions for tcpserver */
/*************************************/
// This function need for MII speed setup
unsigned long GetSystemClock(void)
{
	return SYSCLK;
}


/*****************************************************************************
 * SPI functions
 *****************************************************************************/
#define ENC_MAX_SPI_FREQ (14000000ul)

// ENC28J60 connect to SPI2
#define ENC_SPIBRG			(SPI3BRG)
#define ENC_SPICON			(SPI3CON)
#define ENC_SPICONbits		(SPI3CONbits)
#define ENC_SPISTATbits		(SPI3STATbits)
#define ENC_SPIBUF			(SPI3BUF)

#define ENC_CS_TRIS			(TRISAbits.TRISA6)
#define ENC_CS_IO			(PORTAbits.RA6)
#define ENC_INT_TRIS		(TRISEbits.TRISE8)
#define ENC_INT_IO			(PORTEbits.RE8)


// Set up the SPI module on the PIC for communications with the ENC424J600
void enc424j600_init()
{
	SpiChnOpen(SPI_CHANNEL3, SPI_OPEN_MSTEN|SPI_OPEN_SMP_END|SPI_OPEN_CKE_REV|SPI_OPEN_MODE8, PBCLK/14000000);

	ENC_CS_IO = 1;
	ENC_CS_TRIS = 0;		// Make the Chip Select pin an output

	ENC_INT_IO = 0;
	ENC_INT_TRIS = 1;		// Make the INT pin an input
	ENC_INT_IO = 1;
}


/*************************************
Mandatory functions for tcpserver
This function use by tcpserver to set/reset CS
*************************************/

void enc_cs_pin(int set)
{
	if (set)
		ENC_CS_IO = 1;
	else
		ENC_CS_IO = 0;
}

// Write data to ENC28J60
void _Spi_putc(int data)
{
	/* wait until there's room in the buffer and send the byte */
	SpiChnPutC(SPI_CHANNEL3, (unsigned int)data);
}

// Read data from ENC28J60
int _Spi_getc(void)
{
	int data;

	/* wait until there's data in the buffer and receive it */
	data = (int)SpiChnGetC(SPI_CHANNEL3);
	return data;
}
