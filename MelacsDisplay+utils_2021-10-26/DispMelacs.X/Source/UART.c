#include <stdarg.h>
#include "Common.h"
#include "UART.h"


/******************************************************************************
 * Basic hardware access functions
 *******************************************************************************/
void UART_Init(void)
{
	// 13x divider = 32 MHz / (38,400 bps * 64)
	// (+0.16% error)
	SPBRG1 = 13 - 1;
	BAUDCON1 = 0x00;
	TXSTA1 =
		0x20;  // Enable transmitter
	RCSTA1 = 
		0x80 | // Serial port enabled
		0x10;  // Enable receiver
}

void UART_PutChar(char ch)
{
	if(ch == '\n')
	{
		while(!PIR1bits.TX1IF);
		TXREG1 = '\r';

		// It takes one cycle after writing TXREG for TXIF to get cleared
		Delay1TCY();
	}

 	while(!PIR1bits.TX1IF);
	TXREG1 = ch;
}

char UART_GetChar(void)
{
	while(!PIR1bits.RC1IF);

	if(RCSTA1 & 7)
	{
		RCSTA1bits.CREN = 0;
		RCSTA1bits.CREN = 1;
	}

	return RCREG1;
}


/******************************************************************************
 * High-level printing helpers
 *******************************************************************************/
void UART_PutString(rom const char *ptr)
{
	char ch;
	
	while(ch = *ptr++, ch)
		UART_PutChar(ch);
}

void UART_PutBuffer(const char *ptr)
{
	char ch;

	while(ch = *ptr++, ch)
		UART_PutChar(ch);
}

void UART_PutNumber(unsigned int value, signed char width, unsigned char radix)
{
	char buffer[16];
	char *ptr = &buffer[sizeof buffer - 1];

	*ptr = '\0';

	do
	{
		unsigned char ch = value;
		value /= radix;
		ch -= (unsigned char) value * radix;
		if(ch > 9)
			ch += 'A' - '9' - 1;
		ch += '0';
		*--ptr = ch;
	}
	while(--width > 0 || value);

	UART_PutBuffer(ptr);
}


/******************************************************************************
 * Simple printf-like tracing function
 ******************************************************************************/
void Trace(const char rom *format, ...)
{
	unsigned char ch;
	va_list args;

	va_start(args, format);

	while(ch = *format++, ch)
	{
		unsigned char width;

		if(ch != '%')
		{
			UART_PutChar(ch);
			continue;
		}

		width = 0;

		while(ch = *format++ - '0', ch <= 9)
		{
			width *= 10;
			width += ch;
		}

		ch += '0';

		switch(ch)
		{
		case 'c': UART_PutChar(va_arg(args, char /* unpromoted */)); break;
		case 'b': UART_PutNumber(va_arg(args, unsigned char), width, 2); break;
		case 'u': UART_PutNumber(va_arg(args, unsigned int), width, 10); break;
		case 'x': UART_PutNumber(va_arg(args, unsigned int), width, 16); break;
		case 's': UART_PutBuffer(va_arg(args, const char *)); break;
		case 'S': UART_PutString(va_arg(args, const char rom *)); break;
		}
	}
	
	va_end(args);
}