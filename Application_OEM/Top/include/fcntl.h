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

#ifndef _fcntl_h_
#define _fcntl_h_

#ifdef __cplusplus
extern "C" {
#endif

#define O_RDONLY    0x0001
#define O_WRONLY    0x0002
#define O_RDWR      (O_RDONLY | O_WRONLY)
#define O_CREAT     0x0004
#define O_APPEND    0x0008
#define O_EXCL      0x0010
#define O_NONBLOCK  0x0020
#define O_TRUNC     0x0040


// new definitions required by file system, used to be in unison.h I think
#define O_CONTIG     0x0100
#define O_DIRECT     0x0200

// old defn with new placement here for specifying a read only file system when mounting
// used in struct MOUNT_RQST passed to server, used in server, MT_RWFLAGS
#define FS_RDONLY 0x80000000


int creat(const char *path , mode_t mode);
int open(const char *path, int oflag, ...);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif  /* _fcntl_h_ */
