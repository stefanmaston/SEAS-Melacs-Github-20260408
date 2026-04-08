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

#ifndef __iorqst_h__
#define __iorqst_h__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *
 *	STANDARD I/O REQUESTS
 *
 ************************************************************************/

struct STD_RQST 
{
	uint_16		MSG_SIZE;
	int_16		MSG_TYPE;
};

struct STD_RPLY 
{
	uint_16		MSG_SIZE;
	uint_16		MSG_padding;
	int 		RESULT;
};

struct OPEN_RQST 
{
	uint_16	OP_MSGSIZE;	/* size of this structure */
	uint_16	OP_MSGTYPE;	/* equal to IO_OPEN */
	NetAddr OP_NAME;	/* the balance of the open name (after :)*/
	uint_16	OP_NAMELEN;	/* Added length str after : */
	uint_16	OP_padding;	
	uint	OP_FLAGS;	/* O_READ,O_WRITE, etc */
	uint_32	OP_MODE;	/* 3rd arg in open */
	uint_32	OP_MINALLOC;	/* 4th arg in open */
};

struct OPEN_RPLY 
{		
	uint_16	OPR_MSGSIZE;	/* size of this structure */
	uint_16	OP_padding;	
	int	OPR_STATUS;	/* Status of request (EOK, ENOMEM, etc)*/
	uint	OPR_HANDLE;	/* Server handle on rqst - not interpreted*/
	uint	OPR_BLOCKSIZE;	/* Max Stdio rqst */
	uint_16	OPR_READPORT;	/* port that should be used for reads */
	uint_16 OPR_WRITEPORT;	/* port that should be used for writes */
	uint_32	OPR_SERVER;	/* Task Id of server to use for cnx */
};

struct CLOSE_RQST 
{
	uint_16	CL_MSGSIZE;	/* size of this structure */
	uint_16	CL_MSGTYPE;	/* equal to IO_CLOSE */
	uint	CL_HANDLE;	/* Server handle on cnx-only used by server */
};

struct RDWR_RQST 
{
	uint_16	RW_MSGSIZE;	/* size of this structure */
	uint_16	RW_MSGTYPE;	/* equal to IO_READ/IO_WRITE */
	NetAddr RW_BUFFER;	/* ptr to buffer to send/receive */
	size_t	RW_BUFSIZ;	/* max. amount of data to send/receive */
	uint	RW_HANDLE;	/* server handle - only used by server */
};

struct RDWR_RPLY 
{
	uint_16	RWR_MSGSIZE;	/* size of this structure */
	uint_16	RWR_padding;	
	int	RWR_STATUS;	/* Status of rqst (E_OK, E_BAD_UCB, etc)*/
	size_t	RWR_BUFSIZ;	/* actual amount of data read/written */
};

struct IOCTL_RQST 
{
	uint_16	IOC_MSGSIZE;	/* size of this request */
	uint_16	IOC_MSGTYPE;	/* equal to IO_IOCTL */
	uint	IOC_HANDLE;	/* server handle - used only by server */
	uint_32 IOC_REQUEST;	
	NetAddr IOC_ARG;	/* ptr to arg. passed in ioctl call */
	uint_32 IOC_UCB_NUM; 	/* the integer number of the ucb */
};

struct SDESTROY_RQST 
{
	uint_16	SD_MSGSIZE;
	uint_16	SD_MSGTYPE;
};

struct ERR_RPLY 
{
	uint_16	ERR_MSGSIZE;
	uint_16	ERR_padding;
	int		ERR_STATUS;
};

/************************************************************************
 *
 *	TCP/IP REQUESTS
 ************************************************************************/

struct SOCKET_RQST 
{
	uint_16	SO_MSGSIZE;
	uint_16	SO_MSGTYPE;
	int	SO_ADDRFORMAT;
	int	SO_RQST_TYPE;
	int	SO_RQST_PROTOCOL;
};
	
struct BIND_RQST 
{
	uint_16	BI_MSGSIZE;
	uint_16	BI_MSGTYPE;
	uint	BI_HANDLE;
	NetAddr	BI_ADDR;
	int	BI_ADDRLEN;
};

struct SEND_RQST 
{
	uint_16		SND_MSGSIZE;
	uint_16		SND_MSGTYPE;
	uint		SND_HANDLE;
	NetAddr		SND_IOVEC;
	uint		SND_IOVCNT;
	uint		SND_FLAGS;
	NetAddr		SND_ADDR;
	uint		SND_ADDRLEN;
};

struct RECV_RQST 
{
	uint_16		RCV_MSGSIZE;
	uint_16		RCV_MSGTYPE;
	uint		RCV_HANDLE;
	NetAddr		RCV_IOVEC;
	uint		RCV_IOVCNT;
	uint		RCV_FLAGS;
	NetAddr		RCV_ADDR;
	NetAddr		RCV_ADDRLEN;
};

struct SENDRECV_RQST 
{
	uint_16		SR_MSGSIZE;
	uint_16		SR_MSGTYPE;
	uint		SR_HANDLE;
	NetAddr		SR_BUFFER;
	unsigned	SR_BUFLEN;
	int		SR_FLAGS;
	NetAddr		SR_ADDR;
	int		SR_ADDRLEN;
};

struct CONNECT_RQST 
{
	uint_16	CO_MSGSIZE;
	uint_16	CO_MSGTYPE;
	uint	CO_HANDLE;
	NetAddr	CO_ADDR;
	int	CO_ADDRLEN;
};

struct ACCEPT_RQST 
{
	uint_16	AC_MSGSIZE;
	uint_16	AC_MSGTYPE;
	uint	AC_HANDLE;
	NetAddr	AC_ADDR;
	NetAddr	AC_ADDRLEN;
};

struct	ACCEPT_RPLY 
{
	uint_16	AC_MSGSIZE;
	uint_16	AC_padding;
	int	AC_STATUS;
	uint	AC_HANDLE;
	uint	AC_BLOCKSIZE;
	uint_16	AC_READPORT;
	uint_16 AC_WRITEPORT;
	pid_t	AC_SERVER;
};

struct GETSOCKNAME_RQST 
{
	uint_16	SN_MSGSIZE;
	uint_16	SN_MSGTYPE;
	uint	SN_HANDLE;
	NetAddr	SN_ADDR;
	NetAddr	SN_ADDRLEN;
};

struct GETPEERNAME_RQST 
{
	uint_16	SN_MSGSIZE;
	uint_16	SN_MSGTYPE;
	uint	SN_HANDLE;
	NetAddr	SN_ADDR;
	NetAddr	SN_ADDRLEN;
};

struct GETSOCKOPT_RQST 
{
	uint_16	GSO_MSGSIZE;
	uint_16	GSO_MSGTYPE;
	uint	GSO_HANDLE;
	int		GSO_LEVEL;
	int		GSO_OPTNAME;
	NetAddr	GSO_OPTVAL;
	NetAddr	GSO_OPTLEN;
};

struct SETSOCKOPT_RQST 
{
	uint_16	SSO_MSGSIZE;
	uint_16	SSO_MSGTYPE;
	uint	SSO_HANDLE;
	uint	SSO_LEVEL;
	uint	SSO_OPTNAME;
	NetAddr	SSO_OPTVAL;
	uint	SSO_OPTLEN;
};

struct LISTEN_RQST 
{
	uint_16	LI_MSGSIZE;
	uint_16	LI_MSGTYPE;
	uint	LI_HANDLE;
	int	LI_BACKLOG;
};

struct SHUTDOWN_RQST 
{
	uint_16	SH_MSGSIZE;
	uint_16	SH_MSGTYPE;
	uint	SH_HANDLE;
	int	SH_HOW;
};

/* #if 0 */
/************************************************************************
 *
 *	FILE REQUESTS
 *
 ************************************************************************/

struct LSEEK_RQST 
{
	uint_16	LS_MSGSIZE;	/* sizeof this request */
	uint_16	LS_MSGTYPE;	/* IO_LSEEK */
	uint	LS_HANDLE;	/* server handle - used by server only */
	int_32	LS_OFFSET;	/* current offset in stream */
	int	LS_WHENCE;	/* direction to seek */
};

struct LSEEK_RPLY 
{
	uint_16	LSR_MSGSIZE;	/* size of this structure */
	uint_16	LSR_padding;	
	int	LSR_STATUS;	/* Status of Request - E_OK, etc */
	uint_32	LSR_FILEPOS;	/* New offset in stream */
};

struct LINK_RQST 
{
	uint_16	LI_MSGSIZE;
	uint_16	LI_MSGTYPE;
	NetAddr LI_SRCNAME;
	uint_16	LI_SRCLEN;
	uint_16	LI_DSTLEN;
	NetAddr LI_DSTNAME;
};

struct UNLINK_RQST 
{
	uint_16	UL_MSGSIZE;
	uint_16	UL_MSGTYPE;
	NetAddr UL_NAME;
	uint_16	UL_padding;
	uint_16	UL_NAMELEN;
};

struct RENAME_RQST 
{
	uint_16	RN_MSGSIZE;
	uint_16	RN_MSGTYPE;
	NetAddr RN_SRCNAME;
	uint_16	RN_SRCLEN;
	uint_16	RN_DSTLEN;
	NetAddr RN_DSTNAME;
};

struct RMDIR_RQST 
{
	uint_16	RMD_MSGSIZE;
	uint_16	RMD_MSGTYPE;
	NetAddr RMD_NAME;
	uint_16	RMD_padding;
	uint_16	RMD_NAMELEN;
};

struct STAT_RQST 
{
	uint_16	ST_MSGSIZE;
	uint_16	ST_MSGTYPE;
	NetAddr ST_NAME;
	uint_16	ST_NAMELEN;
	uint_16	ST_padding;
	NetAddr ST_BUFFER;
};

struct FSTAT_RQST 
{
	uint_16	FS_MSGSIZE;
	uint_16	FS_MSGTYPE;
	uint	FS_HANDLE;
	NetAddr FS_BUFFER;
};

struct CHMOD_RQST 
{
	uint_16	CM_MSGSIZE;
	uint_16	CM_MSGTYPE;
	NetAddr CM_NAME;
	uint_16	CM_NAMELEN;
	uint_16	CM_padding;
	uint_32	CM_MODE;
};

struct MKDIR_RQST 
{
	uint_16	MKD_MSGSIZE;
	uint_16	MKD_MSGTYPE;
	NetAddr MKD_NAME;
	uint_16	MKD_NAMELEN;
	uint_16	MKD_padding;
	uint_32	MKD_MODE;
};

struct MOUNT_RQST 
{
	uint_16	MT_MSGSIZE;
	uint_16 MT_MSGTYPE;
	NetAddr MT_NAME;
	uint_16	MT_NAMELEN;
	uint_16 MT_DEVNUM;
	uint_32 MT_RWFLAG;
};

struct NFSMOUNT_RQST 
{
	uint_16	NMT_MSGSIZE;
	uint_16 NMT_MSGTYPE;
	uint_32	NMT_IPADDRESS;
	NetAddr	NMT_REMOTENAME;
	NetAddr	NMT_LOCALNAME;
	uint_16	NMT_REMOTENAMELEN;
	uint_16	NMT_LOCALNAMELEN;
	uint_32	NMT_FLAGS;
};

struct UMOUNT_RQST 
{
	uint_16	UMT_MSGSIZE;
	uint_16 UMT_MSGTYPE;
	NetAddr UMT_NAME;
	uint_16	UMT_NAMELEN;
	uint_16	UMT_padding;
};

struct MKFS_RQST 
{
	uint_16 MF_MSGSIZE;
	uint_16 MF_MSGTYPE;
	uint_16 MF_DEVNUM;
	uint_16 MF_NUNODES;
	uint_32 MF_DISKSIZE;
};

struct GETDIRENTS_RQST 
{
	uint_16		GD_MSGSIZE;
	uint_16		GD_MSGTYPE;
	uint		GD_HANDLE;
	NetAddr		GD_BUFFER;
	unsigned	GD_BUFLEN;
	uint_32		GD_FILEPOS; 
};

struct GETDIRENTS_RPLY 
{
	uint_16		GDR_MSGSIZE;
	uint_16		GDR_padding;
	int		GDR_STATUS;
	uint_32		GDR_FILEPOS;
	uint_32		GDR_BUFSIZE;
};

struct ADDFS_RQST
{
	uint_16	FS_MSGSIZE;
	uint_16 FS_MSGTYPE;
	NetAddr FS_DRV;
	NetAddr FS_DEVNO;
};

struct DELFS_RQST
{
	uint_16	FS_MSGSIZE;
	uint_16 FS_MSGTYPE;
	uint_32 FS_DEVNO;
};

/* endif*/
/*
 * Message types that stream I/O servers must be prepared to
 * respond to.
 */
#define IO_OPEN			1
#define IO_CLOSE		2
#define IO_READ			3
#define IO_WRITE		4
#define IO_IOCTL		5
#define	IO_SDESTROY		6

#define IO_SOCKET		10
#define IO_BIND			11
#define IO_RECV			12
#define IO_SEND			13
#define IO_ACCEPT		14
#define IO_CONNECT		15
#define IO_LISTEN		16
#define IO_GETSOCKNAME	17
#define IO_GETPEERNAME	18
#define IO_GETSOCKOPT	19
#define IO_SETSOCKOPT	20
#define IO_SHUTDOWN		21

#define IO_SENDTO       22
#define IO_RECVFROM     23


/* #if 0 */
#define IO_LSEEK		30
#define IO_LINK			31
#define IO_UNLINK		32
#define IO_STAT			33
#define IO_FSTAT		34
#define IO_CHMOD		35
#define IO_SYNC			36
#define IO_MKDIR		37
#define IO_MOUNT		38
#define IO_MKFS			39
#define IO_NFSMOUNT		40
#define IO_GETDIRENTS	41
#define IO_RMDIR		42
#define IO_UMOUNT		43
#define IO_ADDFS		44
#define IO_DELFS		45
#define IO_RENAME		46
/* #endif*/

union SERVER_RQST 
{
	struct STD_RQST			SV_STANDARD;
	struct OPEN_RQST		SV_OPEN;
	struct CLOSE_RQST		SV_CLOSE;
	struct RDWR_RQST		SV_RDWR;
	struct IOCTL_RQST		SV_IOCTL;
	struct SDESTROY_RQST	SV_SDESTROY;

	struct SOCKET_RQST		SV_SOCKET;
	struct BIND_RQST		SV_BIND;
	struct SEND_RQST		SV_SEND;
	struct RECV_RQST		SV_RECV;
	struct ACCEPT_RQST      SV_ACCEPT;
	struct CONNECT_RQST     SV_CONNECT;
	struct GETSOCKNAME_RQST SV_GETSOCKNAME;
	struct GETPEERNAME_RQST SV_GETPEERNAME;
	struct SETSOCKOPT_RQST  SV_SETSOCKOPT;
	struct GETSOCKOPT_RQST  SV_GETSOCKOPT;
	struct LISTEN_RQST      SV_LISTEN;
	struct SHUTDOWN_RQST    SV_SHUTDOWN;


/* #if 0 */
	struct LSEEK_RQST		SV_LSEEK;
	struct LINK_RQST		SV_LINK;
	struct UNLINK_RQST		SV_UNLINK;
	struct STAT_RQST		SV_STAT;
	struct FSTAT_RQST		SV_FSTAT;
	struct CHMOD_RQST		SV_CHMOD;
	struct MKDIR_RQST		SV_MKDIR;
	struct RMDIR_RQST		SV_RMDIR;
	struct MOUNT_RQST		SV_MOUNT;
	struct NFSMOUNT_RQST	SV_NFSMOUNT;
	struct UMOUNT_RQST		SV_UMOUNT;
	struct MKFS_RQST		SV_MKFS;
	struct GETDIRENTS_RQST	SV_GETDIRENTS;

	struct ADDFS_RQST		SV_ADDFS;
	struct DELFS_RQST		SV_DELFS;
	struct RENAME_RQST		SV_RENAME;	
/* #endif*/
};

union SERVER_RPLY 
{
	struct STD_RPLY			SV_STD;
	struct ERR_RPLY			SV_ERR;
	struct OPEN_RPLY		SV_OPEN;
	struct RDWR_RPLY		SV_RDWR;

	struct ACCEPT_RPLY		SV_ACCEPT;

/*#if 0 */
	struct GETDIRENTS_RPLY	SV_GETDIRENTS;
	struct LSEEK_RPLY		SV_LSEEK;
/* #endif */
};

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _iorqst_h_ */
