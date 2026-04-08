/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2013 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
#ifndef _limits_h_
#define _limits_h_

#include <stdint.h>


//Number of bits in a type char.
#undef CHAR_BIT
#define CHAR_BIT 8

//Minimum and Maximum value for an object of type char.
#   ifdef __CHAR_UNSIGNED__
#    undef CHAR_MIN
#    define CHAR_MIN 0
#    undef CHAR_MAX
#    define CHAR_MAX UINT8_MAX
#   else
#    undef CHAR_MIN
#    define CHAR_MIN INT8_MIN
#    undef CHAR_MAX
#    define CHAR_MAX INT8_MAX
#   endif 
 
//Maximum value for an object of type int. 
#undef INT_MAX
#define INT_MAX INT32_MAX

//Minimum value for an object of type int. 
#undef INT_MIN
#define INT_MIN INT32_MIN

#ifdef __u_int64_defined__ 
	//Maximum value for an object of type long long.
	#undef LLONG_MAX
	#define LLONG_MAX INT64_MAX
  
	//Minimum value for an object of type long long.
	#undef LLONG_MIN
	#define LLONG_MIN INT64_MIN
#endif 
 
//Number of bits in an object of type long. 
#undef LONG_BIT
#define LONG_BIT 32
 
//Maximum value for an object of type long. 
#undef LONG_MAX
#define LONG_MAX INT32_MAX 

//Minimum value for an object of type long.
#undef LONG_MIN
#define LONG_MIN INT32_MIN

//Maximum number of bytes in a character, for any supported locale. 
#ifndef MB_LEN_MAX
#define MB_LEN_MAX 1
#endif

//Maximum value for an object of type signed char. 
#undef SCHAR_MAX
#define SCHAR_MAX INT8_MAX 

//Minimum value for an object of type signed char.
#undef SCHAR_MIN
#define SCHAR_MIN INT8_MIN

//Maximum value for an object of type short.
#undef SHRT_MAX
#define SHRT_MAX  INT16_MAX
  
//Minimum value for an object of type short.  
#undef SHRT_MIN
#define SHRT_MIN INT16_MIN

//Maximum value for an object of type ssize_t.  
#undef SSIZE_MAX
#if __WORDSIZE == 16
	#define SSIZE_MAX INT16_MAX
#else
	#define SSIZE_MAX INT32_MAX
#endif

//Maximum value for an object of type unsigned char. 
#undef UCHAR_MAX
#define UCHAR_MAX UINT8_MAX

//Maximum value for an object of type unsigned.
//Minimum Acceptable Value: 4 294 967 295 
#undef UINT_MAX
#define UINT_MAX UINT32_MAX

#ifdef __u_int64_defined__ 
	//Maximum value for an object of type unsigned long long. 
	#undef ULLONG_MAX
	#define ULLONG_MAX UINT64_MAX
#endif 
 
//Maximum value for an object of type unsigned long. 
#undef ULONG_MAX
#define ULONG_MAX UINT32_MAX

//Maximum value for an object of type unsigned short. 
#undef USHRT_MAX
#define USHRT_MAX UINT16_MAX

//Number of bits in an object of type int.
//Minimum Acceptable Value: 32
#undef WORD_BIT
#define WORD_BIT 32

#endif /* _limits_h_ */
