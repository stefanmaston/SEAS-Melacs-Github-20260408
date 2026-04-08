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

/*	$NetBSD: ip_nat.h,v 1.10.2.2 1997/11/17 16:33:19 mrg Exp $	*/

/*
 * Copyright (C) 1995-1997 by Darren Reed.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and due credit is given
 * to the original author and the contributors.
 *
 * @(#)ip_nat.h	1.5 2/4/96
 * Id: ip_nat.h,v 2.0.2.23.2.1 1997/11/05 11:08:18 darrenr Exp
 */

#ifndef	__IP_NAT_H__
#define	__IP_NAT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	SIOCADNAT	_IOW('r', 80, struct ipnat)
#define	SIOCRMNAT	_IOW('r', 81, struct ipnat)
#define	SIOCGNATS	_IOR('r', 82, struct natstat)
#define	SIOCGNATL	_IOWR('r', 83, struct natlookup)
#define SIOCGFRST	_IOR('r', 84, struct ipfrstat)
#define SIOCGIPST	_IOR('r', 85, struct ips_stat)
#define	SIOCFLNAT	_IOWR('r', 86, int)
#define	SIOCCNATL	_IOWR('r', 87, int)

#define	NAT_SIZE	367
#ifndef	APR_LABELLEN
#define	APR_LABELLEN	16
#endif

typedef	struct	nat	{
	u_long	nat_age;
	int	nat_flags;
	u_long	nat_sumd;
	u_long	nat_ipsumd;
	void	*nat_data;
	struct	in_addr	nat_inip;
	struct	in_addr	nat_outip;
	struct	in_addr	nat_oip;	/* other ip */
#ifdef	USE_DUAL_TCP_STACK
	u_quad_t	nat_pkts;
	u_quad_t	nat_bytes;
#else	//OLD IPV4 ONLY TCP STACK
	U_QUAD_T	nat_pkts;
	U_QUAD_T	nat_bytes;
#endif	//USE_DUAL_TCP_STACK
	u_short	nat_oport;	/* other port */
	u_short	nat_inport;
	u_short	nat_outport;
	u_short	nat_use;
	u_char	nat_state[2];
	struct	ipnat	*nat_ptr;
	struct	nat	*nat_next;
	struct	nat	*nat_hnext[2];
	struct	nat	**nat_hstart[2];
	void	*nat_ifp;
	int	nat_dir;
} nat_t;

typedef	struct	ipnat	{
	struct	ipnat	*in_next;
	void	*in_ifp;
	void	*in_apr;
	u_int	in_space;
	u_int	in_use;
	struct	in_addr	in_nextip;
	u_short	in_pnext;
	u_short	in_flags;
	u_short	in_port[2];
	struct	in_addr	in_in[2];
	struct	in_addr	in_out[2];
	int	in_redir; /* 0 if it's a mapping, 1 if it's a hard redir */
	char	in_ifname[IFNAMSIZ];
	char	in_plabel[APR_LABELLEN];	/* proxy label */
	char	in_p;	/* protocol */
	u_short	in_dport;
} ipnat_t;

#define	in_pmin		in_port[0]	/* Also holds static redir port */
#define	in_pmax		in_port[1]
#define	in_nip		in_nextip.s_addr
#define	in_inip		in_in[0].s_addr
#define	in_inmsk	in_in[1].s_addr
#define	in_outip	in_out[0].s_addr
#define	in_outmsk	in_out[1].s_addr

#define	NAT_OUTBOUND	0
#define	NAT_INBOUND	1

#define	NAT_MAP		0x01
#define	NAT_REDIRECT	0x02
#define	NAT_BIMAP	(NAT_MAP|NAT_REDIRECT)

#define	IPN_CMPSIZ	(sizeof(struct in_addr) * 4 + sizeof(u_short) * 3 + \
			 sizeof(int) + IFNAMSIZ + APR_LABELLEN + sizeof(char))

typedef	struct	natlookup {
	struct	in_addr	nl_inip;
	struct	in_addr	nl_outip;
	struct	in_addr	nl_realip;
	int	nl_flags;
	u_short	nl_inport;
	u_short	nl_outport;
	u_short	nl_realport;
} natlookup_t;

typedef	struct	natstat	{
	u_long	ns_mapped[2];
	u_long	ns_rules;
	u_long	ns_added;
	u_long	ns_expire;
	u_long	ns_inuse;
	u_long	ns_logged;
	u_long	ns_logfail;
	nat_t	**ns_table[2];
	ipnat_t	*ns_list;
} natstat_t;

#define	IPN_ANY		0x00
#define	IPN_TCP		0x01
#define	IPN_UDP		0x02
#define	IPN_TCPUDP	0x03
#define	IPN_DELETE	0x04
#define	IPN_ICMPERR	0x08


typedef	struct	natlog {
	struct	in_addr	nl_origip;
	struct	in_addr	nl_outip;
	struct	in_addr	nl_inip;
	u_short	nl_origport;
	u_short	nl_outport;
	u_short	nl_inport;
	u_short	nl_type;
	int	nl_rule;
#ifdef	USE_DUAL_TCP_STACK
	u_quad_t	nl_pkts;
	u_quad_t	nl_bytes;
#else	//OLD IPV4 ONLY TCP STACK
	U_QUAD_T	nl_pkts;
	U_QUAD_T	nl_bytes;
#endif	//USE_DUAL_TCP_STACK
} natlog_t;


#define	NL_NEWMAP	NAT_MAP
#define	NL_NEWRDR	NAT_REDIRECT
#define	NL_EXPIRE	0xffff


extern	u_long	fr_defnatage;
extern	u_long	fr_defnaticmpage;
extern	nat_t	*nat_table[2][NAT_SIZE];

int nat_ioctl(u_long cmd, caddr_t data);

extern	nat_t	*nat_new (ipnat_t *, ip_t *, fr_info_t *, u_short, int);
extern	nat_t	*nat_outlookup (void *, int, struct in_addr, u_short,
				 struct in_addr, u_short);
extern	nat_t	*nat_inlookup (void *, int, struct in_addr, u_short,
				struct in_addr, u_short);
extern	nat_t	*nat_lookupredir (natlookup_t *);
extern	nat_t	*nat_lookupmapip (void *, int, struct in_addr, u_short,
				   struct in_addr, u_short);
extern	nat_t	*nat_icmpinlookup (ip_t *, fr_info_t *);
extern	nat_t	*nat_icmpin (ip_t *, fr_info_t *, int *);

extern	int	ip_natout (ip_t *, int, fr_info_t *);
extern	int	ip_natin (ip_t *, int, fr_info_t *);
extern	void	ip_natunload (void), ip_natexpire (void);
extern	void	nat_log (struct nat *, u_short);
extern	void	fix_incksum (u_short *, u_long);
extern	void	fix_outcksum (u_short *, u_long);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* __IP_NAT_H__ */
