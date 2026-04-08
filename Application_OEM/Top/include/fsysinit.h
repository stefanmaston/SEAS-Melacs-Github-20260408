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


/*****************************************************************************
* Name        : fsysinit.h
* Subsystem   : FSYS
* Description : Initialization message for fsys server
* Assumptions : 
*******************************************************************************
* Modification Records
*******************************************************************************
Date         Details (release, sub's affected, describe change)
*******************************************************************************

*****)*************************************************************************/

#ifndef __fsysinit_h__
#define	__fsysinit_h__

#ifdef __cplusplus
extern "C" {
#endif

struct fsysinit {
	uint_16 fsi_msgsize;
	uint_16	fsi_nclones;	/* Number of servers to create. */
	uint_32	fsi_datalog;	/* Past Global index of server. Now datlog bit definition */
	uint_16	fsi_nbuffers;	/* Number of buffers in buffer cache */
	uint_16 fsi_maxopen;	/* Max number of open files */
	uint_16	fsi_blocksize;	/* Memory block size: 256 for RAM-disc, 512 for sd-card */
	uint_16 fsi_ndrives;	/* Maximum number of allocated disk*/
};

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
