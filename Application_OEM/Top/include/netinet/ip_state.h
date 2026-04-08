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

/*	$NetBSD: ip_state.h,v 1.8.2.2 1997/11/17 16:33:30 mrg Exp $	*/

/*
 * Copyright (C) 1995-1997 by Darren Reed.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and due credit is given
 * to the original author and the contributors.
 *
 * @(#)ip_state.h	1.3 1/12/96 (C) 1995 Darren Reed
 * Id: ip_state.h,v 2.0.2.14.2.1 1997/11/06 21:23:15 darrenr Exp
 */
#ifndef	__IP_STATE_H__
#define	__IP_STATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	IPSTATE_SIZE	257
#define	IPSTATE_MAX	2048	/* Maximum number of states held */

#define	PAIRS(s1,d1,s2,d2)	((((s1) == (s2)) && ((d1) == (d2))) ||\
				 (((s1) == (d2)) && ((d1) == (s2))))
#define	IPPAIR(s1,d1,s2,d2)	PAIRS((s1).s_addr, (d1).s_addr, \
				      (s2).s_addr, (d2).s_addr)


typedef struct udpstate {
	u_short	us_sport;
	u_short	us_dport;
} udpstate_t;

typedef struct icmpstate {
	u_short	ics_id;
	u_short	ics_seq;
	u_char	ics_type;
} icmpstate_t;

typedef	struct tcpstate {
	u_short	ts_sport;
	u_short	ts_dport;
	u_long	ts_seq;
	u_long	ts_ack;
	u_short	ts_swin;
	u_short	ts_dwin;
	u_char	ts_state[2];
} tcpstate_t;

typedef struct ipstate {
	struct	ipstate	*is_next;
	u_long	is_age;
	u_int	is_pass;
#ifdef	USE_DUAL_TCP_STACK
	u_quad_t	is_pkts;
	u_quad_t	is_bytes;
#else	//OLD IPV4 ONLY TCP STACK
	U_QUAD_T	is_pkts;
	U_QUAD_T	is_bytes;
#endif	//USE_DUAL_TCP_STACK
	struct	in_addr	is_src;
	struct	in_addr	is_dst;
	u_char	is_p;
	u_char	is_flags;
	union {
		icmpstate_t	is_ics;
		tcpstate_t	is_ts;
		udpstate_t	is_us;
	} is_ps;
} ipstate_t;

#define	is_icmp	is_ps.is_ics
#define	is_tcp	is_ps.is_ts
#define	is_udp	is_ps.is_us
#define	is_seq	is_tcp.ts_seq
#define	is_ack	is_tcp.ts_ack
#define	is_dwin	is_tcp.ts_dwin
#define	is_swin	is_tcp.ts_swin
#define	is_sport	is_tcp.ts_sport
#define	is_dport	is_tcp.ts_dport
#define	is_state	is_tcp.ts_state

#define	TH_OPENING	(TH_SYN|TH_ACK)


typedef	struct	ipslog	{
#ifdef	USE_DUAL_TCP_STACK
	u_quad_t	isl_pkts;
	u_quad_t	isl_bytes;
#else	//OLD IPV4 ONLY TCP STACK
	U_QUAD_T	isl_pkts;
	U_QUAD_T	isl_bytes;
#endif	//USE_DUAL_TCP_STACK
	struct	in_addr	isl_src;
	struct	in_addr	isl_dst;
	u_char	isl_p;
	u_char	isl_flags;
	u_short	isl_type;
	union {
		u_short	isl_filler[2];
		u_short	isl_ports[2];
		u_short	isl_icmp;
	} isl_ps;
} ipslog_t;

#define	isl_sport	isl_ps.isl_ports[0]
#define	isl_dport	isl_ps.isl_ports[1]
#define	isl_itype	isl_ps.isl_icmp

#define	ISL_NEW		0
#define	ISL_EXPIRE	0xffff
#define	ISL_FLUSH	0xfffe


typedef	struct	ips_stat {
	u_long	iss_hits;
	u_long	iss_miss;
	u_long	iss_max;
	u_long	iss_tcp;
	u_long	iss_udp;
	u_long	iss_icmp;
	u_long	iss_nomem;
	u_long	iss_expire;
	u_long	iss_fin;
	u_long	iss_active;
	u_long	iss_logged;
	u_long	iss_logfail;
	ipstate_t **iss_table;
} ips_stat_t;


extern	u_long	fr_tcpidletimeout;
extern	u_long	fr_tcpclosewait;
extern	u_long	fr_tcplastack;
extern	u_long	fr_tcptimeout;
extern	u_long	fr_tcpclosed;
extern	u_long	fr_udptimeout;
extern	u_long	fr_icmptimeout;
extern	int	fr_tcpstate (ipstate_t *, fr_info_t *, ip_t *,
			    tcphdr_t *, u_short);
extern	ips_stat_t	*fr_statetstats (void);
extern	int	fr_addstate (ip_t *, fr_info_t *, u_int);
extern	int	fr_checkstate (ip_t *, fr_info_t *);
extern	void	fr_timeoutstate (void);
extern	void	fr_tcp_age (u_long *, u_char *, ip_t *, fr_info_t *, int);
extern	int	fr_state_flush (int);
extern	void	fr_stateunload (void);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* __IP_STATE_H__ */
