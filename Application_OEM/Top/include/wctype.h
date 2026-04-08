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

#ifndef _wctype_h_
#define _wctype_h_

#include <wchar.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef int wctype_t;
#endif

#ifndef _WCTRANS_T
#define _WCTRANS_T
typedef int wctrans_t;
#endif

/* Not Defined in Unison yet  
locale_t  - should be in <locale.h> - This is Extension to the ISO C standard.
*/


int       iswalnum(wint_t);
//int       iswalnum_l(wint_t, locale_t);	//POSIX defined 
int       iswalpha(wint_t);
//int       iswalpha_l(wint_t, locale_t);	//POSIX defined 
int       iswblank(wint_t);
//int       iswblank_l(wint_t, locale_t); //POSIX defined 
int       iswcntrl(wint_t);
//int       iswcntrl_l(wint_t, locale_t);	//POSIX defined 
int       iswctype(wint_t, wctype_t);
//int       iswctype_l(wint_t, wctype_t, locale_t);//POSIX defined 
int       iswdigit(wint_t);
//int       iswdigit_l(wint_t, locale_t);//POSIX defined 
int       iswgraph(wint_t);
//int       iswgraph_l(wint_t, locale_t);//POSIX defined 
int       iswlower(wint_t);
//int       iswlower_l(wint_t, locale_t);//POSIX defined 
int       iswprint(wint_t);
//int       iswprint_l(wint_t, locale_t);//POSIX defined 
int       iswpunct(wint_t);
//int       iswpunct_l(wint_t, locale_t);//POSIX defined 
int       iswspace(wint_t);
//int       iswspace_l(wint_t, locale_t);//POSIX defined 
int       iswupper(wint_t);
//int       iswupper_l(wint_t, locale_t);//POSIX defined 
int       iswxdigit(wint_t);
//int       iswxdigit_l(wint_t, locale_t);//POSIX defined 
wint_t    towctrans(wint_t, wctrans_t);
//wint_t    towctrans_l(wint_t, wctrans_t, locale_t);//POSIX defined 
wint_t    towlower(wint_t);
//wint_t    towlower_l(wint_t, locale_t);//POSIX defined 
wint_t    towupper(wint_t);
//wint_t    towupper_l(wint_t, locale_t);//POSIX defined 
wctrans_t wctrans(const char *);
//wctrans_t wctrans_l(const char *, locale_t);//POSIX defined 
wctype_t  wctype(const char *);
//wctype_t  wctype_l(const char *, locale_t);//POSIX defined 


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _wchar_h_ */
