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

#ifndef _wordsize_h_
#define _wordsize_h_

#ifdef __cplusplus
extern "C" {
#endif

/* Set up default wordsize  */
#if defined(__PIC24F__) || defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(M16C)
	#define __WORDSIZE	16
#elif defined(__PIC32MX__) || defined(__PIC32MZ__) || defined(__R32C100__) || defined(__ARMCORTEXM3__) || defined(_SH2A) || defined(_SH2AFPU) || defined(__RX) || defined (NC100) || defined(__MICROBLAZE__)|| defined(__CORTEX_A8__) || defined(__YDFP__) || defined(__ARMCORTEXM4F__)
	#define __WORDSIZE	32
#else
	#error You must define the platform bits for this port!
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _wordsize_h_ */
