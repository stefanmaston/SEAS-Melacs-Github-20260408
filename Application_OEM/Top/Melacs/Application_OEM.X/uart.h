#include "modbus_client.h"
#include <stdbool.h>
#include "delay.h"

#define MEMLED2          LATGbits.LATG14
//#define MEMLED2          PORTGbits.RG14
#define MEMLED2_DIR      TRISGbits.TRISG14
#define MEMLED          LATFbits.LATF1
//#define MEMLED          PORTFbits.RF1
#define MEMLED_DIR      TRISFbits.TRISF1

#define LED3          LATAbits.LATA2
#define LED3_DIR      TRISAbits.TRISA2
#define LED1          LATAbits.LATA3
#define LED1_DIR      TRISAbits.TRISA3

#define LED4          LATBbits.LATB12
#define LED4_DIR      TRISBbits.TRISB12
#define LED2          LATAbits.LATA1
#define LED2_DIR      TRISAbits.TRISA1
#define Inverter_01 0x01

typedef struct Serial_Buffer_tag
{
	Timer_t timer_receive;
	uint32_t overflow_counter;
	uint8_t head;
	uint8_t tail;
	uint8_t buffer[MODBUS_BUFFER_SIZE];
    bool check; 
} Serial_Buffer_t;

typedef struct Serial_Instance_tag
{
	Serial_Buffer_t transmit;
	Serial_Buffer_t receive;
} Serial_Instance_t;

#ifdef _UART_
void Uart_Init();
void clear_buffer();  
//void WriteString(const char *string);
bool Serial_Add(uint8_t data);
void PutCharacter(const char character);
void ModbustransmitOn();
void ModbusReceiveOn();
void UARTThread ();
void Serial_SendPacket(uint8_t *buffer,  uint8_t length);
//void Serial_UartStart(void);
void Serial_UartTxMode(void);

void Serial_UartRxMode(void);
/*
void Serial_Receive(void)
void Serial_Send(void);
*/
#endif