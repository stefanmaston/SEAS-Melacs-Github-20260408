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
* Name        : device.h
* Subsystem   : FSYS
* Description : Device table for FSYS server
* Assumptions : 
*******************************************************************************
* Modification Records
*******************************************************************************
Date         Details (release, sub's affected, describe change)
*******************************************************************************

*******************************************************************************/

#ifndef __device_h__
#define	__device_h__

#include <sys/types.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef	unsigned	short	udev_t;

#define NO_DEV		(udev_t)0

struct bdevsw {
	int	(* bdev_strategy)(udev_t, int_32, int, char*, int);
	int	(* bdev_open)(udev_t);
	int	(* bdev_close)(udev_t);
	int	(* bdev_reserved)(udev_t);
};

extern struct bdevsw bdevsw[];
extern int	     bdevswmax;

#define	DEV_MAJOR(dev)	((dev) >> 8)
#define DEV_MINOR(dev)	((dev) & 0xff)

#define	dev_open(dev)	(* bdevsw[DEV_MAJOR(dev)].bdev_open)(dev)
#define dev_close(dev)	(* bdevsw[DEV_MAJOR(dev)].bdev_close)(dev)
#define	dev_strategy(dev, off, len, buf, rwflag) \
	(* bdevsw[DEV_MAJOR(dev)].bdev_strategy)(dev, off, len, buf, rwflag)

/*
 * One of the following is passed to bdev_strategy to tell it which
 * direction the I/O should go.
 */
#define BDEV_READ	0x00
#define BDEV_WRITE	0x01


/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */


/* Status of Disk Functions */
typedef uchar	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = EOK,				/* Successful */
	RES_ERROR = EIO,			/* R/W Error */
	RES_WRPRT = EACCES,			/* Write Protected */
	RES_NOTRDY = EBUSY,			/* Not Ready */
	RES_PARERR = ENOTSUPPORTED	/* Invalid Parameter */
} DRESULT;

typedef struct tagDiskDriver
{
	DSTATUS	(* disk_initialize)(void);
	DSTATUS (* disk_status)(void);
	DRESULT (* disk_read)(uchar*, ulong, uchar);
	DRESULT (* disk_write)(const uchar*, ulong, uchar);
	DRESULT (* disk_ioctl)(uchar, void*);
	void (*disk_timerproc)(void);
} DISK_DRIVER;

/*
 * STRUCTURES FOR UART DRIVER
 */

typedef struct
{
	void * dev;
} UART_DRIVER;

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
