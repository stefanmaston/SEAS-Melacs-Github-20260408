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

/*	$OpenBSD: mbuf.h,v 1.22 2001/03/31 23:03:37 angelos Exp $	*/
/*	$NetBSD: mbuf.h,v 1.19 1996/02/09 18:25:14 christos Exp $	*/

/*
 * Copyright (c) 1982, 1986, 1988, 1993
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
 *	@(#)mbuf.h	8.5 (Berkeley) 2/19/95
 */

#ifndef _SYS_MBUF_H_
#define _SYS_MBUF_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK

/*
 * Convert MALLOC/FREE to mbuf mechanism
 */
#define	MALLOC(space, cast, size, type, flags) \
	(space) = (cast)mbuf_malloc((u_int)(size), type, flags)
#define	FREE(addr, type) mbuf_free((caddr_t)(addr), type)

// used in MFREE
void retry_pend_rqsts(void **q);

#ifndef M_WAITOK

/*
* flags to malloc
*/
#define	M_WAITOK	0x0000
#define	M_NOWAIT	0x0001

/*
 * Types of memory to be allocated in mbuf
 */
#define	M_SOCKET	MT_SOCKET	/* socket structure */
#define	M_PCB		MT_PCB		/* protocol control block */
#define	M_RTABLE	MT_RTABLE	/* routing tables */
#define	M_IFADDR	MT_IFADDR	/* interface address */
#define	M_SOOPTS	MT_SOOPTS	/* socket options */
#define	M_IPMOPTS	MT_MCAST	/* internet multicast options */
#define	M_IPMADDR	MT_MCAST	/* internet multicast address */
#define	M_IFMADDR	MT_MCAST	/* link-level multicast address */
#define M_MRTABLE	MT_MRTABLE	/* multicast routing tables */
#define	M_IPQ		MT_IPQ		/* IP packet queue entry */
#define	M_TEMP		MT_TEMP		/* misc temporary data buffers */
#define M_FTABLE	MT_FTABLE	/* fragment reassembly header */

/* KAME IPv6 */
#define	M_IP6OPT	MT_IP6	/* IPv6 options */
#define	M_IP6NDP	MT_IP6	/* IPv6 Neighbour Discovery */
#define	M_IP6RR		MT_IP6	/* IPv6 Router Renumbering Prefix */
#define	M_RR_ADDR	MT_IP6	/* IPv6 Router Renumbering Ifid */

/* IPsec */
#define	M_TDB		MT_IPSEC	/* Transforms database */
#define	M_XDATA		MT_IPSEC	/* IPsec data */
#define	M_PFKEY		MT_IPSEC	/* pfkey data */
#endif

extern void *ipsp_copy_ident(void *);

/*
 * Mbufs are of a single size, MSIZE (machine/param.h), which
 * includes overhead.  An mbuf may add a single "mbuf cluster" of size
 * MCLBYTES (also in machine/param.h), which has no additional overhead
 * and is used instead of the internal data area; this is done when
 * at least MINCLSIZE of data must be stored.
 */

#define	MLEN		(MSIZE - sizeof(struct m_hdr))	/* normal data len */
#define	MHLEN		(MLEN - sizeof(struct pkthdr))	/* data len w/pkthdr */

#define	MINCLSIZE	(MHLEN + 1)	/* smallest amount to put in cluster */
#define	M_MAXCOMPRESS	(MHLEN / 2)	/* max amount to copy for compression */

/*
 * Macros for type conversion
 * mtod(m,t) -	convert mbuf pointer to data pointer of correct type
 * dtom(x) -	convert data pointer within mbuf to mbuf pointer (XXX)
 * mtocl(x) -	convert pointer within cluster to cluster index #
 * cltom(x) -	convert cluster # to ptr to beginning of cluster
 */
#define	mtod(m,t)	((t)((m)->m_data))
#define	dtom(x)		((struct mbuf *)((long)(x) & ~(MSIZE-1)))
#define	mtocl(x)	(((u_long)(x) - (u_long)mbutl) >> MCLSHIFT)
#define	cltom(x)	((caddr_t)((u_long)mbutl + ((u_long)(x) << MCLSHIFT)))

/* header at beginning of each mbuf: */
struct m_hdr {
	struct	mbuf *mh_next;		/* next buffer in chain */
	struct	mbuf *mh_nextpkt;	/* next chain in queue/record */
	caddr_t	mh_data;		/* location of data */
	u_int	mh_len;			/* amount of data in this mbuf */
	short	mh_type;		/* type of data in this mbuf */
	short	mh_flags;		/* flags; see below */
};

/* record/packet header in first mbuf of chain; valid if M_PKTHDR set */
struct	pkthdr {
	struct	ifnet *rcvif;		/* rcv interface */
	u_short	len;			/* total packet length */
	void	*tdbi;			/* pointer to struct tdb_ident */
};

/* description of external storage mapped into mbuf, valid if M_EXT set */
struct m_ext {
	caddr_t	ext_buf;		/* start of buffer */
	u_int	ext_size;		/* size of buffer */
};

struct mbuf {
	struct	m_hdr m_hdr;
	union {
		struct {
			struct	pkthdr MH_pkthdr;	/* M_PKTHDR set */
			union {
				struct	m_ext MH_ext;	/* M_EXT set */
				char	MH_databuf[MHLEN];
			} MH_dat;
		} MH;
		char	M_databuf[MLEN];		/* !M_PKTHDR, !M_EXT */
	} M_dat;
};
#define	m_next		m_hdr.mh_next
#define	m_len		m_hdr.mh_len
#define	m_data		m_hdr.mh_data
#define	m_type		m_hdr.mh_type
#define	m_flags		m_hdr.mh_flags
#define	m_nextpkt	m_hdr.mh_nextpkt
#define	m_act		m_nextpkt
#define	m_pkthdr	M_dat.MH.MH_pkthdr
#define	m_ext		M_dat.MH.MH_dat.MH_ext
#define	m_pktdat	M_dat.MH.MH_dat.MH_databuf
#define	m_dat		M_dat.M_databuf

/* mbuf flags */
#define	M_EXT		0x0001	/* has associated external storage */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */
#define	M_PROTO1	0x0008	/* protocol-specific */

/* mbuf pkthdr flags, also in m_flags */
#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */
#define M_CONF		0x0400  /* packet was encrypted (ESP-transport) */
#define M_AUTH		0x0800  /* packet was authenticated (AH) */

/* KAME IPv6 */
#define M_ANYCAST6	0x4000	/* received as IPv6 anycast */

#define M_LOOP		0x0040	/* for Mbuf statistics */

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(M_PKTHDR|M_EOR|M_PROTO1|M_BCAST|M_MCAST|M_CONF|M_AUTH|M_ANYCAST6|M_LOOP)

/* mbuf types */
#define	MT_FREE		0	/* should be on free list */
#define	MT_DATA		1	/* dynamic (data) allocation */
#define	MT_HEADER	2	/* packet header */
#define	MT_SOCKET	3	/* socket structure */
#define	MT_PCB		4	/* protocol control block */
#define	MT_RTABLE	5	/* routing tables (size <= MLEN/3) */
#define	MT_RTABLEb	6	/* routing tables (size > MLEN/3) */
#define	MT_SONAME	7	/* socket name */
#define	MT_SOOPTS	8	/* socket options */
#define	MT_FTABLE	9	/* fragment reassembly header */
#define	MT_IFADDR	10	/* interface address */
#define	MT_CONTROL	11	/* extra-data protocol message */
#define	MT_OOBDATA	12	/* expedited data  */
#define MT_MCAST	13	/* data for multacast */
#define MT_MRTABLE	14	/* multicast routing tables */
#define MT_IPQ		15	/* IP packet queue entry */
#define MT_TEMP		16	/* misc temporary data buffers */
#define	MT_PENDING	17	/* pending ether server request */
#define	MT_IP6		18	/* IPv6 mbufs */
#define	MT_IPSEC	19	/* IPsec data */
#define MT_MAX		20	/* mbuf types count for mbstat */

/* flags to m_get/MGET */
#define	M_DONTWAIT	M_NOWAIT
#define	M_WAIT		M_WAITOK

/* flags to m_clalloc */
#define	GET_MBUFS		0	/* put new mbufs on free list */
#define	GET_CLUSTERS	1	/* put new clusters on free list */


/*
 * Tag functions
 */
#define PACKET_TAG_PF_GENERATED	0x1000	//stored in m_flags

#define m_tag_prepend(m, tag)	(m)->m_flags |= tag
#define m_tag_find(m, tag)		((m)->m_flags & tag)


/*
 * mbuf utility macros:
 *
 *  MBUFALLOC(m)
 * allocate mbufs from ether_pool.
 *
 *	MBUFLOCK(code)
 * prevents a section of code from from being interrupted by network
 * drivers.
 */
#define MBUFALLOC(m) { \
	if (mfree == NULL) \
		(void)m_clalloc(1, GET_MBUFS); \
	if (((m) = mfree) != 0) { \
		MBUF_STAT(mbstat.m_mtypes[MT_FREE]--); \
		mfree = (m)->m_next; \
	} \
}

#define	MBUFLOCK(code) \
	{ int ms = splimp(); \
	  { code } \
	  splx(ms); \
	}

/*
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */
#define	MGET(m, how, type) { \
	/*MALLOC((m), struct mbuf *, MSIZE, mbtypes[type], (how))*/; \
	MBUFALLOC(m); \
	if (m) { \
		(m)->m_type = (type); \
		MBUFLOCK(MBUF_STAT(mbstat.m_mtypes[type]++);) \
		(m)->m_next = (struct mbuf *)NULL; \
		(m)->m_nextpkt = (struct mbuf *)NULL; \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
	} else \
		(m) = m_retry((how), (type)); \
}

#define	MGETHDR(m, how, type) { \
	/*MALLOC((m), struct mbuf *, MSIZE, mbtypes[type], (how))*/; \
	MBUFALLOC(m); \
	if (m) { \
		(m)->m_type = (type); \
		MBUFLOCK(MBUF_STAT(mbstat.m_mtypes[type]++);) \
		(m)->m_next = (struct mbuf *)NULL; \
		(m)->m_nextpkt = (struct mbuf *)NULL; \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
 		(m)->m_pkthdr.tdbi = NULL; \
	} else \
		(m) = m_retryhdr((how), (type)); \
}

/*
 * Mbuf cluster macros.
 * MCLALLOC(caddr_t p, int how) allocates an mbuf cluster.
 * MCLGET adds such clusters to a normal mbuf;
 * the flag M_EXT is set upon success.
 * MCLFREE releases a reference to a cluster allocated by MCLALLOC,
 * freeing the cluster if the reference count has reached 0.
 *
 * Normal mbuf clusters are normally treated as character arrays
 * after allocation, but use the first word of the buffer as a free list
 * pointer while on the free list.
 */
union mcluster {
	union	mcluster *mcl_next;
	char	mcl_buf[MCLBYTES];
};

#define	MCLALLOC(p, how) \
	MBUFLOCK( \
	  if (mclfree == 0) \
		(void)m_clalloc(1, GET_CLUSTERS); \
	  if (((p) = (caddr_t)mclfree) != 0) { \
		++mclrefcnt[mtocl(p)]; \
		MBUF_STAT(mbstat.m_clfree--); \
		mclfree = ((union mcluster *)(p))->mcl_next; \
	  } \
	)

#define	MCLGET(m, how) \
	{ /*xprintf("< %s %d", __FILE__, __LINE__);*/ \
MCLALLOC((m)->m_ext.ext_buf, (how)); \
	  if ((m)->m_ext.ext_buf != NULL) { \
		(m)->m_data = (m)->m_ext.ext_buf; \
		(m)->m_flags |= M_EXT; \
		(m)->m_ext.ext_size = MCLBYTES;  \
	  } \
	}

#define	MCLFREE(p) \
	MBUFLOCK ( \
			/*xprintf("%s %d (%x)>", __FILE__, __LINE__, p);*/ \
	  if (--mclrefcnt[mtocl(p)] == 0) { \
		((union mcluster *)(p))->mcl_next = mclfree; \
		mclfree = (union mcluster *)(p); \
		MBUF_STAT(mbstat.m_clfree++); \
	  } \
	)

/*
 * For cluster mbufs (regardless of header or not).
 */
#define MCL_ALIGN(m, len) \
	{ (m)->m_data += (MCLBYTES - (len)) &~ (sizeof(long) -1); }

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 */
#define	MFREE(m, n) \
	{ MBUFLOCK(MBUF_STAT(mbstat.m_mtypes[(m)->m_type]--);) \
	  if ((m)->m_flags & M_EXT) { \
			MCLFREE((m)->m_ext.ext_buf); \
	  } \
	  if (((m)->m_flags & M_PKTHDR) && ((m)->m_pkthdr.tdbi)) { \
		mbuf_free((m)->m_pkthdr.tdbi, M_TEMP); \
		(m)->m_pkthdr.tdbi = NULL; \
	  } \
	  (n) = (m)->m_next; \
	  /*FREE((m), mbtypes[(m)->m_type])*/; \
	  (m)->m_next = mfree; \
	  mfree = (m); \
	  MBUF_STAT(mbstat.m_mtypes[MT_FREE]++); \
	  if (mfree_pend) \
		retry_pend_rqsts(&mfree_pend); \
	}

/*
 * Copy just m_pkthdr from from to to.
 */
#define M_COPY_HDR(to, from) { \
	(to)->m_pkthdr = (from)->m_pkthdr; \
}

#ifdef IPSEC
/*
 * Duplicate just m_pkthdr from from to to.
 * XXX Deal with a generic packet attribute framework.
 * XXX When that happens, we only need one version of the macro.
 */
#define M_DUP_HDR(to, from) { \
	M_COPY_HDR((to), (from)); \
	if ((from)->m_pkthdr.tdbi) { \
		(to)->m_pkthdr.tdbi = ipsp_copy_ident((from)->m_pkthdr.tdbi); \
	} \
}
#else /* IPSEC */
#define M_DUP_HDR(to, from) { \
	M_COPY_HDR((to), (from)); \
}
#endif /* IPSEC */

/*
 * Duplicate mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */
#define M_DUP_PKTHDR(to, from) { \
	M_DUP_HDR((to), (from)); \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
	(to)->m_data = (to)->m_pktdat; \
}

/*
 * Copy mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */
#define	M_COPY_PKTHDR(to, from) { \
	M_COPY_HDR((to), (from)); \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
	(to)->m_data = (to)->m_pktdat; \
}

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the end of the mbuf, longword aligned.
 */
#define	M_ALIGN(m, len) \
	{ (m)->m_data += (MLEN - (len)) &~ (sizeof(long) - 1); }
/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) \
	{ (m)->m_data += (MHLEN - (len)) &~ (sizeof(long) - 1); }

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 */
#define	M_LEADINGSPACE(m) \
	((m)->m_flags & M_EXT ? /* (m)->m_data - (m)->m_ext.ext_buf */ 0 : \
	    (m)->m_flags & M_PKTHDR ? (m)->m_data - (m)->m_pktdat : \
	    (m)->m_data - (m)->m_dat)

/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 */
#define	M_TRAILINGSPACE(m) \
	((m)->m_flags & M_EXT ? (m)->m_ext.ext_buf + (m)->m_ext.ext_size - \
	    ((m)->m_data + (m)->m_len) : \
	    &(m)->m_dat[MLEN] - ((m)->m_data + (m)->m_len))

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */
#define	M_PREPEND(m, plen, how) { \
	if (M_LEADINGSPACE(m) >= (plen)) { \
		(m)->m_data -= (plen); \
		(m)->m_len += (plen); \
	} else \
		(m) = m_prepend((m), (plen), (how)); \
	if ((m) && (m)->m_flags & M_PKTHDR) \
		(m)->m_pkthdr.len += (plen); \
}

/* change mbuf to new type */
#define MCHTYPE(m, t) { \
	MBUFLOCK(MBUF_STAT(mbstat.m_mtypes[(m)->m_type]--); MBUF_STAT(mbstat.m_mtypes[t]++);) \
	(m)->m_type = t;\
}

/* length to m_copy to copy all */
#define	M_COPYALL	1000000000

/* compatiblity with 4.3 */
#define  m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)

/*
 * Mbuf statistics.
 */
struct mbstat {
	u_short	m_mbufs;	/* mbufs obtained from page pool */
	u_short	m_clusters;	/* clusters obtained from page pool */
	u_long	m_clfree;	/* free clusters */
	u_long	m_drain;	/* times drained protocols for space */
	u_short	m_mtypes[MT_MAX];	/* type specific mbuf allocations */
};

#ifdef	_KERNEL
extern	struct mbuf *mbutl;		/* virtual address of mclusters */
//extern	char *mclrefcnt;		/* cluster reference counts */
extern	char mclrefcnt[];		/* cluster reference counts */
extern	struct	mbstat mbstat;
extern	int nmbclusters;
extern	union	mcluster *mclfree;
extern	caddr_t	ether_pool_start;		/* start of ethernet pool */
extern	int	ether_pool_length;		/* length of ethernet pool */
extern	struct	mbuf *mfree;
extern	int	max_linkhdr;			/* largest link-level header */
extern	int	max_protohdr;			/* largest protocol header */
extern	int	max_hdr;			/* largest link+protocol header */
extern	int	max_datalen;			/* MHLEN - max_hdr */
extern	int mbtypes[];			/* XXX */
extern	int needqueuedrain;		/* True if allocation failed at */
					/* interrupt level */
extern void	*mfree_pend;			/* people wanting for buffers */

void	mbinit(caddr_t, uint);
struct	mbuf *m_copym2(struct mbuf *, int, int, int);
struct	mbuf *m_copym(struct mbuf *, int, int, int);
struct	mbuf *m_free(struct mbuf *);
struct	mbuf *m_get(int, int);
struct	mbuf *m_getclr(int, int);
struct	mbuf *m_gethdr(int, int);
struct	mbuf *m_prepend(struct mbuf *, int, int);
struct	mbuf *m_pulldown(struct mbuf *, int, int, int *);
struct	mbuf *m_pullup(struct mbuf *, int);
struct	mbuf *m_pullup2(struct mbuf *, int);
struct	mbuf *m_retry(int, int);
struct	mbuf *m_retryhdr(int, int);
struct	mbuf *m_split(struct mbuf *, int, int);
struct  mbuf *m_inject(struct mbuf *, int, int, int);
struct  mbuf *m_getptr(struct mbuf *, int, int *);
void	m_adj(struct mbuf *, int);
int	m_clalloc(int, int);
void	m_copyback(struct mbuf *, int, int, caddr_t);
void	m_freem(struct mbuf *);
void	m_reclaim(void);
void	m_copydata(struct mbuf *, int, int, caddr_t);
void	m_cat(struct mbuf *, struct mbuf *);
struct mbuf *m_devget(char *, int, int, struct ifnet *,
	    void (*)(const void *, void *, size_t));
void	m_zero(struct mbuf *);
int	m_apply(struct mbuf *, int, int,
	    int (*)(caddr_t, caddr_t, unsigned int), caddr_t);

void *mbuf_malloc (unsigned int size, int type, int flags);
void mbuf_free (void *addr, int type);

#endif /* _KERNEL */

#else	//OLD IPV4 ONLY TCP STACK

/******************************************************************************
* Name        : sys/mbuf.h
* Subsystem   : Unison TCP/IP
* Description : This is the mbuf routines required by TCPIP
* Assumptions :
*******************************************************************************
* Modification Records
*******************************************************************************
Date      Details
*******************************************************************************

*******************************************************************************/

/*
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
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
 *	@(#)mbuf.h	7.8.1.3 (Berkeley) 2/14/89
 */

#include <bits/wordsize.h>

/*
 * Constants related to memory allocator.
 */
#define	MSIZE		128			/* size of an mbuf */

#if CLBYTES > 1024
#define	MCLBYTES	1024
#define	MCLSHIFT	10
#define	MCLOFSET	(MCLBYTES - 1)
#else
#define	MCLBYTES	CLBYTES
#define	MCLSHIFT	CLSHIFT
#define	MCLOFSET	CLOFSET
#endif

#if __WORDSIZE == 16
	#define	MMINOFF		8			/* mbuf header length */
	#define	MTAIL		2
#elif __WORDSIZE == 32
	#define	MMINOFF		12			/* mbuf header length */
	#define	MTAIL		4
#else
	#error You must define the platform bits for this port!
#endif

#define	MMAXOFF		(MSIZE-MTAIL)		/* offset where data ends */
#define	MLEN		(MSIZE-MMINOFF-MTAIL)	/* mbuf data length */
#ifdef GATEWAY
#define	NMBCLUSTERS	64//512
#else
#define	NMBCLUSTERS	64//256
#endif
#define	NMBPCL		(CLBYTES/MSIZE)		/* # mbufs per cluster */

/*
 * Macros for type conversion
 */

/* network cluster number to virtual address, and back */
#define	cltom(x) ((struct mbuf *)((unsigned int)mbutl + ((x) << MCLSHIFT)))
#define	mtocl(x) (((unsigned int)x - (unsigned int)mbutl) >> MCLSHIFT)

/* address in mbuf to mbuf head */
#define	dtom(x)		((struct mbuf *)((unsigned int)x & ~(MSIZE-1)))

/* mbuf head, to typed data */
#define	mtod(x,t)	((t)((unsigned int)(x) + (x)->m_off))

struct mbuf {
	struct	mbuf *m_next;		/* next buffer in chain */
	u_int	m_off;			/* offset of data */
	short	m_len;			/* amount of data in this mbuf */
	short	m_type;			/* mbuf type (0 == free) */
	u_char	m_dat[MLEN];		/* data storage */
	struct	mbuf *m_act;		/* link in higher-level mbuf list */
};

/* mbuf types */
#define	MT_FREE		0	/* should be on free list */
#define	MT_DATA		1	/* dynamic (data) allocation */
#define	MT_HEADER	2	/* packet header */
#define	MT_SOCKET	3	/* socket structure */
#define	MT_PCB		4	/* protocol control block */
#define	MT_RTABLE	5	/* routing tables */
#define	MT_HTABLE	6	/* IMP host tables */
#define	MT_ATABLE	7	/* address resolution tables */
#define	MT_SONAME	8	/* socket name */
#define	MT_ZOMBIE	9	/* zombie proc status */
#define	MT_SOOPTS	10	/* socket options */
#define	MT_FTABLE	11	/* fragment reassembly header */
#define	MT_RIGHTS	12	/* access rights */
#define	MT_IFADDR	13	/* interface address */
#define	MT_PENDING	14	/* pending ether server request */

/* flags to m_get */
#define	M_DONTWAIT	0
#define	M_WAIT		1

/* flags to m_pgalloc */
#define	MPG_MBUFS	0		/* put new mbufs on free list */
#define	MPG_CLUSTERS	1		/* put new clusters on free list */
#define	MPG_SPACE	2		/* don't free; caller wants space */

/* length to m_copy to copy all */
#if __WORDSIZE == 16
	#define	M_COPYALL	0x7FFF
#elif __WORDSIZE == 32
	#define	M_COPYALL	1000000000
#else
	#error You must define the platform bits for this port!
#endif

/*
 * m_pullup will pull up additional length if convenient;
 * should be enough to hold headers of second-level and higher protocols.
 */
#define	MPULL_EXTRA	32

#define	MGET(m, i, t) \
	{	\
		int ms = splimp(); \
		if ((m)=mfree) \
		{	\
			if ((m)->m_type != MT_FREE) \
				panic("mget"); \
			(m)->m_type = t; \
			mbstat.m_mtypes[MT_FREE]--; \
			mbstat.m_mtypes[t]++; \
			mfree = (m)->m_next; \
			(m)->m_next = 0; \
			(m)->m_off = MMINOFF; 	\
		} \
		else \
			(m) = m_more(i, t); \
		splx(ms); 	\
	}
/*
 * Mbuf page cluster macros.
 * MCLALLOC allocates mbuf page clusters.
 * Note that it works only with a count of 1 at the moment.
 * MCLGET adds such clusters to a normal mbuf.
 * m->m_len is set to MCLBYTES upon success, and to MLEN on failure.
 * MCLFREE frees clusters allocated by MCLALLOC.
 */
#define	MCLALLOC(m, i) \
	{ int ms = splimp(); \
	  if (mclfree == 0) \
		(void)m_clalloc((i), MPG_CLUSTERS, M_DONTWAIT); \
	  if ((m)=mclfree) \
	     {++mclrefcnt[mtocl(m)];mbstat.m_clfree--;mclfree = (m)->m_next;} \
	  splx(ms); }
#define	M_HASCL(m)	((m)->m_off >= MSIZE)
#define	MTOCL(m)	((struct mbuf *)(mtod((m), int) &~ MCLOFSET))

#define	MCLGET(m) \
	{ struct mbuf *p; \
	  MCLALLOC(p, 1); \
	  if (p) { \
		(m)->m_off = (int)p - (int)(m); \
		(m)->m_len = MCLBYTES; \
	  } else \
		(m)->m_len = MLEN; \
	}
#define	MCLFREE(m) { \
	if (--mclrefcnt[mtocl(m)] == 0) \
	    { (m)->m_next = mclfree;mclfree = (m);mbstat.m_clfree++;} \
	}
/*
 *	MODIFIED so that using mfree_pend request queue, TOM WILSON
 */
#define	MFREE(m, n) 	\
{	\
	int ms = splimp(); 	\
	if ((m)->m_type == MT_FREE) 	\
		panic("mfree"); 	\
	mbstat.m_mtypes[(m)->m_type]--; 	\
	mbstat.m_mtypes[MT_FREE]++; 	\
	(m)->m_type = MT_FREE; 	\
	if (M_HASCL(m)) 	\
	{ 	\
		(n) = MTOCL(m); 	\
		MCLFREE(n); 	\
	} 	\
	(n) = (m)->m_next; 	\
	(m)->m_next = mfree; 	\
	(m)->m_off = 0; 	\
	(m)->m_act = 0; 	\
	mfree = (m); 	\
	if (mfree_pend /*m_want*/) 	\
	{ 	\
		m_want = 0; 	\
		/*wakeup((caddr_t)&mfree);*/ 	\
		retry_pend_rqsts(&mfree_pend); 	\
	} 	\
	splx(ms); 	\
}

/*
 * Mbuf statistics.
 */
struct mbstat {
	u_long	m_mbufs;	/* mbufs obtained from page pool */
	u_long	m_clusters;	/* clusters obtained from page pool */
	u_long	m_space;	/* interface pages obtained from page pool */
	u_long	m_clfree;	/* free clusters */
	u_long	m_drops;	/* times failed to find space */
	u_long	m_wait;		/* times waited for space */
	u_long	m_drain;	/* times drained protocols for space */
	u_short	m_mtypes[256];	/* type specific mbuf allocations */
};

#ifdef KERNEL
extern caddr_t	ether_pool_start;		/* start of ethernet pool */
extern int	ether_pool_length;		/* length of ethernet pool */
extern	struct mbuf *mbutl;		/* virtual address of net free mem */
extern struct	mbstat mbstat;
extern int	nmbclusters;
extern struct	mbuf *mfree, *mclfree;
extern char	mclrefcnt[NMBCLUSTERS + 1];
extern int	m_want;
extern void	*mfree_pend;			/* people wanting for buffers */
struct	mbuf *m_get(),*m_getclr(),*m_free(),*m_more(),*m_copy(),*m_pullup();
//caddr_t	m_clalloc();
caddr_t	m_clalloc(int, int, int);
#endif

#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _SYS_MBUF_H_ */
