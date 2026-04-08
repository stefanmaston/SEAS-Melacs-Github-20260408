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

#ifndef _DHCP_H_
#define _DHCP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************
 * Constant data
 *******************************************************************/
#define MAX_NUM_RETRY                   5
#define MAX_TRY_TIME                    60
#define DHCP_MAX_PKT_LEN                576			//per RFC2131

#define DHCP_CLIENT_PORT                68
#define DHCP_SERVER_PORT                67

// DHCP Message Field Values
#define BOOT_REQUEST                    1
#define BOOT_REPLY                      2
#define HW_TYPE                         1
#define LEN_OF_HW_TYPE                  6

// DHCP Message Option Values
#define DHCP_SUBNET_MASK                1
#define DHCP_PARAM_IPv4_ADDRESS_LEN     4
#define DHCP_ROUTER                     3
#define DHCP_DNS_OPTION                 6

#define DHCP_PARAM_REQUEST_IP_ADDRESS   50

#define DHCP_PARAM_IP_LEASE_TIME        51
#define DHCP_PARAM_IP_LEASE_TIME_LEN    4

#define DHCP_MESSAGE_TYPE               53
#define DHCP_MESSAGE_TYPE_LEN           1

#define DHCP_UNKNOWN_MESSAGE            0
#define DHCP_DISCOVER_MESSAGE           1
#define DHCP_OFFER_MESSAGE              2
#define DHCP_REQUEST_MESSAGE            3
#define DHCP_DECLINE_MESSAGE            4
#define DHCP_ACK_MESSAGE                5
#define DHCP_NAK_MESSAGE                6
#define DHCP_RELEASE_MESSAGE            7
#define DHCP_SERVER_IDENTIFIER          54
#define DHCP_PARAM_REQUEST_LIST         55
#define DHCP_PARAM_REQUEST_LIST_LEN     2

#define DHCP_END_OPTION                 255

#define DHCP_OPT_PAD                    0


#define DHCP_MAGIC_COOKIE               99


/*******************************************************************/
/*     DHCP Message Type                                           */
/*******************************************************************/
/*  message types       Value  */
#define DHCPDISCOVER      1
#define DHCPOFFER         2
#define DHCPREQUEST       3
#define DHCPDECLINE       4
#define DHCPACK           5
#define DHCPNAK           6
#define DHCPRELEASE       7
#define DHCPINFORM        8
/******************************************************************
    Code   Len  Type
    +-----+-----+-----+
    |  53 |  1  | 1-9 |
    +-----+-----+-----+
*******************************************************************/


typedef struct _DHCP_MSG_HEADER
{
    uchar    	Op;
    uchar    	Htype;
    uchar    	Hlen;
    uchar    	Hops;
    ushort    	Xid[2];
    ushort    	Secs;
    ushort	Flags;
    in_addr_t 	Ciaddr;
    in_addr_t 	Yiaddr;
    in_addr_t 	Siaddr;
    in_addr_t 	Giaddr;
    uchar    	Chaddr[16];
    uchar    	Sname[64];
    uchar    	file[128];
} DHCP_MSG_HEADER;


// Full dhcp packet
typedef struct _DHCP_PACKET
{
	DHCP_MSG_HEADER	dhcpHeader;
	uchar	dhcpOptions[DHCP_MAX_PKT_LEN];
} DHCP_PACKET;


// Minimum dhcp packet (6 fields)
typedef struct _DHCP_PACKET_MIN
{
	DHCP_MSG_HEADER	dhcpHeader;
	uchar	dhcpOptions[44]; 		//[Cookie +  Msg Type +  Field*6 + End]
} DHCP_PACKET_MIN;


typedef enum _SM_DHCP
{
	SM_DHCP_INIT,
	SM_DHCP_RESET_WAIT,
	SM_DHCP_DISCOVER,
	SM_DHCP_SELECTING,
	SM_DHCP_REQUESTING,
	SM_DHCP_PREBOUND,
	SM_DHCP_BOUND,
	SM_DHCP_RENEW,
	SM_DHCP_REBIND,
	SM_DHCP_DISABLED,
	SM_DHCP_ABORTED
} SM_DHCP;


typedef  struct  _DHCP_OPTION
{
    in_addr_t	ip_router;
    in_addr_t	ip_subnet_mask;
    in_addr_t	ip_start;
    in_addr_t	ip_end;
    in_addr_t	ip_dns1;
    in_addr_t	ip_dns2;
}DHCP_SETUP;

typedef	struct
{
    in_addr_t	ip_target;
    in_addr_t	ip_router;
    in_addr_t	ip_subnet_mask;
    in_addr_t	ip_dns1;
    in_addr_t	ip_dns2;
}_dhcp_params;


#ifdef	USE_DUAL_TCP_STACK
int dhcpd_v4(char *serv_addr, DHCP_SETUP *dhcp_setup);
int dhcp_get_params (unsigned char *mac, char *if_name, _dhcp_params * param);
#else
int dhcp_get_params(struct tcpinit *init, _dhcp_params * param);
#endif	//USE_DUAL_TCP_STACK

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	/* _DHCP_H_ */
