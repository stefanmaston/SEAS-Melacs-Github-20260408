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

#ifndef _SSL_STRUCT_H_
#define _SSL_STRUCT_H_

#include <stdint.h>
#include <ssl/crypto.h>
#include <ssl/x509.h>


#define SSL_SESSION_ID_SIZE                     32

#define SSL_RANDOM_SIZE             32
#define SSL_SECRET_SIZE             48
#define SSL_FINISHED_HASH_SIZE      12
#define SSL_RECORD_SIZE             5

#define RT_MAX_PLAIN_LENGTH         16384
#define RT_EXTRA                    1024
#define RT_STATIC                   1500


typedef struct 
{
    uint8_t cipher;
    uint8_t key_size;
    uint8_t iv_size;
    uint8_t key_block_size;
    uint8_t padding_size;
    uint8_t digest_size;
    hmac_func hmac;
    crypt_func encrypt;
    crypt_func decrypt;
} cipher_info_t;


typedef struct 
{
    time_t conn_time;
    uint8_t session_id[SSL_SESSION_ID_SIZE];
    uint8_t master_secret[SSL_SECRET_SIZE];
} SSL_SESSION;

typedef struct
{
    uint8_t *buf;
    int size;
} SSL_CERT;

typedef struct
{
    MD5_CTX md5_ctx;
    SHA1_CTX sha1_ctx;
    uint8_t final_finish_mac[SSL_FINISHED_HASH_SIZE];
    uint8_t *key_block;
    uint8_t master_secret[SSL_SECRET_SIZE];
    uint8_t client_random[SSL_RANDOM_SIZE]; /* client's random sequence */
    uint8_t server_random[SSL_RANDOM_SIZE]; /* server's random sequence */
    uint16_t bm_proc_index;
} DISPOSABLE_CTX;

struct _SSL
{
    uint32_t flag;
    uint16_t need_bytes;
    uint16_t got_bytes;
    uint8_t record_type;
    uint8_t cipher;
    uint8_t sess_id_size;
    uint8_t version;
    uint8_t client_version;
    int16_t next_state;
    int16_t hs_status;
    DISPOSABLE_CTX *dc;         /* temporary data which we'll get rid of soon */
    int client_fd;
    const cipher_info_t *cipher_info;
    void *encrypt_ctx;
    void *decrypt_ctx;
    uint8_t bm_static[RT_STATIC+RT_EXTRA];
    uint8_t *bm_all_data;
    uint8_t *bm_data;
    uint16_t bm_index;
    uint16_t bm_read_index;
    uint16_t bm_read_data;
    struct _SSL *next;                  /* doubly linked list */
    struct _SSL *prev;
    struct _SSL_CTX *ssl_ctx;           /* back reference to a clnt/svr ctx */
#ifndef CONFIG_SSL_SKELETON_MODE
    uint16_t session_index;
    SSL_SESSION *session;
#endif
    X509_CTX *x509_ctx;

    uint8_t session_id[SSL_SESSION_ID_SIZE]; 
    uint8_t client_mac[SHA1_SIZE];  /* for HMAC verification */
    uint8_t server_mac[SHA1_SIZE];  /* for HMAC verification */
    uint8_t read_sequence[8];       /* 64 bit sequence number */
    uint8_t write_sequence[8];      /* 64 bit sequence number */
    uint8_t hmac_header[SSL_RECORD_SIZE];    /* rx hmac */
};

typedef struct _SSL SSL;

struct _SSL_CTX
{
    uint32_t options;
    uint8_t chain_length;
    RSA_CTX *rsa_ctx;
    CA_CERT_CTX *ca_cert_ctx;
    SSL *head;
    SSL *tail;
    SSL_CERT certs[CONFIG_SSL_MAX_CERTS];
#ifndef CONFIG_SSL_SKELETON_MODE
    uint16_t num_sessions;
    SSL_SESSION **ssl_sessions;
#endif
#ifdef CONFIG_SSL_CTX_MUTEXING
    SSL_CTX_MUTEX_TYPE mutex;
#endif
    void *bonus_attr;
};

typedef struct _SSL_CTX SSL_CTX;

#endif /* _SSL_STRUCT_H_ */
