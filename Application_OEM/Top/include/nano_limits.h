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
#ifndef _nano_limits_h_
#define _nano_limits_h_

#include <bits/wordsize.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Minimum values */
#define _POSIX_AIO_LISTIO_MAX       2
#define _POSIX_AIO_MAX              1
#define _POSIX_ARG_MAX              4096
#define _POSIX_CHILD_MAX            6
#define _POSIX_DELAYTIMER_MAX       32
#define _POSIX_LINK_MAX             8
#define _POSIX_MAX_CANON            255
#define _POSIX_MAX_INPUT            255
#define _POSIX_MQ_OPEN_MAX          8
#define _POSIX_MQ_PRIO_MAX          32
#define _POSIX_NAME_MAX             14
#define _POSIX_NGROUPS_MAX          0
#define _POSIX_OPEN_MAX             16
#define _POSIX_PATH_MAX             255
#define _POSIX_PIPE_BUF             512
#define _POSIX_RTSIG_MAX            8
#define _POSIX_SEM_NSEMS_MAX        256
#define _POSIX_SEM_VALUE_MAX        32767
#define _POSIX_SIGQUEUE_MAX         32
#define _POSIX_SSIZE_MAX            32767
#define _POSIX_STREAM_MAX           8
#define _POSIX_TIMER_MAX            32
#define _POSIX_TZNAME_MAX           3
#define _POSIX_CLOCKRES_MIN         20000        /* nanoseconds */

/*
 * These defines should be modified, together with:
 * fsys\limits.h or fsys-fatfs\limits.h,
 * depending of file system used in your application
 */
#define PATH_MAX					128		
#define NAME_MAX					50

/* Actual values */
#define MQ_PRIO_MAX                 _POSIX_MQ_PRIO_MAX

#define SEM_VALUE_MAX               0x3fff 

#define PTHREAD_PRIO_MAX            16           
#define MR_SIG_MAX                  32          


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _nano_limits_h_ */
