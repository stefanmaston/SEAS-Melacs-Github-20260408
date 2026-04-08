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
 * The authors of this code are John Ioannidis (ji@tla.org),
 * Angelos D. Keromytis (kermit@csd.uch.gr) and 
 * Niels Provos (provos@physnet.uni-hamburg.de).
 *
 * This code was written by John Ioannidis for BSD/OS in Athens, Greece, 
 * in November 1995.
 *
 * Ported to OpenBSD and NetBSD, with additional transforms, in December 1996,
 * by Angelos D. Keromytis.
 *
 * Additional transforms and features in 1997 and 1998 by Angelos D. Keromytis
 * and Niels Provos.
 *
 * Copyright (C) 1995, 1996, 1997, 1998 by John Ioannidis, Angelos D. Keromytis
 * and Niels Provos.
 *	
 * Permission to use, copy, and modify this software without fee
 * is hereby granted, provided that this entire notice is included in
 * all copies of any software which is or includes a copy or
 * modification of this software. 
 * You may use this code under the GNU public license if you so wish. Please
 * contribute changes back to the authors under this freer than GPL license
 * so that we may further the use of strong encryption without limitations to
 * all.
 *
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTY. IN PARTICULAR, NONE OF THE AUTHORS MAKES ANY
 * REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE
 * MERCHANTABILITY OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR
 * PURPOSE.
 */

#ifndef _IF_ENC_H_
#define _IF_ENC_H_

#define ENCMTU		(1024+512)
#define ENC_HDRLEN	12

struct enc_softc {
	struct ifnet		sc_if;  /* the interface */
};

struct enchdr {
	u_int32_t af;
	u_int32_t spi;
	u_int32_t flags;
};

extern struct enc_softc encif[];
#endif
