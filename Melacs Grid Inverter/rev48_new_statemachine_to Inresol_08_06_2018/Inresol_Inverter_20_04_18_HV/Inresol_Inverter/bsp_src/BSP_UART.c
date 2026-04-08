/*
 *  File name: BSP_UART.c
 *
 *  Description: Board Support Package function implementations for UART processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"
#include "ring_buffer.h"

// UART 1 Baudrate Error checkings. Must be below 2%.
#ifdef FCY
	#ifdef APP_SETTINGS_UART_1_BAUDRATE
		#define MACRO_UART_1_BRG						((FCY / (16 * APP_SETTINGS_UART_1_BAUDRATE)) - 1)
		#define MACRO_UART_1_BAUDRATE_ACTUAL			(FCY / (16 * (MACRO_UART_1_BRG + 1)))
		#define MACRO_UART_1_BAUD_ERROR					((MACRO_UART_1_BAUDRATE_ACTUAL > APP_SETTINGS_UART_1_BAUDRATE) ? \
														MACRO_UART_1_BAUDRATE_ACTUAL - APP_SETTINGS_UART_1_BAUDRATE : \
														APP_SETTINGS_UART_1_BAUDRATE - MACRO_UART_1_BAUDRATE_ACTUAL)
		#define MACRO_UART_1_BAUD_ERROR_PERCENT			(((MACRO_UART_1_BAUD_ERROR * 100) + (APP_SETTINGS_UART_1_BAUDRATE / 2)) / APP_SETTINGS_UART_1_BAUDRATE)
		#if (MACRO_UART_1_BAUD_ERROR_PERCENT > 2)
			#error The value loaded to the BRG register produces a baud rate error higher than 2%
		#endif
	#else
		#error Cannot calculate BRG value. Please define APP_SETTINGS_UART_1_BAUDRATE
	#endif
#else
	#error Cannot calculate MACRO_UART_1_BRG value. Please define FCY
#endif

#if defined(BSP_UART_1_TX_RB_SIZE)
// Transmit ring buffer structure
static RINGBUFF_T Uart_1_Tx_Ring;
// Transmit data buffer
static uint8_t Uart_1_Tx_Buff[BSP_UART_1_TX_RB_SIZE];
#else
#error Please define BSP_UART_1_TX_RB_SIZE !!!
#endif
#if defined(BSP_UART_1_RX_RB_SIZE)
// Receive ring buffer structure
static RINGBUFF_T Uart_1_Rx_Ring;
// Receive data buffer
static uint8_t Uart_1_Rx_Buff[BSP_UART_1_RX_RB_SIZE];
#else
#error Please define BSP_UART_1_RX_RB_SIZE !!!
#endif

#if defined(BSP_UART_2_TX_RB_SIZE)
// Transmit ring buffer structure
static RINGBUFF_T Uart_2_Tx_Ring;
// Transmit data buffer
static uint8_t Uart_2_Tx_Buff[BSP_UART_2_TX_RB_SIZE];
#else
#error Please define BSP_UART_2_TX_RB_SIZE !!!
#endif
#if defined(BSP_UART_2_RX_RB_SIZE)
// Receive ring buffer structure
static RINGBUFF_T Uart_2_Rx_Ring;
// Receive data buffer
static uint8_t Uart_2_Rx_Buff[BSP_UART_2_RX_RB_SIZE];
#else
#error Please define BSP_UART_2_RX_RB_SIZE !!!
#endif

// **************************************
// *********   UART 1 (DEBUG)  **********
// **************************************

void BSP_UART_1_Config_Pins(void)
{
	//
	// Disables or enables pull-ups/pull-downs and enable digital mode.
	//
	BSP_IO_GPIO_DIR_IN(UART1_RX_PORTPIN);		// Configures pin RB7 (U1RX) as input
	BSP_IO_GPIO_PU_ON(UART1_RX_PORTPIN);		// Enables pin RB7 (U1RX) Pull-Up
	BSP_IO_GPIO_SET(UART1_TX_PORTPIN);			// Sets pin RB6 (U1TX) state as '1' - USART's IDLE state
	BSP_IO_GPIO_DIR_OUT(UART1_TX_PORTPIN);		// Configures pin RB6 (U1TX) as output
#ifdef DEBUG_ON_RS485
	BSP_IO_GPIO_CLR(UART2_TXEN_PORTPIN);		// Sets pin RB4 (U1_TXEN) state as '0' - RS422 TX Enabled
	BSP_IO_GPIO_DIR_OUT(UART2_TXEN_PORTPIN);	// Configures pin RB4 (U1_TXEN) as output
#endif
	//
	// UART signal muxing via PPS.
	//
	// Assign UART1 signals to pins RP
	BSP_IO_PPS_UnLock();
	BSP_IO_PPS_Set_Input(BSP_IO_PPS_IN_FN_U1RX, BSP_IO_PPS_IN_PIN_U1RX);
	BSP_IO_PPS_Set_Output(BSP_IO_PPS_OUT_FN_U1TX, BSP_IO_PPS_OUT_PIN_U1TX);
	BSP_IO_PPS_Lock();
}

void BSP_UART_1_Set_Baudrate(uint32_t Baudrate)
{
	U1BRG  = ((uint32_t)FCY / (Baudrate * 16)) - 1;
}

void BSP_UART_1_Set_Mode(uint16_t Mode)
{
	U1MODE = Mode;
//	U1MODE = 0x8000; /* Reset UART to 8-n-1, alt pins, and enable */
//	U1STA  = 0x0440; /* Reset status register and enable TX & RX*/
//	_U1RXIF = 0;
}

void BSP_UART_1_Set_Sta(uint16_t Sta)
{
	U1STA = Sta;
}

void BSP_UART_1_Set_Int(uint16_t Int)
{
	// Clear IF flags
	_U1RXIF = 0;
	_U1TXIF = 0;

	// Set priority
	_U1RXIP = 0x0007 & Int;
	_U1TXIP = (0x0070 & Int) >> 4;

	// Enable/Disable interrupt
	_U1RXIE = (0x0008 & Int) >> 3;
	_U1TXIE = (0x0080 & Int) >> 7;
}

void BSP_UART_1_Init(uint16_t Mode, uint16_t Sta, uint32_t Baudrate)
{
	//
	// Disable the UART before configuring it.
	//
	U1MODEbits.UARTEN = 0;

	//
	// Configure the UART.
	//
	BSP_UART_1_Set_Baudrate(Baudrate);
	BSP_UART_1_Set_Mode(Mode);
	BSP_UART_1_Set_Sta(Sta);

	//
	// Enable the UART.
	//
	U1MODEbits.UARTEN = 1;

	//
	// Before using the ring buffers, initialize them using the ring buffer init function.
	//
#if (BSP_UART_1_TX_RB_SIZE != 0)
	RingBuffer_Init(&Uart_1_Tx_Ring, Uart_1_Tx_Buff, 1, BSP_UART_1_TX_RB_SIZE);
#endif
#if (BSP_UART_1_RX_RB_SIZE != 0)
	RingBuffer_Init(&Uart_1_Rx_Ring, Uart_1_Rx_Buff, 1, BSP_UART_1_RX_RB_SIZE);
#endif
}

void BSP_UART_1_DeInit(void)
{
	//
	// Configure the UART.
	//
	U1MODEbits.UARTEN = 0;
	_U1RXIE = 0;
	_U1TXIE = 0;
	_U1RXIF = 0;
	_U1TXIF = 0;
}

inline void BSP_UART_1_Rx_Interrupt_Enable(void)
{
	//
	// Enable the UART interrupts.
	//
	_U1RXIE = 1;
}

inline void BSP_UART_1_Tx_Interrupt_Enable(void)
{
	//
	// Enable the UART interrupts.
	//
	_U1TXIE = 1;
}

inline void BSP_UART_1_Rx_Interrupt_Disable(void)
{
	//
	// Disable the UART RX interrupt.
	//
	_U1RXIE = 0;
}

inline void BSP_UART_1_Tx_Interrupt_Disable(void)
{
	//
	// Disable the UART TX interrupt.
	//
	_U1TXIE = 0;
}

inline void BSP_UART_1_Rx_Interrupt_Clear(void)
{
	//
	// Clear the UART RX interrupt.
	//
	_U1RXIF = 0;
}

inline void BSP_UART_1_Tx_Interrupt_Clear(void)
{
	//
	// Clear the UART TX interrupt.
	//
	_U1TXIF = 0;
}

inline void BSP_UART_1_Rx_Interrupt_Priority(uint8_t Priority)
{
	//
	// Set the UART RX interrupt priority.
	//
	_U1RXIP = Priority;
}

inline void BSP_UART_1_Tx_Interrupt_Priority(uint8_t Priority)
{
	//
	// Set the UART TX interrupt priority.
	//
	_U1TXIP = Priority;
}

#if 0
/*************************************************************************
* Function Name     : BusyUART1                                          *
* Description       : This returns status whether the transmission       *
*                     is in progress or not, by checking Status bit TRMT *
* Parameters        : None                                               *
* Return Value      : Info about whether transmission is in progress.    *
*************************************************************************/
char BusyUART1(void)
{  
    return(!U1STAbits.TRMT);
}

/*********************************************************************
* Function Name     : DataRdyUart1                                   *
* Description       : This function checks whether there is any data *
*                     that can be read from the input buffer, by     *
*                     checking URXDA bit                             *
* Parameters        : None                                           *
* Return Value      : char if any data available in buffer           *
*********************************************************************/
char DataRdyUART1(void)
{
    return(U1STAbits.URXDA);
}

/******************************************************************************
* Function Name     : getsUART1                                               *
* Description       : This function gets a string of data of specified length * 
*                     if available in the UxRXREG buffer into the buffer      *
*                     specified.                                              *
* Parameters        : unsigned int length the length expected                 *
*                     unsigned int *buffer  the received data to be           * 
*                                  recorded to this array                     *
*                     unsigned int uart_data_wait timeout value               *
* Return Value      : unsigned int number of data bytes yet to be received    *
******************************************************************************/
unsigned int getsUART1(unsigned int length,unsigned int *buffer,
                       unsigned int uart_data_wait)
{
    int wait = 0;
    char *temp_ptr = (char *) buffer;

    while(length)                         /* read till length is 0 */
    {
        while(!DataRdyUART1())
        {
            if(wait < uart_data_wait)
                wait++ ;                  /*wait for more data */
            else
                return(length);           /*Time out- Return words/bytes to be read */
        }
        wait=0;
        if(U1MODEbits.PDSEL == 3)         /* check if TX/RX is 8bits or 9bits */
            *buffer++ = U1RXREG;          /* data word from HW buffer to SW buffer */
	else
            *temp_ptr++ = U1RXREG & 0xFF; /* data byte from HW buffer to SW buffer */

        length--;
    }

    return(length);                       /* number of data yet to be received i.e.,0 */
}

/***************************************************************************
* Function Name     : putsUART1                                            *
* Description       : This function puts the data string to be transmitted *
*                     into the transmit buffer (till NULL character)       *
* Parameters        : unsigned int * address of the string buffer to be    *  
*                     transmitted                                          *
* Return Value      : None                                                 *
***************************************************************************/
void putsUART1(unsigned int *buffer)
{
    char * temp_ptr = (char *) buffer;

    /* transmit till NULL character is encountered */

    if(U1MODEbits.PDSEL == 3)        /* check if TX is 8bits or 9bits */
    {
        while(*buffer != '\0') 
        {
            while(U1STAbits.UTXBF); /* wait if the buffer is full */
            U1TXREG = *buffer++;    /* transfer data word to TX reg */
        }
    }
    else
    {
        while(*temp_ptr != '\0')
        {
            while(U1STAbits.UTXBF);  /* wait if the buffer is full */
            U1TXREG = *temp_ptr++;   /* transfer data byte to TX reg */
        }
    }
}

/***************************************************************************
* Function Name     : ReadUART1                                            *
* Description       : This function returns the contents of UxRXREG buffer * 
* Parameters        : None                                                 *
* Return Value      : unsigned int value from UxRXREG receive buffer       *
***************************************************************************/
unsigned int ReadUART1(void)
{
    if(U1MODEbits.PDSEL == 3)
        return (U1RXREG);
    else
        return (U1RXREG & 0xFF);
}

/*********************************************************************
* Function Name     : WriteUART1                                     *
* Description       : This function writes data into the UxTXREG,    *
* Parameters        : unsigned int data the data to be written       *
* Return Value      : None                                           *
*********************************************************************/
void WriteUART1(unsigned int data)
{
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}
#endif

void WriteUART1(unsigned char data)
{
	U1TXREG = data;
}

unsigned char ReadUART1(void)
{
	return (U1RXREG);
}

char DataRdyUART1(void)
{
	return(U1STAbits.URXDA);
}

// Transmit a byte array through the UART peripheral (non-blocking)
int BlockWriteUART1(const void *data, int numBytes)
{
	int sent = 0;
	uint8_t *p8 = (uint8_t*)data;

	// Send until the transmit FIFO is full or out of bytes
	while((sent < numBytes) && (U1STAbits.UTXBF == 0)) {
		WriteUART1(*p8);
		p8++;
		sent++;
	}
	return sent;
}

#if (BSP_UART_1_RX_RB_SIZE != 0)
// UART receive-only interrupt handler for ring buffers
static void BSP_UART_1_Rx_IntHandlerRB(void)
{
	// Read the receive buffer until at least one or more character can be read
	// New data will be ignored if data not popped in time
	while(DataRdyUART1()) {
		uint8_t ch = ReadUART1();
		RingBuffer_Insert(&Uart_1_Rx_Ring, &ch);
	}
}
#endif

#if (BSP_UART_1_TX_RB_SIZE != 0)
// UART transmit-only interrupt handler for ring buffers
static void BSP_UART_1_Tx_IntHandlerRB(void)
{
	uint8_t ch;

	// Fill FIFO until full or until TX ring buffer is empty
	while((U1STAbits.UTXBF == 0) && RingBuffer_Pop(&Uart_1_Tx_Ring, &ch)) {
		WriteUART1(ch);
	}
}
#endif

int BSP_UART_1_Send_Data_Blocking(const void  *data, uint16_t length)
{
	//
	// Message sent using blocking method (prevent ring buffer overflow)
	//
	int pass, sent = 0;
	uint8_t *p8 = (uint8_t*)data;

	while(length > 0) {
		pass = BlockWriteUART1(p8, length);
		length -= pass;
		sent += pass;
		p8 += pass;
	}
	return sent;
}

int BSP_UART_1_Send_Data_NoBlocking(const void  *data, uint16_t length)
{
	//
	// Message sent using no-blocking method (may overflow the ring buffer)
	//
	// Populate a transmit ring buffer and start UART transmit
	uint16_t ret;
	uint8_t *p8 = (uint8_t*)data;

	// Don't let UART transmit ring buffer change in the UART IRQ handler
	BSP_UART_1_Tx_Interrupt_Disable();

	// Move as much data as possible into transmit ring buffer
	ret = RingBuffer_InsertMult(&Uart_1_Tx_Ring, p8, length);
	BSP_UART_1_Tx_IntHandlerRB();

	/* Add additional data to transmit ring buffer if possible */
	ret += RingBuffer_InsertMult(&Uart_1_Tx_Ring, (p8 + ret), (length - ret));

	// Enable UART transmit interrupt
	BSP_UART_1_Tx_Interrupt_Enable();

	return ret;
}

int BSP_UART_1_Receive_Data(void *data, uint16_t size)
{
	return RingBuffer_PopMult(&Uart_1_Rx_Ring, (uint8_t *)data, size);
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_UART_1_RX_INTERRUPT_HANDLER()
{
	BSP_UART_1_RX_INTERRUPT_CLEAR();
//	LED4_OUT = 1;
#if (BSP_UART_1_RX_RB_SIZE != 0)
	//
	// Handle receive interrupt with ring buffer
	//
	BSP_UART_1_Rx_IntHandlerRB();
#else
	//
	// Handle receive interrupt w/o ring buffer
	//
	BSP_UART_1_RX_INTERRUPT_CALLBACK();
#endif
//	LED4_OUT = 0;
//	LED4_OUT ^= 1;			// Toggle LED
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_UART_1_TX_INTERRUPT_HANDLER()
{
	BSP_UART_1_TX_INTERRUPT_CLEAR();
//	LED4_OUT = 1;
#if (BSP_UART_1_TX_RB_SIZE != 0)
	//
	// Handle transmit interrupt with ring buffer (if enabled))
	//
//	if((U1STA & 0x2000) != 0) {
		BSP_UART_1_Tx_IntHandlerRB();

		// Disable transmit interrupt if the ring buffer is empty
		if(RingBuffer_IsEmpty(&Uart_1_Tx_Ring)) {
			BSP_UART_1_Tx_Interrupt_Disable();
		}
//	}
#else
	//
	// Handle transmit interrupt w/o ring buffer
	//
	BSP_UART_1_TX_INTERRUPT_CALLBACK();
#endif
//	LED4_OUT = 0;
//	LED4_OUT ^= 1;
}

// **************************************
// *********   UART 2 (RS4XX)  **********
// **************************************

void BSP_UART_2_Config_Pins(void)
{
	//
	// Disables or enables pull-ups/pull-downs and enable digital mode.
	//
	BSP_IO_GPIO_DIR_IN(UART2_RX_PORTPIN);		// Configures pin RB7 (U1RX) as input
	BSP_IO_GPIO_PU_ON(UART2_RX_PORTPIN);		// Enables pin RB7 (U1RX) Pull-Up
	BSP_IO_GPIO_SET(UART2_TX_PORTPIN);			// Sets pin RB6 (U1TX) state as '1' - USART's IDLE state
	BSP_IO_GPIO_DIR_OUT(UART2_TX_PORTPIN);		// Configures pin RB6 (U1TX) as output
#ifndef DEBUG_ON_RS485
	BSP_IO_GPIO_SET(UART2_TXEN_PORTPIN);		// Sets pin RB4 (U1_TXEN) state as '0' - RS422 TX Enabled
	BSP_IO_GPIO_DIR_OUT(UART2_TXEN_PORTPIN);	// Configures pin RB4 (U1_TXEN) as output
#endif

	//
	// UART signal muxing via PPS.
	//
	// Assign UART2 signals to pins RP
	BSP_IO_PPS_UnLock();
	BSP_IO_PPS_Set_Input(BSP_IO_PPS_IN_FN_U2RX, BSP_IO_PPS_IN_PIN_U2RX);
	BSP_IO_PPS_Set_Output(BSP_IO_PPS_OUT_FN_U2TX, BSP_IO_PPS_OUT_PIN_U2TX);
#ifndef DEBUG_ON_RS485
	BSP_IO_PPS_Set_Input(BSP_IO_PPS_IN_FN_U2CTS, BSP_IO_PPS_IN_PIN_U2CTS);
	BSP_IO_PPS_Set_Output(BSP_IO_PPS_OUT_FN_U2RTS, BSP_IO_PPS_OUT_PIN_U2RTS);
#endif
	BSP_IO_PPS_Lock();
}

void BSP_UART_2_Set_Baudrate(uint32_t Baudrate)
{
	U2BRG  = ((uint32_t)FCY / (Baudrate * 16)) - 1;
}

void BSP_UART_2_Set_Mode(uint16_t Mode)
{
	U2MODE = Mode;
//	U2MODE = 0x8000; /* Reset UART to 8-n-1, alt pins, and enable */
//	U2STA  = 0x0440; /* Reset status register and enable TX & RX*/
//	_U2RXIF = 0;
}

void BSP_UART_2_Set_Sta(uint16_t Sta)
{
	U2STA = Sta;
}

void BSP_UART_2_Set_Int(uint16_t Int)
{
	// Clear IF flags
	_U2RXIF = 0;
	_U2TXIF = 0;

	// Set priority
	_U2RXIP = 0x0007 & Int;
	_U2TXIP = (0x0070 & Int) >> 4;

	// Enable/Disable interrupt
	_U2RXIE = (0x0008 & Int) >> 3;
	_U2TXIE = (0x0080 & Int) >> 7;
}

void BSP_UART_2_Init(uint16_t Mode, uint16_t Sta, uint32_t Baudrate)
{
	//
	// Disable the UART before configuring it.
	//
	U2MODEbits.UARTEN = 0;

	//
	// Configure the UART.
	//
	BSP_UART_2_Set_Baudrate(Baudrate);
	BSP_UART_2_Set_Mode(Mode);
	BSP_UART_2_Set_Sta(Sta);

	//
	// Enable the UART.
	//
	U2MODEbits.UARTEN = 1;
	U2STAbits.UTXEN = 1;

	//
	// Before using the ring buffers, initialize them using the ring buffer init function.
	//
#if (BSP_UART_2_TX_RB_SIZE != 0)
	RingBuffer_Init(&Uart_2_Tx_Ring, Uart_2_Tx_Buff, 1, BSP_UART_2_TX_RB_SIZE);
#else
	(void)Uart_2_Tx_Buff;
#endif
#if (BSP_UART_2_RX_RB_SIZE != 0)
	RingBuffer_Init(&Uart_2_Rx_Ring, Uart_2_Rx_Buff, 1, BSP_UART_2_RX_RB_SIZE);
#else
	(void)Uart_2_Rx_Buff;
#endif
}

void BSP_UART_2_DeInit(void)
{
	//
	// Configure the UART.
	//
	U2MODEbits.UARTEN = 0;
	_U2RXIE = 0;
	_U2TXIE = 0;
	_U2RXIF = 0;
	_U2TXIF = 0;
}

inline void BSP_UART_2_Rx_Interrupt_Enable(void)
{
	//
	// Enable the UART interrupts.
	//
	_U2RXIE = 1;
}

inline void BSP_UART_2_Tx_Interrupt_Enable(void)
{
	MB_TST2_CLR();

	//
	// Enable the UART interrupts.
	//
	_U2TXIE = 1;

	//
	// Fire the UART interrupt.
	//
	_U2TXIF = 1;
}

inline void BSP_UART_2_Rx_Interrupt_Disable(void)
{
	//
	// Disable the UART RX interrupt.
	//
	_U2RXIE = 0;
}

inline void BSP_UART_2_Tx_Interrupt_Disable(void)
{
	//
	// Disable the UART TX interrupt.
	//
	_U2TXIE = 0;
}

inline void BSP_UART_2_Rx_Interrupt_Clear(void)
{
	//
	// Clear the UART RX interrupt.
	//
	_U2RXIF = 0;
}

inline void BSP_UART_2_Tx_Interrupt_Clear(void)
{
	//
	// Clear the UART TX interrupt.
	//
	_U2TXIF = 0;
}

inline void BSP_UART_2_Rx_Interrupt_Priority(uint8_t Priority)
{
	//
	// Set the UART RX interrupt priority.
	//
	_U2RXIP = Priority;
}

inline void BSP_UART_2_Tx_Interrupt_Priority(uint8_t Priority)
{
	//
	// Set the UART TX interrupt priority.
	//
	_U2TXIP = Priority;
}

/*inline*/ void BSP_UART_2_Write_Byte(uint8_t data)
{
	U2TXREG = data;
}

/*inline*/ uint8_t BSP_UART_2_Read_Byte(void)
{
	return (U2RXREG);
}

/*inline*/ bool BSP_UART_2_Ready_for_Write(void)
{
	if((_U2TXIE == 1) && (U2STAbits.UTXBF == 0))
		return true;
	else
		return false;
}

void WriteUART2(unsigned char data)
{
	U2TXREG = data;
}

unsigned char ReadUART2(void)
{
	return (U2RXREG);
}

char DataRdyUART2(void)
{
	return(U2STAbits.URXDA);
}

// Transmit a byte array through the UART peripheral (non-blocking)
int BlockWriteUART2(const void *data, int numBytes)
{
	int sent = 0;
	uint8_t *p8 = (uint8_t*)data;

	// Send until the transmit FIFO is full or out of bytes
	while((sent < numBytes) && (U2STAbits.UTXBF == 0)) {
		WriteUART2(*p8);
		p8++;
		sent++;
	}
	return sent;
}

#if (BSP_UART_2_RX_RB_SIZE != 0)
// UART receive-only interrupt handler for ring buffers
static void BSP_UART_2_Rx_IntHandlerRB(void)
{
	// Read the receive buffer until at least one or more character can be read
	// New data will be ignored if data not popped in time
	while(DataRdyUART2()) {
		uint8_t ch = ReadUART2();
		RingBuffer_Insert(&Uart_2_Rx_Ring, &ch);
	}
}
#endif

#if (BSP_UART_2_TX_RB_SIZE != 0)
// UART transmit-only interrupt handler for ring buffers
static void BSP_UART_2_Tx_IntHandlerRB(void)
{
	uint8_t ch;

	// Fill FIFO until full or until TX ring buffer is empty
	while((U2STAbits.UTXBF == 0) && RingBuffer_Pop(&Uart_2_Tx_Ring, &ch)) {
		WriteUART2(ch);
	}
}
#endif

int BSP_UART_2_Send_Data_Blocking(const void  *data, uint16_t length)
{
	//
	// Message sent using blocking method (prevent ring buffer overflow)
	//
	int pass, sent = 0;
	uint8_t *p8 = (uint8_t*)data;

	while(length > 0) {
		pass = BlockWriteUART2(p8, length);
		length -= pass;
		sent += pass;
		p8 += pass;
	}
	return sent;
}

int BSP_UART_2_Send_Data_NoBlocking(const void  *data, uint16_t length)
{
	//
	// Message sent using no-blocking method (may overflow the ring buffer)
	//
	// Populate a transmit ring buffer and start UART transmit
	uint16_t ret;
	uint8_t *p8 = (uint8_t*)data;

	// Don't let UART transmit ring buffer change in the UART IRQ handler
	BSP_UART_2_Tx_Interrupt_Disable();

	// Move as much data as possible into transmit ring buffer
	ret = RingBuffer_InsertMult(&Uart_2_Tx_Ring, p8, length);
#if (BSP_UART_2_TX_RB_SIZE != 0)
	BSP_UART_2_Tx_IntHandlerRB();
#endif

	/* Add additional data to transmit ring buffer if possible */
	ret += RingBuffer_InsertMult(&Uart_2_Tx_Ring, (p8 + ret), (length - ret));

	// Enable UART transmit interrupt
	BSP_UART_2_Tx_Interrupt_Enable();

	return ret;
}

int BSP_UART_2_Receive_Data(void *data, uint16_t size)
{
	return RingBuffer_PopMult(&Uart_2_Rx_Ring, (uint8_t *)data, size);
}

void BSP_UART_2_Rx_Flush(void)
{
	U2STABITS U2STA_reg;

	*((uint16_t*)&U2STA_reg) = U2STA;
	if(U2STA_reg.FERR == 1) {
		while(DataRdyUART2()) {
			(void)ReadUART2();
		}
	}
	if(U2STA_reg.PERR == 1) {
		while(DataRdyUART2()) {
			(void)ReadUART2();
		}
	}
	// Must clear the overrun error to keep UART receiving
	if(U2STA_reg.OERR == 1) {
		U2STAbits.OERR = 0;
		while(DataRdyUART2()) {
			(void)ReadUART2();
		}
		U2STAbits.OERR = 0;
	}
	while(DataRdyUART2()) {
		(void)U2RXREG;
	}
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_UART_2_RX_INTERRUPT_HANDLER()
{
	U2STABITS U2STA_reg;

	BSP_UART_2_RX_INTERRUPT_CLEAR();

	*((uint16_t*)&U2STA_reg) = U2STA;
	// Check for receive errors
	if(U2STA_reg.FERR == 1) {
//		while(DataRdyUART2()) {
//			(void)ReadUART2();
//		}
		MB_TST1_TGL();
		return;
	}
	if(U2STA_reg.PERR == 1) {
//		while(DataRdyUART2()) {
//			(void)ReadUART2();
//		}
		MB_TST1_TGL();
		return;
	}
	// Must clear the overrun error to keep UART receiving
	if(U2STA_reg.OERR == 1) {
		U2STAbits.OERR = 0;
//		while(DataRdyUART2()) {
//			(void)ReadUART2();
//		}
		MB_TST1_TGL();
		return;
	}
	// Get the data
//	MB_TST1_TGL();
#if (BSP_UART_2_RX_RB_SIZE != 0)
	//
	// Handle receive interrupt with ring buffer
	//
	BSP_UART_2_Rx_IntHandlerRB();
#else
	//
	// Handle receive interrupt w/o ring buffer
	//

	// Read the receive buffer until at least one or more character can be read
	// New data will be ignored if data not popped in time
	while(DataRdyUART2()) {
		MB_TST1_TGL();
		BSP_UART_2_RX_INTERRUPT_CALLBACK();
	}
#endif
}

void __attribute__((__interrupt__, no_auto_psv)) BSP_UART_2_TX_INTERRUPT_HANDLER()
{
	BSP_UART_2_TX_INTERRUPT_CLEAR();
	MB_TST1_TGL();
#if (BSP_UART_2_TX_RB_SIZE != 0)
	//
	// Handle transmit interrupt with ring buffer (if enabled))
	//
//	if((U2STA & 0x2000) != 0) {
		BSP_UART_2_Tx_IntHandlerRB();

		// Disable transmit interrupt if the ring buffer is empty
		if(RingBuffer_IsEmpty(&Uart_2_Tx_Ring)) {
			BSP_UART_2_Tx_Interrupt_Disable();
		}
//	}
#else
	//
	// Flush any Rx-ed data during Tx
	// (protection against Rx buffer overrun when line is looped-back)
	//
	while(DataRdyUART2()) {
		(void)U2RXREG;
	}
	//
	// Handle transmit interrupt w/o ring buffer
	//
	while(BSP_UART_2_Ready_for_Write() == true) {
		MB_TST1_TGL();
		BSP_UART_2_TX_INTERRUPT_CALLBACK();
	}
#endif
}
