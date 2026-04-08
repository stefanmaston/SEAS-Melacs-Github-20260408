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

#ifndef _CRYPTO_CRYPTOSOFT_H_
#define _CRYPTO_CRYPTOSOFT_H_

/* Software session entry */
struct swcr_data
{
    int               sw_alg;		/* Algorithm */
    union
    {
	struct
	{
            u_int8_t         *SW_ictx;
            u_int8_t         *SW_octx;
	    u_int32_t         SW_klen;
	    struct auth_hash *SW_axf;
	} SWCR_AUTH;

	struct
	{
            u_int8_t         *SW_kschedule;
            u_int8_t         *SW_iv;
	    struct enc_xform *SW_exf;
	} SWCR_ENC;
    } SWCR_UN;

#define sw_ictx      SWCR_UN.SWCR_AUTH.SW_ictx
#define sw_octx      SWCR_UN.SWCR_AUTH.SW_octx
#define sw_klen      SWCR_UN.SWCR_AUTH.SW_klen
#define sw_axf       SWCR_UN.SWCR_AUTH.SW_axf
#define sw_kschedule SWCR_UN.SWCR_ENC.SW_kschedule
#define sw_iv        SWCR_UN.SWCR_ENC.SW_iv
#define sw_exf       SWCR_UN.SWCR_ENC.SW_exf

    struct swcr_data *sw_next;
};

#ifdef _KERNEL
extern u_int8_t hmac_ipad_buffer[64];
extern u_int8_t hmac_opad_buffer[64];

extern int swcr_encdec(struct cryptodesc *, struct swcr_data *, caddr_t, int);
extern int swcr_authcompute(struct cryptodesc *, struct swcr_data *,
			    caddr_t, int);
extern int swcr_process(struct cryptop *);
extern int swcr_newsession(u_int32_t *, struct cryptoini *);
extern int swcr_freesession(u_int64_t);
extern void swcr_init(void);
#endif /* _KERNEL */

#endif /* _CRYPTO_CRYPTO_H_ */
