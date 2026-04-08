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

#ifndef _mrendez_h_
#define _mrendez_h_

#ifdef __cplusplus
extern "C" {
#endif

int mr_init (int nports);
pthread_t mr_send (void *rqst, void *rply, pthread_t id, int port,
                   struct timespec *timeout);
pthread_t mr_receive (void *rqst, BitMask portmask, BitMask sigmask,
                      int *outport, struct timespec *timeout);
pthread_t mr_reply (void *rply, pthread_t id);
int mr_sigpost (pthread_t id, int signum);
int mr_sigrecv (BitMask sigmask);

/* INTERRUPT_ID is returned by mr_receive when it is woken up by an
   mr_sigpost rather than a message. */
#define INTERRUPT_ID            (pthread_t)0xFFFFFFFF

/* TIMEOUT_ID is returned by mr_receive when it is woken up by an
   mr_sigpost rather than a timeout (timer_tick). */
#define TIMEOUT_ID            (pthread_t)0xFFFFFFFE

/* A timeout value given as FOREVER will block the task until some other
   event occurs; it will never timeout, and will never return the ETIMEOUT
   error code. To poll, pass a timespec struct will both values 0. */
#define FOREVER     0
#define ALLPORTS    (~((BitMask)0))
#define NOPORTS     ((BitMask)0)
#define ALLSIGS     (~((BitMask)0))
#define NOSIGS      ((BitMask)0)

/* convert a port or sigpost signal to mask for mr_receive/mr_sigrecv */
#define MR_MASK(n)  (1 << (n))

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _mrendez_h_ */
