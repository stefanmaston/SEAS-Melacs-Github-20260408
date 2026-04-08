/*
 *  File name: App_MODBUS.h
 *
 *  Description: High level function declarations for MODBUS RTU processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_MODBUS_H
#define APP_MODBUS_H

void App_MODBUS_Init(void *Parameters);
void App_MODBUS_Process(void *Parameters);
void vMBPortTimerInterrupt(void);
void vMBPortUartTxInterrupt(void);
void vMBPortUartRxInterrupt(void);

#endif // APP_MODBUS_H
