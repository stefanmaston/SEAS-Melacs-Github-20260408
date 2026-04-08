/*
 * FreeModbus Port Library: dsPIC
 * Copyright (C) 2018 Future Electronics
 */

#ifndef _PORT_H
#define _PORT_H

#include <assert.h>
#include <stdint.h>
#include "global_includes.h"

#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

// Info: dsPIC Reference Manual - Interrupts
#if 1
#define DisableInterrupts()			asm volatile ("disi #0x3FFF")
#define EnableInterrupts()			asm volatile ("disi #0x0000")
#else
#define DisableInterrupts()			INTCON2bits.GIE = 0
#define EnableInterrupts()			INTCON2bits.GIE = 1
#endif

#if 0	// Disabling/Enabling of all interrupts is removed due to spikes on PWM outputs
#define ENTER_CRITICAL_SECTION()	DisableInterrupts()
#define EXIT_CRITICAL_SECTION()		EnableInterrupts()
#else
#define ENTER_CRITICAL_SECTION()
#define EXIT_CRITICAL_SECTION()
#endif

typedef uint8_t    BOOL;

typedef unsigned char UCHAR;
typedef signed char    CHAR;

typedef uint16_t USHORT;
typedef int16_t  SHORT;

typedef uint32_t ULONG;
typedef int32_t   LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#endif
