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



/******************************************************************************
* Name        : ioctl.h
* Subsystem   : Unison
* Description : u_ioctl headers
* Assumptions : 
*******************************************************************************
* Modification Records
*******************************************************************************
Date         Details (release, sub's affected, describe change)
*******************************************************************************

*******************************************************************************/

#ifndef __ioctl_h__
#define __ioctl_h__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 3 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 256 bytes.
 */
#define IOCCMD_MASK		0xff		/* 0 - 255 */
#define IOCTYPE_MASK	0xff		/* 0 - 255 */
#define IOCPARM_MASK	0xff		/* parameters must be < 256 bytes */

#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
#define	IOC_IN		0x80000000	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)

/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define	_IO(x,y)	(IOC_VOID|(x<<8)|y)
#define	_IOR(x,y,t)	(IOC_OUT | (((uint_32)sizeof(t)&IOCPARM_MASK)<<16) | (x<<8) | y)
#define	_IORN(x,y,t)	(IOC_OUT | (((uint_32)(t)&IOCPARM_MASK)<<16) | (x<<8) | y)
#define	_IOW(x,y,t)	(IOC_IN | (((uint_32)sizeof(t)&IOCPARM_MASK)<<16) | (x<<8) | y)
#define	_IOWN(x,y,t)	(IOC_IN | (((uint_32)(t)&IOCPARM_MASK)<<16) | (x<<8) | y)

/* this should be _IORW, but stdio got there first */
#define	_IOWR(x,y,t)	(IOC_INOUT | (((uint_32)sizeof(t)&IOCPARM_MASK)<<16) | (x<<8) | y)
#define	_IOWRN(x,y,t)	(IOC_INOUT | (((uint_32)(t)&IOCPARM_MASK)<<16) | (x<<8) | y)

/*
 * IOCTL utility functions and macros used to decode ioctl numbers
 */
#define _IOC_DIR(nr)    ((nr) & 0xe0000000)
#define _IOC_CMD(nr)    ((nr) & IOCCMD_MASK)
#define _IOC_TYPE(nr)   (((nr) >> 8) & IOCTYPE_MASK)
#define _IOC_SIZE(nr)   (((nr) >> 16) & IOCPARM_MASK)

#ifdef	USE_DUAL_TCP_STACK

/*
 * socket ioctl commands
 */
#include <sys/sockio.h>

#endif	//USE_DUAL_TCP_STACK

/*
 * tty ioctl commands
 */
#define SET_TTY_MODE	_IOW('t', 0, struct set_tty)/* set tty modes */
#define	TIOCSETD		_IOW('t', 1, int)			/* set line discipline */
#define TIOCSETP	_IOW('t', 2, int)		/* not supported */
#define TIOCLSET	_IOW('t', 3, int)		/* not supported */
#define TIOCSLTC	_IOW('t', 4, int)		/* not supported */
#define TIOCSETC	_IOW('t', 5, int)		/* not supported */
#define TIOCSPGRP	_IOW('t', 6, int)		/* not supported */
#define TIOCNOTTY	_IOW('t', 7, int)		/* not supported */
#define TIOCTCNTL	_IOW('t', 8, int)		/* not supported */
#define TIOCGPGRP	_IOW('t', 9, int)		/* not supported */
#define TIOCSIGNAL	_IOW('t', 10, int)		/* not supported */
#define TIOCSTI		_IOW('t', 11, int)		/* not supported */
#define TCFLSH		_IOW('t', 12, int)		/* flush queue SDLC */
#define SET_OP_MODE	_IOW('t', 13, struct set_op_mode)	/* set tty operation mode  */

/*
 * Ioctl control packet for SET_TTY_MODE 
 */
struct set_tty {
	uint_8		csize;		/* character size , 5,6,7,8 */
	uint_8		parity;		/* parity */
#define	NO_PARITY	0
#define EVEN_PARITY	1
#define	ODD_PARITY	2
	uint_8 	flow;		/* hardware flow control */
#define	NO_FLOWCONTROL			0
#define	CTS_FLOWCONTROL			1
#define	RTS_FLOWCONTROL			2
#define	RTSCTS_FLOWCONTROL		3
#define XONXOFF_FLOWCONTROL		4
	uint_32		speed;		/* set speed, actual number, 9600 */
	uint_8		stop_bits;
	uint_8		tty_int_level;	
	uint_16		timeout_write;	// in sec
	uint_16		rx_buf_size; 
	uint_16		tx_buf_size; 
#if defined(__MICROBLAZE__)
	uint_32		base_adr;
	uint_32		clock_hz;
	uint_8		interrupt_id;
#elif defined (__YDFP__)
	uint_32		base_adr;
	uint_8		interrupt_id;
#endif
};

/*
 * Ioctl commands for TCFLSH
 */
#define FLUSH_IN   0
#define FLUSH_OUT  1
#define FLUSH_BOTH 2

/*
 * Ioctl control packet for SET_OP_MODE 
 */
struct set_op_mode{
	uint_16		mode;				//485 = RS-485, 422 = RS-422, 232 = RS-232, other - reserved.
	void		(*tx_control)(int);	//function ptr, to handle transmitter ON/OFF control signal, should be implemented in USER application.
};

/*
 * Possible line disciplines
 */
#define	TTYLDISC	0		/* new tty discipline */
#define	NETLDISC	1		/* line discip for debugger */
#define RAWLDISC	2		/* RAW line discipline */
#define RAWFLDISC	3		/* Like RAW but with flow control */
#define ECHO		4		/* Turn echo back on - TTYLDISC */
#define NOECHO		5		/* Turn echo off - TTYLDISC */
#define PPPLDISC	6		/* ppp discipline */
#define PPPFSLDISC  7       /* ppp discipline with flow control software*/
#define PPPFHLDISC  8       /* ppp discipline with flow control hardware*/

#ifdef notdef
#define	TIOCGETD	_IOR('t', 0, int)		/* get line discipline */
#define	TIOCGETP	_IOR('t', 1, int)		/* NOT SUPPORTED */
#define	TIOCLGET	_IOR('t', 2, int)		/* NOT SUPPORTED */
#define	TIOCGETC	_IOR('t', 3, int)		/* NOT SUPPORTED */
#define	TIOCGLTC	_IOR('t', 4, int)		/* NOT SUPPORTED */
#endif
#define FIOCONNPEND	_IOR('t', 124, int)	/* any connections pending? */
#define	FIONBIO		_IOW('t', 126, int)	/* set/clear nonblocking i/o */
#define	FIOASYNC	_IOW('t', 125, int)	/* set/clear async i/o */
#define	FIONREAD	_IOR('t', 127, int)	/* get # bytes to read */
#define	FIONWRITE	_IOR('t', 128, int)	/* get # bytes written to socket */

#ifndef	USE_DUAL_TCP_STACK

/* socket i/o controls */
#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, int)		/* get process group */

#define	SIOCADDRT	_IOW('r', 10, struct rtentry)	/* add route */
#define	SIOCDELRT	_IOW('r', 11, struct rtentry)	/* delete route */

#define	SIOCSIFADDR	_IOW('i', 12, struct ifreq)	/* set ifnet address */
#define	SIOCGIFADDR	_IOWR('i',13, struct ifreq)	/* get ifnet address */
#define	SIOCSIFDSTADDR	_IOW('i', 14, struct ifreq)	/* set p-p address */
#define	SIOCGIFDSTADDR	_IOWR('i',15, struct ifreq)	/* get p-p address */
#define	SIOCSIFFLAGS	_IOW('i', 16, struct ifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	_IOWR('i',17, struct ifreq)	/* get ifnet flags */
#define	SIOCSIFMEM	_IOW('i', 18, struct ifreq)	/* set interface mem */
#define	SIOCGIFMEM	_IOWR('i',19, struct ifreq)	/* get interface mem */
#define	SIOCGIFCONF	_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	SIOCSIFMTU	_IOW('i', 21, struct ifreq)	/* set if_mtu */
#define	SIOCGIFMTU	_IOWR('i',22, struct ifreq)	/* get if_mtu */

	/* from 4.3BSD */
#define	SIOCGIFBRDADDR	_IOWR('i',23, struct ifreq)	/* get broadcast addr */
#define	SIOCSIFBRDADDR	_IOW('i',24, struct ifreq)	/* set broadcast addr */
#define	SIOCGIFNETMASK	_IOWR('i',25, struct ifreq)	/* get net addr mask */
#define	SIOCSIFNETMASK	_IOW('i',26, struct ifreq)	/* set net addr mask */
#define	SIOCGIFMETRIC	_IOWR('i',27, struct ifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	_IOW('i',28, struct ifreq)	/* set IF metric */

#define	SIOCSARP	_IOW('i', 30, struct arpreq)	/* set arp entry */
#define	SIOCGARP	_IOWR('i',31, struct arpreq)	/* get arp entry */
#define	SIOCDARP	_IOW('i', 32, struct arpreq)	/* delete arp entry */
#define	SIOCUPPER	_IOW('i', 40, struct ifreq)       /* attach upper layer */
#define	SIOCLOWER	_IOW('i', 41, struct ifreq)       /* attach lower layer */
#define	SIOCSETSYNC	_IOW('i',  44, struct ifreq)	/* set syncmode */
#define	SIOCGETSYNC	_IOWR('i', 45, struct ifreq)	/* get syncmode */
#define	SIOCSSDSTATS	_IOWR('i', 46, struct ifreq)	/* sync data stats */
#define	SIOCSSESTATS	_IOWR('i', 47, struct ifreq)	/* sync error stats */

#define	SIOCSPROMISC	_IOW('i', 48, int)		/* request promisc mode
							   on/off */
#define	SIOCADDMULTI	_IOW('i', 49, struct ifreq)	/* set m/c address */
#define	SIOCDELMULTI	_IOW('i', 50, struct ifreq)	/* clr m/c address */


#define SIOCSETNODELAY 	_IOW('i', 51, int)	/* set non-block IO */
#define SIOCGETNODELAY 	_IOW('i', 52, int)	/* get non-block IO */
#define SIOCSETIOPEND	_IOW('i', 53, int)	/* sig when IO pend */



    /*  GPIB ioctl commands parameters  */
#define GPIB_RESET _IO('i', 200)	   /* do s/w reset on device */
#define GPIB_LISAD _IOW('i', 201, uchar)   /* set device to listener */
#define GPIB_TLKAD _IOW('i', 202, uchar)   /* set device to talker */
#define GPIB_TRIG  _IO('i', 203)	   /* send a trigger cmd */
			/* set the a timeout on certain calls */
#define GPIB_TIME  _IOW('i', 204, uint_32) 
#define GPIB_SRQ   _IOW('i', 205, uchar)   /* request service (device only) */
#define GPIB_COMMAND	_IOW('i', 206, uchar) /* perform GPIB cmd */
#define GPIB_EOR	_IOW('i', 207, uchar) /* get last error code */
					      /* get status of device */
#define GPIB_STATUS	_IOWR('i', 208, struct dev_status*)

			/* poll devices (arg is bit mask of devices) */
#define GPIB_SPOLL	_IOWR('i', 209, uint_32)

			/* Perfom aux command on register */
#define GPIB_AUX_CMD	_IOW('i', 210, uchar)
			/* cause a paralled poll on devices */
#define GPIB_PPOLL_CMD	_IOW('i', 211, uchar)	

#endif	//USE_DUAL_TCP_STACK

    /*  SCSID ioctl commands parameters  */

#define	SCSISEND	_IOWR('t', 0, scsi_iocreq)		/* send SCSI command */



int ioctl(int fildes, uint_32 request, /* arg */ ...);
int _tty_server(char *init, int_8 *arg);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
