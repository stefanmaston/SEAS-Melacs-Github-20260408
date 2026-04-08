/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2010 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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

#ifndef __LOGIN_H__
#define __LOGIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LOGIN_TBL_ENTRIES 32
#define LOGIN_TBL_USER_SIZE   16    // Size in bytes
#define LOGIN_TBL_PSWD_SIZE   16    // Size in bytes
#define LOGIN_TBL_ENTRY_SIZE  59		// Size in bytes
#define LOGIN_TBL_CRYPT_PSWD_SIZE  43	// Size in bytes

int init_login_table( char *loginfile );
void set_loginfile(char * loginfile);
int add_user( char *user, char *pswd );
int delete_user( char *user );
int check_password( char *user, char *pswd );
int update_password( char *user, char *oldpswd, char *newpswd );

#ifdef __cplusplus
} //extern "C" {
#endif

#endif //__LOGIN_H__
