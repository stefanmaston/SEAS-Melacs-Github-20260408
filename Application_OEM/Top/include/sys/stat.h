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
* Name        : ustat.h
* Subsystem   : Unison
* Description : Stat structure return by u_stat and u_fstat.
* Assumptions :
*******************************************************************************
* Modification Records
*******************************************************************************
Date         Details (release, sub's affected, describe change)
*******************************************************************************

*******************************************************************************/

#ifndef __stat_h__
#define __stat_h__

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This is the structure returned by the "_stat" and "_fstat" calls.
 */
 struct stat {
	short int	st_dev;		/* Device identifier */
	unsigned short	st_uno;		/* Unode number */
	unsigned short	st_mode;	/* Permission bits */
	short int	st_nlink;	/* Number of links */
	short int	st_uid;		/* Not used yet */
	short int	st_padding;
	long		st_size;	/* # of bytes used in file */
	long		st_allocated;	/* # of bytes of space allocated */
	int		st_extents;	/* # of extents in file */
	long		st_minalloc;	/* Minimum #blks to allocate */
	long		st_mtime;	/* Last modify time */
};

#ifndef UNIX_SOURCE
/*
 * The meanings of the mode bits. Only the 700 (owner) bits are
 * currently used in determing permissions.
 */
#ifndef S_IFMT
#define S_IFMT   00170000		/* type of file */
#endif
#ifndef S_IFDIR
#define S_IFDIR  00040000  		/* directory */
#endif
#ifndef S_IFREG
#define S_IFREG  00100000		/* regular */
#endif
#ifndef S_ISUID
#define S_ISUID  00004000		/* set user id on execution */
#endif
#ifndef S_ISGID
#define S_ISGID  00002000		/* set group id on execution */
#endif
#ifndef S_ISVTX
#define S_ISVTX  00001000		/* save swapped text even after use */
#endif
#ifndef S_IREAD
#define S_IREAD  00000400		/* read permission, owner */
#endif
#ifndef S_IWRITE
#define S_IWRITE 00000200		/* write permission, owner */
#endif
#ifndef S_IEXEC
#define S_IEXEC  00000100		/* execute/search permission, owner */
#endif


#ifndef S_ISDIR
#define	S_ISDIR(m)	(((m)&S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
#define	S_ISREG(m)	(((m)&S_IFMT) == S_IFREG)
#endif


#ifndef S_IRWXU
#define S_IRWXU 0700
#endif
#ifndef S_IRUSR
#define S_IRUSR 0400
#endif
#ifndef S_IWUSR
#define S_IWUSR 0200
#endif
#ifndef S_IXUSR 
#define S_IXUSR 0100
#endif
//-----------------------------------//

#endif

#if defined(__cplusplus)
extern "C" {
#endif
	

int fstat (int fildes, struct stat *buf);

#if defined(__cplusplus)
}


#endif


int stat(const char *path, struct stat *buf);
int chmod(const char *path , mode_t mode );
int mkdir(const char *path, mode_t mode);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
