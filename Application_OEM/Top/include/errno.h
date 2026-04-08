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
#ifndef _errno_h_
#define _errno_h_

#ifdef __cplusplus
extern "C" {
#endif

/* Note that the Directory task assumes errno fits in 16-bits.
 * This does not apply to fatal errors.
 */
#define EOK                 0
#define EPERM               1
#define ENOENT              2
#define ESRCH               3
#define EINTR               4
#define EIO                 5
#define ENXIO               6
#define E2BIG               7
#define ENOEXEC             8
#define EBADF               9
#define ECHILD              10
#define EAGAIN              11
#define ENOMEM              12
#define EACCES              13
#define EFAULT              14
#define ENOTSUPPORTED       15
#define EBUSY               16
#define EEXIST              17
#define EXDEV               18
#define ENODEV              19
#define ENOTDIR             20
#define EISDIR              21
#define EINVAL              22  /* asm */
#define ENFILE              23
#define EMFILE              24
#define ENOTTY              25
#define ETXTBSY             26
#define EFBIG               27
#define ENOSPC              28
#define ESPIPE              29
#define EROFS               30
#define EMLINK              31
#define EPIPE               32
#define EDOM                33
#define ERANGE              34
#define ELOOP               35
#define EIDRM               36
#define EILSEQ              37
#define EOVERFLOW           38
#define ENODATA             39
#define ENOSR               40
#define ENOSTR              41
#define ETIME               42
#define ENOTRECOVERABLE     43
#define EOWNERDEAD          44
#define EDEADLK             45
#define ENOLCK              46
#define ECANCELED           47
#define ENOTSUP             48
#define ENOMSG              49
#define EBADMSG             50
#define ENAMETOOLONG        51
#define ENOSYS              52
#define ENOTEMPTY           53
#define EMSGSIZE            54
#define EINPROGRESS         55
#define ETIMEDOUT           56
#define EPROTO              57


/* TCP/IP errors */
#define EPROTONOSUPPORT     60
#define EPROTOTYPE          61
#define ENOBUFS             62
#define EOPNOTSUPP          63
#define EISCONN             64
#define ENOTCONN            65
#define EALREADY            66
#define EADDRINUSE          67
#define EDESTADDRREQ        68
#define EWOULDBLOCK         69
#define ENOPROTOOPT         70
#define EAFNOSUPPORT        71
#define ENETUNREACH         72
#define EADDRNOTAVAIL       73
#define EHOSTDOWN           74
#define EHOSTUNREACH        75
#define ECONNREFUSED        76
#define ENETDOWN            77
#define ECONNRESET          78
#define ECONNABORTED        79
#define ENETRESET           80
#define ETOOMANYREFS        81
#define EPFNOSUPPORT        82
#define ENOTSOCK            83


/* POSIX reserved */
#define EMULTIHOP           90
#define ENOLINK             91


/* The following are Unison specific */
#define EBADINDEX           100
#define EBADID              101
#define EBADPORT            102
#define ETHREADDIED         104     /* thread blocked on died */
#define EBADSERVERNAME      105
#define ENOSERVERFOUND      106
#define EBADUCB             107


// Error numbers for file system and other unison servers
#define EBADFSYS            110
#define ENOEXTENTS          111
#define EDQUOT              112    // POSIX reserved uses
#define ESTALE              113    // POSIX reserved uses
#define ENFSERR             114
#define ERPCFAILED          115
#define ECANTSPAWNPROCESS   116
#define ENAMLEN             119
#define EBADBLOCK           120


/* Floating point errors  offset by 100 */
#define EDOMAIN             190

// Use in servers
#define DONT_REPLY          255


extern int errno;

/* These defines are passed to kfatal */
#define FAT_HEAP        	0x40000001
#define FAT_PRIORITY    	0x40000002
#define FAT_NPORTS      	0x40000003
#define FAT_DUPINDEX    	0x40000004
#define FAT_READYQS     	0x40000005
#define FAT_IDLE        	0x40000010
#define FAT_ROOT        	0x40000011
#define FAT_DIRECTORY   	0x40000012
//#define FAT_NTHREAD   	0x40000013
#define FAT_BRIDGE      	0x40000100
#define FAT_MULTIPROC   	0x40000101
#define FAT_KERNEL		0x40000200

#ifdef __cplusplus
} //extern "C" {
#endif

#endif  /* _errno_h_ */
