/******************************************************************************
 * Serial communication at 38400 bps. This is mostly useful for debugging traces
 ******************************************************************************/
#ifndef _UART_H
#define _UART_H

void UART_Init(void);
void UART_PutChar(char ch);
char UART_GetChar(void);
void UART_PutString(rom const char *ptr);
void UART_PutBuffer(const char *ptr);
void UART_PutNumber(unsigned int value, signed char width, unsigned char radix);

#define UART_Ready() (PIR1bits.RC1IF)

#endif