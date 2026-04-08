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
#include <sys.h>

#define 	APPLICATION_HEAD_ADDRESS	(0x9D000000 + BMXPFMSZ - 0x30);
//0x9D07FFD0
#define		APP_BASE			0x9D000000
#define		APP_ENTRY			0x9D001000

/*
#define 	APPLICATION_HEAD_ADDRESS	(0x9D006000 + BMXPFMSZ - 0x30);
//0x9D07FFD0
#define		APP_BASE			0x9D006000
#define		APP_ENTRY			(0x9D006000 + 0x1000)
*/
#define 	PROGRAM_VERSION			0x101
#define 	DATE_OF_COMPILATION		0x16050C


#ifdef __ICCARM__          // IAR 
#pragma pack(1)  /* pack struct members on byte boundaries */
#define __attribute__(...) // GCC 
#elif defined __RX         // Renesas RX
#define __attribute__(X) 	// GCC 
#pragma pack  	/* pack struct members on byte boundaries */
#endif                    // IAR


typedef struct __attribute__ ((packed)) {
	/* START ADDRESS of user application header data - Appheader address + 0x00 */
	const unsigned long int         app_entry_addr;
												/* 	- Appheader address + 0x04. */													
	const unsigned int * const app_start_addr; 
    											/*	- Appheader address + 0x08. */
	const unsigned int * const app_lo_addr;
												/* 	- Appheader address + 0x0C */													
	const unsigned int         programm_version;
    											/* 	- Appheader address + 0x10 */													
    const unsigned int         date_of_compile;
	                                            /*   - Appheader address + 0x14 */	
	const unsigned char        reserved[4]; 	
	                                            /*   - Appheader address + 0x18 */
	const unsigned short       crc_binary_file; 
	 											/*   - Appheader address + 0x1A */	
	const unsigned short       crc_old_binary_file;
												/*   - Appheader address + 0x1C */	
	const unsigned short       crc_coded_file; 
												/*   - Appheader address + 0x1E */	
	const unsigned short       mark_coded; 
} app_header;

#ifdef __ICCARM__		// IAR 
#pragma pack()			/* restore default packing */
#undef __attribute__	// GCC
#elif defined __RX      // Renesas RX
#pragma unpack  /* pack struct members on byte boundaries */
#undef __attribute__    // GCC  
#endif					// IAR

