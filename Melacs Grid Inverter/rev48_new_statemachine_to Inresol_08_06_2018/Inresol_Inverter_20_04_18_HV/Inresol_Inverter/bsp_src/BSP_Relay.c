/*
 *  File name: BSP_Relay.c
 *
 *  Description: Board Support Package function implementations for Relays processing
 *
 *  Author: Future Electronics
 *
 */

#include "global_includes.h"

//#define TST_FLAG_ENABLED

void BSP_Relay_Init(void)
{
#ifdef GPIO_RLY_INV_P_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_RLY_INV_P_PORTPIN);	// Configures pin RLY_INV as output
	BSP_IO_GPIO_CLR(GPIO_RLY_INV_P_PORTPIN);		// RLY_INV Low
#endif
#ifdef GPIO_RLY_INV_N_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_RLY_INV_N_PORTPIN);	// Configures pin RLY_INV_N as output
	BSP_IO_GPIO_CLR(GPIO_RLY_INV_N_PORTPIN);		// RLY_INV_N Low
#endif
#ifdef GPIO_RLY_GRID_P_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_RLY_GRID_P_PORTPIN);	// Configures pin RLY_GRID as output
	BSP_IO_GPIO_CLR(GPIO_RLY_GRID_P_PORTPIN);		// RLY_GRID Low
#endif
#ifdef GPIO_RLY_GRID_N_PORTPIN
	BSP_IO_GPIO_DIR_OUT(GPIO_RLY_GRID_N_PORTPIN);	// Configures pin RLY_GRID_N as output
	BSP_IO_GPIO_CLR(GPIO_RLY_GRID_N_PORTPIN);		// RLY_GRID_N Low
#endif
}

void BSP_Relay_Inv_Phase_On(void)
{
#ifdef GPIO_RLY_INV_P_PORTPIN
	BSP_IO_GPIO_SET(GPIO_RLY_INV_P_PORTPIN);		// RLY_INV High
#endif
#if ((defined GPIO_TST3_PORTPIN) && (defined TST_FLAG_ENABLED))
	BSP_IO_GPIO_SET(GPIO_TST3_PORTPIN);				// Flag TST3 High
#endif
}

void BSP_Relay_Inv_Phase_Off(void)
{
#ifdef GPIO_RLY_INV_P_PORTPIN
	BSP_IO_GPIO_CLR(GPIO_RLY_INV_P_PORTPIN);		// RLY_INV Low
#endif
#if ((defined GPIO_TST3_PORTPIN) && (defined TST_FLAG_ENABLED))
	BSP_IO_GPIO_CLR(GPIO_TST3_PORTPIN);				// Flag TST3 Low
#endif
}

bool BSP_Relay_Inv_Phase_Get(void)
{
#ifndef TST_FLAG_ENABLED
#ifdef GPIO_RLY_INV_P_PORTPIN
	if(BSP_IO_GPIO_OUT_STATUS(GPIO_RLY_INV_P_PORTPIN))
		return true;
#endif
#else	// TST_FLAG_ENABLED
#ifdef GPIO_TST3_PORTPIN
	if(BSP_IO_GPIO_OUT_STATUS(GPIO_TST3_PORTPIN))
		return true;
#endif
#endif	// TST_FLAG_ENABLED
	return false;
}

void BSP_Relay_Inv_Neutral_On(void)
{
#ifdef GPIO_RLY_INV_N_PORTPIN
	BSP_IO_GPIO_SET(GPIO_RLY_INV_N_PORTPIN);		// RLY_INV_N High
#endif
}

void BSP_Relay_Inv_Neutral_Off(void)
{
#ifdef GPIO_RLY_INV_N_PORTPIN
	BSP_IO_GPIO_CLR(GPIO_RLY_INV_N_PORTPIN);		// RLY_INV_N Low
#endif
}

bool BSP_Relay_Inv_Neutral_Get(void)
{
#ifdef GPIO_RLY_INV_N_PORTPIN
	if(BSP_IO_GPIO_OUT_STATUS(GPIO_RLY_INV_N_PORTPIN))
		return true;
#endif
	return false;
}

void BSP_Relay_Grid_Phase_On(void)
{
#ifdef GPIO_RLY_GRID_P_PORTPIN
	BSP_IO_GPIO_SET(GPIO_RLY_GRID_P_PORTPIN);		// RLY_GID High
#endif
}

void BSP_Relay_Grid_Phase_Off(void)
{
#ifdef GPIO_RLY_GRID_P_PORTPIN
	BSP_IO_GPIO_CLR(GPIO_RLY_GRID_P_PORTPIN);		// RLY_GRID Low
#endif
}

bool BSP_Relay_Grid_Phase_Get(void)
{
#ifdef GPIO_RLY_GRID_P_PORTPIN
	if(BSP_IO_GPIO_OUT_STATUS(GPIO_RLY_GRID_P_PORTPIN))
		return true;
#endif
	return false;
}

void BSP_Relay_Grid_Neutral_On(void)
{
#ifdef GPIO_RLY_GRID_N_PORTPIN
	BSP_IO_GPIO_SET(GPIO_RLY_GRID_N_PORTPIN);		// RLY_GRID_N High
#endif
}

void BSP_Relay_Grid_Neutral_Off(void)
{
#ifdef GPIO_RLY_GRID_N_PORTPIN
	BSP_IO_GPIO_CLR(GPIO_RLY_GRID_N_PORTPIN);		// RLY_GRID_N Low
#endif
}

bool BSP_Relay_Grid_Neutral_Get(void)
{
#ifdef GPIO_RLY_GRID_N_PORTPIN
	if(BSP_IO_GPIO_OUT_STATUS(GPIO_RLY_GRID_N_PORTPIN))
		return true;
#endif
	return false;
}
