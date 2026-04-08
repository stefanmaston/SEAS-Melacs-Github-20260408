/*
 * FreeModbus Port Library: dsPIC
 * Copyright (C) 2018 Future Electronics
 */

/* ----------------------- Platform includes --------------------------------*/
#include "global_includes.h"
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

void vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
	if(xRxEnable) {
		BSP_UART_2_Rx_Flush();
		BSP_UART_2_Rx_Interrupt_Enable();
		if(xTxEnable) {
			BSP_UART_2_Tx_Interrupt_Enable();
		} else {
			BSP_UART_2_Tx_Interrupt_Disable();
			BSP_UART_2_Tx_Interrupt_Clear();
		}
	} else {
		BSP_UART_2_Rx_Interrupt_Disable();
		BSP_UART_2_Rx_Interrupt_Clear();
		if(xTxEnable) {
			BSP_UART_2_Tx_Interrupt_Enable();
		} else {
			BSP_UART_2_Tx_Interrupt_Disable();
			BSP_UART_2_Tx_Interrupt_Clear();
		}
	}
}

BOOL xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	USHORT usMode = APP_SETTINGS_UART_2_MODE;

	(void)ucPORT;

	switch(eParity) {
		case MB_PAR_EVEN:
			usMode &= BSP_UART_EVEN_PAR_8BIT;
			break;
		case MB_PAR_ODD:
			usMode &= BSP_UART_ODD_PAR_8BIT;
			break;
		case MB_PAR_NONE:
			switch(ucDataBits) {
				case 8:
					usMode &= BSP_UART_NO_PAR_8BIT;
					break;
				case 9:
					usMode &= BSP_UART_NO_PAR_9BIT;
					break;
			}
			break;
	}

	BSP_UART_2_Config_Pins();
	BSP_UART_2_DeInit();
	BSP_UART_2_Set_Int(APP_SETTINGS_UART_2_INT);
	BSP_UART_2_Init(usMode, APP_SETTINGS_UART_2_STA, ulBaudRate);

    vMBPortSerialEnable( FALSE, FALSE );

	return TRUE;
}

void vMBPortClose(void)
{
	// Not needed
}

void xMBPortSerialClose(void)
{
	// Not needed
}

BOOL xMBPortSerialPutByte( CHAR ucByte )
{
	BSP_UART_2_Write_Byte(ucByte);
    return TRUE;
}

BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
	*pucByte = BSP_UART_2_Read_Byte();
    return TRUE;
}

void vMBPortUartTxInterrupt(void)
{
	(void)pxMBFrameCBTransmitterEmpty();
}

void vMBPortUartRxInterrupt(void)
{
	(void)pxMBFrameCBByteReceived();
}
