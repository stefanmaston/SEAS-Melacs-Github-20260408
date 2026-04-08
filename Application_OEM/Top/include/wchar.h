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

#ifndef _wchar_h_
#define _wchar_h_

#include <stdio.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __REDEFINE_WINT
# ifndef _WINT_T
# define _WINT_T
 typedef unsigned int wint_t;
# endif
#endif //__REDEFINE_WINT


/* Conversion state information.  */
#ifndef _MBSTATE_T
#define _MBSTATE_T
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;		/* Value so far.  */
} mbstate_t;
#endif /* _MBSTATE_T */


/* Not Defined in Unison yet  
locale_t  - should be in <locale.h> - This is Extension to the ISO C standard.
*/

/*The tag tm shall be declared as naming an incomplete structure type, 
the contents of which are described in the <time.h> header.*/
struct tm;

#ifndef WEOF
#define WEOF ((wint_t)-1)
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN 0
#endif

#ifndef WCHAR_MAX
#define WCHAR_MAX 0x7fffffffu
#endif

wint_t        btowc(int);
wint_t        fgetwc(FILE *);
wchar_t      *fgetws(wchar_t *, int, FILE *);
wint_t        fputwc(wchar_t, FILE *);
int           fputws(const wchar_t *, FILE *);
int           fwide(FILE *, int);
int           fwprintf(FILE *, const wchar_t *, ...);
int           fwscanf(FILE *, const wchar_t *, ...);
wint_t        getwc(FILE *);
wint_t        getwchar(void);
/***********   moved to <wctype.h> ****************/
//int           iswalnum(wint_t);	
//int           iswalpha(wint_t);
//int           iswcntrl(wint_t);
//int           iswctype(wint_t, wctype_t);
//int           iswdigit(wint_t);
//int           iswgraph(wint_t);
//int           iswlower(wint_t);
//int           iswprint(wint_t);
//int           iswpunct(wint_t);
//int           iswspace(wint_t);
//int           iswupper(wint_t);
//int           iswxdigit(wint_t);
/*************************************************/
size_t        mbrlen(const char *, size_t, mbstate_t *);
size_t        mbrtowc(wchar_t *, const char *, size_t,  mbstate_t *);
int           mbsinit(const mbstate_t *);
size_t        mbsnrtowcs(wchar_t *, const char **,  size_t, size_t, mbstate_t *);
size_t        mbsrtowcs(wchar_t *, const char **, size_t, mbstate_t *);
FILE         *open_wmemstream(wchar_t **, size_t *);
wint_t        putwc(wchar_t, FILE *);
wint_t        putwchar(wchar_t);
int           swprintf(wchar_t *, size_t, const wchar_t *, ...);
int           swscanf(const wchar_t *, const wchar_t *, ...);
/***********   moved to <wctype.h> ***************/
//wint_t        towlower(wint_t);		
//wint_t        towupper(wint_t);		
/*************************************************/
wint_t        ungetwc(wint_t, FILE *);
int           vfwprintf(FILE *, const wchar_t *, va_list);
int           vfwscanf(FILE *, const wchar_t *, va_list);
int           vswprintf(wchar_t *, size_t, const wchar_t *, va_list);
int           vswscanf(const wchar_t *, const wchar_t *, va_list);
int           vwprintf(const wchar_t *, va_list);
int           vwscanf(const wchar_t *, va_list);
wchar_t      *wcpcpy(wchar_t *, const wchar_t *);
wchar_t      *wcpncpy(wchar_t  *, const wchar_t *, size_t);
size_t        wcrtomb(char *, wchar_t, mbstate_t *);
int           wcscasecmp(const wchar_t *, const wchar_t *);
//int           wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);		//POSIX defined 
wchar_t      *wcscat(wchar_t *, const wchar_t *);
wchar_t      *wcschr(const wchar_t *, wchar_t);
int           wcscmp(const wchar_t *, const wchar_t *);
int           wcscoll(const wchar_t *, const wchar_t *);
//int           wcscoll_l(const wchar_t *, const wchar_t *, locale_t);			//POSIX defined 
wchar_t      *wcscpy(wchar_t *, const wchar_t *);
size_t        wcscspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsdup(const wchar_t *);
size_t        wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm *);
size_t        wcslen(const wchar_t *);
int           wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
//int           wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t, locale_t);		//POSIX defined 
wchar_t      *wcsncat(wchar_t *, const wchar_t *, size_t);
int           wcsncmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wcsncpy(wchar_t *, const wchar_t *, size_t);
size_t        wcsnlen(const wchar_t *, size_t);
size_t        wcsnrtombs(char *, const wchar_t **, size_t, size_t, mbstate_t *);
wchar_t      *wcspbrk(const wchar_t *, const wchar_t *);
wchar_t      *wcsrchr(const wchar_t *, wchar_t);
size_t        wcsrtombs(char *, const wchar_t **, size_t, mbstate_t *);
size_t        wcsspn(const wchar_t *, const wchar_t *);
wchar_t      *wcsstr(const wchar_t *, const wchar_t *);
double        wcstod(const wchar_t *, wchar_t **);
float         wcstof(const wchar_t *, wchar_t **);
wchar_t      *wcstok(wchar_t *, const wchar_t *, wchar_t **);
long          wcstol(const wchar_t *, wchar_t **, int);
long double   wcstold(const wchar_t *, wchar_t **);
long long     wcstoll(const wchar_t *, wchar_t **, int);
unsigned long wcstoul(const wchar_t *, wchar_t **, int);
unsigned long long wcstoull(const wchar_t *, wchar_t **, int);
int           wcswidth(const wchar_t *, size_t);
size_t        wcsxfrm(wchar_t *, const wchar_t *, size_t);
//size_t        wcsxfrm_l(wchar_t *, const wchar_t *, size_t, locale_t);		//POSIX defined 
int           wctob(wint_t);
//wctype_t      wctype(const char *);		// moved to <wctype.h>
int           wcwidth(wchar_t);
wchar_t      *wmemchr(const wchar_t *, wchar_t, size_t);
int           wmemcmp(const wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemcpy(wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemmove(wchar_t *, const wchar_t *, size_t);
wchar_t      *wmemset(wchar_t *, wchar_t, size_t);
int           wprintf(const wchar_t *, ...);
int           wscanf(const wchar_t *, ...);


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _wchar_h_ */
