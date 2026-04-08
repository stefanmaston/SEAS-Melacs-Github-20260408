/*
 *  File name: App_Relay.h
 *
 *  Description: High level function declarations for Relays processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef APP_RELAY_H
#define APP_RELAY_H

extern volatile uint8_t	RelaysState;

void App_Relay_Init(void *Parameters);
void App_Relay_Process(void *Parameters);
void App_Relay_On(uint8_t Relay);
void App_Relay_Off(uint8_t Relay);

#endif // APP_RELAY_H
