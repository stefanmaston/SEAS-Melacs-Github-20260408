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

/*
 * The author of this code is Angelos D. Keromytis (angelos@cis.upenn.edu)
 *
 * This code was written by Angelos D. Keromytis in Athens, Greece, in
 * February 2000. Network Security Technologies Inc. (NSTI) kindly
 * supported the development of this code.
 *
 * Copyright (c) 2000 Angelos D. Keromytis
 *
 * Permission to use, copy, and modify this software without fee
 * is hereby granted, provided that this entire notice is included in
 * all source code copies of any software which is or includes a copy or
 * modification of this software. 
 *
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTY. IN PARTICULAR, NONE OF THE AUTHORS MAKES ANY
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE
 * MERCHANTABILITY OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR
 * PURPOSE.
 */

#ifndef _CRYPTO_XFORM_H_
#define _CRYPTO_XFORM_H_

#include <crypto/md5k.h>
#include <crypto/sha1.h>
#include <crypto/rmd160.h>

/* Declarations */
struct auth_hash
{
    int type;
    char *name;
    u_int16_t keysize;
    u_int16_t hashsize; 
    u_int16_t authsize;
    u_int16_t ctxsize;
    void (*Init) (void *);
    int  (*Update) (void *, u_int8_t *, u_int16_t);
    void (*Final) (u_int8_t *, void *);
};

struct enc_xform
{
    int type;
    char *name;
    u_int16_t blocksize;
    u_int16_t minkey, maxkey;
    u_int32_t ivmask;           /* Or all possible modes, zero iv = 1 */ 
    void (*encrypt) (caddr_t, u_int8_t *);
    void (*decrypt) (caddr_t, u_int8_t *);
    void (*setkey) (u_int8_t **, u_int8_t *, int len);
    void (*zerokey) (u_int8_t **);
};

union authctx {
    MD5_CTX md5ctx;
    SHA1_CTX sha1ctx;
    RMD160_CTX rmd160ctx;
};

extern struct enc_xform enc_xform_des;
extern struct enc_xform enc_xform_3des;
extern struct enc_xform enc_xform_blf;
extern struct enc_xform enc_xform_cast5;
extern struct enc_xform enc_xform_skipjack;
extern struct enc_xform enc_xform_rijndael128;

extern struct auth_hash auth_hash_key_md5;
extern struct auth_hash auth_hash_key_sha1;
extern struct auth_hash auth_hash_hmac_md5_96;
extern struct auth_hash auth_hash_hmac_sha1_96;
extern struct auth_hash auth_hash_hmac_ripemd_160_96;
#endif /* _CRYPTO_XFORM_H_ */
