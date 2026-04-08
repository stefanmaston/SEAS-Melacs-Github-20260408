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
* Name        : tcpinit.h
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

#ifndef __tcpinit_h__
#define	__tcpinit_h__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	USE_DUAL_TCP_STACK

// Ethernet settings
struct eth_settings {
	uint_8			macaddr[6];			/* ethernet MAC */
};

// IEEE 802.15.4 settings
struct ieee802154_settings {
	uint_16			PANid;				/* PAN id           */
	uint_16			shortAddr;			/* short MAC        */
	uint_8			longAddr[8];		/* long MAC         */
//	char			*netPrefix;			/* IPv6 net prefix  */
//	uint_8			netPrefixLen;		/* prefix length    */
	uint_8			channel;			/* work channel     */
	uint_8			power;				/* transiever power */
};


struct IP_settings {
	char			*IP_address;		/* internet address */
	union {
		char		*IP_mask;			/* IPv4 mask        */
		int			IP_prefix;			/* IPv6 pefix       */
	};
};

/*
 * The following structure is passed to the tcp server during creation.
 */
struct tcpinit {
	uint_8			dev_type;				/* device type      */
	uint_8			dev_unit;				/* device number    */
	int				dev_addr;				/* device address   */
	int				dev_vector;				/* device vector    */
	int				dev_level;				/* device int level */
	uint_8			dev_rx_buf_cnt;			/* amount of RX buffers in driver*/
	uint_8			dev_tx_buf_cnt;			/* amount of TX buffers in driver*/
	union {
		struct eth_settings eth;
		struct ieee802154_settings ieee802154;
	} dev;
	
	char *			tcp_pool_start;			/* buffer address   */
	uint			tcp_pool_size;			/* buffer size      */

	struct IP_settings IPv4;				/* IPv4 settings         */
	char *IPv4_default_gateway;				/* IPv4 default gateway  */
	struct IP_settings IPv6;				/* IPv6 settings         */
	char *IPv6_default_gateway;				/* IPv6 default gateway  */
};

#define eth_mac		dev.eth.macaddr

#define wpan_PANid			dev.ieee802154.PANid
#define wpan_shortAddr		dev.ieee802154.shortAddr
#define wpan_longAddr		dev.ieee802154.longAddr
#define wpan_channel		dev.ieee802154.channel
#define wpan_power			dev.ieee802154.power


/*
 * Devices types
 */
#define DEV_ETHERNET		0	// Ethernet
#define DEV_IEEE802154		1	// IEEE 802.15.4
#define DEV_IEEE80211		2	// IEEE 802.11

/*
 * Devices names
 */
#define NAME_ETHERNET		"eth"
#define NAME_IEEE802154		"wpan"
#define NAME_IEEE80211		"wifi"


int tcpd(struct tcpinit *);
void tftpd_main(char *msg, uint_32 arg);
THREAD telnetd(int(*shell)(void), int ip_ver);
int get_autoip(unsigned char *mac, char *if_name);

#else	//OLD IPV4 ONLY TCP STACK

/*
 * The following structure is passed to the tcp server during creation.
 *
 * The devname field specifies the interface name.  ie "le", "sonic"
 */
struct tcpinit {
	uint_16			tcp_msgsize;			/* size of message  */
	uint_32			tcp_default_gateway;	/* default gateway  */
	int				tcp_devport;			/* device address   */
	int				tcp_vector;				/* device vector    */
	uint_32			tcp_IP_address;			/* internet address */
	unsigned char	tcp_ether_address[6];	/* ethernet address */
	unsigned char	tcp_padding[2];			/* padding          */
	int				tcp_level;				/* device int level */
	int				tcp_unit;				/* unit number      */
	char *			tcp_pool_start;			/* buffer address   */
	uint			tcp_pool_size;			/* buffer size      */
	char			tcp_devname[8];			/* device name      */
};

THREAD tcpd(struct tcpinit *init);
void tftpd_main(char *msg, uint_32 arg);
void telnetd(int(*shell)(void));
int get_autoip(struct tcpinit *etherinit);

#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif
