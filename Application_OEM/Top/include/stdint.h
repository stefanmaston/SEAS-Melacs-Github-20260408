/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2013 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
*                           ALL RIGHTS RESERVED
*
*   This computer program is the property of RoweBots Research Inc.,
*   Kitchener, Ontario Canada. and may not be copied or redistributed in any 
*   form or by any means, whether in part or in whole, except under license 
*   granted by RoweBots Research Inc.
*
*   All copies of this program, whether in part or in whole, and whether 
*   modified or not, must display this and all other embedded copyright and 
*   ownership notices in full.  This notice may not be modified.
*
*   All source code is protected by international copyright laws and license
*   agreements.  Do not break the law.  You can obtain a license and source
*   code at rowebots.com subject to licensing conditions and restrictions.
*   Free development, free source code and free non commercial licenses may
*   be obtained in a few seconds on line without any difficult process.
*
*   All demonstration programs may be redistributed as source code to others  
*   as a small part of a Unison or DSPnano application. 
*
* ******************************************************************************   
*
*
*   Save Time and Money.  If you need modifications to the software to support
*   specific processors or peripherals, RoweBots Research can do this for you
*   quickly and easily at low cost.  If you need help with application develop-
*   ment, again we can solve your embedded development problems quickly and 
*   easily at very attractive prices.  We are tiny tiny embedded Linux* experts,
*   let us reduce your risk, accelerate your development and slash your time 
*   to market.  See rowebots.com - contact us.
*
*
*******************************************************************************/

#ifndef __STDINT_H__
#define __STDINT_H__

#include <bits/local_lim.h>
#include <nano_limits.h>
#include <sys/types.h>


#if __SUPPORT_LONG_LONG > 0
#define __u_int64_defined__
#endif

/****************** Pre-processor Definitions ******************/
#define INT8_MIN            0x80
#define INT8_MAX            0x7f
#define UINT8_MAX           0xff

#define INT16_MIN           0x8000
#define INT16_MAX           0x7fff
#define UINT16_MAX          0xffff

#ifdef __u_int24_defined__
#  define INT24_MIN         0x800000
#  define INT24_MAX         0x7fffff
#  define UINT24_MAX        0xffffff
#endif

#define INT32_MIN           0x80000000
#define INT32_MAX           0x7fffffff
#define UINT32_MAX          0xffffffff

#ifdef __u_int64_defined__
#  define INT64_MIN         0x8000000000000000
#  define INT64_MAX         0x7fffffffffffffff
#  define UINT64_MAX        0xffffffffffffffff
#endif

// Limits of minimum-width integer types

#define INT8_LEASTN_MIN     0x80
#define INT8_LEASTN_MAX     0x7f
#define UINT8_LEASTN_MAX    0xff

#define INT16_LEASTN_MIN    0x8000
#define INT16_LEASTN_MAX    0x7fff
#define UINT16_LEASTN_MAX   0xffff

#ifdef __u_int24_defined__
#  define INT24_LEASTN_MIN  0x800000
#  define INT24_LEASTN_MAX  0x7fffff
#  define UINT24_LEASTN_MAX 0xffffff
#endif

#define INT32_LEASTN_MIN    0x80000000
#define INT32_LEASTN_MAX    0x7fffffff
#define UINT32_LEASTN_MAX   0xffffffff

#ifdef __u_int64_defined__
#  define INT64_LEASTN_MIN  0x8000000000000000
#  define INT64_LEASTN_MAX  0x7fffffffffffffff
#  define UINT64_LEASTN_MAX 0xffffffffffffffff
#endif

//Limits of fastest minimum-width integer types

#define INT8_FASTN_MIN      0x80
#define INT8_FASTN_MAX      0x7f
#define UINT8_FASTN_MAX     0xff

#define INT16_FASTN_MIN     0x8000
#define INT16_FASTN_MAX     0x7fff
#define UINT16_FASTN_MAX    0xffff

#ifdef __u_int24_defined__
#  define INT24_FASTN_MIN   0x800000
#  define INT24_FASTN_MAX   0x7fffff
#  define UINT24_FASTN_MAX  0xffffff
#endif

#define INT32_FASTN_MIN     0x80000000
#define INT32_FASTN_MAX     0x7fffffff
#define UINT32_FASTN_MAX    0xffffffff

#ifdef __u_int64_defined__
#  define INT64_FASTN_MIN   0x8000000000000000
#  define INT64_FASTN_MAX   0x7fffffffffffffff
#  define UINT64_FASTN_MAX  0xffffffffffffffff
#endif

//Limits of integer types capable of holding object pointers

#define INTPTR_MIN          PTR_MIN
#define INTPTR_MAX          PTR_MIN
#define UINTPTR_MAX         UPTR_MAX

//Limits of greatest-width integer types
#ifdef __u_int64_defined__
#  define INTMAX_MIN        INT64_MIN
#  define INTMAX_MAX        INT64_MAX

#  define UINTMAX_MIN       UINT64_MIN
#  define UINTMAX_MAX       UINT64_MAX
#else
#  define INTMAX_MIN        INT32_MIN
#  define INTMAX_MAX        INT32_MAX

#  define UINTMAX_MIN       UINT32_MIN
#  define UINTMAX_MAX       UINT32_MAX
#endif

//Macros for minimum-width integer constant expressions
#define INT8_C(x) x
#define INT16_C(x) x
#define INT32_C(x) x ## L
#define INT64_C(x) x ## LL

#define UINT8_C(x) x
#define UINT16_C(x) x
#define UINT32_C(x) x ## UL
#define UINT64_C(x) x ## ULL


//Macros for greatest-width integer constant expressions
#if __SUPPORT_LONG_LONG > 0
#  define INTMAX_C(x) x ## LL
#  define UINTMAX_C(x) x ## ULL
#else
#  define INTMAX_C(x) x ## L
#  define UINTMAX_C(x) x ## UL
#endif

//Limits of Other Integer Types
#  define PTRDIFF_MIN               0x8000
#  define PTRDIFF_MAX               0xffff

#if __WORDSIZE == 16
#  define SSIZE_MAX                 0x7fff
#  define SIZE_MAX                  0xffff
#elif __WORDSIZE == 32
#  define SSIZE_MAX                 0x7fffffff
#  define SIZE_MAX                  0xffffffff	
#else
	#error You must define the platform bits for this port!
#endif

#define WCHAR_MIN 0
#define WCHAR_MAX 0x7fffffffu

#if 0
#  define WINT_MIN
#  define WINT_MAX
#endif

/******************  Public Types ******************/

typedef int_8      int8_t;
typedef uint_8     uint8_t;

typedef int_16     int16_t;
typedef uint_16    uint16_t;

#ifdef __u_int24_defined__
typedef int_24     int24_t;
typedef uint_24    uint24_t;
#endif

typedef int_32     int32_t;
typedef uint_32    uint32_t;

#ifdef __u_int64_defined__
typedef int_64     int64_t;
typedef uint_64    uint64_t;
#endif

//Minimum-width integer types

typedef int_8      int_least8_t;
typedef uint_8     uint_least8_t;

typedef int_16     int_least16_t;
typedef uint_16    uint_least16_t;

#ifdef __u_int24_defined__
typedef int_24     int_least24_t;
typedef uint_24    uint_least24_t;
#else
typedef int_32     int_least24_t;
typedef uint_32    uint_least24_t;
#endif

typedef int_32     int_least32_t;
typedef uint_32    uint_least32_t;

#ifdef __u_int64_defined__
typedef int_64     int_least64_t;
typedef uint_64    uint_least64_t;
#endif

//Fastest minimum-width integer types

typedef int_8      int_fast8_t;
typedef uint_8     uint_fast8_t;

typedef int_16     int_fast16_t;
typedef uint_16    uint_fast16_t;

#ifdef __u_int24_defined__
typedef int_24     int_fast24_t;
typedef uint_24    uint_fast24_t;
#else
typedef int_32     int_fast24_t;
typedef uint_32    uint_fast24_t;
#endif

typedef int_32     int_fast32_t;
typedef uint_32    uint_fast32_t;

#ifdef __u_int64_defined__
typedef int_64     int_fast64_t;
typedef uint_64    uint_fast64_t;
#endif

// Integer types capable of holding object pointers

typedef _intptr_t    intptr_t;
typedef _uintptr_t   uintptr_t;

// Greatest-width integer types

#ifdef __u_int64_defined__
typedef int_64     intmax_t;
typedef uint_64    uintmax_t;
#else
typedef int_32     intmax_t;
typedef uint_32    uintmax_t;
#endif

#endif //__STDINT_H__
