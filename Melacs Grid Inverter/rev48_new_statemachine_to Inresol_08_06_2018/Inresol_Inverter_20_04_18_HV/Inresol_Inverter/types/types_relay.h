/*
 *  File name: types_relay.h
 *
 *  Description: Type definitions for Relays
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_RELAY_H
#define TYPES_RELAY_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum tag_Relay_Type
{
	APP_RELAY_INV_PHASE = 0,
	APP_RELAY_INV_NEUTRAL,
	APP_RELAY_GRID_PHASE,
	APP_RELAY_GRID_NEUTRAL,
	APP_RELAY_MAX
} Relay_Type_t;

#endif	// TYPES_RELAY_H
