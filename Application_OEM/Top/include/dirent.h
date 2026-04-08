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

#ifndef __DIRENT_H
#define __DIRENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * An array of struct direct's is what is returned from the
 * getdirentries call.
 */
#define MAXNAMLEN	255

struct	dirent {
	unsigned long	d_fileno;				/* file number of entry */
	unsigned short	d_reclen;				/* length of this record */
	unsigned char	d_type;					/* file type, see below */
	unsigned char	d_namlen;				/* length of string in d_name */
	char			d_name[MAXNAMLEN + 1];	/* name (up to MAXNAMLEN + 1) */
};


/*
* File types
*/
#define DT_UNKNOWN      0
#define DT_FIFO         1
#define DT_CHR          2
#define DT_DIR          4
#define DT_BLK          6
#define DT_REG          8
#define DT_LNK          10
#define DT_SOCK         12
#define DT_WHT          14


ssize_t getdirentries(int fd, char *buf, size_t nbytes, off_t *basep);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
