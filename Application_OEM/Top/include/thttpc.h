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

#ifndef	__HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#define  	HTTPC_OK                        0
#define  	HTTPC_ENOMEM                    1
#define  	HTTPC_GENERAL_TCP_ERROR         2
#define  	HTTPC_HOST_NOT_ANSWER           3
#define  	HTTPC_FILE_NOT_FOUND            4
#define  	HTTPC_TIMEOUT_DOWNLOAD          5
#define  	HTTPC_DOWNLOAD_SIZE_ERROR       6
#define  	HTTPC_ERROR_FILE_WRITE          7
#define  	HTTPC_ERROR_FILE_READ           8
#define  	HTTPC_ERROR_DATA_SEND           9
#define  	HTTPC_ERROR_ANSWER              10
#define  	HTTPC_TIMEOUT_UPLOAD            11
#define  	HTTPC_TIMEOUT_CONNECT           12

typedef struct {
	const char 	*host_name;
	const char 	*host_ipaddr;
	const char 	*host_path_file;
	int 		host_port;			
	int		fd;
	int		max_file_size;
} http_get_param;



typedef struct {
	const char 	*host_name;
	const char 	*host_ipaddr;
	const char 	*host_path_file;
	const char 	*file_name;
	int 		host_port;			
	int		    fd;
	int		    file_size;
} http_post_param;



typedef struct {
	const char 	*host_name;
	const char 	*host_ipaddr;
	const char 	*host_path_file;
	short        host_port;
	const char 	*file_name;
	const char 	*data ;
	int          data_size;
} http_post_param_bytes;





#endif	//__HTTP_CLIENT_H__
