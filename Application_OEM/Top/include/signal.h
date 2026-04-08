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

#ifndef _signal_h_
#define _signal_h_

#ifdef __cplusplus
extern "C" {
#endif

union sigval
{
  int sival_int;
  void *sival_ptr;
};


struct sigevent
{
	int                    sigev_notify;            //Notification type. 
	int                    sigev_signo ;            //Signal number. 
	union sigval           sigev_value ;            //Signal value. 
//	void(*)(union sigval)  sigev_notify_function   Notification function. 
//	(pthread_attr_t *)     sigev_notify_attributes Notification attributes. 
};




typedef unsigned long sigset_t;		/* at least 32 bits */


/* sigev_notify types */
#define SIGEV_NONE      0
#define SIGEV_SIGPOST   1
//#define SIGEV_SIGNAL	2
#define SIGEV_SIGNAL SIGEV_SIGPOST  

/* argument to sigprocmask */
#define SIG_BLOCK 	1
#define SIG_UNBLOCK	2
#define SIG_SETMASK	3


#define	SIGHUP		1	/* hangup */
#define SIGINT		2	/* interrupt */
#define SIGQUIT		3	/* quit */
#define SIGILL		4	/* illegal instruction */
#ifndef _POSIX_SOURCE
#define SIGTRAP		5	/* break point trap */
#endif
#define SIGABRT		6	/* abort */
#ifndef _POSIX_SOURCE
#define SIGIOT		SIGABRT
#define SIGEMT		7	/* emulator trap */
#endif
#define SIGFPE		8	/* floating point exception */
#define SIGKILL		9	/* kill */
#ifndef _POSIX_SOURCE
#define SIGBUS		10	/* bus error */
#endif
#define SIGSEGV		11	/* segmentation violation */
#ifndef _POSIX_SOURCE
#define SIGSYS		12	/* bad argument to system call */
#endif
#define SIGPIPE		13	/* write on a pipe with no one to read it */
#define SIGALRM		14	/* alarm clock */
#define SIGTERM		15	/* software termination signal */
#ifndef _POSIX_SOURCE
#define SIGURG		16	/* urgent condition (on socket) */
#endif
#define SIGSTOP		17	/* stop (cannot be caught or ignored) */
#define SIGTSTP		18	/* interactive stop signal */
#define SIGCONT		19	/* continue if stopped */
#define SIGCHLD		20	/* child process terminated or stopped */
#define SIGTTIN		21	/* to reader's process group on bg read */
#define SIGTTOU		22	/* to writer's process group on bg write */
#ifndef _POSIX_SOURCE
#define	SIGIO		23	/* input/output possible signal */
#define SIGPOLL		23	/* System V i/o possible */
#define	SIGXCPU		24	/* exceeded CPU time limit */
#define	SIGXFSZ		25	/* exceeded file size limit */
#define	SIGVTALRM	26	/* virtual time alarm */
#define	SIGPROF		27	/* profiling time alarm */
#define SIGWINCH	28	/* window size changes */
#define SIGINFO		29	/* information request */
#endif
#define SIGUSR1		30	/* user defined signal 1 */
#define SIGUSR2		31	/* user defined signal 2 */


typedef struct
{
int           si_signo;  //Signal number. 
int           si_code;   //Signal code. 
int           si_errno;  //If non-zero, an errno value associated with  this signal, as defined in <errno.h>. 
pid_t         si_pid;    //Sending process ID. 
uid_t         si_uid;    //Real user ID of sending process. 
void         *si_addr;   //Address of faulting instruction. 
int           si_status; //Exit value or signal. 
long          si_band;   //Band event for SIGPOLL. 
union sigval  si_value;  //Signal value. 
}siginfo_t;


struct sigaction
{
void (*sa_handler)(int);  //Pointer to a signal-catching function or one of the macros SIG_IGN or SIG_DFL. 
sigset_t sa_mask;         //Set of signals to be blocked during execution of the signal handling function. 
int      sa_flags;        //Special flags. 
void (*sa_sigaction)(int, siginfo_t *, void *); //Pointer to a signal-catching function. 
};

//--------------------------------------------------------------------//

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _signal_h_ */
