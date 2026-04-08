/*
 *  File name: types_system.h
 *
 *  Description: Type definitions for System
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_SYSTEM_H
#define TYPES_SYSTEM_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_RST
{
	RST_POR = 0,
	RST_BOR,
	RST_IDLE,
	RST_SLEEP,
	RST_WDTO,
	RST_SWDTEN,
	RST_SWR,
	RST_EXTR,
	RST_VREGS,
	RST_CM,
	RST_UNIMPLEMENTED0,
	RST_VREGSF,
	RST_UNIMPLEMENTED1,
	RST_UNIMPLEMENTED2,
	RST_IOPUWR,
	RST_TRAPR
} RST_t;

#endif	// TYPES_SYSTEM_H
