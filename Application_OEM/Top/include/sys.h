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

#ifndef _sys_h_
#define _sys_h_

#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/interrupt.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  THREAD (*rootStartRoutine) (void *);
  size_t rootStackSize;
  int rootPriority;
} ConfigTableStruct;

extern ConfigTableStruct ConfigTable;


// type for dir_lookup_type()
typedef struct dir_buf_entry_type
{
	struct dir_buf_entry_type	*next_entry_ptr;//pointer to next entry
	uint						value;			//value 
	char						*name;			//pointer to name
}dir_buf_type_t;

//type for threads utilization
typedef struct thread_util
{
	uint	thread_id;
	char	*thread_name;
	u_long	util;
}thread_util_t;


/*----------------------------------------------------------------------*\
 *                                                                      *
 *                       SYSTEM CALL PROTOTYPES                         *
 *                                                                      *
\*----------------------------------------------------------------------*/

/*----- Board Support Routines -----*/
void hw_init (void);
void malloc_init(void);
void *rtos_malloc(size_t size);
void rtos_free(void *buf);
void set_IdleThread_stack(int size);


#if defined(__PIC24F__) || defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(M16C)
	void DSPexec_Start (void);
#elif defined(__PIC32MX__) || defined(__PIC32MZ__) || defined(__R32C100__) || defined(__ARMCORTEXM3__) || defined(_SH2A)  || \
	  defined(_SH2AFPU) || defined(NC100) || defined(__MICROBLAZE__) || defined(__YDFP__) || defined(__CORTEX_A8__) || defined (__RX) || defined(__ARMCORTEXM4F__)
	void Nano_Start (void);
#else
    #error You must define the kernel start function for this port!
#endif


void *getSP(void);

/*----- Pools -------*/
#define MAXPOOLS        8
int pool_create (int poolno, unsigned long startaddr, unsigned long endaddr);
int pool_destroy (int poolno);
void *pool_alloc (int poolno, size_t size);
int pool_free (int poolno, void *buf);


/*----- Partitions --*/
int pt_create (size_t blocksize, int numblocks);
int pt_destroy (int ptno);
void *pt_getblock (int ptno);
void pt_freeblock (int ptno, void *block);

/*----- Malloc -----*/
int malloc_create (unsigned long startaddr, unsigned long endaddr);


#if defined(_TMS320C30) || defined(_TMS320C40)
/* No worries */
#define ALIGN_LONG(n)   (n)
#elif defined(__YDFP__)
	#define ALIGN_LONG(n)   (((uint_32)(n) + 7) & ~(0x00000007))
#else
/* For alignment on a long word boundry/size where (3UL) is not understood by the compiler */
#define ALIGN_LONG(n)   (((uint_32)(n) + 3) & ~(0x00000003))
#endif

/* polled io functions */
void xputchar (const int c);
void xputs (const char *s);
int xprintf (const char *format, ...);


/* Defines for Directory Services */
#define TYPE_UNKNOWN    0
#define TYPE_THREAD     1
#define TYPE_SERVER     2
#define TYPE_SEMAPHORE  3
#define TYPE_MUTEX      4
#define TYPE_MQUEUE     5
#define TYPE_BARRIER    6
#define TYPE_TIMER      7
#define TYPE_POOL       8
#define TYPE_ENV        9
#define TYPE_COND_VAR   10

/* Directory Services */
int dir_register(const char *name, uint value, uint type);
int dir_deregister(const char *name);
int dir_lookup(const char *name, uint *valuep);
int dir_lookup_string(const char *name, uint *valuep, size_t len);
int dir_lookup_type(dir_buf_type_t *Dir_buf_ptr, uint type);

/* Threads ulization */
int threads_numb(void);
void threads_utilization_start(thread_util_t *thread_table, int threads_num);
void threads_utilization_stop(void);

/* lock/unlock task switching */ 
void Nano_lock (void);
void Nano_unlock (void);

/* Access to kernel internal variables*/
int getisrlevel(void);
int getlocklevel(void);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _sys_h_ */
