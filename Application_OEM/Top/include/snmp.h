/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2011 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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



#ifndef SNMP_H_
#define SNMP_H_

#ifdef __cplusplus
extern "C" {
#endif


#define RONLY	0x01	/* read access for everyone */
#define RWRITE	0x03	/* add write access for community private */

/*Security Level*/
#define SNMP_SEC_LEVEL_NOAUTH		1
#define SNMP_SEC_LEVEL_AUTHNOPRIV	2
#define SNMP_SEC_LEVEL_AUTHPRIV		3

/* defined types (from the SMI, RFC 1157) */
#define IPADDRESS   (ASN_APPLICATION | 0)
#define COUNTER	    (ASN_APPLICATION | 1)
#define GAUGE	    (ASN_APPLICATION | 2)
#define TIMETICKS   (ASN_APPLICATION | 3)
#define OPAQUE	    (ASN_APPLICATION | 4)

/* defined types (from the SMI, RFC ????) */
#define NSAP	    (ASN_APPLICATION | 5)
#define COUNTER64   (ASN_APPLICATION | 6)
#define UINTEGER    (ASN_APPLICATION | 7)

#define SNMP_TRAP_COLDSTART		(0x0)
#define SNMP_TRAP_WARMSTART		(0x1)
#define SNMP_TRAP_LINKDOWN		(0x2)
#define SNMP_TRAP_LINKUP		(0x3)
#define SNMP_TRAP_AUTHFAIL		(0x4)
#define SNMP_TRAP_EGPNEIGHBORLOSS	(0x5)
#define SNMP_TRAP_ENTERPRISESPECIFIC	(0x6)

#define V_3 1

//version access

#define ONE 					1 //access only by snmpv1
#define TWO 					2 //access only by snmpv2c
#define THREE 					3 //access only by snmpv3
#define ONE_TWO 			4 //access only by snmpv1 and snmpv2c
#define ONE_TWO_THREE 5// access by snmpv1, snmpv2c, snmpv3



#define AC_VERSION_1 0x0001
#define AC_VERSION_2 0x0002 
#define AC_VERSION_3 0x0004
#define COMM0_W 		0x0008
#define COMM0_R 	0x0010
#define COMM1_W 		0x0020
#define COMM1_R 	0x0040
#define COMM2_W		0x0080
#define COMM2_R 	0x0100
#define USER0_AC_W  0x0200
#define USER0_AC_R 0x0400
#define USER1_AC_W  0x0800
#define USER1_AC_R 0x1000
#define USER2_AC_W  0x2000
#define USER2_AC_R 0x4000


#define FULL_ACCESS_ALL_VER	AC_VERSION_1|AC_VERSION_2|AC_VERSION_3|COMM0_W|COMM0_R|COMM1_W|COMM1_R|COMM2_W|COMM2_R|USER0_AC_W|USER0_AC_R|USER1_AC_W|USER1_AC_R|USER2_AC_W|USER2_AC_R
#define FULL_ACCESS_V1 					AC_VERSION_1|COMM0_W|COMM0_R|COMM1_W|COMM1_R|COMM2_W|COMM2_R
#define FULL_ACCESS_V2					AC_VERSION_2|COMM0_W|COMM0_R|COMM1_W|COMM1_R|COMM2_W|COMM2_R
#define FULL_ACCESS_V1andV2				AC_VERSION_1|AC_VERSION_2|COMM0_W|COMM0_R|COMM1_W|COMM1_R|COMM2_W|COMM2_R
#define FULL_ACCESS_V3					AC_VERSION_3|USER0_AC_W|USER0_AC_R|USER1_AC_W|USER1_AC_R|USER2_AC_W|USER2_AC_R

/*read access to the variable for the first community of the SNMPv1*/
#define ACCESS_V1_COMM0_R			AC_VERSION_1|COMM0_R
/*write access to the variable for the first community of the SNMPv1*/
#define ACCESS_V1_COMM0_W			AC_VERSION_1|COMM0_W
/*read and write access to the variable for the first community of the SNMPv1*/
#define ACCESS_V1_COMM0_RW			AC_VERSION_1|COMM0_W|COMM0_R
/*read access to the variable for the second community of the SNMPv1*/
#define ACCESS_V1_COMM1_R			AC_VERSION_1|COMM1_R
/*write access to the variable for the second community of the SNMPv1*/
#define ACCESS_V1_COMM1_W			AC_VERSION_1|COMM1_W
/*read and write access to the variable for the second community of the SNMPv1*/
#define ACCESS_V1_COMM1_RW			AC_VERSION_1|COMM1_W|COMM1_R
/*read access to the variable for the third community of the SNMPv1*/
#define ACCESS_V1_COMM2_R			AC_VERSION_1|COMM2_R
/*write access to the variable for the third community of the SNMPv1*/
#define ACCESS_V1_COMM2_W			AC_VERSION_1|COMM2_W
/*read and write access to the variable for the third community of the SNMPv1*/
#define ACCESS_V1_COMM2_RW			AC_VERSION_1|COMM2_W|COMM2_R

/*read access to the variable for the first community of the SNMPv2c*/
#define ACCESS_V2_COMM0_R			AC_VERSION_2|COMM0_R
/*write access to the variable for the first community of the SNMPv2c*/
#define ACCESS_V2_COMM0_W			AC_VERSION_2|COMM0_W
/*read and write access to the variable for the first community of the SNMPv2c*/
#define ACCESS_V2_COMM0_RW			AC_VERSION_2|COMM0_W|COMM0_R
/*read access to the variable for the second community of the SNMPv2c*/
#define ACCESS_V2_COMM1_R			AC_VERSION_2|COMM1_R
/*write access to the variable for the second community of the SNMPv2c*/
#define ACCESS_V2_COMM1_W			AC_VERSION_2|COMM1_W
/*read and write access to the variable for the second community of the SNMPv2c*/
#define ACCESS_V2_COMM1_RW			AC_VERSION_2|COMM1_W|COMM1_R
/*read access to the variable for the third community of the SNMPv2c*/
#define ACCESS_V2_COMM2_R			AC_VERSION_2|COMM2_R
/*write access to the variable for the third community of the SNMPv2c*/
#define ACCESS_V2_COMM2_W			AC_VERSION_2|COMM2_W
/*read and write access to the variable for the third community of the SNMPv2c*/
#define ACCESS_V2_COMM2_RW			AC_VERSION_2|COMM2_W|COMM2_R

/*read access to the variable for the first user of the SNMPv3*/
#define ACCESS_V3_USER0_R				AC_VERSION_3|USER0_AC_R
/*write access to the variable for the first user of the SNMPv3*/
#define ACCESS_V3_USER0_W				AC_VERSION_3|USER0_AC_W
/*read and write access to the variable for the first user of the SNMPv3*/
#define ACCESS_V3_USER0_RW			AC_VERSION_3|USER0_AC_W|USER0_AC_R
/*read access to the variable for the second user of the SNMPv3*/
#define ACCESS_V3_USER1_R				AC_VERSION_3|USER1_AC_R
/*write access to the variable for the second user of the SNMPv3*/
#define ACCESS_V3_USER1_W				AC_VERSION_3|USER1_AC_W
/*read and write access to the variable for the second user of the SNMPv3*/
#define ACCESS_V3_USER1_RW			AC_VERSION_3|USER1_AC_W|USER1_AC_R
/*read access to the variable for the third user of the SNMPv3*/
#define ACCESS_V3_USER2_R				AC_VERSION_3|USER2_AC_R
/*write access to the variable for the third user of the SNMPv3*/
#define ACCESS_V3_USER2_W				AC_VERSION_3|USER2_AC_W
/*read and write access to the variable for the third user of the SNMPv3*/
#define ACCESS_V3_USER2_RW			AC_VERSION_3|USER2_AC_W|USER2_AC_R


#define SNMPD_DES 1
#define SNMPD_AES 2

#define SNMPD_MD5 1
#define SNMPD_SHA 2

#define MAX_USERS 3
#define NUM_COMMUNITIES 3
#define GROUP_ALL_SYS_MIB 		7
#define GROUP_SYSTEM_MIB 		0 
#define GROUP_INTERFACE_MIB 	1
#define GROUP_IP_MIB 				2
#define GROUP_ICMP_MIB			3
#define GROUP_TCP_MIB				4
#define GROUP_UDP_MIB				5
#define GROUP_STATSNMP_MIB	6

#define UNACTIVE_OBJ 0
#define ACTIVE_OBJ 1

#define UNACTIVE_VERSION_1_2C 0
#define ACTIVE_VERSION_1 1
#define ACTIVE_VERSION_2C 2
#define ACTIVE_VERSION_1_2C 3

typedef u_short	oid;

	struct snmpd_user {
		char *login; //max login len  - 32
		char secLevel; 
		char *auth_pass;// max  auth_pass - 32
		char auth_prot;
		char *encrypt_pass;// max encrypt_pass - 32
		char encrypt_prot;
		int active;
		u_char *reload_auth_key;
		u_char *reload_encrypt_key;
		
		/* will filled by snmp agent */
		oid            *authProtocol;
        size_t          authProtocolLen;
        u_char         *authKey;
        size_t          authKeyLen;
        oid            *privProtocol;
        size_t          privProtocolLen;
        u_char         *privKey;
        size_t          privKeyLen;

	};
	
	struct community{
		char *read_community; //max read_community - 32
		char *write_community;//max write_community - 32
		int active;
	};


struct snmpd_settings
{
	const struct variable *oid_table;
	const struct variable *oid_table_trap;
	
	char 	agent_ip_ver;		// 4 for ipv4, 6 for ipv6
	char 	*trap_community;
	
	char 	*sys_trap_ip;
	uint_16 sys_trap_port;
	char 	sys_trap_enable;
	char 	sys_trap_ver;
	char 	sys_trap_ip_ver;	//default for internal(system) trap
	char 	*our_ip;
	oid 	*entrp;
	int 	entrp_len;
	
	struct community com[3];
	u_short sys_mib_access_level[7];
	
#if V_3 > 0
	char	*engine_id_data; // max engine_id_data -  32
	struct snmpd_user user[3];
#endif

	char 	*contact;
	char 	*name;
	char 	*location;
		
};

struct snmpd_new_param {
	
	int_8 num_community;
	int_8 active_com;
	char 	*read_community;
	char 	*write_community;
	char 	*trap_community;
	int_8 number_user_v3;
	int_8 active_user;
	char *login;
	char secLevel;
	char* auth_pass;
	char auth_prot;
	char *encrypt_pass;
	char encrypt_prot;
	
};	


void snmpd_main(struct snmpd_settings *snmpd_init);

//typedef u_long	oid;
//#define MAX_SUBID   0xFFFFFFFF

#define MAX_SUBID   0xFFFF


#define MAX_OID_LEN	    128	/* max subid's in an oid */

#define ASN_BOOLEAN	    (0x01)
#define ASN_INTEGER	    (0x02)
#define ASN_BIT_STR	    (0x03)
#define ASN_OCTET_STR	    (0x04)
#define ASN_NULL	    (0x05)
#define ASN_OBJECT_ID	    (0x06)
#define ASN_SEQUENCE	    (0x10)
#define ASN_SET		    (0x11)

#define ASN_UNIVERSAL	    (0x00)
#define ASN_APPLICATION     (0x40)
#define ASN_CONTEXT	    (0x80)
#define ASN_PRIVATE	    (0xC0)

#define ASN_PRIMITIVE	    (0x00)
#define ASN_CONSTRUCTOR	    (0x20)

#define ASN_IPADDRESS   (ASN_APPLICATION | 0)
#define ASN_UNSIGNED    (ASN_APPLICATION | 2)   /* RFC 1902 - same as GAUGE */
#define ASN_TIMETICKS   (ASN_APPLICATION | 3)

#define ASN_LONG_LEN	    (0x80)
#define ASN_EXTENSION_ID    (0x1F)
#define ASN_BIT8	    (0x80)

#define IS_CONSTRUCTOR(byte)	((byte) & ASN_CONSTRUCTOR)
#define IS_EXTENSION_ID(byte)	(((byte) & ASN_EXTENSION_ID) == ASN_EXTENSION_ID)

struct counter64 {
    u_long high;
    u_long low;
};
/*
    * Error codes (the value of the field error-status in PDUs)
    */

   /*
    * in SNMPv1, SNMPsec, SNMPv2p, SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 PDUs
    */
#define SNMP_ERR_NOERROR                (0)     /* XXX  Used only for PDUs? */
#define SNMP_ERR_TOOBIG	                (1)
#define SNMP_ERR_NOSUCHNAME             (2)
#define SNMP_ERR_BADVALUE               (3)
#define SNMP_ERR_READONLY               (4)
#define SNMP_ERR_GENERR	                (5)

   /*
    * in SNMPv2p, SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 PDUs
    */
#define SNMP_ERR_NOACCESS		(6)
#define SNMP_ERR_WRONGTYPE		(7)
#define SNMP_ERR_WRONGLENGTH		(8)
#define SNMP_ERR_WRONGENCODING		(9)
#define SNMP_ERR_WRONGVALUE		(10)
#define SNMP_ERR_NOCREATION		(11)
#define SNMP_ERR_INCONSISTENTVALUE	(12)
#define SNMP_ERR_RESOURCEUNAVAILABLE	(13)
#define SNMP_ERR_COMMITFAILED		(14)
#define SNMP_ERR_UNDOFAILED		(15)
#define SNMP_ERR_AUTHORIZATIONERROR	(16)
#define SNMP_ERR_NOTWRITABLE		(17)


/**
 * @internal
 * asn_parse_int - pulls a long out of an int type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data       IN - pointer to start of object
 * @param datalength IN/OUT - number of valid bytes left in buffer
 * @param type       OUT - asn type of object
 * @param intp       IN/OUT - pointer to start of output buffer
 * @param intsize    IN - size of output buffer
 *
 * @return pointer to the first byte past the end
 *   of this object (i.e. the start of the next object) Returns NULL on any error
 */
u_char	*
asn_parse_int(u_char *data, int *datalength, u_char *type, long *intp, int intsize);


/**
 * @internal
 * asn_build_int - builds an ASN object containing an integer.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 *
 * @param data         IN - pointer to start of output buffer
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN  - asn type of objec
 * @param intp         IN - pointer to start of long integer
 * @param intsize      IN - size of input buffer
 *
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char	*
asn_build_int(u_char *data, int *datalength, u_char type, long *intp, int intsize);


/**
 * @internal
 * asn_parse_unsigned_int - pulls an unsigned long out of an ASN int type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data       IN - pointer to start of object
 * @param datalength IN/OUT - number of valid bytes left in buffer
 * @param type       OUT - asn type of object
 * @param intp       IN/OUT - pointer to start of output buffer
 * @param intsize    IN - size of output buffer
 *
 * @return pointer to the first byte past the end
 *   of this object (i.e. the start of the next object) Returns NULL on any error
 */
u_char	*
asn_parse_unsigned_int(u_char *data, int *datalength, u_char *type, u_long *intp ,int intsize);

/**
 * @internal
 * asn_build_unsigned_int - builds an ASN object containing an integer.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 *
 * @param data         IN - pointer to start of output buffer
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN  - asn type of objec
 * @param intp         IN - pointer to start of long integer
 * @param intsize      IN - size of input buffer
 *
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char	*
asn_build_unsigned_int(u_char *data, int *datalength, u_char type, u_long *intp, int intsize);


/**
 * @internal
 * asn_parse_string - pulls an octet string out of an ASN octet string type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  "string" is filled with the octet string.
 * ASN.1 octet string   ::=      primstring | cmpdstring
 * primstring           ::= 0x04 asnlength byte {byte}*
 * cmpdstring           ::= 0x24 asnlength string {string}*
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data        IN - pointer to start of object
 * @param datalength  IN/OUT - number of valid bytes left in buffer
 * @param type        OUT - asn type of object
 * @param string      IN/OUT - pointer to start of output buffer
 * @param strlength   IN/OUT - size of output buffer
 *
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char	*
asn_parse_string(u_char *data, int *datalength, u_char *type, u_char *string, int *strlength);


/**
 * @internal
 * asn_build_string - Builds an ASN octet string object containing the input string.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @param string       IN - pointer to start of input buffer
 * @param strlength    IN - size of input buffer
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char	*
asn_build_string(u_char *data, int *datalength, u_char type, u_char *string, int strlength);


/**
 * @internal
 * asn_parse_header - interprets the ID and length of the current object.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   in this object following the id and length.
 *
 *  Returns a pointer to the first byte of the contents of this object.
 *  Returns NULL on any error.
 *
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         OUT - asn type of object
 * @return  Returns a pointer to the first byte of the contents of this object.
 *          Returns NULL on any error.
 *
 */
u_char	*
asn_parse_header(u_char *data, int *datalength, u_char *type);


/**
 * @internal
 * asn_build_header - builds an ASN header for an object with the ID and
 * length specified.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   in this object following the id and length.
 *
 *  This only works on data types < 30, i.e. no extension octets.
 *  The maximum length is 0xFFFF;
 *
 *  Returns a pointer to the first byte of the contents of this object.
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @param length       IN - length of object
 * @return Returns a pointer to the first byte of the contents of this object.
 *          Returns NULL on any error.
 */
u_char	*
asn_build_header(u_char *data, int *datalength, u_char type, int length);


/**
 * @internal
 * asn_build_sequence - builds an ASN header for a sequence with the ID and
 *
 * length specified.
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   in this object following the id and length.
 *
 *  This only works on data types < 30, i.e. no extension octets.
 *  The maximum length is 0xFFFF;
 *
 *  Returns a pointer to the first byte of the contents of this object.
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @param length       IN - length of object
 *
 * @return Returns a pointer to the first byte of the contents of this object.
 *         Returns NULL on any error.
 */

u_char	*
asn_build_sequence(u_char *data, int *datalength, u_char type, int length);


/**
 * @internal
 * asn_parse_length - interprets the length of the current object.
 *
 *  On exit, length contains the value of this length field.
 *
 *  Returns a pointer to the first byte after this length
 *  field (aka: the start of the data field).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of length field
 * @param length       OUT - value of length field
 *
 *  @return Returns a pointer to the first byte after this length
 *          field (aka: the start of the data field).
 *          Returns NULL on any error.
 */

u_char	*
asn_parse_length(u_char *data, u_long *length);


/**
 * @internal
 * asn_build_length - builds an ASN header for a length with
 * length specified.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   in this object following the length.
 *
 *
 *  Returns a pointer to the first byte of the contents of this object.
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param length       IN - length of object
 *
 * @return Returns a pointer to the first byte of the contents of this object.
 *         Returns NULL on any error.
 */
u_char	*
asn_build_length(u_char *data, int *datalength, int length);


/**
 * @internal
 * asn_parse_objid - pulls an object indentifier out of an ASN object identifier type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  "objid" is filled with the object identifier.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         OUT - asn type of object
 * @param objid        IN/OUT - pointer to start of output buffer
 * @param objidlength  IN/OUT - number of sub-id's in objid
 *
 *  @return Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 */
u_char	*
asn_parse_objid(u_char *data, int *datalength, u_char *type, oid *objid, int *objidlength);


/**
 * @internal
 * asn_build_objid - Builds an ASN object identifier object containing the
 * input string.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @param objid        IN - pointer to start of input buffer
 * @param objidlength  IN - number of sub-id's in objid
 *
 * @return   Returns a pointer to the first byte past the end
 *           of this object (i.e. the start of the next object).
 *           Returns NULL on any error.
 */
u_char	*
asn_build_objid(u_char *data, int *datalength, u_char type, oid *objid, int objidlength);

/**
 * @internal
 * asn_parse_null - Interprets an ASN null type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         OUT - asn type of object
 *  @return Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char	*
asn_parse_null(u_char *data, int *datalength, u_char *type);


/**
 * @internal
 * asn_build_null - Builds an ASN null object.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @retun  Returns a pointer to the first byte past the end
 *         of this object (i.e. the start of the next object).
 *         Returns NULL on any error.
 *
 */
u_char	*
asn_build_null(u_char *data, int *datalength, u_char type);


/**
 * @internal
 * asn_parse_bitstring - pulls a bitstring out of an ASN bitstring type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  "string" is filled with the bit string.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         OUT - asn type of object
 * @param string       IN/OUT - pointer to start of output buffer
 * @param strlength    IN/OUT - size of output buffer
 * @return Returns a pointer to the first byte past the end
 *         of this object (i.e. the start of the next object).
 *         Returns NULL on any error.
 */
u_char	*
asn_parse_bitstring(u_char *data, int *datalength, u_char *type, u_char *string, int *strlength);


/**
 * @internal
 * asn_build_bitstring - Builds an ASN bit string object containing the
 * input string.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the beginning of the next object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN - asn type of object
 * @param string       IN - pointer to start of input buffer
 * @param strlength    IN - size of input buffer
 * @return Returns a pointer to the first byte past the end
 *         of this object (i.e. the start of the next object).
 *         Returns NULL on any error.
 */
u_char	*
asn_build_bitstring(u_char *data, int *datalength, u_char type, u_char *string, int strlength);


/**
 * @internal
 * asn_parse_unsigned_int64 - pulls a 64 bit unsigned long out of an ASN int
 * type.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of object
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         OUT - asn type of object
 * @param cp           IN/OUT - pointer to counter struct
 * @param countersize  IN - size of output buffer
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char  *
asn_parse_unsigned_int64(u_char *data, int *datalength, u_char *type, struct counter64 *cp, int countersize);



/**
 * @internal
 * asn_build_unsigned_int64 - builds an ASN object containing a 64 bit integer.
 *
 *  On entry, datalength is input as the number of valid bytes following
 *   "data".  On exit, it is returned as the number of valid bytes
 *   following the end of this object.
 *
 *  Returns a pointer to the first byte past the end
 *   of this object (i.e. the start of the next object).
 *  Returns NULL on any error.
 *
 * @param data         IN - pointer to start of output buffer
 * @param datalength   IN/OUT - number of valid bytes left in buffer
 * @param type         IN  - asn type of object
 * @param cp           IN - pointer to counter struct
 * @param countersize  IN - size of input buffer
 * @return  Returns a pointer to the first byte past the end
 *          of this object (i.e. the start of the next object).
 *          Returns NULL on any error.
 */
u_char  *
asn_build_unsigned_int64(u_char *data, int *datalength, u_char type, struct counter64 *cp, int countersize);


// snmp_oid_compare  return 0	if both strings are equal
int snmp_oid_compare(const oid *,int ,const oid *,int );

/*
  * Function pointer called by the master agent for writes.
  */
typedef int     (WriteMethod) (int action,
							   u_char * var_val,
							   u_char var_val_type,
							   int var_val_len,
							   u_char * statP,
							   u_long * name,
							   int length);



/*
 * Function pointer called by the master agent for mib information retrieval
 */
typedef u_char *(FindVarMethod) (struct variable * vp,
								 oid * name,
								 int * length,
								 int exact,
								 int * var_len,
								 WriteMethod ** write_method);

struct variable {
	u_char	    magic;	    	/* passed to function as a hint */
	char	    type;	    	/* type of variable, INTEGER or (octet) STRING */
	u_char	    acl;	    	/* access control list for variable */
	FindVarMethod  *findVar;        /* function that finds variable */
    u_char	    namelen;	    /* length of above */
    oid		name[26];	    /* object identifier of variable */
	oid 		access_level; 
};
/*
 *      Each variable name is placed in the variable table, without the
 * terminating substring that determines the instance of the variable.  When
 * a string is found that is lexicographicly preceded by the input string,
 * the function for that entry is called to find the method of access of the
 * instance of the named variable.  If that variable is not found, NULL is
 * returned, and the search through the table continues (it will probably
 * stop at the next entry).  If it is found, the function returns a character
 * pointer and a length or a function pointer.  The former is the address
 * of the operand, the latter is a write routine for the variable.
 *
 * u_char *
 * findVar(name, length, exact, var_len, write_method)
 * oid      *name;          IN/OUT - input name requested, output name found
 * int      length;         IN/OUT - number of sub-ids in the in and out oid's
 * int      exact;          IN - TRUE if an exact match was requested.
 * int      len;            OUT - length of variable or 0 if function returned.
 * int      write_method;   OUT - pointer to function to set variable,
 *                                otherwise 0
 *
 *     The writeVar function is returned to handle row addition or complex
 * writes that require boundary checking or executing an action.
 *
 * writeVar(action, var_val, var_val_type, var_val_len, statP, name, name_len)
 * int      action;         IN - COMMIT or RESERVE
 * u_char   *var_val;       IN - input or output buffer space
 * u_char   var_val_type;   IN - type of input buffer
 * int      var_val_len;    IN - input and output buffer len
 * u_char   *statP;         IN - pointer to local statistic
 * oid      *name           IN - pointer to name requested
 * int      name_len        IN - number of sub-ids in the name
 */

 /*
 In the case of a set request,
 * if action is RESERVE, the value is just checked for correct type and
 * value, and resources may need to be reserved.  If the action is COMMIT,
 * the variable is set.  
 * If any error occurs, an error code is returned.
 */
 
 typedef struct {
	oid *name;
	uint_8 name_len;

}_trap_bind;

int _send_traps(char _ip_version, char _trap_version, char trap_type);


int snmpd_send_trap(char ip_ver, char trap_ver, char trap_type,
						char* dst_ip, int_16 dst_port,
						 _trap_bind *trap_bind, int_8 trap_bind_cnt,
						oid* enterprise_id, int enterprise_id_len,
						char specific_trap_code,  int_8  snmpv3_user_number);
											
int snmpd_change_user_config(struct snmpd_new_param *reconfig);
int snmpd_ready();
int snmpd_get_auth_key(int user, u_char**key, int *len);
int snmpd_get_encrypt_key(int user, u_char**key, int *len);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* SNMP_H_ */
