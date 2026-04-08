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

/*	$OpenBSD: tcp_var.h,v 1.35 2000/12/13 09:47:08 provos Exp $	*/
/*	$NetBSD: tcp_var.h,v 1.17 1996/02/13 23:44:24 christos Exp $	*/

/*
 * Copyright (c) 1982, 1986, 1993, 1994
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
 *	@(#)tcp_var.h	8.3 (Berkeley) 4/10/94
 */

#ifndef _NETINET_TCP_VAR_H_
#define _NETINET_TCP_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK


struct sackblk {
	tcp_seq start;		/* start seq no. of sack block */
	tcp_seq end; 		/* end seq no. */
};

struct sackhole {
	tcp_seq start;		/* start seq no. of hole */
	tcp_seq end;		/* end seq no. */
	int	dups;		/* number of dup(s)acks for this hole */
	tcp_seq rxmit;		/* next seq. no in hole to be retransmitted */
	struct sackhole *next;	/* next in list */
};

/*
 * Kernel variables for tcp.
 */

/*
 * Tcp control block, one per tcp; fields:
 */
struct tcpcb {
	struct ipqehead segq;		/* sequencing queue */
	short	t_state;		/* state of this connection */
	short	t_timer[TCPT_NTIMERS];	/* tcp timers */
	short	t_rxtshift;		/* log(2) of rexmt exp. backoff */
	short	t_rxtcur;		/* current retransmit value */
	short	t_dupacks;		/* consecutive dup acks recd */
	u_short	t_maxseg;		/* maximum segment size */
	char	t_force;		/* 1 if forcing out a byte */
	u_short	t_flags;
#define	TF_ACKNOW	0x0001		/* ack peer immediately */
#define	TF_DELACK	0x0002		/* ack, but try to delay it */
#define	TF_NODELAY	0x0004		/* don't delay packets to coalesce */
#define	TF_NOOPT	0x0008		/* don't use tcp options */
#define	TF_SENTFIN	0x0010		/* have sent FIN */
#define	TF_REQ_SCALE	0x0020		/* have/will request window scaling */
#define	TF_RCVD_SCALE	0x0040		/* other side has requested scaling */
#define	TF_REQ_TSTMP	0x0080		/* have/will request timestamps */
#define	TF_RCVD_TSTMP	0x0100		/* a timestamp was received in SYN */
#define	TF_SACK_PERMIT	0x0200		/* other side said I could SACK */
#define	TF_SIGNATURE	0x0400		/* require TCP MD5 signature */
#define TF_REASSLOCK	0x8000		/* reassembling or draining */

	struct	mbuf *t_template;	/* skeletal packet for transmit */
	struct	inpcb *t_inpcb;		/* back pointer to internet pcb */
/*
 * The following fields are used as in the protocol specification.
 * See RFC783, Dec. 1981, page 21.
 */
/* send sequence variables */
	tcp_seq	snd_una;		/* send unacknowledged */
	tcp_seq	snd_nxt;		/* send next */
	tcp_seq	snd_up;			/* send urgent pointer */
	tcp_seq	snd_wl1;		/* window update seg seq number */
	tcp_seq	snd_wl2;		/* window update seg ack number */
	tcp_seq	iss;			/* initial send sequence number */
	u_long	snd_wnd;		/* send window */
#ifdef TCP_SACK
	int	sack_disable;		/* disable SACK for this connection */
	int	snd_numholes;		/* number of holes seen by sender */
	struct sackhole *snd_holes;	/* linked list of holes (sorted) */
#if defined(TCP_SACK) && defined(TCP_FACK)
	tcp_seq snd_fack;		/* for FACK congestion control */
	u_long	snd_awnd;		/* snd_nxt - snd_fack + */
					/* retransmitted data */
	int retran_data;		/* amount of outstanding retx. data  */
#endif /* TCP_FACK */
#endif /* TCP_SACK */
#if defined(TCP_SACK)
	tcp_seq snd_last;		/* for use in fast recovery */
#endif
/* receive sequence variables */
	u_long	rcv_wnd;		/* receive window */
	tcp_seq	rcv_nxt;		/* receive next */
	tcp_seq	rcv_up;			/* receive urgent pointer */
	tcp_seq	irs;			/* initial receive sequence number */
#ifdef TCP_SACK
	tcp_seq rcv_laststart;		/* start of last segment recd. */
	tcp_seq rcv_lastend;		/* end of ... */
	tcp_seq rcv_lastsack;		/* last seq number(+1) sack'd by rcv'r*/
	int	rcv_numsacks;		/* # distinct sack blks present */
	struct sackblk sackblks[MAX_SACK_BLKS]; /* seq nos. of sack blocks */
#endif

/*
 * Additional variables for this implementation.
 */
/* receive variables */
	tcp_seq	rcv_adv;		/* advertised window */
/* retransmit variables */
	tcp_seq	snd_max;		/* highest sequence number sent;
					 * used to recognize retransmits
					 */
/* congestion control (for slow start, source quench, retransmit after loss) */
	u_long	snd_cwnd;		/* congestion-controlled window */
	u_long	snd_ssthresh;		/* snd_cwnd size threshhold for
					 * for slow start exponential to
					 * linear switch
					 */
	u_short	t_maxopd;		/* mss plus options */
	u_short	t_peermss;		/* peer's maximum segment size */

/*
 * transmit timing stuff.  See below for scale of srtt and rttvar.
 * "Variance" is actually smoothed difference.
 */
	short	t_idle;			/* inactivity time */
	short	t_rtt;			/* round trip time */
	tcp_seq	t_rtseq;		/* sequence number being timed */
	short	t_srtt;			/* smoothed round-trip time */
	short	t_rttvar;		/* variance in round-trip time */
	u_short	t_rttmin;		/* minimum rtt allowed */
	u_long	max_sndwnd;		/* largest window peer has offered */

/* out-of-band data */
	char	t_oobflags;		/* have some */
	char	t_iobc;			/* input character */
#define	TCPOOB_HAVEDATA	0x01
#define	TCPOOB_HADDATA	0x02
	short	t_softerror;		/* possible error not yet reported */

/* RFC 1323 variables */
	u_char	snd_scale;		/* window scaling for send window */
	u_char	rcv_scale;		/* window scaling for recv window */
	u_char	request_r_scale;	/* pending window scaling */
	u_char	requested_s_scale;
	u_int32_t ts_recent;		/* timestamp echo data */
	u_int32_t ts_recent_age;		/* when last updated */
	tcp_seq	last_ack_sent;

/* TUBA stuff */
	caddr_t	t_tuba_pcb;		/* next level down pcb for TCP over z */

	int pf;
};

#define	intotcpcb(ip)	((struct tcpcb *)(ip)->inp_ppcb)
#define	sototcpcb(so)	(intotcpcb(sotoinpcb(so)))

/*
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define	TCP_RTT_SCALE		8	/* multiplier for srtt; 3 bits frac. */
#define	TCP_RTT_SHIFT		3	/* shift for srtt; 3 bits frac. */
#define	TCP_RTTVAR_SCALE	4	/* multiplier for rttvar; 2 bits */
#define	TCP_RTTVAR_SHIFT	2	/* multiplier for rttvar; 2 bits */

/*
 * The initial retransmission should happen at rtt + 4 * rttvar.
 * Because of the way we do the smoothing, srtt and rttvar
 * will each average +1/2 tick of bias.  When we compute
 * the retransmit timer, we want 1/2 tick of rounding and
 * 1 extra tick because of +-1/2 tick uncertainty in the
 * firing of the timer.  The bias will give us exactly the
 * 1.5 tick we need.  But, because the bias is
 * statistical, we have to test that we don't drop below
 * the minimum feasible timer (which is 2 ticks).
 * This macro assumes that the value of TCP_RTTVAR_SCALE
 * is the same as the multiplier for rttvar.
 */
#define	TCP_REXMTVAL(tp) \
	((((tp)->t_srtt >> TCP_RTT_SHIFT) + (tp)->t_rttvar) >> 2)

/*
 * TCP statistics.
 * Many of these should be kept per connection,
 * but that's inconvenient at the moment.
 */
struct	tcpstat {
	u_int32_t tcps_connattempt;	/* connections initiated */
	u_int32_t tcps_accepts;		/* connections accepted */
	u_int32_t tcps_connects;	/* connections established */
	u_int32_t tcps_drops;		/* connections dropped */
	u_int32_t tcps_conndrops;	/* embryonic connections dropped */
	u_int32_t tcps_closed;		/* conn. closed (includes drops) */
	u_int32_t tcps_segstimed;	/* segs where we tried to get rtt */
	u_int32_t tcps_rttupdated;	/* times we succeeded */
	u_int32_t tcps_delack;		/* delayed acks sent */
	u_int32_t tcps_timeoutdrop;	/* conn. dropped in rxmt timeout */
	u_int32_t tcps_rexmttimeo;	/* retransmit timeouts */
	u_int32_t tcps_persisttimeo;	/* persist timeouts */
	u_int32_t tcps_persistdrop;	/* connections dropped in persist */
	u_int32_t tcps_keeptimeo;	/* keepalive timeouts */
	u_int32_t tcps_keepprobe;	/* keepalive probes sent */
	u_int32_t tcps_keepdrops;	/* connections dropped in keepalive */

	u_int32_t tcps_sndtotal;		/* total packets sent */
	u_int32_t tcps_sndpack;		/* data packets sent */
	u_int64_t tcps_sndbyte;		/* data bytes sent */
	u_int32_t tcps_sndrexmitpack;	/* data packets retransmitted */
	u_int64_t tcps_sndrexmitbyte;	/* data bytes retransmitted */
	u_int64_t tcps_sndrexmitfast;	/* Fast retransmits */
	u_int32_t tcps_sndacks;		/* ack-only packets sent */
	u_int32_t tcps_sndprobe;	/* window probes sent */
	u_int32_t tcps_sndurg;		/* packets sent with URG only */
	u_int32_t tcps_sndwinup;	/* window update-only packets sent */
	u_int32_t tcps_sndctrl;		/* control (SYN|FIN|RST) packets sent */

	u_int32_t tcps_rcvtotal;	/* total packets received */
	u_int32_t tcps_rcvpack;		/* packets received in sequence */
	u_int64_t tcps_rcvbyte;		/* bytes received in sequence */
	u_int32_t tcps_rcvbadsum;	/* packets received with ccksum errs */
	u_int32_t tcps_rcvbadoff;	/* packets received with bad offset */
	u_int32_t tcps_rcvmemdrop;	/* packets dropped for lack of memory */
	u_int32_t tcps_rcvnosec;	/* packets dropped for lack of ipsec */
	u_int32_t tcps_rcvshort;	/* packets received too short */
	u_int32_t tcps_rcvduppack;	/* duplicate-only packets received */
	u_int64_t tcps_rcvdupbyte;	/* duplicate-only bytes received */
	u_int32_t tcps_rcvpartduppack;	/* packets with some duplicate data */
	u_int64_t tcps_rcvpartdupbyte;	/* dup. bytes in part-dup. packets */
	u_int32_t tcps_rcvoopack;	/* out-of-order packets received */
	u_int64_t tcps_rcvoobyte;	/* out-of-order bytes received */
	u_int32_t tcps_rcvpackafterwin;	/* packets with data after window */
	u_int64_t tcps_rcvbyteafterwin;	/* bytes rcvd after window */
	u_int32_t tcps_rcvafterclose;	/* packets rcvd after "close" */
	u_int32_t tcps_rcvwinprobe;	/* rcvd window probe packets */
	u_int32_t tcps_rcvdupack;	/* rcvd duplicate acks */
	u_int32_t tcps_rcvacktoomuch;	/* rcvd acks for unsent data */
	u_int32_t tcps_rcvackpack;	/* rcvd ack packets */
	u_int64_t tcps_rcvackbyte;	/* bytes acked by rcvd acks */
	u_int32_t tcps_rcvwinupd;	/* rcvd window update packets */
	u_int32_t tcps_pawsdrop;	/* segments dropped due to PAWS */
	u_int32_t tcps_predack;		/* times hdr predict ok for acks */
	u_int32_t tcps_preddat;		/* times hdr predict ok for data pkts */

	u_int32_t tcps_noport;		/* no socket on port */
	u_int32_t tcps_badsyn;		/* SYN packet with src==dst rcv'ed */

	u_int32_t tcps_rcvbadsig;	/* rcvd bad/missing TCP signatures */
	u_int64_t tcps_rcvgoodsig;	/* rcvd good TCP signatures */
};

/*
 * Names for TCP sysctl objects.
 */

#define	TCPCTL_RFC1323		1 /* enable/disable RFC1323 timestamps/scaling */
#define	TCPCTL_KEEPINITTIME	2 /* TCPT_KEEP value */
#define TCPCTL_KEEPIDLE		3 /* allow tcp_keepidle to be changed */
#define TCPCTL_KEEPINTVL	4 /* allow tcp_keepintvl to be changed */
#define TCPCTL_SLOWHZ		5 /* return kernel idea of PR_SLOWHZ */
#define TCPCTL_BADDYNAMIC	6 /* return bad dynamic port bitmap */
#define	TCPCTL_RECVSPACE	7 /* receive buffer space */
#define	TCPCTL_SENDSPACE	8 /* send buffer space */
#define	TCPCTL_IDENT		9 /* get connection owner */
#define	TCPCTL_SACK	       10 /* selective acknowledgement, rfc 2018 */
#define TCPCTL_MSSDFLT	       11 /* Default maximum segment size */
#define	TCPCTL_RSTPPSLIMIT     12 /* RST pps limit */
#define	TCPCTL_MAXID	       13

struct tcp_ident_mapping {
	struct sockaddr_storage faddr, laddr;
	int euid, ruid;
};

#ifdef _KERNEL
extern struct	inpcbtable tcbtable;	/* head of queue of active tcpcb's */
extern	struct tcpstat tcpstat;	/* tcp statistics */
extern u_int32_t tcp_now;		/* for RFC 1323 timestamps */
extern	int tcp_do_rfc1323;	/* enabled/disabled? */
extern	int tcp_mssdflt;	/* default maximum segment size */
#ifdef TCP_SACK
extern	int tcp_do_sack;	/* SACK enabled/disabled */
#endif

int	 tcp_attach (struct socket *);
void	 tcp_canceltimers (struct tcpcb *);
struct tcpcb *
	 tcp_close (struct tcpcb *);
#if defined(INET6) && !defined(TCP6)
void	 tcp6_ctlinput(int, struct sockaddr *, void *);
#endif
void	 *tcp_ctlinput(int, struct sockaddr *, void *);
int	 tcp_ctloutput(int, struct socket *, int, int, struct mbuf **);
struct tcpcb *
	 tcp_disconnect(struct tcpcb *);
struct tcpcb *
	 tcp_drop(struct tcpcb *, int);
void	 tcp_dooptions(struct tcpcb *, u_char *, int, struct tcphdr *,
		int *, u_int32_t *, u_int32_t *);
void	 tcp_drain (void);
void	 tcp_fasttimo (void);
void	 tcp_init (void);
#if defined(INET6) && !defined(TCP6)
int	 tcp6_input(struct mbuf **, int *, int);
#endif
void	 tcp_input(struct mbuf *, ...);
int	 tcp_mss(struct tcpcb *, int);
void	 tcp_mss_update(struct tcpcb *);
void	 tcp_mtudisc(struct inpcb *, int);
void	 tcp_mtudisc_increase(struct inpcb *, int);
#ifdef INET6
void	tcp6_mtudisc(struct inpcb *, int);
void	tcp6_mtudisc_callback(struct in6_addr *);
#endif
struct tcpcb *
	 tcp_newtcpcb(struct inpcb *);
void	 tcp_notify(struct inpcb *, int);
int	 tcp_output(struct tcpcb *);
void	 tcp_pulloutofband(struct socket *, u_int, struct mbuf *, int);
void	 tcp_quench(struct inpcb *, int);
int	 tcp_reass(struct tcpcb *, struct tcphdr *, struct mbuf *, int *);
void	 tcp_rscale(struct tcpcb *, u_long);
void	 tcp_respond(struct tcpcb *, caddr_t, struct mbuf *, tcp_seq,
		tcp_seq, int);
void	 tcp_setpersist(struct tcpcb *);
void	 tcp_slowtimo(void);
struct mbuf *
	 tcp_template (struct tcpcb *);
struct tcpcb *
	 tcp_timers (struct tcpcb *, int);
void	 tcp_trace (int, int, struct tcpcb *, caddr_t, int, int);
struct tcpcb *
	 tcp_usrclosed (struct tcpcb *);
int	 tcp_usrreq (struct socket *,
	    int, struct mbuf *, struct mbuf *, struct mbuf *);
void	 tcp_xmit_timer(struct tcpcb *, int);
void	 tcpdropoldhalfopen(struct tcpcb *, u_int16_t);
#ifdef TCP_SACK
int	 tcp_sack_option(struct tcpcb *,struct tcphdr *,u_char *,int);
void	 tcp_update_sack_list(struct tcpcb *tp);
void	 tcp_del_sackholes(struct tcpcb *, struct tcphdr *);
void	 tcp_clean_sackreport(struct tcpcb *tp);
void	 tcp_sack_adjust(struct tcpcb *tp);
struct sackhole *
	 tcp_sack_output(struct tcpcb *tp);
int	 tcp_sack_partialack(struct tcpcb *, struct tcphdr *);
#ifdef DEBUG
void	 tcp_print_holes(struct tcpcb *tp);
#endif
#endif /* TCP_SACK */
#if defined(TCP_SACK)
int	 tcp_newreno(struct tcpcb *, struct tcphdr *);
u_long	 tcp_seq_subtract(u_long, u_long );
#endif /* TCP_SACK */
void	tcp_rndiss_init(void);
tcp_seq	tcp_rndiss_next(void);
u_int16_t
	tcp_rndiss_encrypt(u_int16_t);

#endif /* _KERNEL */

#else	//OLD IPV4 ONLY TCP STACK

/*
 * TCP configuration:  This is a half-assed attempt to make TCP
 * self-configure for a few varieties of 4.2 and 4.3-based unixes.
 * If you don't have a) a 4.3bsd vax or b) a 3.x Sun (x<6), check
 * this carefully (it's probably not right).  Please send me mail
 * if you run into configuration problems.
 *  - Van Jacobson (van@lbl-csam.arpa)
 */

#ifndef BSD
#define BSD 42	/* if we're not 4.3, pretend we're 4.2 */
#define OLDSTAT	/* set if we have to use old netstat binaries */
#endif

/* #define OLDSTAT	*/ /* set if we have to use old netstat binaries */

#if BSD < 43
#define TCP_COMPAT_42	/* set if we have to interop w/4.2 systems */
#endif

#ifndef SB_MAX
#ifdef	SB_MAXCOUNT
#define	SB_MAX	SB_MAXCOUNT	/* Sun has to be a little bit different... */
#else
#define SB_MAX	32767		/* XXX */
#endif	
#endif	

#ifndef IP_MAXPACKET
#define	IP_MAXPACKET	65535u		/* maximum packet size */
#endif

/*
 * Bill Nowicki pointed out that the page size (CLBYTES) has
 * nothing to do with the mbuf cluster size.  So, we followed
 * Sun's lead and made the new define MCLBYTES stand for the mbuf
 * cluster size.  The following define makes up backwards compatible
 * with 4.3 and 4.2.  If CLBYTES is >1024 on your machine, check
 * this against the mbuf cluster definitions in /usr/include/sys/mbuf.h.
 */
#ifndef MCLBYTES
#define	MCLBYTES CLBYTES	/* XXX */
#endif

/* --------------- end of TCP config ---------------- */

/*
 * Kernel variables for tcp.
 */

/*
 * Tcp control block, one per tcp; fields:
 */
struct tcpcb {
	struct	tcpiphdr *seg_next;	/* sequencing queue */
	struct	tcpiphdr *seg_prev;
	short	t_state;		/* state of this connection */
	short	t_timer[TCPT_NTIMERS];	/* tcp timers */
	short	t_rxtshift;		/* log(2) of rexmt exp. backoff */
	short	t_rxtcur;		/* current retransmit value */
	short	t_dupacks;		/* consecutive dup acks recd */
	u_short	t_maxseg;		/* maximum segment size */
	char	t_force;		/* 1 if forcing out a byte */
	u_char	t_flags;
#define	TF_ACKNOW	0x01		/* ack peer immediately */
#define	TF_DELACK	0x02		/* ack, but try to delay it */
#define	TF_NODELAY	0x04		/* don't delay packets to coalesce */
#define	TF_NOOPT	0x08		/* don't use tcp options */
#define	TF_SENTFIN	0x10		/* have sent FIN */
	struct	tcpiphdr *t_template;	/* skeletal packet for transmit */
	struct	inpcb *t_inpcb;		/* back pointer to internet pcb */
/*
 * The following fields are used as in the protocol specification.
 * See RFC783, Dec. 1981, page 21.
 */
/* send sequence variables */
	tcp_seq	snd_una;		/* send unacknowledged */
	tcp_seq	snd_nxt;		/* send next */
	tcp_seq	snd_up;			/* send urgent pointer */
	tcp_seq	snd_wl1;		/* window update seg seq number */
	tcp_seq	snd_wl2;		/* window update seg ack number */
	tcp_seq	iss;			/* initial send sequence number */
	u_short	snd_wnd;		/* send window */
/* receive sequence variables */
	u_short	rcv_wnd;		/* receive window */
	tcp_seq	rcv_nxt;		/* receive next */
	tcp_seq	rcv_up;			/* receive urgent pointer */
	tcp_seq	irs;			/* initial receive sequence number */
/*
 * Additional variables for this implementation.
 */
/* receive variables */
	tcp_seq	rcv_adv;		/* advertised window */
/* retransmit variables */
	tcp_seq	snd_max;		/* highest sequence number sent
					 * used to recognize retransmits
					 */
/* congestion control (for slow start, source quench, retransmit after loss) */
	u_short	snd_cwnd;		/* congestion-controlled window */
	u_short snd_ssthresh;		/* snd_cwnd size threshhold for
					 * for slow start exponential to
					 * linear switch */
/*
 * transmit timing stuff.
 * srtt and rttvar are stored as fixed point; for convenience in smoothing,
 * srtt has 3 bits to the right of the binary point, rttvar has 2.
 * "Variance" is actually smoothed difference.
 */
	short	t_idle;			/* inactivity time */
	short	t_rtt;			/* round trip time */
	tcp_seq	t_rtseq;		/* sequence number being timed */
	short	t_srtt;			/* smoothed round-trip time */
	short	t_rttvar;		/* variance in round-trip time */
	u_short max_rcvd;		/* most peer has sent into window */
	u_short	max_sndwnd;		/* largest window peer has offered */
/* out-of-band data */
	char	t_oobflags;		/* have some */
	char	t_iobc;			/* input character */
#define	TCPOOB_HAVEDATA	0x01
#define	TCPOOB_HADDATA	0x02
};

#define	intotcpcb(ip)	((struct tcpcb *)(ip)->inp_ppcb)
#define	sototcpcb(so)	(intotcpcb(sotoinpcb(so)))

/*
 * TCP statistics.
 * Many of these should be kept per connection,
 * but that's inconvenient at the moment.
 */
struct	tcpstat {
#ifdef OLDSTAT
	/*
	 * Declare statistics the same as in 4.3
	 * at the start of tcpstat (same size and
	 * position) for netstat.
	 */
	int	tcps_rcvbadsum;
	int	tcps_rcvbadoff;
	int	tcps_rcvshort;
	int	tcps_badsegs;
	int	tcps_unack;
#define	tcps_badsum	tcps_rcvbadsum
#define	tcps_badoff	tcps_rcvbadoff
#define	tcps_hdrops	tcps_rcvshort

#endif 
	u_long	tcps_connattempt;	/* connections initiated */
	u_long	tcps_accepts;		/* connections accepted */
	u_long	tcps_connects;		/* connections established */
	u_long	tcps_drops;		/* connections dropped */
	u_long	tcps_conndrops;		/* embryonic connections dropped */
	u_long	tcps_closed;		/* conn. closed (includes drops) */
	u_long	tcps_segstimed;		/* segs where we tried to get rtt */
	u_long	tcps_rttupdated;	/* times we succeeded */
	u_long	tcps_delack;		/* delayed acks sent */
	u_long	tcps_timeoutdrop;	/* conn. dropped in rxmt timeout */
	u_long	tcps_rexmttimeo;	/* retransmit timeouts */
	u_long	tcps_persisttimeo;	/* persist timeouts */
	u_long	tcps_keeptimeo;		/* keepalive timeouts */
	u_long	tcps_keepprobe;		/* keepalive probes sent */
	u_long	tcps_keepdrops;		/* connections dropped in keepalive */

	u_long	tcps_sndtotal;		/* total packets sent */
	u_long	tcps_sndpack;		/* data packets sent */
	u_long	tcps_sndbyte;		/* data bytes sent */
	u_long	tcps_sndrexmitpack;	/* data packets retransmitted */
	u_long	tcps_sndrexmitbyte;	/* data bytes retransmitted */
	u_long	tcps_sndacks;		/* ack-only packets sent */
	u_long	tcps_sndprobe;		/* window probes sent */
	u_long	tcps_sndurg;		/* packets sent with URG only */
	u_long	tcps_sndwinup;		/* window update-only packets sent */
	u_long	tcps_sndctrl;		/* control (SYN|FIN|RST) packets sent */

	u_long	tcps_rcvtotal;		/* total packets received */
	u_long	tcps_rcvpack;		/* packets received in sequence */
	u_long	tcps_rcvbyte;		/* bytes received in sequence */
#ifndef OLDSTAT
	u_long	tcps_rcvbadsum;		/* packets received with ccksum errs */
	u_long	tcps_rcvbadoff;		/* packets received with bad offset */
	u_long	tcps_rcvshort;		/* packets received too short */
#endif
	u_long	tcps_rcvduppack;	/* duplicate-only packets received */
	u_long	tcps_rcvdupbyte;	/* duplicate-only bytes received */
	u_long	tcps_rcvpartduppack;	/* packets with some duplicate data */
	u_long	tcps_rcvpartdupbyte;	/* dup. bytes in part-dup. packets */
	u_long	tcps_rcvoopack;		/* out-of-order packets received */
	u_long	tcps_rcvoobyte;		/* out-of-order bytes received */
	u_long	tcps_rcvpackafterwin;	/* packets with data after window */
	u_long	tcps_rcvbyteafterwin;	/* bytes rcvd after window */
	u_long	tcps_rcvafterclose;	/* packets rcvd after "close" */
	u_long	tcps_rcvwinprobe;	/* rcvd window probe packets */
	u_long	tcps_rcvdupack;		/* rcvd duplicate acks */
	u_long	tcps_rcvacktoomuch;	/* rcvd acks for unsent data */
	u_long	tcps_rcvackpack;	/* rcvd ack packets */
	u_long	tcps_rcvackbyte;	/* bytes acked by rcvd acks */
	u_long	tcps_rcvwinupd;		/* rcvd window update packets */
};

#ifdef KERNEL
extern struct	inpcb tcb;		/* head of queue of active tcpcb's */
extern struct	tcpstat tcpstat;	/* tcp statistics */
struct	tcpiphdr *tcp_template();
struct	tcpcb *tcp_close(), *tcp_drop();
struct	tcpcb *tcp_timers(), *tcp_disconnect(), *tcp_usrclosed();
#endif

#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _NETINET_TCP_VAR_H_ */
