/*
 *  File name: types_datarec.h
 *
 *  Description: Type definitions for Data Recording
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_DATAREC_H
#define TYPES_DATAREC_H

/*****************/
/* Basic Defines */
/*****************/

typedef enum RecStatusType_e {
	REC_DATA_READY = 0,
	REC_DATA_REREAD
} RecStatusType_t;

typedef enum RecControlType_e {
	REC_CONTROL_REINIT = 0,
	REC_CONTROL_REREAD
} RecControlType_t;

#endif	// TYPES_DATAREC_H
