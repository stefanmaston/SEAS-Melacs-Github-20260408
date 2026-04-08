/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2008 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _MALLOC_FUNC_

#include <sys.h>

//#define MEMSIZE_32F 31000 //Maximum is around this value
//#define MEMSIZE_32F 23000  //This does not work for the Ethernet code, wonder why
#define MEMSIZE_32F 20000 
static uint_32 _Heap_start[MEMSIZE_32F];
unsigned HeapSize; 

void malloc_init()
{
	/* can only fail if pool already created */
	HeapSize = MEMSIZE_32F;
    
	pool_create(0, (unsigned long)&_Heap_start, (unsigned long)&_Heap_start[MEMSIZE_32F-1]);
}

void *malloc(size_t size)
{
	return pool_alloc(0, size);
}

void free(void *ptr)
{
	pool_free(0, ptr);
}

#endif