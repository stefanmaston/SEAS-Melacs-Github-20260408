/*
 *  File name: config_uart.h
 *
 *  Description: UARTs settings
 *
 *  Author: Future Electronics
 *
 */

#ifndef CONFIG_UART_H
#define CONFIG_UART_H

//*****************************************************************************
//
// UART 1 (DEBUG) BSP settings.
//
//*****************************************************************************
#define BSP_UART_1_RX_INTERRUPT_HANDLER()				_U1RXInterrupt()
#define BSP_UART_1_TX_INTERRUPT_HANDLER()				_U1TXInterrupt()
//#define BSP_UART_1_RX_INTERRUPT_CALLBACK()				App_UART_1_RX_Process()
//#define BSP_UART_1_TX_INTERRUPT_CALLBACK()				App_UART_1_TX_Process()
#define BSP_UART_1_RX_INTERRUPT_LEVEL					3
#define BSP_UART_1_TX_INTERRUPT_LEVEL					2
#define BSP_UART_1_RX_INTERRUPT_CLEAR()					BSP_UART_1_Rx_Interrupt_Clear()
#define BSP_UART_1_TX_INTERRUPT_CLEAR()					BSP_UART_1_Tx_Interrupt_Clear()
#define BSP_UART_1_TX_RB_SIZE							128
#define BSP_UART_1_RX_RB_SIZE							64

//*****************************************************************************
//
// UART 2 (RS4XX) BSP settings.
//
//*****************************************************************************
#define BSP_UART_2_RX_INTERRUPT_HANDLER()				_U2RXInterrupt()
#define BSP_UART_2_TX_INTERRUPT_HANDLER()				_U2TXInterrupt()
#define BSP_UART_2_RX_INTERRUPT_CALLBACK()				vMBPortUartRxInterrupt()
#define BSP_UART_2_TX_INTERRUPT_CALLBACK()				vMBPortUartTxInterrupt()
#define BSP_UART_2_RX_INTERRUPT_LEVEL					3
#define BSP_UART_2_TX_INTERRUPT_LEVEL					2
#define BSP_UART_2_RX_INTERRUPT_CLEAR()					BSP_UART_2_Rx_Interrupt_Clear()
#define BSP_UART_2_TX_INTERRUPT_CLEAR()					BSP_UART_2_Tx_Interrupt_Clear()
#define BSP_UART_2_TX_RB_SIZE							0
#define BSP_UART_2_RX_RB_SIZE							0

//*****************************************************************************
//
// UART 1 (DEBUG) App parameters.
//
//*****************************************************************************
#define APP_SETTINGS_UART_1_BAUDRATE					115200
// Configure UART module to transmit 8 bit data with one stopbit.
#define APP_SETTINGS_UART_1_MODE						(BSP_UART_EN & \
														BSP_UART_IDLE_CON & \
														BSP_UART_IrDA_DISABLE & \
														BSP_UART_MODE_FLOW & \
														BSP_UART_UEN_00 & \
														BSP_UART_DIS_WAKE & \
														BSP_UART_DIS_LOOPBACK & \
														BSP_UART_DIS_ABAUD & \
														BSP_UART_UXRX_IDLE_ONE & \
														BSP_UART_BRGH_SIXTEEN & \
														BSP_UART_NO_PAR_8BIT & \
														BSP_UART_1STOPBIT)
//#define STA_VALUE	(BSP_UART_INT_TX_BUF_EMPTY & BSP_UART_TX_ENABLE & BSP_UART_INT_RX_CHAR & BSP_UART_ADR_DETECT_DIS & BSP_UART_RX_OVERRUN_CLEAR)
#define APP_SETTINGS_UART_1_STA							(BSP_UART_INT_TX_BUF_EMPTY & \
														BSP_UART_IrDA_POL_INV_ZERO & \
														BSP_UART_SYNC_BREAK_DISABLED & \
														BSP_UART_TX_ENABLE & \
														BSP_UART_INT_RX_CHAR & \
														BSP_UART_ADR_DETECT_DIS & \
														BSP_UART_RX_OVERRUN_CLEAR)	// FFDD

//														BSP_UART_INT_TX
//														BSP_UART_INT_TX_LAST_CH

// Configure UART receive and transmit interrupt
#define APP_SETTINGS_UART_1_INT							(BSP_UART_RX_INT_DIS & \
														(BSP_UART_RX_INT_PR0 + BSP_UART_1_RX_INTERRUPT_LEVEL) & \
														BSP_UART_TX_INT_DIS & \
														BSP_UART_TX_INT_PR2)
//														(BSP_UART_TX_INT_PR0 + BSP_UART_1_TX_INTERRUPT_LEVEL))

#define APP_SETTINGS_DEBUG_RX_BIN_BUFFER_SIZE			64
#define APP_SETTINGS_DEBUG_RX_ASCIIHEX_BUFFER_SIZE		((APP_SETTINGS_DEBUG_RX_BIN_BUFFER_SIZE * 2) + 4)	// +4 -> (Start_of_Frame + Cmd_Code[2] + End_of_Frame)
#define APP_SETTINGS_DEBUG_TX_BIN_BUFFER_SIZE			64
#define APP_SETTINGS_DEBUG_TX_ASCIIHEX_BUFFER_SIZE		((APP_SETTINGS_DEBUG_TX_BIN_BUFFER_SIZE * 2) + 4)	// +4 -> (Start_of_Frame + Cmd_Code[2] + End_of_Frame)

//*****************************************************************************
//
// UART 1 (DEBUG) App parameters.
//
//*****************************************************************************
//#define APP_SETTINGS_UART_2_BAUDRATE					38400
// Configure UART module to transmit 8 bit data with one stopbit.
#define APP_SETTINGS_UART_2_MODE						(BSP_UART_EN & \
														BSP_UART_IDLE_CON & \
														BSP_UART_IrDA_DISABLE & \
														BSP_UART_MODE_SIMPLEX & \
														BSP_UART_UEN_10 & \
														BSP_UART_DIS_WAKE & \
														BSP_UART_DIS_LOOPBACK & \
														BSP_UART_DIS_ABAUD & \
														BSP_UART_UXRX_IDLE_ONE & \
														BSP_UART_BRGH_SIXTEEN & \
														BSP_UART_1STOPBIT)
//														BSP_UART_NO_PAR_8BIT
//														BSP_UART_MODE_FLOW
//														BSP_UART_UEN_00

//#define STA_VALUE	(BSP_UART_INT_TX_BUF_EMPTY & BSP_UART_TX_ENABLE & BSP_UART_INT_RX_CHAR & BSP_UART_ADR_DETECT_DIS & BSP_UART_RX_OVERRUN_CLEAR)
#define APP_SETTINGS_UART_2_STA							(BSP_UART_INT_TX_BUF_EMPTY & \
														BSP_UART_IrDA_POL_INV_ZERO & \
														BSP_UART_SYNC_BREAK_DISABLED & \
														BSP_UART_TX_ENABLE & \
														BSP_UART_INT_RX_CHAR & \
														BSP_UART_ADR_DETECT_DIS & \
														BSP_UART_RX_OVERRUN_CLEAR)	// FFDD

//														BSP_UART_INT_TX
//														BSP_UART_INT_TX_LAST_CH

// Configure UART receive and transmit interrupt
#define APP_SETTINGS_UART_2_INT							(BSP_UART_RX_INT_DIS & \
														(BSP_UART_RX_INT_PR0 + BSP_UART_2_RX_INTERRUPT_LEVEL) & \
														BSP_UART_TX_INT_DIS & \
														BSP_UART_TX_INT_PR2)
//														(BSP_UART_TX_INT_PR0 + BSP_UART_2_TX_INTERRUPT_LEVEL))

#endif	// CONFIG_UART_H
