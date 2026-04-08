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

#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdint.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>



#ifdef __cplusplus
extern "C" {
#endif

#define FLOATS		//enable/disable FLOAT support in stdio, by default enabled.

#define EOF (-1)
#define BUFSIZ 128

#define CAN_WR_BUF(stream)	((stream->_ptr+1 < stream->_base+BUFSIZ) || (stream->_flags & I_STRINGS))
#define CAN_RD_BUF(stream)	((stream->_ptr < stream->_base+stream->_cnt) || ((stream->_flags & I_STRINGS) && (*stream->_ptr != 0)))
#define UPDATE_CNT(stream)	if ((stream->_ptr+1 > stream->_base+stream->_cnt) || (stream->_flags & I_STRINGS)) stream->_cnt++


#define FILE_MUTEX_INIT(stream)     pthread_mutex_init(&stream->file_mutex, 0)
#define FILE_MUTEX_LOCK(stream)		pthread_mutex_lock(&stream->file_mutex)
#define FILE_MUTEX_UNLOCK(stream)	pthread_mutex_unlock(&stream->file_mutex)

// bits for the _flags field
#define _IOREAD		0x0001
#define _IOWRITE	0x0002
#define I_ERR       0x0004
#define I_EOF       0x0008
#define I_STRINGS   0x0010
#define I_PERPRINTF 0x0020
#define _BUFMOD		0x0040
#define _ENDBUF		0x0080
#define _BUFMALLOC	0x0100		/* _base is from malloc() */


#define L_ctermid	9
#define P_tmpdir	"/tmp"
#define L_tmpnam	20

#define	TMP_MAX		25

#define	FOPEN_MAX		8		/* must be <= MAXFDS <iolib/ucb.c> */
#define	FILENAME_MAX	50		/* must be <= NAME_MAX <nano_limits.h> */


#define _IOFBF	0 /* Fully buffered. */
#define _IOLBF	1 /* Line buffered. */
#define _IONBF	2 /* No buffering. */

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2



#define INF_BUFFER	SSIZE_MAX

typedef struct FILE {
	char *_base;
	char *_ptr;
	int _file;
	int _cnt;
	int _flags;
	int _buflen;
	pthread_mutex_t file_mutex;
}FILE;

typedef int fpos_t; 	//A non-array type containing all information needed
						//to specify uniquely every position within a file.
extern FILE* _stdin;
extern FILE* _stdout;
extern FILE* _stderr;	


/*----- our internal functions -----*/
FILE * stdin_init (char *fildes);
FILE * get_stdin_ptr(void);
void stdin_close(void);

FILE * stdout_init (char *fildes);
FILE * get_stdout_ptr(void);
void stdout_close (void);

FILE * stderr_init (char *fildes);
FILE * get_stderr_ptr(void);
void stderr_close (void);

int doprnt(const char *format, va_list args, FILE *stream);
int	doscan(FILE *stream, const char *format, va_list args);

int _fclose(FILE *);
int _fgetc(FILE *);
int _fputc (int , FILE *);
size_t _fread (void *, size_t, size_t, FILE *);
int _ungetc(int,FILE *);
int	_fflush (FILE *);
size_t _fwrite (const void *, size_t, size_t, FILE *);

const char *_sys_get_name(int err);
const char *_sys_get_msg(int err);


/* --- Streams: open and close --- */
FILE *fopen(const char *, const char *);
FILE *freopen (const char *, const char *, FILE *);
FILE *fdopen(int,const char*);
int fclose(FILE *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
FILE *fmemopen(void *, size_t, const char *);
FILE *open_memstream(char **, size_t *);

/* --- Streams: input --- */
int fgetc(FILE *);
int fgetpos(FILE *, fpos_t *);
char *fgets(char*,int,FILE *);
size_t fread (void *, size_t, size_t, FILE *);
int fscanf (FILE *, const char *, ...);
int getc(FILE *);
ssize_t getdelim(char **, size_t *, int, FILE *);
ssize_t getline(char **, size_t *, FILE *);
int getchar (void);
char *gets (char *);
int scanf (const char *, ...);
int sscanf (const char *, const char *, ...);
int vscanf (const char *, va_list);
int vsscanf (const char *, const char *, va_list);
int vfscanf (FILE *, const char *, va_list);
int ungetc(int,FILE *);

/* --- Streams: output --- */
int	fprintf (FILE *, const char *, ...);
int	fputc (int , FILE *);
int	fputs (const char *, FILE *);
size_t	fwrite (const void *, size_t, size_t, FILE *);
int dprintf(int, const char *, ...);
int	printf (const char *, ...);
int	putc (int, FILE *);
int	putchar (int);
int	puts (const char *);
int	sprintf (char *, const char *, ...);
int	snprintf (char *, size_t, const char *, ...);
int	vfprintf (FILE *, const char *, va_list);
int vdprintf(int, const char *, va_list);
int	vprintf (const char *, va_list);
int	vsprintf (char *, const char *, va_list);
int	vsnprintf (char *, size_t, const char *, va_list);
void perprintf(FILE * stream);
void noperprintf(FILE * stream);
void perror(const char *);

/* --- Streams: inquiry and control --- */
void clearerr(FILE *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fileno(FILE *);
int fseek(FILE *,long, int);
int fseeko(FILE *, off_t, int);
int	fsetpos(FILE *, const fpos_t *);
long ftell(FILE *);
off_t ftello(FILE *);
void rewind(FILE *);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);

/* --- File system manipulation --- */
int remove(const char *);
int rename(const char *, const char *);
int renameat(int, const char *, int, const char *);


char *ctermid(char *);
char *tmpnam(char *);
char *tempnam(const char *, const char *);
FILE *tmpfile(void);


/* Handle locking of streams.  */
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);


/*
 * The POSIX standard says, that next function can be a macro
 */
//#define putc(c, fp)	fputc(c, fp)
#define	putchar(x)	putc(x, _stdout)
//#define getc(fp)	fgetc(fp)
#define getchar(x)	getc(_stdin)
#define	putchar_unlocked(x)	putc_unlocked(x, _stdout)
#define getchar_unlocked(x)	getc_unlocked(_stdin)


#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* __STDIO_H__ */
