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
#ifndef _NETINET_PPP_H_
#define _NETINET_PPP_H_

#include <sys/socket.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXNAMELEN                      128     /* max length of hostname or name for auth */
#define MAXSECRETLEN                    128     /* max length of password or secret */



/*************************
*** PUBLIC DEFINITIONS ***
*************************/

/* Error codes. */
#define PPPERR_NONE 0				/* No error. */
#define PPPERR_PARAM -1				/* Invalid parameter. */
#define PPPERR_OPEN -2				/* Unable to open PPP session. */
#define PPPERR_DEVICE -3			/* Invalid I/O device for PPP. */
#define PPPERR_ALLOC -4				/* Unable to allocate resources. */
#define PPPERR_USER -5				/* User interrupt. */
#define PPPERR_CONNECT -6			/* Connection lost. */
#define PPPERR_AUTHFAIL -7			/* Failed authentication challenge. */
#define PPPERR_PROTOCOL -8			/* Failed to meet protocol. */

/* Flow control codes */
#define FLCTL_NONE		0
#define FLCTL_XONXOFF	1
#define FLCTL_CRTSCTS	2

/*
 * PPP IOCTL commands.
 */
/*
 * Get the up status - 0 for down, non-zero for up.  The argument must
 * point to an int.
 */
#define PPPCTLG_UPSTATUS 100	/* Get the up status - 0 down else up */
#define PPPCTLS_ERRCODE 101		/* Set the error code */
#define PPPCTLG_ERRCODE 102		/* Get the error code */
#define	PPPCTLG_FD		103		/* Get the fd associated with the ppp */
#define	PPPCTLG_STATS	104		/* Get the ppp statistics */

/************************
*** PUBLIC DATA TYPES ***
************************/
struct ppp_settings {
	u_int  disable_defaultip : 1;   /* Don't use hostname for default IP addrs */
	u_int  auth_required : 1;      /* Peer is required to authenticate */
	u_int  explicit_remote : 1;    /* remote_name specified with remotename opt */
	u_int  refuse_pap : 1;         /* Don't wanna auth. ourselves with PAP */
	u_int  refuse_chap : 1;        /* Don't wanna auth. ourselves with CHAP */
	u_int  usehostname : 1;        /* Use hostname for our_name */
	u_int  usepeerdns : 1;         /* Ask peer for DNS adds */

	u_short idle_time_limit; /* Shut down link if idle for this long */
	int  maxconnect;         /* Maximum connect time (seconds) */
	char flow_ctl;           /* Flow control mode */

	char user[MAXNAMELEN + 1];/* Username for PAP */
	char passwd[MAXSECRETLEN + 1];           /* Password for PAP, secret for CHAP */
	char our_name[MAXNAMELEN + 1];         /* Our name for authentication purposes */
	char remote_name[MAXNAMELEN + 1];      /* Peer's name for authentication */
};

struct ppp_addrs {
    struct in_addr our_ipaddr, his_ipaddr, netmask, dns1, dns2;
};

/*
 * Structure for pppd statistics.
 */
struct pppd_stats {
    unsigned long	pkts_in;
    unsigned long	pkts_out;
    unsigned long	pkts_drop;
    unsigned long	pkts_lenerr;
    unsigned long	pkts_chkerr;
};

/*****************************
*** PUBLIC DATA STRUCTURES ***
*****************************/
extern struct ppp_settings ppp_settings;

/***********************
*** PUBLIC FUNCTIONS ***
***********************/

/* Initialize the PPP subsystem. */
void pppInit(void);

/* Warning: Using PPPAUTHTYPE_ANY might have security consequences.
 * RFC 1994 says:
 *
 * In practice, within or associated with each PPP server, there is a
 * database which associates "user" names with authentication
 * information ("secrets").  It is not anticipated that a particular
 * named user would be authenticated by multiple methods.  This would
 * make the user vulnerable to attacks which negotiate the least secure
 * method from among a set (such as PAP rather than CHAP).  If the same
 * secret was used, PAP would reveal the secret to be used later with
 * CHAP.
 *
 * Instead, for each user name there should be an indication of exactly
 * one method used to authenticate that user name.  If a user needs to
 * make use of different authentication methods under different
 * circumstances, then distinct user names SHOULD be employed, each of
 * which identifies exactly one authentication method.
 *
 */
enum pppAuthType {
    PPPAUTHTYPE_NONE,
    PPPAUTHTYPE_ANY,
    PPPAUTHTYPE_PAP,
    PPPAUTHTYPE_CHAP
};

void pppSetAuth(enum pppAuthType authType, const char *user, const char *passwd);

/*
 * Open a new PPP connection using the given I/O device.
 * This initializes the PPP control block but does not
 * attempt to negotiate the LCP session.
 * Return a new PPP connection descriptor on success or
 * an error code (negative) on failure.
 */
int pppOpen(char *tty_name, int prio, void (*linkStatusCB)(void *ctx, int errCode, void *arg), void *linkStatusCtx);

/*
 * Close a PPP connection and release the descriptor.
 * Any outstanding packets in the queues are dropped.
 * Return 0 on success, an error code on failure.
 */
int pppClose(int pd);

/*
 * Indicate to the PPP process that the line has disconnected.
 */
void pppSigHUP(int pd);

/*
 * Get and set parameters for the given connection.
 * Return 0 on success, an error code on failure.
 */
int  pppIOCtl(int pd, int cmd, void *arg);

/*
 * Return the Maximum Transmission Unit for the given PPP connection.
 */
u_int pppMTU(int pd);

/*
 * Get all IP addresses for PPP connection
 */
struct ppp_addrs *pppGetIP(int pd);

/*
 * Set default IP addresses for PPP server
 */
void pppSetServerDefaultIP(uint_32 ip);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif //_NETINET_PPP_H_
