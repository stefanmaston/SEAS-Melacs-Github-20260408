/*
 *  File name: types_uart.h
 *
 *  Description: Type definitions for UART
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_UART_H
#define TYPES_UART_H

#include "config_system.h"

/*****************/
/* Basic Defines */
/*****************/

// Defines for UxMODE register

#define BSP_UART_EN						0xFFFF	/* Module enable */
#define BSP_UART_DIS					0x7FFF	/* Module disable */

#define BSP_UART_IDLE_CON				0xDFFF	/* Work in IDLE mode */
#define BSP_UART_IDLE_STOP				0xFFFF	/* Stop all functions in IDLE mode*/

#define BSP_UART_IrDA_ENABLE			0xFFFF	/* IrDA encoder and decoder enabled*/
#define BSP_UART_IrDA_DISABLE			0xEFFF	/* IrDA encoder and decoder disabled */

#define BSP_UART_MODE_SIMPLEX			0xFFFF	/* UxRTS pin in Simplex mode */
#define BSP_UART_MODE_FLOW				0xF7FF	/* UxRTS pin in Flow Control mode*/

#define BSP_UART_UEN_11					0xFFFF	/*UxTX,UxRX and BCLK pins are enabled and used; UxCTS pin controlled by port latches*/
#define BSP_UART_UEN_10					0xFEFF	/*UxTX,UxRX, UxCTS and UxRTS pins are enabled and used*/
#define BSP_UART_UEN_01					0xFDFF	/*UxTX,UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by port latches*/
#define BSP_UART_UEN_00					0xFCFF	/*UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLK pins controlled by port latches*/

#define BSP_UART_EN_WAKE				0xFFFF	/*Enable Wake-up on START bit Detect during SLEEP Mode bit*/
#define BSP_UART_DIS_WAKE				0xFF7F	/*Disable Wake-up on START bit Detect during SLEEP Mode bit*/

#define BSP_UART_EN_LOOPBACK			0xFFFF	/*Loop back enabled*/
#define BSP_UART_DIS_LOOPBACK			0xFFBF	/*Loop back disabled*/

#define BSP_UART_EN_ABAUD				0xFFFF	/*Enable baud rate measurement on the next character*/
#define BSP_UART_DIS_ABAUD				0xFFDF	/*Baud rate measurement disabled or completed*/

#define BSP_UART_UXRX_IDLE_ZERO			0xFFFF	/* UxRX Idle state is zero */
#define BSP_UART_UXRX_IDLE_ONE			0xFFEF	/* UxRx Idle state is one */

#define BSP_UART_BRGH_FOUR				0xFFFF	/* BRG generates 4 clocks per bit period */
#define BSP_UART_BRGH_SIXTEEN			0xFFF7	/* BRG generates 16 clocks per bit period */

#define BSP_UART_NO_PAR_9BIT			0xFFFF	/*No parity 9 bit*/
#define BSP_UART_ODD_PAR_8BIT			0xFFFD	/*odd parity 8 bit*/
#define BSP_UART_EVEN_PAR_8BIT			0xFFFB	/*even parity 8 bit*/
#define BSP_UART_NO_PAR_8BIT			0xFFF9	/*no parity 8 bit*/

#define BSP_UART_2STOPBITS				0xFFFF	/*2 stop bits*/
#define BSP_UART_1STOPBIT				0xFFFE	/*1 stop bit*/

// Defines for UART Status register

#define BSP_UART_INT_TX_BUF_EMPTY		0xDFFF	/* Interrupt on TXBUF becoming empty */
#define BSP_UART_INT_TX_LAST_CH			0x7FFF	/* Interrupt when last character shifted out*/
#define BSP_UART_INT_TX					0x5FFF	/* Interrupt on transfer of every character to TSR */

#define BSP_UART_IrDA_POL_INV_ONE		0xFFFF	/*IrDA encoded, UxTX Idle state is '1' */
#define BSP_UART_IrDA_POL_INV_ZERO		0xBFFF	/* IrDA encoded, UxTX Idel state is '0' */

#define BSP_UART_SYNC_BREAK_ENABLED		0xFFFF	/* Send sync break on next transmission */
#define BSP_UART_SYNC_BREAK_DISABLED	0xF7FF	/* Sync break transmission disabled or completed */

#define BSP_UART_TX_ENABLE				0xFFFF	/* Transmit enable */
#define BSP_UART_TX_DISABLE				0xFBFF	/* Transmit disable */

#define BSP_UART_TX_BUF_FUL				0xFFFF	/* Transmit buffer is full */
#define BSP_UART_TX_BUF_NOT_FUL			0xFDFF	/* Transmit buffer is not full */

#define BSP_UART_INT_RX_BUF_FUL			0xFFFF	/* Interrupt on RXBUF full */
#define BSP_UART_INT_RX_3_4_FUL			0xFFBF	/* Interrupt on RXBUF 3/4 full */
#define BSP_UART_INT_RX_CHAR			0xFF7F	/* Interrupt on every char received */

#define BSP_UART_ADR_DETECT_EN			0xFFFF	/* address detect enable */
#define BSP_UART_ADR_DETECT_DIS			0xFFDF	/* address detect disable */

#define BSP_UART_RX_OVERRUN_CLEAR		0xFFFD	/* Rx buffer Over run status bit clear */

// Defines for UART Interrupt configuartion
#define BSP_UART_RX_INT_EN				0xFFFF	/*Receive interrupt enabled*/
#define BSP_UART_RX_INT_DIS				0xFFF7	/*Receive interrupt disabled*/

#define BSP_UART_RX_INT_PR0				0xFFF8	/*Priority RX interrupt 0*/
#define BSP_UART_RX_INT_PR1				0xFFF9	/*Priority RX interrupt 1*/
#define BSP_UART_RX_INT_PR2				0xFFFA	/*Priority RX interrupt 2*/
#define BSP_UART_RX_INT_PR3				0xFFFB	/*Priority RX interrupt 3*/
#define BSP_UART_RX_INT_PR4				0xFFFC	/*Priority RX interrupt 4*/
#define BSP_UART_RX_INT_PR5				0xFFFD	/*Priority RX interrupt 5*/
#define BSP_UART_RX_INT_PR6				0xFFFE	/*Priority RX interrupt 6*/
#define BSP_UART_RX_INT_PR7				0xFFFF	/*Priority RX interrupt 7*/

#define BSP_UART_TX_INT_EN				0xFFFF	/*transmit interrupt enabled*/
#define BSP_UART_TX_INT_DIS				0xFF7F	/*transmit interrupt disabled*/

#define BSP_UART_TX_INT_PR0				0xFF8F	/*Priority TX interrupt 0*/
#define BSP_UART_TX_INT_PR1				0xFF9F	/*Priority TX interrupt 1*/
#define BSP_UART_TX_INT_PR2				0xFFAF	/*Priority TX interrupt 2*/
#define BSP_UART_TX_INT_PR3				0xFFBF	/*Priority TX interrupt 3*/
#define BSP_UART_TX_INT_PR4				0xFFCF	/*Priority TX interrupt 4*/
#define BSP_UART_TX_INT_PR5				0xFFDF	/*Priority TX interrupt 5*/
#define BSP_UART_TX_INT_PR6				0xFFEF	/*Priority TX interrupt 6*/
#define BSP_UART_TX_INT_PR7				0xFFFF	/*Priority TX interrupt 7*/

#if 0
// Macros to  Enable/Disable interrupts and set Interrupt priority of UART1
#define EnableIntU1RX                    _U1RXIE = 1
#define EnableIntU1TX                    _U1TXIE = 1

#define DisableIntU1RX                   _U1RXIE = 0
#define DisableIntU1TX                   _U1TXIE = 0

#define SetPriorityIntU1RX(priority)     _U1RXIP = priority
#define SetPriorityIntU1TX(priority)     _U1TXIP = priority
#endif

#endif	// TYPES_UART_H
