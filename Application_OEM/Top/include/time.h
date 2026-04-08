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

#ifndef _time_h_
#define _time_h_

#if _POSIX_TIMERS > 0

#include <signal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Posix time.h For the stuff covered by _POSIX_TIMERS option. */

/* Note deviations from Posix: */
/* timer_getoverrun() returns -1 and does nothing else. The Posix realtime
   signals option is not implemented, and the standard allows this functions
   return value to be undefined in that case. */
/* timer_tick() is a hardware support function. The user is expected to call
   this from his interrupt service routine for a clock. It updates any timers 
   on that clock. */
/* clock_init() is a hardware support function. The user is expected to call
   this from his setup code, before calling DSPexec_Start(). It only sets the
   resolution of the specified clock. */


/* IKM 2007/05: As of this writing, the only clock allowed is CLOCK_REALTIME. 
   Some functions will return -1 and set errno to EINVAL if any other clock
   id is provided. clock_init() will do nothing, as there's no task running
   for errno to belong to, and timer_tick() will do nothing as it's in an
   ISR. */


struct timeval {
    long    tv_sec;         /* seconds */
    long    tv_usec;        /* microseconds */
};

struct timespec
{
  time_t tv_sec; 	 /* seconds */
  long tv_nsec;		 /* nanoseconds */
};

struct itimerspec
{
  struct timespec it_interval;
  struct timespec it_value;
};

struct tm
{
  int tm_sec;     /* second (0-61, allows for leap seconds) */
  int tm_min;     /* minute (0-59) */
  int tm_hour;    /* hour (0-23) */
  int tm_mday;    /* day of the month (1-31) */
  int tm_mon;     /* month (0-11) */
  int tm_year;    /* years since 1900 */
  int tm_wday;    /* day of the week (0-6) */
  int tm_yday;    /* day of the year (0-365) */
  int tm_isdst;   /* non-0 if daylight savings time is in effect */
};

#define CLOCK_REALTIME      0
#define CLOCK_MONOTONIC     1
//Not defined in Unison
//#define CLOCK_PROCESS_CPUTIME_ID
//#define CLOCK_THREAD_CPUTIME_ID


char      *asctime(const struct tm *);
char      *asctime_r(const struct tm *, char *);
clock_t    clock(void);
int        clock_getcpuclockid(pid_t, clockid_t *);
int        clock_getres(clockid_t, struct timespec *);
int        clock_gettime(clockid_t, struct timespec *);
int        clock_nanosleep(clockid_t, int, const struct timespec *, struct timespec *);
int        clock_settime(clockid_t, const struct timespec *);
char      *ctime(const time_t *);
char      *ctime_r(const time_t *, char *);
double     difftime(time_t, time_t);
struct tm *getdate(const char *);
struct tm *gmtime(const time_t *);
struct tm *gmtime_r(const time_t *, struct tm *);
struct tm *localtime(const time_t *);
struct tm *localtime_r(const time_t *, struct tm *);
time_t     mktime(struct tm *);
int        nanosleep(const struct timespec *, struct timespec *);
size_t     strftime(char *, size_t, const char *, const struct tm *);
//size_t     strftime_l(char *, size_t, const char *, const struct tm *, locale_t);
char      *strptime(const char *, const char *, struct tm *);
time_t     time(time_t *);
int        timer_create(clockid_t, struct sigevent *, timer_t *);
int        timer_delete(timer_t);
int        timer_getoverrun(timer_t);
int        timer_gettime(timer_t, struct itimerspec *);
int        timer_settime(timer_t, int, const struct itimerspec *, struct itimerspec *);
void       tzset(void);
//non posix
int clock_init (clockid_t clockid, const struct timespec *res);
void timer_tick (clockid_t clockid);
time_t uptime (time_t *tloc);


/* for timer_settime flags */
#define TIMER_ABSTIME       1

#define NANOSECOND          1000000000

/* Some handy conversions to nanoseconds. It is so easy to get all those
   zeros wrong. */
#define SECOND2NANO(n)      ((n) * 1000000000)
#define MILLISEC2NANO(n)    ((n) * 1000000)
#define MICROSEC2NANO(n)    ((n) * 1000)

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _POSIX_TIMERS */
#endif /* _time_h_ */
