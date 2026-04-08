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
 * OpenSSL compatible layer. Contain basic defines, types and functions
 */

#ifndef _OPENSSL_H_
#define _OPENSSL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <ssl/config.h>
#include <ssl/ssl_struct.h>



// File type
#define SSL_FILETYPE_ASN1	1
#define SSL_FILETYPE_PEM	2

// Connection option
#define SSL_VERIFY_NONE					0x00
#define SSL_VERIFY_PEER					0x01
#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT	0x02	// not used
#define SSL_VERIFY_CLIENT_ONCE			0x04	// not used

// Errors
#define SSL_ERROR_NONE			0
#define SSL_ERROR_SSL			1
#define SSL_ERROR_WANT_READ		2
#define SSL_ERROR_WANT_WRITE		3
#define SSL_ERROR_WANT_X509_LOOKUP	4
#define SSL_ERROR_SYSCALL		5 /* look at error stack/return value/errno */
#define SSL_ERROR_ZERO_RETURN		6
#define SSL_ERROR_WANT_CONNECT		7
#define SSL_ERROR_WANT_ACCEPT		8




/*
 * X.509 verify errors
 */
#define		X509_V_OK					0
/* illegal error (for uninitialized values, to avoid X509_V_OK): 1 */

#define		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT		2
#define		X509_V_ERR_UNABLE_TO_GET_CRL			3
#define		X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE	4
#define		X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE	5
#define		X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY	6
#define		X509_V_ERR_CERT_SIGNATURE_FAILURE		7
#define		X509_V_ERR_CRL_SIGNATURE_FAILURE		8
#define		X509_V_ERR_CERT_NOT_YET_VALID			9
#define		X509_V_ERR_CERT_HAS_EXPIRED			10
#define		X509_V_ERR_CRL_NOT_YET_VALID			11
#define		X509_V_ERR_CRL_HAS_EXPIRED			12
#define		X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD	13
#define		X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD	14
#define		X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD	15
#define		X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD	16
#define		X509_V_ERR_OUT_OF_MEM				17
#define		X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT		18
#define		X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN		19
#define		X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY	20
#define		X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE	21
#define		X509_V_ERR_CERT_CHAIN_TOO_LONG			22
#define		X509_V_ERR_CERT_REVOKED				23
#define		X509_V_ERR_INVALID_CA				24
#define		X509_V_ERR_PATH_LENGTH_EXCEEDED			25
#define		X509_V_ERR_INVALID_PURPOSE			26
#define		X509_V_ERR_CERT_UNTRUSTED			27
#define		X509_V_ERR_CERT_REJECTED			28
/* These are 'informational' when looking for issuer cert */
#define		X509_V_ERR_SUBJECT_ISSUER_MISMATCH		29
#define		X509_V_ERR_AKID_SKID_MISMATCH			30
#define		X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH		31
#define		X509_V_ERR_KEYUSAGE_NO_CERTSIGN			32

#define		X509_V_ERR_UNABLE_TO_GET_CRL_ISSUER		33
#define		X509_V_ERR_UNHANDLED_CRITICAL_EXTENSION		34
#define		X509_V_ERR_KEYUSAGE_NO_CRL_SIGN			35
#define		X509_V_ERR_UNHANDLED_CRITICAL_CRL_EXTENSION	36
#define		X509_V_ERR_INVALID_NON_CA			37
#define		X509_V_ERR_PROXY_PATH_LENGTH_EXCEEDED		38
#define		X509_V_ERR_KEYUSAGE_NO_DIGITAL_SIGNATURE	39
#define		X509_V_ERR_PROXY_CERTIFICATES_NOT_ALLOWED	40

#define		X509_V_ERR_INVALID_EXTENSION			41
#define		X509_V_ERR_INVALID_POLICY_EXTENSION		42
#define		X509_V_ERR_NO_EXPLICIT_POLICY			43
#define		X509_V_ERR_DIFFERENT_CRL_SCOPE			44
#define		X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE	45

#define		X509_V_ERR_UNNESTED_RESOURCE			46

#define		X509_V_ERR_PERMITTED_VIOLATION			47
#define		X509_V_ERR_EXCLUDED_VIOLATION			48
#define		X509_V_ERR_SUBTREE_MINMAX			49
#define		X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE		51
#define		X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX	52
#define		X509_V_ERR_UNSUPPORTED_NAME_SYNTAX		53
#define		X509_V_ERR_CRL_PATH_VALIDATION_ERROR		54

/* The application is not happy */
#define		X509_V_ERR_APPLICATION_VERIFICATION		50




/*
 * Non OpenSSL debug flags
 */
#define DBG_DISPLAY_STATES		0x0001
#define DBG_DISPLAY_BYTES		0x0002
#define DBG_DISPLAY_CERTS		0x0004
#define DBG_DISPLAY_RSA			0x0008
#define DBG_ALL					0x000f




/*
 * Dummy types
 */
typedef char SSL_METHOD;
typedef char X509_STORE_CTX;


/*
 * Method functions
 */
const SSL_METHOD *TLSv1_server_method(void);	/* TLSv1.0 */
const SSL_METHOD *TLSv1_client_method(void);	/* TLSv1.0 */

const SSL_METHOD *TLSv1_1_server_method(void);	/* TLSv1.1 */
const SSL_METHOD *TLSv1_1_client_method(void);	/* TLSv1.1 */




/*
 * User application functions
 */

SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);
void SSL_CTX_free(SSL_CTX *ctx);


void SSL_CTX_set_default_passwd_cb_userdata(SSL_CTX *ctx, void *u);
int SSL_CTX_use_RSAPrivateKey_file(SSL_CTX *ctx, const char *file, int type);
int SSL_CTX_use_RSAPrivateKey_ASN1(SSL_CTX *ctx, unsigned char *d, long len);
#define SSL_CTX_use_PrivateKey_file SSL_CTX_use_RSAPrivateKey_file
int SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file, int type);
int SSL_CTX_use_certificate_ASN1(SSL_CTX *ctx, int len, unsigned char *d);
int SSL_CTX_load_verify_locations(SSL_CTX *ctx, const char *CAfile, const char *CApath);
int SSL_CTX_load_verify_ASN1(SSL_CTX *ctx, unsigned char *d, long len);
long SSL_CTX_get_timeout(const SSL_CTX *ctx);

void SSL_CTX_set_verify(SSL_CTX *ctx, int mode, int (*verify_callback)(int, X509_STORE_CTX *));
void SSL_set_verify(SSL *s, int mode, int (*verify_callback)(int, X509_STORE_CTX *));
void SSL_CTX_set_verify_depth(SSL_CTX *ctx, int depth);
void SSL_set_verify_depth(SSL *s, int depth);
int SSL_CTX_get_verify_mode(const SSL_CTX *ctx);
int SSL_get_verify_mode(const SSL *ssl);
int SSL_CTX_get_verify_depth(const SSL_CTX *ctx);
int SSL_get_verify_depth(const SSL *ssl);

long SSL_get_verify_result(const SSL *ssl);

SSL *SSL_new(SSL_CTX *ctx);
void SSL_free(SSL *ssl);
int SSL_set_fd(SSL *ssl, int fd);
int SSL_shutdown(SSL *ssl);

int SSL_connect(SSL *ssl);
int SSL_accept(SSL *ssl);

const char *SSL_get_version(const SSL *ssl);
const char *SSL_get_cipher(const SSL *ssl);
#define SSL_get_cipher_name SSL_get_cipher

int SSL_read(SSL *ssl, void *buf, int num);
int SSL_write(SSL *ssl, const void *buf, int num);
int SSL_get_error(const SSL *ssl, int ret);


// Non OpenSSL functions
void SSL_CTX_debug(SSL_CTX *ctx, int debug);
int SSL_CTX_use_PKCS8_file(SSL_CTX *ctx, const char *file, char *password);
int SSL_CTX_use_PKCS8_memory(SSL_CTX *ctx, unsigned char *d, long len, char *password);
int SSL_CTX_use_PKCS12_file(SSL_CTX *ctx, const char *file, char *password);
int SSL_CTX_use_PKCS12_memory(SSL_CTX *ctx, unsigned char *d, long len, char *password);



/*
 * Empty functions
 */
void SSL_load_error_strings(void);
int SSL_library_init(void);
#define OpenSSL_add_ssl_algorithms()	SSL_library_init()
int SSL_state(SSL *ssl);




#ifdef __cplusplus
}
#endif

#endif /* _OPENSSL_H_ */
