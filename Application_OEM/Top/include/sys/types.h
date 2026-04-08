/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2012 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
#ifndef _types_h_
#define _types_h_

#include <bits/wordsize.h>
#ifdef	USE_DUAL_TCP_STACK
#include <endian.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*  The following typedefs allow us to minimize portability problems
 *  due to the various C compilers (even for the same processor) not
 *  agreeing on the sizes of "int"s and "short int"s.
 * These types are not posix types.
 */
#if __WORDSIZE == 16
	typedef signed   char   int_8;
	typedef          short  int_16;
	typedef          long   int_32;
	#if __SUPPORT_LONG_LONG > 0	
	typedef signed long long   int_64;		
	#endif	
	typedef unsigned char   uint_8;
	typedef unsigned short     uint_16;
	typedef unsigned long   uint_32;
	#if __SUPPORT_LONG_LONG > 0
	typedef unsigned long long uint_64;		
	#endif
#elif __WORDSIZE == 32
	typedef signed   char   int_8;
	typedef          short  int_16;
	typedef          int    int_32;
	#if __SUPPORT_LONG_LONG > 0
	typedef signed long long   int_64;	
	#endif		
	typedef unsigned char   uint_8;
	typedef unsigned short 	uint_16;
	typedef unsigned int    uint_32;
	#if __SUPPORT_LONG_LONG > 0
	typedef unsigned long long uint_64;	
	#endif		
#else
	#error You must define the platform bits for this port!
#endif

#ifdef	USE_DUAL_TCP_STACK
/*
 * For tcp-server
 */
#define u_int8_t	uint_8
#define u_int16_t	uint_16
#define u_int32_t	uint_32
#define u_int64_t   uint_64
typedef	uint_32     u_quad_t;   /* quads */
typedef	int_32      quad_t;     /* quads */

#define	NBBY	8		/* number of bits in a byte */
/*
 * From <sys/param.h>
*/
#ifndef howmany
#define	howmany(x, y)	(((x) + ((y) - 1)) / (y))
#endif
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))

#endif	//USE_DUAL_TCP_STACK

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;

typedef signed long     off_t;         //Used for file sizes, shall be signed integer types.
typedef int             pid_t;         //Used for process IDs and process group IDs, shall be signed integer types	
typedef	uint_16         uid_t;         //user id, shall be integer types.
typedef	uint_16         gid_t;		   //shall be integer types
typedef uint_32         id_t;          //Used as a general identifier; can be used to contain at least a pid_t, uid_t, or gid_t.

typedef uint/*_32*/     opaque;
typedef void *          NetAddr;
typedef uint_32         BitMask;

typedef int_32          _intptr_t;
typedef uint_32         _uintptr_t;		

#define ADDR_TO_NET(x)	addr_to_net(x)
#define NET_TO_ADDR(x)	net_to_addr(x)

#define addr_to_net(X)  (NetAddr)(X)
#define net_to_addr(X)  (NetAddr)(X)

#if defined(__PIC24F__) || defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(M16C)
	typedef uint_16 Status;
#elif defined(_SH2A) || defined(_SH2AFPU) || defined(__ARMCORTEXM3__) || defined(__RX) || defined(__R32C100__) || \
	defined(__PIC32MX__) || defined(__PIC32MZ__) || defined (NC100) || defined(__MICROBLAZE__) || defined(__YDFP__) || defined(__CORTEX_A8__) || defined(__ARMCORTEXM4F__)
	typedef uint_32 Status;
#else
	#error Select platform!
#endif

typedef int             mode_t;       //mode_t shall be an integer type.
typedef char *          caddr_t;
typedef long            time_t;       //Used for time in seconds, shall be integer or real-floating types.	
typedef uint_32         clock_t;      //shall be integer or real-floating types.
typedef opaque          clockid_t;
typedef opaque          timer_t;      //Used for timer ID returned by timer_create(), 

typedef u_long          useconds_t;
typedef int_32          suseconds_t;  //Used for time in microseconds, the widths are no greater than the width of type long 

typedef int             blkcnt_t;     //shall be signed integer types.
typedef int             blksize_t;    //shall be signed integer types	
typedef uint_16     	dev_t;        //Used for device IDs
typedef uint_32         ino_t;        //Used for file serial numbers, shall be defined as unsigned integer types
typedef uint_16         nlink_t;      //Used for link counts, shall be integer types.

/*not defined in Unison implementation:
 * fsblkcnt_t , locale_t, fsfilcnt_t ,
 * key_t, trace_attr_t, trace_event_id_t
 * trace_event_set_t , trace_id_t
*/

#include <stddef.h>		// size_t, NULL
typedef int             ssize_t;		//ssize_t shall be signed integer types

#ifdef __cplusplus
} //extern "C" {
#endif

#endif  /* _types_h_ */
