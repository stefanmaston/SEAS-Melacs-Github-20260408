/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2011 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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

/*
 * "Copyright (c) 2008,2010 The Regents of the University  of California.
 * All rights reserved."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 */


#ifndef _NETINET_6LOWPAN_H_
#define _NETINET_6LOWPAN_H_

#include <stdint.h>
#include <netinet/ieee802154.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * For header options processing
 */
struct tlv_hdr
{
	u_int8_t type;
	u_int8_t len;
};

/*
 * For UDP packet size calculation
 */
struct udp_calc
{
	u_int8_t *data_ptr;
	u_int16_t *len_ptr;
};

/*
 * lengths of different lowpan headers
 */
enum {
  LOWMSG_MESH_LEN = 5,
  LOWMSG_BCAST_LEN = 2,
  LOWMSG_FRAG1_LEN = 4,
  LOWMSG_FRAGN_LEN = 5,
};

enum {
  INET_MTU = 1280,
  LIB6LOWPAN_MAX_LEN = 100,
  LOWPAN_LINK_MTU = 109,
  /*
   * The time, in binary milliseconds, after which we stop waiting for
   * fragments and report a failed receive.  We 
   */
  FRAG_EXPIRE_TIME = 4096,
};

/*
 * magic numbers from rfc4944; some of them shifted: mostly dispatch values.
 */
enum {
  LOWPAN_NALP_PATTERN = 0x0,
  LOWPAN_MESH_PATTERN = 0x2,
  LOWPAN_FRAG1_PATTERN = 0x18,
  LOWPAN_FRAGN_PATTERN = 0x1c,
  LOWPAN_BCAST_PATTERN = 0x50,
  LOWPAN_IPV6_PATTERN = 0x41,
};

enum {
  LOWPAN_MESH_V_MASK = 0x20,
  LOWPAN_MESH_F_MASK = 0x10,
  LOWPAN_MESH_HOPS_MASK = 0x0f,
};

/* 
 * values for LOWPAN_IPHC from draft-ietf-6lowpan-hc-06
 */
enum {
  LOWPAN_DISPATCH_BYTE_MASK = 0xe0,
  LOWPAN_DISPATCH_BYTE_VAL  = 0x60,

  LOWPAN_IPHC_TF_MASK = 0x18,
  LOWPAN_IPHC_TF_NONE = 0x18,
  LOWPAN_IPHC_TF_ECN_DSCP = 0x10,
  LOWPAN_IPHC_TF_ECN_FL   = 0x08,
  LOWPAN_IPHC_TF_ECN_DSCP_FL = 0x00,

  LOWPAN_IPHC_NH_MASK = 0x04,
  LOWPAN_IPHC_NH_INLINE = 0,

  LOWPAN_IPHC_HLIM_MASK = 0x03,
  LOWPAN_IPHC_HLIM_NONE = 0x00,
  LOWPAN_IPHC_HLIM_1  = 0x01,
  LOWPAN_IPHC_HLIM_64 = 0x02,
  LOWPAN_IPHC_HLIM_255 = 0x03,

  LOWPAN_IPHC_CID_MASK = 0x80,
  LOWPAN_IPHC_CID_PRESENT = 0x80,

  LOWPAN_IPHC_SAM_SHIFT = 4,
  LOWPAN_IPHC_M = 0x08,
  LOWPAN_IPHC_DAM_SHIFT = 0,

  LOWPAN_IPHC_AC_CONTEXT = 0x04,
  LOWPAN_IPHC_AM_MASK = 0x3,
  LOWPAN_IPHC_AM_128 = 0x0,
  LOWPAN_IPHC_AM_64  = 0x1,
  LOWPAN_IPHC_AM_16  = 0x2,
  LOWPAN_IPHC_AM_0   = 0x3,

  LOWPAN_IPHC_AM_M     = 0x08,
  LOWPAN_IPHC_AM_M_128 = 0x0,
  LOWPAN_IPHC_AM_M_48  = 0x1,
  LOWPAN_IPHC_AM_M_32  = 0x2,
  LOWPAN_IPHC_AM_M_8   = 0x3,
};

/* 
 * values for LOWPAN_IPNH from draft-ietf-6lowpan-hc-06
 */
enum {
  LOWPAN_NHC_IPV6_MASK    = 0xf0,
  LOWPAN_NHC_IPV6_PATTERN = 0xe0,

  LOWPAN_NHC_EID_SHIFT  = 0x1,
  LOWPAN_NHC_EID_MASK   = 0xe,
  LOWPAN_NHC_EID_HOP     = 0x0 << LOWPAN_NHC_EID_SHIFT,
  LOWPAN_NHC_EID_ROUTING = 0x1 << LOWPAN_NHC_EID_SHIFT,
  LOWPAN_NHC_EID_FRAG    = 0x2 << LOWPAN_NHC_EID_SHIFT,
  LOWPAN_NHC_EID_DEST    = 0x3 << LOWPAN_NHC_EID_SHIFT,
  LOWPAN_NHC_EID_MOBILE  = 0x4 << LOWPAN_NHC_EID_SHIFT,
  LOWPAN_NHC_EID_IPV6    = 0x7 << LOWPAN_NHC_EID_SHIFT,

  LOWPAN_NHC_NH          = 0x1,

  LOWPAN_NHC_UDP_MASK    = 0xf8,
  LOWPAN_NHC_UDP_PATTERN = 0xf0,

  LOWPAN_NHC_UDP_CKSUM      = 0x4,

  LOWPAN_NHC_UDP_PORT_MASK  = 0x3,
  LOWPAN_NHC_UDP_PORT_FULL  = 0x0,
  LOWPAN_NHC_UDP_PORT_SRC_FULL = 0x1,
  LOWPAN_NHC_UDP_PORT_DST_FULL = 0x2,
  LOWPAN_NHC_UDP_PORT_SHORT = 0x3,
};





#define LOWPAN_MTU 1280
#define LINK_DATA_MTU 100
// 802.15.4 space left after the 802.15.4 header: 128 - xx = 102 bytes max



/* Normal dispatch */
#define DISPATCH_NORMAL 0x40
#define DISPATCH_UNCOMPRESSED_IPV6 0x41
#define DISPATCH_COMPRESSED_IPV6 0x42

#define DISPATCH_BC0 0x50

/* Mesh header */
#define DISPATCH_MESH 0x80
#define DISPATCH_MESH_MASK 0xC0
#define DISPATCH_MESH_O_FLAG 0x20
#define DISPATCH_MESH_F_FLAG 0x10
#define DISPATCH_MESH_HOPSLEFT_MASK 0x0F

/* Fragmentatoin header */
#define DISPATCH_FIRST_FRAG 0xC0
#define DISPATCH_SUBSEQ_FRAG 0xE0
#define DISPATCH_FRAG_MASK 0xF8

#ifdef __ICCARM__          // IAR 
#pragma pack(1)  /* pack struct members on byte boundaries */
#define __attribute__(...) // GCC 
#elif defined __RX          // Renesas RX
#define __attribute__(X) // GCC 
#pragma pack  	/* pack struct members on byte boundaries */
#endif                     // IAR


#ifdef notyet
struct __attribute__ ((__packed__)) lowpan_mesh_hdr {
    uint8_t dispatch; // dispatch, flags and hops left
    // address length depends on flags in dispatch
};
#endif

struct __attribute__ ((__packed__)) lowpan_broadcast_hdr {
    u_int8_t dispatch;
    u_int8_t seq_no; // sequence number
};

struct __attribute__ ((__packed__)) lowpan_frag_hdr {
    union __attribute__ ((__packed__)) {
        u_int8_t dispatch;
        u_int16_t dgram_size;
        u_int8_t dgram_size8[2];
    };
    u_int16_t dgram_tag;
};

#ifdef __ICCARM__          // IAR 
#pragma pack()  /* restore default packing */
#undef __attribute__       // GCC 
#elif defined __RX          // Renesas RX
#pragma unpack  /* pack struct members on byte boundaries */
#undef __attribute__       // GCC
#endif  


struct wpancom
{
    struct ifnet ac_if;     /* network-visible interface */
    u_int16_t	PANid;
    u_int16_t	shortAddr;
    uint_8		longAddr[8];
};

//#define ac_addr PANid


void lowpan_ifattach (struct ifnet *);
int lowpan_ioctl (struct ifnet *, struct wpancom *, u_long, caddr_t);
void lowpan_input (struct ifnet *ifp, struct mbuf *m);



u_int8_t *lowpan_pack_headers(u_int8_t *packet,
		hw_addr_t *dst_addr, hw_addr_t *src_addr,
		u_int8_t *buf);
int pack_nhc_chain(u_int8_t **dest, size_t cnt, u_int8_t *packet);

int lowpan_unpack_headers(hw_addr_t *dst_addr, hw_addr_t *src_addr, struct mbuf *m);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _NETINET_6LOWPAN_H_ */
