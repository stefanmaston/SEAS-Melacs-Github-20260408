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

/*	$NetBSD: ip_compat.h,v 1.9.2.2 1997/11/17 16:32:43 mrg Exp $	*/

/*
 * Copyright (C) 1993-1997 by Darren Reed.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that this notice is preserved and due credit is given
 * to the original author and the contributors.
 *
 * @(#)ip_compat.h	1.8 1/14/96
 * Id: ip_compat.h,v 2.0.2.31.2.4 1997/11/12 10:48:43 darrenr Exp
 */

#ifndef	__IP_COMPAT_H__
#define	__IP_COMPAT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define	IFNAMSIZ	16

#if defined(_KERNEL) && !defined(KERNEL)
# define	KERNEL
#endif
#if defined(KERNEL) && !defined(_KERNEL)
# define	_KERNEL
#endif
#if!defined(__KERNEL__) && defined(KERNEL)
# define 	__KERNEL__
#endif

#ifndef	USE_DUAL_TCP_STACK
#  define	bzero(a,b)	memset(a,0,b)
#  define	bcmp		memcmp
#  define	bcopy(a,b,c)	memmove(b,a,c)
#endif	//USE_DUAL_TCP_STACK

#define IPL_PRFX ipl
#define IPL_EXTERN(ep) ipl##ep

#define	IPMINLEN(i, h)	((i)->ip_len >= ((i)->ip_hl * 4 + sizeof(struct h)))

#ifndef	IP_OFFMASK
#define	IP_OFFMASK	0x1fff
#endif

#ifndef	USE_DUAL_TCP_STACK
#if	BSD > 199306
# define	USE_QUAD_T
# define	U_QUAD_T	u_quad_t
# define	QUAD_T		quad_t
#else /* BSD > 199306 */
# define	U_QUAD_T	u_long
# define	QUAD_T		long
#endif /* BSD > 199306 */

#ifndef	MAX
#define	MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#endif	//USE_DUAL_TCP_STACK

/*
 * Really, any arch where sizeof(long) != sizeof(int).
 */

typedef unsigned long   u_32_t;


/*
 * Security Options for Intenet Protocol (IPSO) as defined in RFC 1108.
 *
 * Basic Option
 *
 * 00000001   -   (Reserved 4)
 * 00111101   -   Top Secret
 * 01011010   -   Secret
 * 10010110   -   Confidential
 * 01100110   -   (Reserved 3)
 * 11001100   -   (Reserved 2)
 * 10101011   -   Unclassified
 * 11110001   -   (Reserved 1)
 */
#define	IPSO_CLASS_RES4		0x01
#define	IPSO_CLASS_TOPS		0x3d
#define	IPSO_CLASS_SECR		0x5a
#define	IPSO_CLASS_CONF		0x96
#define	IPSO_CLASS_RES3		0x66
#define	IPSO_CLASS_RES2		0xcc
#define	IPSO_CLASS_UNCL		0xab
#define	IPSO_CLASS_RES1		0xf1

#define	IPSO_AUTH_GENSER	0x80
#define	IPSO_AUTH_ESI		0x40
#define	IPSO_AUTH_SCI		0x20
#define	IPSO_AUTH_NSA		0x10
#define	IPSO_AUTH_DOE		0x08
#define	IPSO_AUTH_UN		0x06
#define	IPSO_AUTH_FTE		0x01

/*
 * IP option #defines
 */
/*#define	IPOPT_RR	7 */
#define	IPOPT_ZSU	10	/* ZSU */
#define	IPOPT_MTUP	11	/* MTUP */
#define	IPOPT_MTUR	12	/* MTUR */
#define	IPOPT_ENCODE	15	/* ENCODE */
/*#define	IPOPT_TS	68 */
#define	IPOPT_TR	82	/* TR */
/*#define	IPOPT_SECURITY	130 */
/*#define	IPOPT_LSRR	131 */
#define	IPOPT_E_SEC	133	/* E-SEC */
#define	IPOPT_CIPSO	134	/* CIPSO */
/*#define	IPOPT_SATID	136 */
#ifndef	IPOPT_SID
# define	IPOPT_SID	IPOPT_SATID
#endif
/*#define	IPOPT_SSRR	137 */
#define	IPOPT_ADDEXT	147	/* ADDEXT */
#define	IPOPT_VISA	142	/* VISA */
#define	IPOPT_IMITD	144	/* IMITD */
#define	IPOPT_EIP	145	/* EIP */
#define	IPOPT_FINN	205	/* FINN */


/*
 * Build some macros and #defines to enable the same code to compile anywhere
 * Well, that's the idea, anyway :-)
 */
#ifdef KERNEL

# define	MUTEX_ENTER(x)	;
# define	MUTEX_EXIT(x)	;
# define	FREE_MB_T(m)	m_freem(m)
# define	MTOD(m,t)	mtod(m,t)
# define	IRCOPY(a,b,c)	bcopy((a), (b), (c))
# define	IWCOPY(a,b,c)	bcopy((a), (b), (c))
# define	KMALLOC(a,b,c)	(a) = (b)malloc(c)
# define	KFREE(x)	free(x)

/*
 * file flags.
 */
# define	FWRITE	WRITE
# define	FREAD	READ

# define	GETUNIT(n)	ifunit((n))
# ifndef	GET_MINOR
#  define	GET_MINOR(x)	minor(x)
# endif
# define	SPL_IMP(x)	x = splimp()
# define	SPL_NET(x)	x = splnet()
# define	SPL_X(x)	(void) splx(x)
# define	PANIC(x,y)	if (x) panic y
#else /* KERNEL */

# define	SLEEP(x,y)	;
# define	WAKEUP(x)	;
# define	PANIC(x,y)	;
# define	MUTEX_ENTER(x)	;
# define	MUTEX_EXIT(x)	;
# define	SPL_NET(x)	;
# define	SPL_IMP(x)	;
# undef		SPL_X
# define	SPL_X(x)	;
# define	KMALLOC(a,b,c)	(a) = (b)malloc(c)
# define	KFREE(x)	free(x)
# define	KFREES(x,s)	free(x)
# define	GETUNIT(x)	get_unit(x)
# define	IRCOPY(a,b,c)	bcopy((a), (b), (c))
# define	IWCOPY(a,b,c)	bcopy((a), (b), (c))
#endif /* KERNEL */


typedef struct mbuf mb_t;

typedef	struct	tcphdr	tcphdr_t;
typedef	struct	udphdr	udphdr_t;
typedef	struct	icmp	icmphdr_t;
typedef	struct	ip	ip_t;
typedef	struct	ether_header	ether_header_t;


#ifndef	ICMP_ROUTERADVERT
# define	ICMP_ROUTERADVERT	9
#endif
#ifndef	ICMP_ROUTERSOLICIT
# define	ICMP_ROUTERSOLICIT	10
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	/* __IP_COMPAT_H__ */
