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

#ifndef _NETDB_H_
#define _NETDB_H_

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */

#define	NETDB_INTERNAL	-1	/* see errno */
#define	NETDB_SUCCESS	0	/* no problem */
#define	HOST_NOT_FOUND	1 /* Authoritative Answer Host not found */
#define	TRY_AGAIN	2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define	NO_RECOVERY	3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define	NO_DATA		4 /* Valid name, no data record of requested type */
#define	NO_ADDRESS	NO_DATA		/* no address, look for MX record */

/* Values for getaddrinfo() and getnameinfo() */
#define AI_PASSIVE	1	/* socket address is intended for bind() */
#define AI_CANONNAME	2	/* request for canonical name */
#define AI_NUMERICHOST	4	/* don't ever try hostname lookup */
#define AI_EXT		8	/* enable non-portable extensions */
#define AI_NUMERICSERV	16	/* don't ever try servname lookup */
/* valid flags for addrinfo */
#define AI_MASK \
    (AI_PASSIVE | AI_CANONNAME | AI_NUMERICHOST | AI_NUMERICSERV)

#define NI_NUMERICHOST	1	/* return the host address, not the name */
#define NI_NUMERICSERV	2	/* return the service address, not the name */
#define NI_NOFQDN	4	/* return a short name if in the local domain */
#define NI_NAMEREQD	8	/* fail if either host or service name is unknown */
#define NI_DGRAM	16	/* look up datagram service instead of stream */

#define NI_MAXHOST	MAXHOSTNAMELEN	/* max host name returned by getnameinfo */
#define NI_MAXSERV	32	/* max serv. name length returned by getnameinfo */

/*
 * Scope delimit character (KAME hack)
 */
#define SCOPE_DELIMITER '%'

#define EAI_BADFLAGS	-1	/* invalid value for ai_flags */
#define EAI_NONAME	-2	/* name or service is not known */
#define EAI_AGAIN	-3	/* temporary failure in name resolution */
#define EAI_FAIL	-4	/* non-recoverable failure in name resolution */
#define EAI_NODATA	-5	/* no address associated with name */
#define EAI_FAMILY	-6	/* ai_family not supported */
#define EAI_SOCKTYPE	-7	/* ai_socktype not supported */
#define EAI_SERVICE	-8	/* service not supported for ai_socktype */
#define EAI_ADDRFAMILY	-9	/* address family for name not supported */
#define EAI_MEMORY	-10	/* memory allocation failure */
#define EAI_SYSTEM	-11	/* system error (code indicated in errno) */
#define EAI_BADHINTS	-12	/* invalid value for hints */
#define EAI_PROTOCOL	-13	/* resolved protocol is unknown */

struct addrinfo {
	int ai_flags;		/* input flags */
	int ai_family;		/* protocol family for socket */
	int ai_socktype;	/* socket type */
	int ai_protocol;	/* protocol for socket */
	socklen_t ai_addrlen;	/* length of socket-address */
	struct sockaddr *ai_addr; /* socket-address for socket */
	char *ai_canonname;	/* canonical name for service location (iff req) */
	struct addrinfo *ai_next; /* pointer to next in list */
};

/*
 * Flags for getrrsetbyname()
 */
#define RRSET_VALIDATED		1

/*
 * Return codes for getrrsetbyname()
 */
#define ERRSET_SUCCESS		0
#define ERRSET_NOMEMORY		1
#define ERRSET_FAIL		2
#define ERRSET_INVAL		3
#define ERRSET_NONAME		4
#define ERRSET_NODATA		5



int		getaddrinfo(const char *, const char *,
		    const struct addrinfo *, struct addrinfo **);
void		freeaddrinfo(struct addrinfo *);
int getnameinfo(const struct sockaddr *sa, socklen_t salen,
                char *host, size_t hostlen,
                char *serv, size_t servlen, int flags);

int set_dns_server_address(char* ipv4_addr, char*ipv6_addr, char *mac);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* !_NETDB_H_ */
