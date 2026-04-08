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

#ifndef _NETINET_IEEE802154_H_
#define _NETINET_IEEE802154_H_

#ifdef __cplusplus
extern "C" {
#endif

/* 802.15.4 address */
enum {
    HW_ADDR_SHORT,
    HW_ADDR_LONG
};

typedef struct hw_addr {
    u_int8_t type; // HW_ADDR_SHORT | HW_ADDR_LONG
    u_int16_t PANid;
    union {
		u_int16_t addr_short;
		u_int8_t addr_long[8];
    };
} hw_addr_t;

#ifdef __ICCARM__          // IAR 
#pragma pack(1)  /* pack struct members on byte boundaries */
#define __attribute__(...) // GCC 
#elif defined __RX          // Renesas RX
#define __attribute__(X) // GCC 
#pragma pack  	/* pack struct members on byte boundaries */
#endif                     // IAR

/*
 * IEEE 802.15.4 short MAC header:
 *   - 16bit PANs and addresses for destination
 *   - 16bit PANs and addresses for source
 *   - without security
 */
struct __attribute__ ((__packed__)) ieee802154_short_hdr
{
    u_int16_t   fcf;       // frame control field
    u_int8_t    seq_no;
    u_int16_t   dstPAN;
    u_int16_t   dstAddr;
    u_int16_t   srcPAN;
    u_int16_t   srcAddr;
}; 


/*
 * IEEE 802.15.4 simple MAC header:
 *   - 16bit PANs and addresses for destination
 *   - 16bit addresses for source
 *   - without security
 */
struct __attribute__ ((__packed__)) ieee802154_simple_hdr
{
    u_int16_t   fcf;       // frame control field
    u_int8_t    seq_no;
    u_int16_t   dstPAN;
    u_int16_t   dstAddr;
    u_int16_t   srcAddr;
};

#ifdef __ICCARM__          // IAR 
#pragma pack()  /* restore default packing */
#undef __attribute__       // GCC 
#elif defined __RX          // Renesas RX
#pragma unpack  /* pack struct members on byte boundaries */
#undef __attribute__       // GCC
#endif  
/*
 * Frame control field
 */
/* Frame Type */
#define FRAME_TYPE_MASK     (7 << 0)
#define FRAME_TYPE_BEACON   (0 << 0)
#define FRAME_TYPE_DATA     (1 << 0)
#define FRAME_TYPE_ACK      (2 << 0)
#define FRAME_TYPE_CMD      (3 << 0)

#define SECURITY_ENA        (1 << 3)
#define FRAME_PEND          (1 << 4)
#define ACK_REQUEST         (1 << 5)
#define PAN_ID_COMPRESS     (1 << 6)
#define RESERVED_MASK       (7 << 7)

#define DST_ADDR_MASK       (3 << 10)
#define DST_ADDR_NP         (0 << 10)
#define DST_ADDR_RSV        (1 << 10)
#define DST_ADDR_16         (2 << 10)
#define DST_ADDR_64         (3 << 10)

#define FRAME_VERS_MASK     (3 << 12)
#define FRAME_VERS_2003     (0 << 12)
#define FRAME_VERS_2006     (1 << 12)

#define SRC_ADDR_MASK       (3 << 14)
#define SRC_ADDR_NP         (0 << 14)
#define SRC_ADDR_RSV        (1 << 14)
#define SRC_ADDR_16         (2 << 14)
#define SRC_ADDR_64         (3 << 14)



/*
 * Security control field
 */
/* Security level*/
#define SEC_LEVEL_MASK					(7 << 0)
#define SEC_LEVEL_ATTRNONE_CONFOFF		(0 << 0)
#define SEC_LEVEL_ATTRMIC32_CONFOFF		(1 << 0)
#define SEC_LEVEL_ATTRMIC64_CONFOFF		(2 << 0)
#define SEC_LEVEL_ATTRMIC128_CONFOFF	(3 << 0)
#define SEC_LEVEL_ATTRENC_CONFON		(4 << 0)
#define SEC_LEVEL_ATTRENC32_CONFON		(5 << 0)
#define SEC_LEVEL_ATTRENC64_CONFON		(6 << 0)
#define SEC_LEVEL_ATTRENC128_CONFON		(7 << 0)

/* Key identifier */
#define KEY_MASK	(3 << 3)
#define KEY_0		(0 << 3)
#define KEY_1		(1 << 3)
#define KEY_2		(2 << 3)
#define KEY_3		(3 << 3)



//http://book.itep.ru/4/41/zigbee.htm

#define IEEE802154MTU			128
#define IEEE802154_ADDR_LEN		4
#define IEEE802154_MAX_HDR		28


/******************/
/* Swap functions */
/******************/
/*
 * IEEE 802.15.4 header works with swapped data format
 * This format is reverse than network format
 */
#if BYTE_ORDER == LITTLE_ENDIAN
	#define	itoh_2(x)	(x)
	#define	htoi_2(x)	(x)
	#define	iton_2(x)	swap_2(x)
	#define	ntoi_2(x)	swap_2(x)

	#define	ITOH_2(x)	(void) (x)
	#define	HTOI_2(x)	(void) (x)
	#define	ITON_2(x)	(x) = swap_2((uint_16)(x))
	#define	NTOI_2(x)	(x) = swap_2((uint_16)(x))

#else
	#define	itoh_2(x)	swap_2(x)
	#define	htoi_2(x)	swap_2(x)
	#define	iton_2(x)	(x)
	#define	ntoi_2(x)	(x)

	#define	ITOH_2(x)	(x) = swap_2((uint_16)(x))
	#define	HTOI_2(x)	(x) = swap_2((uint_16)(x))
	#define	ITON_2(x)	(void) (x)
	#define	NTOI_2(x)	(void) (x)

#endif /* BYTE_ORDER */

uint_16 swap_2(uint_16);

#define itoh_8(x, y)	htoi_8(x, y)
void htoi_8(uint_8 *src, uint_8 *dst);
#define ITOH_8(x)	itoh_8(x, x)
#define HTOI_8(x)	htoi_8(x, x)



void ieee802154_set_short_hdr(u_int16_t dstPAN, u_int16_t dstAddr,
        u_int16_t srcPAN, u_int16_t srcAddr, struct mbuf *m);
void ieee802154_set_simple_hdr(u_int16_t dstPAN, u_int16_t dstAddr,
        u_int16_t srcAddr, struct mbuf *m);
u_int8_t *ieee802154_strip_header(u_int8_t *pkt, int *len,
		hw_addr_t *dst_addr, hw_addr_t *src_addr);
void ieee802154_init(void);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _NETINET_IEEE802154_H_ */
