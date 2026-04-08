/*
 *  File name: BSP_UART.h
 *
 *  Description: Board Support Package function declarations for UART processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_UART_H
#define BSP_UART_H

void BSP_UART_1_Config_Pins(void);
void BSP_UART_1_Set_Baudrate(uint32_t Baudrate);
void BSP_UART_1_Set_Mode(uint16_t Mode);
void BSP_UART_1_Set_Sta(uint16_t Sta);
void BSP_UART_1_Set_Int(uint16_t Int);
void BSP_UART_1_Init(uint16_t Mode, uint16_t Sta, uint32_t Baudrate);
void BSP_UART_1_DeInit(void);
inline void BSP_UART_1_Rx_Interrupt_Enable(void);
inline void BSP_UART_1_Tx_Interrupt_Enable(void);
inline void BSP_UART_1_Rx_Interrupt_Disable(void);
inline void BSP_UART_1_Tx_Interrupt_Disable(void);
inline void BSP_UART_1_Rx_Interrupt_Clear(void);
inline void BSP_UART_1_Tx_Interrupt_Clear(void);
inline void BSP_UART_1_Rx_Interrupt_Priority(uint8_t Priority);
inline void BSP_UART_1_Tx_Interrupt_Priority(uint8_t Priority);
int BSP_UART_1_Send_Data_Blocking(const void *data, uint16_t length);
int BSP_UART_1_Send_Data_NoBlocking(const void *data, uint16_t length);
int BSP_UART_1_Receive_Data(void *data, uint16_t size);

void BSP_UART_2_Config_Pins(void);
void BSP_UART_2_Set_Baudrate(uint32_t Baudrate);
void BSP_UART_2_Set_Mode(uint16_t Mode);
void BSP_UART_2_Set_Sta(uint16_t Sta);
void BSP_UART_2_Set_Int(uint16_t Int);
void BSP_UART_2_Init(uint16_t Mode, uint16_t Sta, uint32_t Baudrate);
void BSP_UART_2_DeInit(void);
inline void BSP_UART_2_Rx_Interrupt_Enable(void);
inline void BSP_UART_2_Tx_Interrupt_Enable(void);
inline void BSP_UART_2_Rx_Interrupt_Disable(void);
inline void BSP_UART_2_Tx_Interrupt_Disable(void);
inline void BSP_UART_2_Rx_Interrupt_Clear(void);
inline void BSP_UART_2_Tx_Interrupt_Clear(void);
inline void BSP_UART_2_Rx_Interrupt_Priority(uint8_t Priority);
inline void BSP_UART_2_Tx_Interrupt_Priority(uint8_t Priority);
int BSP_UART_2_Send_Data_Blocking(const void *data, uint16_t length);
int BSP_UART_2_Send_Data_NoBlocking(const void *data, uint16_t length);
int BSP_UART_2_Receive_Data(void *data, uint16_t size);
/*inline*/ void BSP_UART_2_Write_Byte(uint8_t data);
/*inline*/ uint8_t BSP_UART_2_Read_Byte(void);
/*inline*/ bool BSP_UART_2_Ready_for_Write(void);
void BSP_UART_2_Rx_Flush(void);

#endif // BSP_UART_H
