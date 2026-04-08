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

#ifndef _unistd_h
#define _unistd_h

#ifdef __cplusplus
extern "C" {
#endif

/* Unistd.h */

/* kfatal() is a user-defined routine that does something useful with the
   error number. The default routine writes the error number to a global
   variable, disables interrupts, and spins. */
/* The error numbers passable to kfatal are listed in errno.h, and all start
   with FAT_... */
/* Finally, the error codes are 32 bits long. Hence the ulong, as Nano is
   targeted at smaller-than-32-bit machines. */
void kfatal (unsigned long int fatal);

/* Posix test macros and Nano build options */

/* There are four Nano build options. These options remove some code from
   general areas of the kernel, allowing for a smaller kernel for
   applications that don't use these features. */
/* These options do not cover all the feature sets, or all the Posix feature
   test macros. This is simply because Posix messages and semaphors, and
   Unison messages and rendezvous features carry no overhead within the
   kernel. They are completely self contained, and if you don't reference
   them in your code, the linker brings none of it in. */
/* The build options, however, cover areas that affect the context switch and 
   the handling of the ready queue and waiting queues. They remove fields
   from the task descriptor and code that handles the capabilities the
   options cover. */

/* NANO_OPTION_NO_TIMERS (Implies NANO_OPTION_NO_TIMEOUTS) Removes all the
   machinery that handles timers, and removes the timer_tick() function and
   the various sleep functions. Removes round-robin stuff from the task
   descriptor. */

/* NANO_OPTION_NO_TIMEOUTS Removes all the machinery that handles timeouts,
   including the dedicated timer built into the task descriptor. Removes all
   timeout functons, like mq_timedreceive. Unison rendezvous functions will
   wiat forever if their timeout parameters indicate a wait (and not a poll) */

/* NANO_OPTION_NO_PRIORITY_SCHEDULING: Implies
   NANO_OPTION_NO_PRIORITY_INHERIT. All threads run at the same priority,
   code that moves task descriptors around is simplified. Fifo and
   Round-Robin scheduling (if timers are included) still apply at the one
   priority level. */

/* NANO_OPTION_NO_PRIORITY_INHERIT: Disable priority inheritance on thread
   mutexes. With this feature disabled, threads only have an assigned
   priority, and thread mutex grabbing code is simplified. With inheritance
   enabled, threads have their assigned priority, but will run at their
   effective priority (which could be higher) if they hold a mutex. */
#define NANO_OPTION_NO_PRIORITY_INHERIT
#ifdef NANO_OPTION_NO_PRIORITY_SCHEDULING
#error Disabling priority scheduling not implemented yet!
#endif


#define _POSIX_VERSION	200112L
#undef _XOPEN_VERSION

/* Set up POSIX test macros for the selected Nano build options */

#if defined(NANO_OPTION_NO_TIMERS)
#  define _POSIX_TIMERS -1
#  define _POSIX_TIMEOUTS -1
#else /* no timers */
#  define _POSIX_TIMERS 200112L
#  if defined(NANO_OPTION_NO_TIMEOUTS)
#    define _POSIX_TIMEOUTS -1
#  else /* no timeouts */
#    define _POSIX_TIMEOUTS 200112L
#  endif /* no timeouts */
#endif /* no timers */

#if defined(NANO_OPTION_NO_PRIORITY_SCHED)
#  define _POSIX_PRIORITY_SCHEDULING -1
#  define _POSIX_THREAD_PRIORITY_SCHEDULING -1
#  define _POSIX_THRED_PRIO_INHERIT -1
#else /* no priority scheduling */
#  define _POSIX_PRIORITY_SCHEDULING 200112L
#  define _POSIX_THREAD_PRIORITY_SCHEDULING 200112L
#  if defined(NANO_OPTION_NO_PRIORITY_INHERIT)
#    define _POSIX_THREAD_PRIO_INHERIT -1
#  else /* no priority inheritance */
#    define _POSIX_THREAD_PRIO_INHERIT 200112L
#  endif /* no priority inheritance */
#endif /* no priority scheduling */

/* These features are always enabled. */
#define _POSIX_MESSAGE_PASSING		    200112L
#define _POSIX_SEMAPHORES		    200112L
#define _POSIX_THREAD_ATTR_STACKADDR	    200112L
#define _POSIX_THREAD_ATTR_STACKSIZE	    200112L
#define _POSIX_THREADS			    200112L


#ifndef NANO_OPTION_NO_PRIORITY_INHERIT
#error Nano Priority Inheritance NOT implemented yet!
#endif


#include <sys/types.h>


ssize_t write(int fildes , const void *buf , size_t nbyte);
ssize_t read(int fildes , void *buf , size_t nbyte);
int unlink(const char *path);
int link(const char *src, const char *dst);
void sync(const char *server);
int fsync(int fildes);
int close(int fildes);
off_t lseek(int fildes, off_t offset, int relative);

int rmdir(const char *);

unsigned int sleep (unsigned int seconds);
int usleep(useconds_t useconds);

char *ctermid(char *s);
int fork(void);
int isatty(int file);
void _exit(int);


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* #ifndef _unistd_h */
