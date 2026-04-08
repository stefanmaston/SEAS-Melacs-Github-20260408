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

/*
 * Maximum number of certificate authorities
 */
#define CONFIG_X509_MAX_CA_CERTS 150

/*
 * Maximum number of chained certificates
 */
#define CONFIG_SSL_MAX_CERTS 3


/*
 * If the SSL_CTX object is not thread safe e.g. the case where a
 * new thread is created for each SSL object, then mutexing is required.
 */
#undef CONFIG_SSL_CTX_MUTEXING




/******************
 * BigInt Options
 *****************/

/*
 * Barrett Reduction Algorithm
 *
 * Barrett performs expensive precomputation before reduction and partial
 * multiplies for computational speed.
 */
#define CONFIG_BIGINT_BARRETT


/*
 * Chinese Remainder Theorem (CRT)
 *
 * Uses a number of extra coefficients from the private key to improve the
 * performance of a decryption. This feature is one of the most
 * significant performance improvements (it reduces a decryption time by
 * over 3 times).
 */
#define CONFIG_BIGINT_CRT


