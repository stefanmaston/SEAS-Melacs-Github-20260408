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

/*	$OpenBSD: in_pcb.h,v 1.33 2001/03/28 20:03:02 angelos Exp $	*/
/*	$NetBSD: in_pcb.h,v 1.14 1996/02/13 23:42:00 christos Exp $	*/

/*
 * Copyright (C) 1995, 1996, 1997, and 1998 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Copyright (c) 1982, 1986, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)in_pcb.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_IN_PCB_H_
#define _NETINET_IN_PCB_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK

#include <sys/queue.h>
#include <netinet/ip6.h>
#include <netinet6/ip6_var.h>
#include <netinet/icmp6.h>
#ifdef IPSEC
#include <netinet/ip_ipsp.h>
#endif

union inpaddru {
	struct in6_addr iau_addr6;
	struct {
		u_int8_t pad[12];
		struct in_addr inaddr;	/* easier transition */
	} iau_a4u;
};

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	CIRCLEQ_ENTRY(inpcb) inp_queue;
	struct	  inpcbtable *inp_table;
	union	  inpaddru inp_faddru;		/* Foreign address. */
	union	  inpaddru inp_laddru;		/* Local address. */
#define	inp_faddr	inp_faddru.iau_a4u.inaddr
#define	inp_faddr6	inp_faddru.iau_addr6
#define	inp_laddr	inp_laddru.iau_a4u.inaddr
#define	inp_laddr6	inp_laddru.iau_addr6
	u_int16_t inp_fport;		/* foreign port */
	u_int16_t inp_lport;		/* local port */
	struct	  socket *inp_socket;	/* back pointer to socket */
	caddr_t	  inp_ppcb;		/* pointer to per-protocol pcb */
	union {				/* Route (notice increased size). */
		struct route ru_route;
		struct route_in6 ru_route6;
	} inp_ru;
#define	inp_route	inp_ru.ru_route
#define	inp_route6	inp_ru.ru_route6
	int	  inp_flags;		/* generic IP/datagram flags */
	union {				/* Header prototype. */
		struct ip hu_ip;
		struct ip6_hdr hu_ipv6;
	} inp_hu;
#define	inp_ip		inp_hu.hu_ip
#define	inp_ipv6	inp_hu.hu_ipv6
	struct	  mbuf *inp_options;	/* IP options */
	struct ip6_pktopts *inp_outputopts6; /* IP6 options for outgoing packets */
	short inp_hops;
	union {
		struct ip_moptions *mou_mo;    /* IPv4 multicast options */
		struct ip6_moptions *mou_mo6; /* IPv6 multicast options */
	} inp_mou;
#define inp_moptions inp_mou.mou_mo
#define inp_moptions6 inp_mou.mou_mo6
#ifdef IPSEC
	u_char	  inp_seclevel[3];
#define SL_AUTH           0             /* Authentication level */
#define SL_ESP_TRANS      1             /* ESP transport level */
#define SL_ESP_NETWORK    2             /* ESP network (encapsulation) level */
	u_int8_t  inp_secrequire:4,     /* Condensed State from above */
	          inp_secresult:4;	/* Result from Key Management */
#define SR_FAILED         1             /* Negotiation failed permanently */
#define SR_SUCCESS        2             /* SA successfully established */
#define SR_WAIT           3             /* Waiting for SA */
	TAILQ_ENTRY(inpcb) inp_tdb_in_next, inp_tdb_out_next;
	struct tdb     *inp_tdb_in, *inp_tdb_out;
#endif
#define	inp_flowinfo	inp_hu.hu_ipv6.ip6_flow

	int	in6p_cksum;
#ifndef _KERNEL
#define inp_csumoffset	in6p_cksum
#endif
	struct	icmp6_filter *inp_icmp6filt;
};

struct inpcbtable {
	CIRCLEQ_HEAD(, inpcb) inpt_queue;
	u_int16_t inpt_lastport;
};

/* flags in inp_flags: */
#define	INP_RECVOPTS	0x001	/* receive incoming IP options */
#define	INP_RECVRETOPTS	0x002	/* receive IP options for reply */
#define	INP_RECVDSTADDR	0x004	/* receive IP dst address */

#define	INP_RXDSTOPTS	INP_RECVOPTS
#define	INP_RXHOPOPTS	INP_RECVRETOPTS
#define	INP_RXINFO	INP_RECVDSTADDR
#define	INP_RXSRCRT	0x010
#define	INP_HOPLIMIT	0x020

#define	INP_CONTROLOPTS	(INP_RECVOPTS|INP_RECVRETOPTS|INP_RECVDSTADDR| \
	    INP_RXSRCRT|INP_HOPLIMIT)

#define	INP_HDRINCL	0x008	/* user supplies entire IP header */
#define	INP_HIGHPORT	0x010	/* user wants "high" port binding */
#define	INP_LOWPORT	0x020	/* user wants "low" port binding */

/*
 * These flags' values should be determined by either the transport
 * protocol at PRU_BIND, PRU_LISTEN, PRU_CONNECT, etc, or by in_pcb*().
 */
#define	INP_IPV6	0x100	/* sotopf(inp->inp_socket) == PF_INET6 */

#if 1	/*KAME*/
/*
 * Flags in in6p_flags
 * We define KAME's original flags in higher 16 bits as much as possible
 * for compatibility with *bsd*s.
 * XXX: Should IN6P_HIGHPORT and IN6P_LOWPORT be moved as well?
 */
#define IN6P_RECVOPTS		INP_RECVOPTS	/* recv incoming IP6 options */
#define IN6P_RECVRETOPTS	INP_RECVRETOPTS /* recv IP6 options for reply */
#define IN6P_RECVDSTADDR	INP_RECVDSTADDR /* recv IP6 dst address */
#define IN6P_HIGHPORT		INP_HIGHPORT	/* user wants "high" port */
#define IN6P_LOWPORT		INP_LOWPORT	/* user wants "low" port */
#define IN6P_PKTINFO		0x010000 /* receive IP6 dst and I/F */
#define IN6P_HOPLIMIT		0x020000 /* receive hoplimit */
#define IN6P_HOPOPTS		0x040000 /* receive hop-by-hop options */
#define IN6P_DSTOPTS		0x080000 /* receive dst options after rthdr */
#define IN6P_RTHDR		0x100000 /* receive routing header */
#define IN6P_RTHDRDSTOPTS	0x200000 /* receive dstoptions before rthdr */

#define IN6P_ANONPORT		0x4000000 /* port chosen for user */
#define IN6P_FAITH		0x8000000 /* accept FAITH'ed connections */

#define IN6P_CONTROLOPTS	(IN6P_PKTINFO|IN6P_HOPLIMIT|IN6P_HOPOPTS|\
				 IN6P_DSTOPTS|IN6P_RTHDR|IN6P_RTHDRDSTOPTS)
#endif

#define	INPLOOKUP_WILDCARD	1
#define	INPLOOKUP_SETLOCAL	2
#define	INPLOOKUP_IPV6		4

#define	sotoinpcb(so)	((struct inpcb *)(so)->so_pcb)

#ifdef _KERNEL

#define sotopf(so)  (so->so_proto->pr_domain->dom_family)

void	 in_losing(struct inpcb *);
int	 in_pcballoc(struct socket *, void *);
int	 in_pcbbind(void *, struct mbuf *);
int	 in_pcbconnect(void *, struct mbuf *);
void	 in_pcbdetach(void *);
void	 in_pcbdisconnect(void *);
struct inpcb *
	 in_pcbhashlookup(struct inpcbtable *, struct in_addr,
			       u_int, struct in_addr, u_int);
#ifdef INET6
struct inpcb *
	 in6_pcbhashlookup(struct inpcbtable *, struct in6_addr *,
			       u_int, struct in6_addr *, u_int);
int	 in6_pcbbind(struct inpcb *, struct mbuf *);
int	 in6_pcbconnect(struct inpcb *, struct mbuf *);
int	 in6_setsockaddr(struct inpcb *, struct mbuf *);
int	 in6_setpeeraddr(struct inpcb *, struct mbuf *);
#endif /* INET6 */
void in_pcbinit(struct inpcbtable *table);
struct inpcb *
	 in_pcblookup(struct inpcbtable *, void *, u_int, void *,
	    u_int, int);
void	 in_pcbnotify(struct inpcbtable *, struct sockaddr *,
	    u_int, struct in_addr, u_int, int, void (*)(struct inpcb *, int));
void	 in_pcbnotifyall(struct inpcbtable *, struct sockaddr *,
	    int, void (*)(struct inpcb *, int));
void	 in_pcbrehash(struct inpcb *);
void	 in_rtchange(struct inpcb *, int);
void	 in_setpeeraddr(struct inpcb *, struct mbuf *);
void	 in_setsockaddr(struct inpcb *, struct mbuf *);
extern struct sockaddr_in *in_selectsrc(struct sockaddr_in *,
	struct route *, int, struct ip_moptions *, int *);
struct rtentry *
	in_pcbrtentry(struct inpcb *);

/* INET6 stuff */
int	in6_pcbnotify(struct inpcbtable *, struct sockaddr *,
			   u_int, struct sockaddr *, u_int, int, void *,
			   void (*)(struct inpcb *, int));
struct 	in6_addr *in6_selectsrc(struct sockaddr_in6 *,
				     struct ip6_pktopts *,
				     struct ip6_moptions *,
				     struct route_in6 *,
				     struct in6_addr *, int *);
int	in6_selecthlim(struct inpcb *, struct ifnet *);
int	in6_pcbsetport(struct in6_addr *, struct inpcb *);
#endif

#else	//OLD IPV4 ONLY TCP STACK

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)in_pcb.h	7.3 (Berkeley) 6/29/88
 */

/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	struct	inpcb *inp_next,*inp_prev;
					/* pointers to other pcb's */
	struct	inpcb *inp_head;	/* pointer back to chain of inpcb's
					   for this protocol */
	struct	in_addr inp_faddr;	/* foreign host table entry */
	u_short	inp_fport;		/* foreign port */
	struct	in_addr inp_laddr;	/* local host table entry */
	u_short	inp_lport;		/* local port */
	struct	socket *inp_socket;	/* back pointer to socket */
	caddr_t	inp_ppcb;		/* pointer to per-protocol pcb */
	struct	route inp_route;	/* placeholder for routing entry */
	struct	mbuf *inp_options;	/* IP options */
};

#define	INPLOOKUP_WILDCARD	1
#define	INPLOOKUP_SETLOCAL	2

#define	sotoinpcb(so)	((struct inpcb *)(so)->so_pcb)

#ifdef KERNEL
struct	inpcb *in_pcblookup();
#endif

#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _NETINET_IN_PCB_H_ */
