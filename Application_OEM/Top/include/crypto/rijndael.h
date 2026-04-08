/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2014 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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

/*	$OpenBSD: rijndael.h,v 1.2 2000/10/16 22:44:33 deraadt Exp $	*/

/* This is an independent implementation of the encryption algorithm:   */
/*                                                                      */
/*         RIJNDAEL by Joan Daemen and Vincent Rijmen                   */
/*                                                                      */
/* which is a candidate algorithm in the Advanced Encryption Standard   */
/* programme of the US National Institute of Standards and Technology.  */
/*                                                                      */
/* Copyright in this implementation is held by Dr B R Gladman but I     */
/* hereby give permission for its free direct or derivative use subject */
/* to acknowledgment of its origin and compliance with any conditions   */
/* that the originators of the algorithm place on its exploitation.     */
/*                                                                      */
/* Dr Brian Gladman (gladman@seven77.demon.co.uk) 14th January 1999     */

#ifndef _RIJNDAEL_H_
#define _RIJNDAEL_H_

/* 1. Standard types for AES cryptography source code               */

typedef u_int8_t   u1byte; /* an 8 bit unsigned character type */
typedef u_int16_t  u2byte; /* a 16 bit unsigned integer type   */
typedef u_int32_t  u4byte; /* a 32 bit unsigned integer type   */

typedef int8_t     s1byte; /* an 8 bit signed character type   */
typedef int16_t    s2byte; /* a 16 bit signed integer type     */
typedef int32_t    s4byte; /* a 32 bit signed integer type     */

typedef struct _rijndael_ctx {
	u4byte  k_len;
	int decrypt;
	u4byte  e_key[64];
	u4byte  d_key[64];
} rijndael_ctx;


/* 2. Standard interface for AES cryptographic routines             */

/* These are all based on 32 bit unsigned values and will therefore */
/* require endian conversions for big-endian architectures          */

rijndael_ctx *rijndael_set_key  (rijndael_ctx *, const u4byte *, u4byte, int);
void rijndael_encrypt (rijndael_ctx *, const u1byte *, u1byte *);
void rijndael_decrypt (rijndael_ctx *, const u1byte *, u1byte *);

#endif /* _RIJNDAEL_H_ */
