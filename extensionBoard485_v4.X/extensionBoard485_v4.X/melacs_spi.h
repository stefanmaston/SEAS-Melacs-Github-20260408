/* 
 * File:   melacs_spi.h
 * Author: Bala
 *
 * Created on June 18, 2015, 3:57 PM
 */

#ifndef MELACS_SPI_H
#define	MELACS_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "main.h"
#include "stdint.h"


#define SPI_STATbits	(SPI3STATbits)
#define SPI_STAT_CLR	(SPI3STATCLR)
#define SPICON		(SPI3CON)
#define SPICONbits	(SPI3CONbits)
#define SPIBRG		(SPI3BRG)
#define SPIBUF   	(SPI3BUF)
#define SPI_RFIF_BIT 	(IFS0bits.SPI3RXIF)

uint8_t Master_SPI_Receive();
uint8_t Master_SPI_Send(uint8_t data);
uint8_t Slave_SPI_Receive();
uint8_t Slave_SPI_send(uint8_t data);
void Slave_SPI_clear_stat();
void Master_SPI_Init();
void Slave_SPI_Init();
void Master_SPI_Select();
void Master_SPI_Deselect();

#define SPI_MAX_MSG_SIZE 46
#define START_BYTE 1

//Command Bytes
#define DISPLAY_STRING 02
#define ENQUIRY 03
#define MOTOR_CONTROL 04



#ifdef	__cplusplus
}
#endif

#endif	/* MELACS_SPI_H */

