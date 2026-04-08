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

/*	$NetBSD: ip_frag.h,v 1.8.2.1 1997/10/30 07:13:47 mrg Exp $	*/

/*
 * Copyright (C) 1993-1997 by Darren Reed.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and due credit is given
 * to the original author and the contributors.
 *
 * @(#)ip_frag.h	1.5 3/24/96
 * Id: ip_frag.h,v 2.0.2.12 1997/10/23 14:56:01 darrenr Exp
 */

#ifndef	__IP_FRAG_H__
#define	__IP_FRAG_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	IPFT_SIZE	257

typedef	struct	ipfr	{
	struct	ipfr	*ipfr_next, *ipfr_prev;
	void	*ipfr_data;
	struct	in_addr	ipfr_src;
	struct	in_addr	ipfr_dst;
	u_short	ipfr_id;
	u_char	ipfr_p;
	u_char	ipfr_tos;
	u_short	ipfr_off;
	u_short	ipfr_ttl;
	u_char	ipfr_pass;
} ipfr_t;


typedef	struct	ipfrstat {
	u_long	ifs_exists;	/* add & already exists */
	u_long	ifs_nomem;
	u_long	ifs_new;
	u_long	ifs_hits;
	u_long	ifs_expire;
	u_long	ifs_inuse;
	struct	ipfr	**ifs_table;
	struct	ipfr	**ifs_nattab;
} ipfrstat_t;

#define	IPFR_CMPSZ	(4 + 4 + 2 + 1 + 1)

extern	int	fr_ipfrttl;
extern	ipfrstat_t	*ipfr_fragstats (void);
extern	int	ipfr_newfrag (ip_t *, fr_info_t *, int);
extern	int	ipfr_nat_newfrag (ip_t *, fr_info_t *, int, struct nat *);
extern	nat_t	*ipfr_nat_knownfrag (ip_t *, fr_info_t *);
extern	int	ipfr_knownfrag (ip_t *, fr_info_t *);
extern	void	ipfr_forget (void *);
extern	void	ipfr_unload (void);
#ifdef	USE_DUAL_TCP_STACK
extern	void	ipfr_slowtimer (void);
#else	//OLD IPV4 ONLY TCP STACK
extern	int	ipfr_slowtimer (void);
#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	/* __IP_FIL_H__ */
