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

#ifndef _stdlib_h_
#define _stdlib_h_

#include <stddef.h>
#include <bits/wordsize.h>
#include <locale.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif 

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef RAND_MAX
	#if __WORDSIZE == 16
		#define RAND_MAX 32767
	#else
		#define RAND_MAX 0x7fffffff
	#endif
#endif	

//Maximum number of bytes in a character specified by
//the current locale (category LC_CTYPE ).
#ifndef MB_CUR_MAX
#define MB_CUR_MAX	LC_CTYPE
#endif

typedef struct 
{
  int quot; /* quotient */
  int rem; /* remainder */
} div_t;

typedef struct 
{
  long quot; /* quotient */
  long rem; /* remainder */
} ldiv_t;

typedef struct
{
  long long int quot; /* quotient */
  long long int rem; /* remainder */
} lldiv_t;


void          _Exit(int);
long          a64l(const char *);
void          abort(void);
int           abs(int);
int           atexit(void (*)(void));
double        atof(const char *);
int           atoi(const char *);
long          atol(const char *);
long long     atoll(const char *);
void         *bsearch(const void *, const void *, size_t, size_t,
                  int (*)(const void *, const void *));
void         *calloc(size_t, size_t);
div_t         div(int, int);
double        drand48(void);
double        erand48(unsigned short [3]);
void          exit(int);
void          free(void *);
char         *getenv(const char *);
int           getsubopt(char **, char *const *, char **);
int           grantpt(int);
char         *initstate(unsigned, char *, size_t);
long          jrand48(unsigned short [3]);
char         *l64a(long);
long          labs(long);
void          lcong48(unsigned short [7]);
ldiv_t        ldiv(long, long);
long long     llabs(long long);
lldiv_t       lldiv(long long, long long);
long          lrand48(void);
void         *malloc(size_t);
int           mblen(const char *, size_t);
size_t        mbstowcs(wchar_t *, const char *, size_t);
int           mbtowc(wchar_t *, const char *, size_t);
char         *mkdtemp(char *);
int           mkstemp(char *);
long          mrand48(void);
long          nrand48(unsigned short [3]);
int           posix_memalign(void **, size_t, size_t);
int           posix_openpt(int);
char         *ptsname(int);
int           putenv(char *);
void          qsort(void *, size_t, size_t, int (*)(const void *,
                  const void *));
int           rand(void);
int           rand_r(unsigned int*);
long          random(void);
void         *realloc(void *, size_t);
char         *realpath(const char *, char *);
unsigned short *seed48(unsigned short [3]);
int           setenv(const char *, const char *, int);
void          setkey(const char *);
char         *setstate(char *);
void          srand(unsigned int);
void          srand48(long);
void          srandom(unsigned int);
double        strtod(const char *, char **);
float         strtof(const char *, char **);
long          strtol(const char *, char **, int);
long double   strtold(const char *, char **);
long long     strtoll(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);
unsigned long long
              strtoull(const char *, char **, int);
int           system(const char *);
int           unlockpt(int);
int           unsetenv(const char *);
size_t        wcstombs(char *, const wchar_t *, size_t);
int           wctomb(char *, wchar_t);

//Unison specific function
void          malloc_init(void);


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _stdlib_h_ */
