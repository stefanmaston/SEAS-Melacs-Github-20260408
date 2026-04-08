/*
 *  File name: BSP_IO.h
 *
 *  Description: Board Support Package function declarations for I/O processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_IO_H
#define BSP_IO_H

#define iBSP_IO_GPIO_OUT(portpin)			_LAT##portpin
#define BSP_IO_GPIO_CLR(portpin)			iBSP_IO_GPIO_OUT(portpin) = 0
#define BSP_IO_GPIO_SET(portpin)			iBSP_IO_GPIO_OUT(portpin) = 1
#define BSP_IO_GPIO_TGL(portpin)			iBSP_IO_GPIO_OUT(portpin) ^= 1
#define BSP_IO_GPIO_OUT_STATUS(portpin)		iBSP_IO_GPIO_OUT(portpin)
#define iBSP_IO_GPIO_INP(portpin)			_R##portpin
#define BSP_IO_GPIO_INP_STATUS(portpin)		iBSP_IO_GPIO_INP(portpin)
#define iBSP_IO_GPIO_DIR(portpin)			_TRIS##portpin
#define BSP_IO_GPIO_DIR_IN(portpin)			iBSP_IO_GPIO_DIR(portpin) = 1
#define BSP_IO_GPIO_DIR_OUT(portpin)		iBSP_IO_GPIO_DIR(portpin) = 0
#define iBSP_IO_GPIO_PU(portpin)			_CNPU##portpin
#define BSP_IO_GPIO_PU_ON(portpin)			iBSP_IO_GPIO_PU(portpin) = 1
#define BSP_IO_GPIO_PU_OFF(portpin)			iBSP_IO_GPIO_PU(portpin) = 0
#define iBSP_IO_GPIO_PD(portpin)			_CNPD##portpin
#define BSP_IO_GPIO_PD_ON(portpin)			iBSP_IO_GPIO_PD(portpin) = 1
#define BSP_IO_GPIO_PD_OFF(portpin)			iBSP_IO_GPIO_PD(portpin) = 0
#define iBSP_IO_GPIO_ANSEL(portpin)			_ANS##portpin
#define BSP_IO_GPIO_AN_ON(portpin)			iBSP_IO_GPIO_ANSEL(portpin) = 1

#define BSP_IO_PPS_UnLock()					__builtin_write_OSCCONL(OSCCON & 0xBF)
//#define BSP_IO_PPS_Lock()					__builtin_write_OSCCONL(OSCCON | 0x40)
#define BSP_IO_PPS_Lock()

#define iBSP_IO_PPS_Set_Input(fn, pin)		fn = pin
#define BSP_IO_PPS_Set_Input(fn, pin)		iBSP_IO_PPS_Set_Input(fn, pin)

#define iBSP_IO_PPS_Set_Output(pin, fn)		pin = fn
#define BSP_IO_PPS_Set_Output(fn, pin)		iBSP_IO_PPS_Set_Output(pin, fn)

#define BSP_IO_PPS_IN_FN_U1RX				RPINR18bits.U1RXR
#define BSP_IO_PPS_OUT_FN_U1TX				0x01

#define BSP_IO_PPS_IN_FN_U2RX				RPINR19bits.U2RXR
#define BSP_IO_PPS_OUT_FN_U2TX				0x03

#define BSP_IO_PPS_IN_FN_U2CTS				RPINR19bits.U2CTSR
#define BSP_IO_PPS_OUT_FN_U2RTS				0x04
#if ((!defined EVAL_BOARD) && (!defined PINS28_STARTER_BOARD))
// Inresol Inverter
//#define BSP_IO_PPS_IN_PIN_U1RX				62
//#define BSP_IO_PPS_OUT_PIN_U1TX				RPOR17bits.RP63R
#define BSP_IO_PPS_IN_PIN_U1RX				UART1_RX_REMAP
#if UART1_TX_REMAP == 61
#define BSP_IO_PPS_OUT_PIN_U1TX				RPOR16bits.RP61R
#elif UART1_TX_REMAP == 63
#define BSP_IO_PPS_OUT_PIN_U1TX				RPOR17bits.RP63R
#endif
#define BSP_IO_PPS_IN_PIN_U2RX				UART2_RX_REMAP
#if UART2_TX_REMAP == 61
#define BSP_IO_PPS_OUT_PIN_U2TX				RPOR16bits.RP61R
#elif UART2_TX_REMAP == 63
#define BSP_IO_PPS_OUT_PIN_U2TX				RPOR17bits.RP63R
#endif
#define BSP_IO_PPS_IN_PIN_U2CTS				UART2_TXEN_REMAP
#if UART2_TXEN_REMAP == 36
#define BSP_IO_PPS_OUT_PIN_U2RTS			RPOR4bits.RP36R
#endif
#elif (!defined PINS28_STARTER_BOARD)
// Engineering Sample Evaluation Board
#define BSP_IO_PPS_IN_PIN_U1RX				UART1_RX_REMAP
#if UART1_TX_REMAP == 62
#define BSP_IO_PPS_OUT_PIN_U1TX				RPOR16bits.RP62R
#endif
#define BSP_IO_PPS_IN_PIN_U2RX				UART2_RX_REMAP
#if UART2_TX_REMAP == 34
#define BSP_IO_PPS_OUT_PIN_U2TX				RPOR3bits.RP34R
#endif
#else
// 28-pins Starter Board
#define BSP_IO_PPS_IN_PIN_U1RX				UART1_RX_REMAP
#if UART1_TX_REMAP == 38
#define BSP_IO_PPS_OUT_PIN_U1TX				RPOR3bits.RP38R
#endif
#endif

void BSP_IO_Pins_DeInit(void);
void BSP_IO_Pins_Init(void);

#endif	// BSP_IO_H
