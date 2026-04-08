/*
 * FreeModbus Port Library: dsPIC
 * Copyright (C) 2018 Future Electronics
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Variables ----------------------------------------*/
static eMBEventType eQueuedEvent;
static BOOL     xEventInQueue;

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortEventInit( void )
{
	xEventInQueue = FALSE;
	return TRUE;
}

BOOL xMBPortEventPost( eMBEventType eEvent )
{
	eQueuedEvent = eEvent;
	xEventInQueue = TRUE;
	return TRUE;
}

BOOL xMBPortEventGet( eMBEventType * eEvent )
{
	BOOL	xEventHappened = FALSE;

	if( xEventInQueue ) {
		*eEvent = eQueuedEvent;
		xEventInQueue = FALSE;
		xEventHappened = TRUE;
	}
	return xEventHappened;
}
