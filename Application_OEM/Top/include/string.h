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

#ifndef _string_h_
#define _string_h_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void    *memccpy(void *, const void *, int, size_t); //Extension to the ISO C standard
void    *memchr(const void *, int, size_t);
int      memcmp(const void *, const void *, size_t);
void    *memcpy(void *, const void *, size_t);
void    *memmove(void *, const void *, size_t);
void    *memset(void *, int, size_t);
char    *stpcpy(char *, const char *);				//Extension to the ISO C standard
char    *stpncpy(char *, const char *, size_t);		//Extension to the ISO C standard
char    *strcat(char *, const char *);
char    *strchr(const char *, int);
int      strcmp(const char *, const char *);
int      strcoll(const char *, const char *);
//int      strcoll_l(const char *, const char *, locale_t);	//Extension to the ISO C standard
char    *strcpy(char *, const char *);
size_t   strcspn(const char *, const char *);
char    *strdup(const char *);						//Extension to the ISO C standard
char    *strerror(int);
//char    *strerror_l(int, locale_t);				//Extension to the ISO C standard
int      strerror_r(int, char *, size_t);			//Extension to the ISO C standard	
size_t   strlen(const char *);
char    *strncat(char *, const char *, size_t);
int      strncmp(const char *, const char *, size_t);
char    *strncpy(char *, const char *, size_t);
char    *strndup(const char *, size_t);				//Extension to the ISO C standard
size_t   strnlen(const char *, size_t);				//Extension to the ISO C standard
char    *strpbrk(const char *, const char *);
char    *strrchr(const char *, int);
char    *strsignal(int);							//Extension to the ISO C standard
size_t   strspn(const char *, const char *);
char    *strstr(const char *, const char *);
char    *strtok(char *, const char *);
char    *strtok_r(char *, const char *, char **);	//Extension to the ISO C standard
size_t   strxfrm(char *, const char *, size_t);
//size_t   strxfrm_l(char *restrict, const char *restrict, size_t, locale_t); //Extension to the ISO C standard

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _string_h_ */	 
