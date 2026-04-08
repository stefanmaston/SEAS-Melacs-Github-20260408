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
#ifndef _mqueue_h_
#define _mqueue_h_

#include <fcntl.h>
#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int mqd_t;

struct mq_attr
{
 long mq_flags;                /* Message queue flags. */
 long mq_maxmsg;               /* Maximum number of messages. */
 long mq_msgsize;              /* Maximum message size. */
 long mq_curmsgs;              /* Number of messages currently queued. */
};

/* This global contains the default attributes for a create of attr == 0 */
extern struct mq_attr DefaultAttr;

mqd_t mq_open (const char *name, int oflag, ...);
int mq_close (mqd_t mqdes);
int mq_unlink (const char *name);
int mq_send (mqd_t mqdes, const char *msg_ptr, size_t msg_len,
           unsigned int msg_prio);
int mq_timedsend (mqd_t mqdes, const char *msg_ptr, size_t msg_len,
                 unsigned int msg_prio, const struct timespec *timeout);
ssize_t mq_receive (mqd_t mqdes, char *msg_ptr, size_t msg_len,
                  unsigned int *msg_prio);
ssize_t mq_timedreceive (mqd_t, char *msg_ptr, size_t msg_len,
                         unsigned int *msg_prio,
                        const struct timespec *timeout);
int mq_notify (mqd_t mqdes, const struct sigevent *notification);
int mq_setattr (mqd_t mqdes, const struct mq_attr *mqstat,
                struct mq_attr *omqstat);
int mq_getattr (mqd_t mqdes, struct mq_attr *mqstat);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _mqueue_h_ */
