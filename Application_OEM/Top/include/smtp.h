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

#ifndef _SMTP_H_
#define _SMTP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ssl/ssltls.h>

/*
 *-------------------------------------------------
 * Smtp Errors
 *-------------------------------------------------
 */

#define SMTP_ERR_RESPONSE 				-1
#define SMTP_ERR_IO_SOCK 				-2
#define SMTP_ERR_PARAM 					-3

#define SMTP_ERR_4 							4 		//Transient Negative Completion reply
#define SMTP_ERR_5 							5		//Permanent Negative Completion reply


#define SMTP_MAIL_UNAVAIL 				450 //Requested mail action not taken: mailbox unavailable
#define SMTP_ERR_IN_PROC 				451 //Requested action aborted: error in processing
#define SMTP_INSUF_SYS_STOR 			452 // Requested action not taken: insufficient system storage
#define SMTP_UN_ACCOMOD_PARAM 	455 // Server unable to accommodate parameters

#define SMTP_INVAL_ARG		 			501 // Syntax error in parameters or arguments
#define SMTP_COM_NOT_IMPL 			502 // Command not implemented
#define SMTP_BAD_SEQ_COM				503 // Bad sequence of commands
#define SMTP_COM_PAR_NOT_IMPL 	504 //Command parameter not implemented
#define SMTP_MAIL_UANAVAIL 			550 // Requested action not taken: mailbox unavailable
#define SMTP_USER_NOT_LOCAL 		551 // User not local; please try <forward-path>
#define SMTP_EXCEED_STOR_ALLOC 	552 //Requested mail action aborted: exceeded storage allocation
#define SMTP_MAIL_NAME_NO_ALLOW 553 //Requested action not taken: mailbox name not allowed
#define SMTP_TRANS_FAIL 					554 // Transaction failed
#define SMTP_PAR_NO_REC_IMPL 		555 //MAIL FROM/RCPT TO parameters not recognized or not implemented

struct smtp_account_config{
	char*	hostname;	
	char*	client_mail;	
	char*	client_login;
	char* 	client_pass;
	char* 	smtp_server;	

};

struct smtp_mail_attribute{
  
	char* data;
	int cnt_address;
	char* address_to_send[10];
	char* subject;
	
};

struct smtp_timout {

	int connect;
	int mail;
	int rcpt;
	int data_start;
	int data_block;
	int data_end;
	
};

int smtp_accounts_setup(struct smtp_account_config * smtp_account_config, struct smtp_timout* timeout);
int smtp_send_mail(struct smtp_mail_attribute * smtp_mail_attribute, int sock, int ssl_flag, SSL *ssl);


#ifdef __cplusplus
} //extern "C" {
#endif

#endif  //_SMTP_H_
