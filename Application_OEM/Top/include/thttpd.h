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


#ifndef __THTTPD_H__
#define __THTTPD_H__

#ifdef __cplusplus
extern "C" {
#endif

//prototype of cgi handler
typedef int (*tcgi_funk)(char * path , char ** argv , char ** envp, int fd);	

//Http server main thread
void	thttpd_main(char *config_path);		

//register new cgi handler
signed char	register_cgi_handler(char * , char * , tcgi_funk);	
//delete exsist cgi handler
int		del_cgi_handler(char * name);						

//get env variable value from list
char 	* httpgetenv(char *name, char ** envp);		
//parsing from string from browser and get parm value
char 	* getparam(char *buffer,char *name);	
//transform ascii to integer
int atoi (const char *nptr);
//write to http connection 
ssize_t 	httpwrite(int fd, const void *buf, size_t len);
ssize_t 	httpread(int fd, const void *buf, size_t len);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /*thttpd*/
