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


/******************************************************************************
* Name        : tcpinitN.h
* Subsystem   : TCP
* Description : TCP/IP initialization message for server
* Assumptions : 
*               
*******************************************************************************
* Modification Records
*******************************************************************************
Date      Details
*******************************************************************************

******************************************************************************/

#ifndef __tcpinitN_h__
#define	__tcpinitN_h__

#include <tcpinit.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK

/*
 * The following structure defines the device interface.
 */
struct tcpif {
	uint_8			dev_type;				/* device type         */
	uint_8			dev_unit;				/* device number       */
	int				dev_addr;				/* device address      */
	int				dev_vector;				/* device vector       */
	int				dev_level;				/* device int level    */
	uint_8			dev_rx_buf_cnt;			/* amount of RX buffers in driver*/
	uint_8			dev_tx_buf_cnt;			/* amount of TX buffers in driver*/	

	union {
		struct eth_settings eth;
		struct ieee802154_settings ieee802154;
	} dev;

	struct IP_settings IPv4;				/* IPv4 settings       */
	struct IP_settings IPv6;				/* IPv6 settings       */

	uint_8			drv_number;				/* driver number       */
	void			*(*if_attach)();		/* attach function     */
	void			(*if_intr)();			/* interrupt function  */
};


/*
 * The following structure is passed to the tcp server during creation.
 */
struct tcpinitN {
	char			*tcp_pool_start;		/* buffer address   */
	uint			tcp_pool_size;			/* buffer size      */

	uint_8			tcp_nif;				/* number of ifs    */
	struct tcpif	*tcp_if;				/* array of ifs     */

	char *IPv4_default_gateway;				/* IPv4 default gateway  */
	char *IPv6_default_gateway;				/* IPv6 default gateway  */
};

int tcpdN(struct tcpinitN *);
#else	//OLD IPV4 ONLY TCP STACK

/*
 * The following structure defines the device interface.
 */
struct tcpif {
	char			tcp_devname[8];			/* device name      */
	int				tcp_devport;			/* device address   */
	int				tcp_vector;				/* device vector    */
	uint_32			tcp_IP_address;			/* internet address */
	unsigned char	tcp_ether_address[6];	/* ethernet address */
	unsigned char	tcp_padding[2];			/* padding          */
	int				tcp_level;				/* device int level */
};

/*
 * The following structure is passed to the tcp server during creation.
 */
struct tcpinitN {
	uint_16         tcp_msgsize;         /* size of message      */
	uint_32			tcp_default_gateway; /* default gateway      */
	uint_16         tcp_nif;             /* number of interfaces */
	char *          tcp_pool_start;      /* buffer address       */
	uint_32         tcp_pool_size;       /* buffer size          */
#define NIF 2
	struct tcpif    tcp_if[NIF];         /* number of units      */
};

/* structure used to hold initialization and interrupt routines of
 * different ifterfaces .
 */
struct iftable {
    uint_16 devunit;	
	void (*if_attach) ();
	void (*if_intr)   ();
};

THREAD tcpdN(struct tcpinitN *);
#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
