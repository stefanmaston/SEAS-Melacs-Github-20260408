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
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <sys.h>
#include <plib.h>
#include <p32xxxx.h>
#include "configurations.h"
#include "main.h"
#include "mutex.h"
#include <mrendez.h>
#include <sys/interrupt.h>
#include "uart.h"
#include "sd_spi.h"


uint_32 spi_active = 0;
int stat = 0;
extern int g_flag_sd;
pthread_mutex_t		spi_mutex;
pthread_mutex_t     testmutex_test;
#define SYSSTK	1024
char _isr_stack[SYSSTK] __attribute__(( __aligned__(8)));



#ifdef _ETHERNET_
extern void encx24j600_int(uint_32 arg);
extern int g_write_protect_sd;

void enc424j600_init();
void Led_TOGGLE(char num);
void T3Interrupt(uint_32 arg);
int read_pin_rg15(void);

void spi_ether_conf(void);
#endif

#define VCCout_ON_DIR TRISAbits.TRISA0
#define VCCout_ON LATAbits.LATA0

#define  DEBUG_TO_BUF   1 /*If DEBUG_TO_BUF is equal to 0, you should comment _UART_ in main.h otherwise uncomment _UART_ in main.h since they share same UART channel*/

#if  DEBUG_TO_BUF == 0
void DBG_UARTInit();
void DebugMessageOnUART5(const char *string);
#endif
bool testpoint = false;

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

#ifdef _ETHERNET_
int led = 0;
int encint = 0;
int res_unlock = 0;
int pin = 0;
#endif
/**********************************************************************************
Function Name: 	SysTickHandler
Description:	RTOS system timer with period = TICKS_PER_SEC
Parameters: 	arg - must be ignored
Return value: 	none
***********************************************************************************/
void T1InterruptBody (uint_32 arg)
{
    //MEMLED = ~MEMLED;
    //sched_yield();
 
    timer_tick(CLOCK_REALTIME); 			/******TIMER TICK******/
    
    mT1ClearIntFlag();                      // clear the interrupt flag
    //------ fat-fsys function  -------//
    sd_disk_timerproc();
    
#ifdef _ETHERNET_
    
    if(led == (1000000000ul / CLOCK_TIME_PERIOD) / 2) {		//Every 500 ms
            led = 0;
            Led_TOGGLE(2);
    }
    else
    {
        led++;
    }
    if(encint >= (1000000000ul / CLOCK_TIME_PERIOD) / 50) {	//Every 10 ms
            encint = 0;
            //encx24j600_int(0);
            
    }
    else
    {
            encint++;
    }
#endif
}
#ifdef _ETHERNET_
void T3Interrupt(uint_32 arg)
{
    encx24j600_int(0);
	mT3ClearIntFlag();
   
}
#endif
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
#ifdef _ETHERNET_
 //led port init
        AD1PCFG = 0; 
        TRISFbits.TRISF1 = 0;
        LATFbits.LATF1 = 0;
        
        
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
	INTConfigureSystem(INT_SYSTEM_CONFIG_SINGLE_VECTOR);
            
    #if DEBUG_TO_BUF == 0
	DBG_UARTInit();
	#endif
    
    // INITIALIZATION OF RS485 pins 
    TRISDbits.TRISD5 = 0;            // Direction Output  RAN485EN IN PORTD RD5 in PIC32MX795512L JP27P2   
    TRISFbits.TRISF3   =0;         // Direction Output   REC485EN RF3
    PORTFbits.RF3 = 1; //Activate Receiver. From Inverter Active == 0; Deactive == 1
    PORTDbits.RD5 = 0; // Activate the Transmitter To Inverter Active ==1 deactive ==0 

    i_set_interrupt(_TIMER_1_VECTOR, T1InterruptBody, 0);
	OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, CORE_TIMER_PERIOD); //Set Interrupt interval 2ms
	ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_1);

    LED1_DIR = 0;
    LED1 = 0;
    
    LED3_DIR = 0;
    LED3  = 0;
    
    LED4_DIR = 0;
    LED4 = 0;
    
    LED2_DIR = 0;
    LED2 = 0;
    
    VCCout_ON_DIR = 0;
    VCCout_ON = 1 ;
    spiMutexInit();
    
    bufWriteMutexInit();
    bufReadMutexInit();
    speedControlMutexInit();
	sd_pictail_init();
    
    //dir_register("mutex", (uint)&testmutex_test, TYPE_MUTEX);
    
    TEST_MUTEX_INIT
	hw_processor_init_pic32();

#ifdef _ETHERNET_
    //uptime(NULL); //Added by Bala //Else some problem linking with the uptime function
    TEST_MUTEX_INIT
    enc424j600_init();  
    i_set_interrupt(_TIMER_3_VECTOR, T3Interrupt, 0);
	OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, CORE_TIMER_PERIOD*10); //Set Interrupt interval 20ms 
	ConfigIntTimer3(T3_INT_OFF | T3_INT_PRIOR_3 | T3_INT_SUB_PRIOR_0);
    
#endif

}

#if DEBUG_TO_BUF == 0
        void DBG_UARTInit()
        {
              //OpenUART1(UART_EN, UART_TX_ENABLE, BAUD_VALUE);
      
            U5MODEbits.ON = 0;
            UARTConfigure(UART5, UART_ENABLE_PINS_TX_RX_ONLY);
            UARTSetFifoMode(UART5, UART_INTERRUPT_ON_TX_BUFFER_EMPTY | UART_INTERRUPT_ON_RX_NOT_EMPTY);
            UARTSetLineControl(UART5, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
            UARTSetDataRate(UART5, PBCLK, DESIRED_BAUDRATE);
            UARTEnable(UART5, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));
            /*Tris have to be set in order to get information in Extension Board RS485*/
            TRISDbits.TRISD5 = 0;		    // Direction Output
            TRISFbits.TRISF3   =0;  
            LATDbits.LATD5 = 1; // Activate the Transmitter
            LATFbits.LATF3 = 0; //Activate Receiver.
            
            /*End of Tris Configuration*/
            
            U5MODEbits.ON = 1;
            DebugMessageOnUART5("*********************** Debug Has Activated on RS485**************************\r\n");
 
        }
#endif
        
        void xputchar (const int c)
{
	#if DEBUG_TO_BUF == 0
            
                //putcUART1(c);	/* Write data into Uart Tx. */
                do{while(!U5STAbits.TRMT);  U5TXREG = (c);}while(0);
               
	#endif
}
        
void DebugMessageOnUART5(const char *string)
{
    while(*string != '\0')
    {
        while(!UARTTransmitterIsReady(UART5))
            ;

        UARTSendDataByte(UART5, *string);
        //putcUART1(c)
        string++;

        while(!UARTTransmissionHasCompleted(UART5))
            ;
    }
}
#ifdef _ETHERNET_
void Led_TOGGLE(char num)
{
 /*  if(num)
    {
        PORTF ^= (1 << (num-1));
    }
 */
}

        
/*************************************/
/* Mandatory functions for tcpserver */
/*************************************/
// This function need for MII speed setup

/*unsigned long GetSystemClock(void)
{
	return SYSCLK;
}*/


int read_pin_rg15(void){

    //PORTReadBits(IOPORT_G, BIT_15);
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
//#define ENC_INT_TRIS		(TRISEbits.TRISE8)
//#define ENC_INT_IO			(PORTEbits.RE8)

void ethernet_spi_init()
{
	SpiChnOpen(SPI_CHANNEL3, SPI_OPEN_MSTEN|SPI_OPEN_SMP_END|SPI_OPEN_CKE_REV|SPI_OPEN_MODE8, PBCLK/14000000);
}
void spi_ether_conf()
{
    int rdata;
    
    SDSPICONbits.ON 	= 0;
        
	SDSPICON			= 0;
	rdata 				= SDSPIBUF;
	SD_SPIBRG 			= PBCLK/14000000;
	SDSPI_STAT_CLR		= 0x40;   //SPIROV = 0;
  

	SDSPICONbits.MSTEN = 1;
    SDSPICONbits.CKE 	= 1;
    SDSPICONbits.SMP 	= 1;
    
   	SDSPICONbits.ON 	= 1;
}
// Set up the SPI module on the PIC for communications with the ENC424J600
void enc424j600_init()
{
	ethernet_spi_init();
    //spi_ether_conf();
	ENC_CS_IO = 1;
	ENC_CS_TRIS = 0;		// Make the Chip Select pin an output

//	ENC_INT_IO = 0;
//	ENC_INT_TRIS = 1;		// Make the INT pin an input This interrupt pin is not actually connected. 
//	ENC_INT_IO = 1;
}

/*************************************
Mandatory functions for tcpserver
This function use by tcpserver to set/reset CS
*************************************/

void enc_cs_pin(int set)
{   
    stat++;
    if(stat > 150 && !mT3GetIntEnable())
        return;
	if (set){
        ENC_CS_IO = 1;
    }
	else
    {
        ethernet_spi_init();
        ENC_CS_IO = 0;
    }
}    
// Write data to ENC28J60
void _Spi_putc(int data)
{
        //ENC_CS_IO = 1;
	/* wait until there's room in the buffer and send the byte */
	SpiChnPutC(SPI_CHANNEL3, (unsigned int)data);
        //ENC_CS_IO = 0;
}

// Read data from ENC28J60
int _Spi_getc(void)
{
	int data;
        //ENC_CS_IO = 1;
	/*wait until there's data in the buffer and receive it */
	data = (int)SpiChnGetC(SPI_CHANNEL3);
	//ENC_CS_IO = 0;
	return data;
}
/*****************************************************************************
 * Function: ether_int_off
 * Precondition: None.
 * Overview: Disable Timer2 interrupts.
 * Input: None.
 * Output: None.
 *****************************************************************************/
void ether_int_off(void ){
	
    DisableIntT3;
};

/*****************************************************************************
 * Function: ether_int_on
 * Precondition: None.
 * Overview: Enable Timer2 interrupts.
 * Input: None.
 * Output: None.
 *****************************************************************************/
void ether_int_on(void ){
	
    EnableIntT3;
};
/*****************************************************************************
 * Function: spi_dev_int_dis
 * Precondition: None.
 * Overview: Disable spi interrups.
 * Input: None.
 * Output: None.
 *****************************************************************************/
unsigned int spi_dev_int_dis(void ){
    unsigned int status = 0;
    Status ps;
    
    ps = i_disable();
    if(mT3GetIntEnable()){
        DisableIntT3;
        status = 1;
    }    
    i_restore(ps);
    return status; 
};

/*****************************************************************************
 * Function: spi_dev_int_res
 * Precondition: None.
 * Overview: Restore spi interrupts.
 * Input: None.
 * Output: None.
 *****************************************************************************/
void spi_dev_int_res(unsigned int status ){
    Status ps;
    
    ps = i_disable();
    
    if(status & 0x00000001){
    	EnableIntT3;
    }  
    
    i_restore(ps);
};
#endif
