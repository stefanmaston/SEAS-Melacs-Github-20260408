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



/******************************************************************************
* Name        : sys/param.h
* Subsystem   : Unison TCP/IP
* Description : This is a collection of defines required by TCP/IP
* Assumptions : 
*******************************************************************************
* Modification Records
*******************************************************************************
Date      Details
*******************************************************************************

*******************************************************************************/

#ifndef __param_h__
#define	__param_h__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK

#ifndef NULL
#define NULL	((void*)0)
#endif
#define KERNEL	1
#define NETHER	1
#define	MAXHOSTNAMELEN	64


/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than NBPG (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define	MSIZE		256		/* size of an mbuf */
#define	MCLSHIFT	11		/* convert bytes to m_buf clusters */
#define	MCLBYTES	(1 << MCLSHIFT)	/* size of a m_buf cluster */
#define	MCLOFSET	(MCLBYTES - 1)	/* offset within a m_buf cluster */

#if (IP4_FORWARD | IP6_FORWARD)
  #define	NMBCLUSTERS	4		/* map size, max cluster allocation */
 #else
  #define	NMBCLUSTERS	16		/* map size, max cluster allocation */
#endif /* IP4_FORWARD | IP6_FORWARD */


/*
 * Macros for fast min/max.
 */
#ifndef MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define	MAX(a,b) (((a)>(b))?(a):(b))
#endif

#else	//OLD IPV4 ONLY TCP STACK

#define	BSD	43
#ifndef NULL
#define NULL	((void*)0) 
#endif
#define KERNEL	1
#define INET	1
#define NETHER	1
#define	MAXHOSTNAMELEN	64
#define	PAGESIZE		256//1024
#define	CLBYTES			(PAGESIZE)
#define CLOFSET			(PAGESIZE-1)
#define CLSHIFT			8//10 	/* log2(CLOFSSET) */
#define CLSIZE			1			/* clusters in page */
#define	PZERO			0
#define NOFILE			1024	/* no limit on the number of open files */
#define MAXSYMLINKS		0

/*
 * Macros for fast min/max.
 */
#ifndef MIN
#define	MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define	MAX(a,b) (((a)>(b))?(a):(b))
#endif

#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif //__param_h__