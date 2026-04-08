/*
 *  File name: BSP_Relay.h
 *
 *  Description: Board Support Package function declarations for Relays processing
 *
 *  Author: Future Electronics
 *
 */

#ifndef BSP_RELAY_H
#define BSP_RELAY_H

void BSP_Relay_Init(void);
void BSP_Relay_Inv_Phase_On(void);
void BSP_Relay_Inv_Phase_Off(void);
bool BSP_Relay_Inv_Phase_Get(void);
void BSP_Relay_Inv_Neutral_On(void);
void BSP_Relay_Inv_Neutral_Off(void);
bool BSP_Relay_Inv_Neutral_Get(void);
void BSP_Relay_Grid_Phase_On(void);
void BSP_Relay_Grid_Phase_Off(void);
bool BSP_Relay_Grid_Phase_Get(void);
void BSP_Relay_Grid_Neutral_On(void);
void BSP_Relay_Grid_Neutral_Off(void);
bool BSP_Relay_Grid_Neutral_Get(void);

#endif	// BSP_RELAY_H
