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

#ifndef _rcs_h_
#define _rcs_h_

#ifdef __cplusplus
extern "C" {
#endif

//
// RCS initialization structure
//

struct rcs_settings
{
	struct RCS_variable *RCS_vars;	// RCS control variables
	u_char RCS_vars_numb;			// RCS control variables numbers

	void *dlog_control_funcs;		// pointer to dlog control functions structure

	u_short server_port;			// RCS port
};




// RCS variables types
#define type_int32_32	0	// 32-bits variable / 32-bits address
#define type_int16_32	1	// 16-bits variable / 32-bits address
#define type_int8_32	2	// 8-bits variable / 32-bits address
#define type_bool_32	3	// bool variable / 32-bits address

#define type_int32_16	4	// 32-bits variable / 16-bits address
#define type_int16_16	5	// 16-bits variable / 16-bits address
#define type_int8_16	6	// 8-bits variable / 16-bits address
#define type_bool_16	7	// bool variable / 16-bits address


// Access bits for RCS variables
#define acc_read	0	// read only
#define acc_write	1	// write only
#define acc_rdwr	2	// read/write


#ifdef __ICCARM__          // IAR 
#pragma pack(1)  /* pack struct members on byte boundaries */
#define __attribute__(...) // GCC 
#elif defined __RX          // Renesas RX
#define __attribute__(X) // GCC 
#pragma pack  	/* pack struct members on byte boundaries */
#endif                     // IAR

// RCS variable description
struct RCS_variable
{
	uchar VarName[16];
    uchar VarType;
    uchar VarAccessBits;
    uint_32 VarAddress;
} __attribute__((__packed__));

#ifdef __ICCARM__          // IAR 
#pragma pack()  /* restore default packing */
#undef __attribute__       // GCC 
#elif defined __RX          // Renesas RX
#pragma unpack  /* pack struct members on byte boundaries */
#undef __attribute__       // GCC 
#endif                     // IAR

// User functions
THREAD rcs(struct rcs_settings *rcs_init);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _rcs_h_ */
