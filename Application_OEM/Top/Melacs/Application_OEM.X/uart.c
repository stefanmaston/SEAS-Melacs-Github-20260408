#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include "main.h"
#include <GenericTypeDefs.h>
#include <plib.h>
#include "UART.h"
#include <sys/attribs.h>
#include "configurations.h"
#include <stdio.h>
#include <xc.h>
#include<unistd.h>
#include <stdlib.h>
#include <mrendez.h>
#include <sys/interrupt.h>
#include "display.h"
#include <string.h>
#include "delay.h"
#include "modbus.h"
#include "sd_spi.h"

#define MELCSPI3			LATDbits.LATD5      // RAN485EN IN PORTD RD5 in PIC32MX795512L JP27P2   
#define MEL_SPICLK          LATFbits.LATF3      //REC485EN RF3
extern uint8_t mutexresult[8];
    
Serial_Instance_t Serial_Instance;
        
UART_DATA c;
struct Transmit {
  UART_DATA message[64];
  int header;
  int tail;
  int size;
} Transmit;

void IntUart5Handler(uint_32 arg);
THREAD UartMain(void *);

void UARTThread (){
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
    
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 2;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 1024);             

    if(pthread_create(&pid, &attr, &UartMain, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return; 
}


THREAD UartMain (void *arg)
{
    Uart_Init();
    i_set_interrupt(_UART_5_VECTOR,IntUart5Handler, 0 );
    INTSetVectorPriority(INT_VECTOR_UART(UART5), INT_PRIORITY_LEVEL_5); //1 lowest 7 highest
    INTSetVectorSubPriority(INT_VECTOR_UART(UART5), INT_SUB_PRIORITY_LEVEL_1); // 0 lowest 3 Highest
    uint16_t RLY[1] = {15};
    uint16_t DDS_READING_CHANGE_VALUE[6] = 
       {
        Modbus_FreqCalculator(65.0), 
        Modbus_PhaseCalculator(258.7), 
        Modbus_PhaseCalculator(155.9),
        Modbus_GainCalculator(0.983), 
        Modbus_GainCalculator(0.432),
        Modbus_GainCalculator(0.234)
        };
    Modbus_Client_Run(RLY, DDS_READING_CHANGE_VALUE);  
    
}

void Uart_Init()
{   
    AD1PCFG = 0;

    UARTConfigure(UART5, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART5, UART_INTERRUPT_ON_TX_DONE | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART5, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART5, PBCLK, DESIRED_BAUDRATE);
    UARTEnable(UART5, UART_ENABLE_FLAGS(UART_PERIPHERAL| UART_RX | UART_TX));
    MEMLED2_DIR = 0;
    MEMLED2 = 1;
    
    
    MEMLED_DIR = 0;
    MEMLED = 1;
}

void IntUart5Handler(uint_32 arg)
{   
	if(INTGetFlag(INT_SOURCE_UART_RX(UART5)))
	{   
        INTClearFlag(INT_SOURCE_UART_RX(UART5));
       
        if(_U1STA_URXDA_MASK == (uartReg[UART5]->sta.reg & _U1STA_URXDA_MASK))
        {   
            Serial_Buffer_t *p = &Serial_Instance.receive;            
            c = UARTGetData(UART5);
            
            p->buffer[p->head] = (c.data8bit);
            p->head++;
            p->timer_receive = Timer_Reset();
        }
	}
	
	if (INTGetFlag(INT_U5TX))    
	{  
        Serial_UartRxMode();
	}
}


void Serial_SendPacket(uint8_t buffer[MODBUS_BUFFER_SIZE],  uint8_t length)
{
    uint8_t i;
    
    Serial_UartTxMode();
    
    for (i = 0; i < length; i++)
        PutCharacter(buffer[i]);
    
    DelayUs(303);
    IEC2bits.U5TXIE = 1;
  
}
bool Serial_Add(uint8_t data)
{ 
    Serial_Buffer_t *p = &Serial_Instance.transmit;
    
    p->buffer[p->head] = data;
    p->head++;
    return true; 
}

void Serial_UartTxMode(void)
{
    //IFS2bits.U5RXIF = 0; //Reset interrupt flag
    MEL_SPICLK = 1; //Activate Receiver. From Inverter Active == 0; Deactive == 1
    MELCSPI3 = 1;    // Activate the Transmitter To Inverter Active ==1 deactive ==0
    IFS2bits.U5TXIF = 1;
    IEC2bits.U5RXIE = 0; //Interrupt disable for receive
    IEC2bits.U5TXIE = 0;
    
}

void Serial_UartRxMode(void)
{
    MEL_SPICLK = 0; //Activate Receiver. From Inverter Active == 0; Deactive == 1
    MELCSPI3 = 0; // Activate the Transmitter To Inverter Active ==1 deactive ==0 
    IFS2bits.U5RXIF = 0;
    IFS2bits.U5TXIF = 0;
    IEC2bits.U5TXIE = 0;
    if(U5STAbits.OERR)
     U5STAbits.OERR= 0;
    IEC2bits.U5RXIE = 1; //Interrupt Enable for receive
    
}
void PutCharacter(const char character)
{
   
    do{while(!U5STAbits.TRMT); U5TXREG = (int)(character);}while(0);
    
}

