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
#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <sys.h>
#include <mqueue.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CORE_NAME_STR			"root"

#define SPP_NAME_STR			"SPP"
#define DUN_NAME_STR			"DUN"
#define LAN_NAME_STR			"LAN"
#define FTP_NAME_STR			"FTP"
#define OPP_NAME_STR			"OPP"
#define PAN_PANU_NAME_STR		"PAN-PANU"
#define PAN_NAP_NAMME_STR		"PAN-NAP"
#define HFP_NAME_STR			"HFP"
#define HFPGW_NAME_STR			"HFPGW"
#define HSP_NAME_STR			"HSP"
#define HSPGW_NAME_STR			"HSPGW"


#define BT_CONNECT_REQ		0
#define BT_CONNECT_EVT		1
#define BT_DISCONNECT_EVT	2
#define BT_CONNECT_ERR		3
#define BT_PIN_REQ			4
#define BT_KEY_REQ			5
#define BT_KEY_NOT			6
#define BT_KEY_DELETE		7
#define	BT_INQ_COMPLETE	8

#define BT_MAX_NAME_LEN		0x20

typedef int (*bt_user_cacllback)( void *, void *, int);

struct bd_addr {
	unsigned char addr[6];
};

#define BDADDR_LOCAL    (&(struct bd_addr) {{0, 0, 0, 0xff, 0xff, 0xff}})
#define BDADDR_ANY      (&(struct bd_addr) {{0, 0, 0, 0, 0, 0}})
#define BDADDR_ALL      (&(struct bd_addr) {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}})

#define	BTIOCTL		_IOW('b', 6, int)			/*Bluetooth control*/

#define BTRFLUSH 			0				/* flush recive buffer */
#define BTTFLUSH 			1				/* flush transmit buffer*/
#define BTRST 				2				/* bluetooth  module hardware reset*/
#define BTUSPD 				3				/* set bluetooth uart interface speed */
#define BTGETIF 			65				/* get bluetooth hardware interface type*/
#define	BTHW_RAW			66


/* power modes */
#define	BTACTIVE			0
#define	BTSLEEP				1
#define	BTDEEPSLEEP			2


struct BT_STSPEED_st {
	int cmd;
	int speed;
};

#define BTUFLOW 			4				/*set bluetooth uart interface flow control*/
struct BT_STFLOW_st {
	int cmd;
	int flow;
};

#define	BTSDISC				5				/* set local device discoverability mode*/
struct BT_STDISCOVER_st {
	int cmd;
#define DISCOVER_NONE		1
#define DISCOVER_LIMITED	2
#define DISCOVER_GENERAL	3
	int mode;
};

#define	BTSCOD				6				/* set local device COD (ClassOfDevice)*/
struct BT_SCOD_st {
	int cmd;
	int COD;
};

#define	BTGLNAME			9				/* get local name*/
struct BT_GLNAME_st {
	int cmd;
	char * name;
};

#define	BTSNAME				7				/* set local device name*/
struct BT_SNAME_st {
	int cmd;
	char * name;
};

#define	GETLADDR			8				/* get local BD addr*/
struct BT_GETLADDR_st {
	int cmd;
	struct bd_addr * bdaddr;
};

#define	BTSETLADDR			31				/*set local BD addr*/
struct BT_SETLADDR_st {
	int cmd;
	struct bd_addr * bdaddr;
};

#define	BTDISCOVER			10				/* devices discovery */
struct BT_DISCOVER_st {
	int cmd;
	int timeout;
};

#define	BTGPLIST			11				/* get total peers cnt*/
struct BT_GPLIST_st {
	int cmd;
	int peer_cnt;
};

#define	BTGPBDADDR			14				/* get peer BD addr */
struct BT_GPBDADDR_st {
	int cmd;
	int dev_index;
	struct bd_addr * bdaddr;
};

#define	BTGPNAME			12				/* get peer name */
struct BT_GPNAME_st {
	int cmd;
	int dev_index;
	char * name;
};

#define	BTGADDRNAME			13				/* get peer name from BD addr */
struct BT_GADDRNAME_st {
	int cmd;
	struct bd_addr * bdaddr;
	char * name;
};


#define	BTGCOD				15				/* get peer COD (class of device) */
struct BT_GCOD_st {
	int cmd;
	int dev_index;
	int COD;
};

#define	BTSVCDISC			16				/* device service discovery*/
struct BT_SVCDISC_st {
	int cmd;
	int dev_index;
};

#define	BTSVCMDISC			17				/* device service discovery by bdaddr*/
struct BT_SVCMDISC_st {
	int cmd;
	struct bd_addr * bdaddr;
};

#define	BTNSVCCNT			18				/* get device servise cnt*/
struct BT_NSVCCNT_st {
	int cmd;
	int dev_index;
	int service_cnt;
};

#define	BTGETSVCONCNT		19				/* Get connected services count*/
struct BT_GETSVCONCNT_st {
	int cmd;
	int dev_index;
	int service_cnt;
};

#define	BTSVCPROP			20				/* Get service name and port count*/
struct BT_SVCPROP_st {
	int cmd;
	int dev_index;
	int service_index;
	char * name;
	int port_cnt;
};

#define BTGETSVCCONPROP		21				/*Get service propertis*/
struct BT_GETSVCCONPROP_st {
	int cmd;
	int dev_index;
	int service_index;
	char * svc_name;
	char svc_fd;
	char out;
	char svc_ch;
	char * name;
};

#define	BTCONNECT			22				/* connect to peer service*/
struct BT_CONNECT_st {
	int cmd;
	int dev_index;
	char *svc_name;
	int svc_port;
};

#define	BTDISCON			23				/* disconnect form peer service */
struct BT_DISCON_st {
	int cmd;
	char *svc_name;
	int  svc_port;
};

#define	BTDEVRM				24				/* remove selected device with all connected services*/
struct BT_DEVRM_st {
	int cmd;
	int dev_index;
};

#define	BTPAIR				25				/* pair device by num in list*/
struct BT_PAIR_st {
	int cmd;
	int dev_index;
};

#define	BTBDADDRPAIR		26				/* pair device by BD addr*/
struct BT_BDADDRPAIR_st {
	int cmd;
	struct bd_addr * bdaddr;
};

#define	BTGHWVER			27				/* Get Hardware version*/
struct BT_GHWVER_st {
	int cmd;
	char hci_ver;
	short hci_rev;
	char lmp_ver;
	short lmp_subver;
	short manufacturer;
};

#define	BTSSVCNAME			28				/* set local service name*/
struct BT_SSVCNAMEst {
	int cmd;
	char * svc_type;
	int svc_idx;
	char * name;
};

#define	BTSTAT				30				/* stack staticstic */
struct BT_STATst {	
	int cmd;

	uint_32 ACL_pkt_in;
	uint_32 ACL_data_in;
	uint_32 ACL_pkt_out;
	uint_32 ACL_data_out;

	uint_32 SCO_pkt_in;
	uint_32 SCO_data_in;
	uint_32 SCO_pkt_out;
	uint_32 SCO_data_out;

	uint_32	EVT_pkt;
	uint_32 EVT_data;
	uint_32 CMD_pkt;
	uint_32 CMD_data;
};


#define	BTSETPWRMODE		32				/*set power safe mode*/
struct BT_SETPWRMODE_st {
	int cmd;
#define	BT_PWR_ACTIVE		0
#define	BT_PWR_SLEEP		1
#define	BT_PWR_DEEP_SLEEP	2
#define	BT_PWR_OFF			3
	int mode;
	void * param;
};

#define	BTSETSLEEPENA		33				/*set sleep enable*/
struct BT_SETSLEEPENA_st {
	int cmd;
	int ena;
};

#define	BTGETPOWERSTATE		35				/*get current power state*/
struct BT_GETPWRSTATE_st {
	int cmd;
	int ena;
	int state;
	int mode;
};


#define	BTSETSCOROUTING	36
#define	BTGETSCOROUTING	37
struct BT_SCO_ROUTING_st{
	int cmd;
#define	SCO_HCI		0
#define	SCO_PCM 	1
	uint_8	sco_routing;
};


#define	BTWRVOICESETTINGS	38
#define	BTRDVOICESETTINGS	39
struct BT_VOICE_SETTINGS_st{
	int cmd;
	char icf;	//Input Coding
	char idf;	//Input Data Format
	char iss;	//Input Sample Size
	char acf;	//Air Coding Format
	char lbp;	//Linear_PCM_Bit_Pos

};

#define	BRSNDCMD			63				/* send hci command*/
struct BT_SNDCMD_st {
	int cmd;
	short OGF;
	short OCF;
	char * data;
	int data_size;
	char * rsp;
	int rsp_size;
	int timeout_ms;
};

typedef union {
	int cmd;
	struct BT_STSPEED_st 		io_set_speed;
	struct BT_STFLOW_st			io_set_flow;
	struct BT_STDISCOVER_st		io_set_discover;
	struct BT_SCOD_st			io_set_COD;
	struct BT_SNAME_st			io_set_name;
	struct BT_GLNAME_st			io_get_local_name;
	struct BT_GETLADDR_st		io_get_local_addr;
	struct BT_SETLADDR_st		io_set_local_addr;
	struct BT_DISCOVER_st		io_discovery;
	struct BT_SVCDISC_st		io_svc_discover;
	struct BT_SVCMDISC_st		io_svc_addr_discover;
	struct BT_CONNECT_st		io_connect;
	struct BT_DISCON_st			io_disconnect;
	struct BT_DEVRM_st			io_dev_rmv;
	struct BT_PAIR_st			io_pair;
	struct BT_BDADDRPAIR_st		io_addr_pair;
	struct BT_GHWVER_st			io_get_hw_ver;
	struct BT_GPLIST_st			io_get_dev_list;
	struct BT_GPNAME_st			io_get_dev_name;
	struct BT_GADDRNAME_st 		io_get_dev_name_addr;
	struct BT_GPBDADDR_st		io_get_bdaddr;
	struct BT_GCOD_st			io_get_COD;
	struct BT_NSVCCNT_st		io_get_svc_cnt;
	struct BT_SVCPROP_st		io_get_svc_prop;
	struct BT_GETSVCONCNT_st 	io_get_svc_conn_cnt;
	struct BT_GETSVCCONPROP_st 	io_ger_svc_conn_prop;
	struct BT_SSVCNAMEst		io_set_svc_name;
	struct BT_STATst			io_stat;
	struct BT_SNDCMD_st			io_send_cmd;
	struct BT_SETPWRMODE_st		io_set_pwr_mode;
	struct BT_SETSLEEPENA_st 	io_sleep_ena;
	struct BT_GETPWRSTATE_st	io_pwr_state;
	struct BT_SCO_ROUTING_st	io_set_sco_routing;
	struct BT_SCO_ROUTING_st	io_get_sco_routing;
	struct BT_VOICE_SETTINGS_st	io_write_voice_setting;
	struct BT_VOICE_SETTINGS_st	io_read_voice_setting;
}BT_IO_CMD;

/*
 * Ioctl control packet for SET_BT_UART_MODE
 */
#ifdef NO_PARITY
	#undef NO_PARITY
#endif	//NO_PARITY

#ifdef EVEN_PARITY
	#undef EVEN_PARITY
#endif	//EVEN_PARITY

#ifdef ODD_PARITY
	#undef ODD_PARITY
#endif	//ODD_PARITY

#ifdef NO_FLOWCONTROL
	#undef NO_FLOWCONTROL
#endif	//NO_FLOWCONTROL

#ifdef CTS_FLOWCONTROL
	#undef CTS_FLOWCONTROL
#endif	//CTS_FLOWCONTROL
 
struct set_bt_uart {
	uint_8		csize;		/* character size , 5,6,7,8 */
	uint_8		parity;		/* parity */
#define	NO_PARITY	0
#define EVEN_PARITY	1
#define	ODD_PARITY	2
	uint_8 	flow;		/* hardware flow control */
#define	NO_FLOWCONTROL			0
#define	CTS_FLOWCONTROL			1
	uint		speed;		/* set speed, actual number, 9600 */
	uint_8		stop_bits;
	uint_8		bt_int_level;
	uint_16		timeout_write;	// in sec
	uint_16		rx_buf_size;
	uint_16		tx_buf_size;
	int (*read_init_file)(char *data, int size, int * pos, void * arg);
};


struct set_bt_spi {
	uint_8		SPI_mode;		/*SPI mode 0,1,2,3*/
	uint_8		SPI_datasize;	/* 8 or 16 bit mode */
	uint_8		SPI_order;		/* Valid if 16 bit SPI selected.
									SPI_oreder 0 -  LITTLE_ENDIAN
									SPI_oreder 0 -  BIG_ENDIAN*/
	uint		speed;			/* set speed, actual number, 1Mbps */
	uint_16		rx_buf_size;
	int (*read_init_file)(char *data, int size, int * pos, void * arg);
};

typedef union
{
	struct set_bt_uart set_uart;
	struct set_bt_spi  set_spi;
} tSet_bt;

enum ebt_hw
{
	ebt_hw_uart,
	ebt_hw_spi,
} ;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char * svc_name;
	int svc_port;
	char * host_dev_name;		//SPP0, DUN2
	char dir_out;
} tconnect_evt_data;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char * svc_name;
	int svc_port;
	char * host_dev_name;		//SPP0, DUN2
} tdiscon_evt_data;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char * svc_name;
	int svc_port;
} tconn_err_evt;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char pin[10];
} tpin_req_evt;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char key[16];
} tkey_req_evt;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
	char key[16];
	int type;
} tkey_not_evt;

typedef struct
{
	char * name;
	struct bd_addr * bdaddr;
} tkey_delete_evt;

typedef struct
{
	int devnum;
} tinq_compleate_evt;

typedef union
{
	tconnect_evt_data	con_evt;
	tdiscon_evt_data	discon_evt;
	tconn_err_evt		con_err;
	tpin_req_evt		pin_req;
	tkey_req_evt		key_req;
	tkey_not_evt		key_evt;
	tkey_delete_evt		key_delete_evt;
	tinq_compleate_evt	inq_evt;
} tbt_evt;


#define BT_MODE_USER	0x0
#define BT_MODE_GW		0x80

#define HF_FEATURE_EC_ANDOR_NR				0x0001
#define HF_FEATURE_CALL_WAITING_AND_3WAY	0x0002
#define HF_FEATURE_CLI_PRESENTATION			0x0004
#define HF_FEATURE_VOICE_RECOGNITION		0x0008
#define HF_FEATURE_REMOTE_VOLUME_CONTROL	0x0010
#define HF_FEATURE_ENHANCED_CALL_STATUS		0x0020
#define HF_FEATURE_ENHANCED_CALL_CONTROL	0x0040

#define AG_FEATURE_THREE_WAY_CALLING		0x0001
#define AG_FEATURE_EC_ANDOR_NR				0x0002
#define AG_FEATURE_VOICE_RECOGNITION		0x0004
#define AG_FEATURE_INBAND_RINGTONE			0x0008
#define AG_FEATURE_ATTACH_NUMBER_TO_VOICETAG 0x0010
#define AG_FEATURE_REJECT_A_CALL			0x0020
#define AG_FEATURE_ENHANCED_CALL_STATUS		0x0040
#define AG_FEATURE_ENHANCED_CALL_CONTROL	0x0080
#define AG_FEATURE_EXTENDED_ERROR_RESULT_CODES	0x0100

struct set_hfp{
	int futures;
	int flags;
	pthread_t user_thread;
};

#define HFP_GENERIC_HDR uint_16 type; \
						uint_8 ch;	\
						uint_8 res;	\
						void(*destroy)(void * msg)

struct hfp_generic_agw{
	HFP_GENERIC_HDR;
};

struct hfp_conn_agw{
	HFP_GENERIC_HDR;
	struct bd_addr	bdaddr;

};

struct hfp_call{
	HFP_GENERIC_HDR;
	char * number;
};

struct hfp_gain{
	HFP_GENERIC_HDR;
	int gain;
};

struct hfp_key{
	HFP_GENERIC_HDR;
	char * key_str;
};

#define	HFP_MSG_RSP_OK				0
#define	HFP_MSG_RSP_ERR				1

#define	HFP_MSG_SVC_CONNECTED		0x11
#define	HFP_MSG_SVC_DISCONNECTED	0x12
#define	HFP_MSG_INCOMING			0x13
#define	HFP_MSG_ALERTING			0x14
#define	HFP_MSG_CONNECTED			0x16
#define	HFP_MSG_DISCONNECTED		0x17
#define	HFP_CALL_STATUS_WAITING_RSP 0x18
#define	HFP_MSG_DIALING_RSP			0x19
#define	HFP_MSG_CALLSETUP_OUTGOING	0x1A
#define	HFP_CALLSETUP_ALERTING		0x1B
#define	HFP_CALLSETUP_ACTIVE		0x1C
#define	HFP_MSG_ANSWER				0x1D
#define	HFP_VOICE_START				0x1E
#define	HFP_VOICE_STOP				0x1F
#define	HFP_CALL_TRMINATE			0x20
#define	HFP_CALL_RELEASE			0x21
#define	HFP_MIC_GAIN				0x22
#define	HFP_SPK_GAIN				0x23
#define	HFP_KEY_PRESS				0x24
#define	HFP_CALL_HOLD				0x25
#define	HFP_DTMF_TONE				0x26

#define	HFP_LAST_DIAL_NUMBER_REQ	0x29
#define	HFP_DIAL_NUMBER_REQ			0x30
#define	HFP_INCOMING_CALL_REQ		0x31

typedef union {
	char raw[0x20];
	struct hfp_generic_agw		hfp;
	struct hfp_conn_agw 		conn;
	struct hfp_call 			call;
	struct hfp_gain 			gain;
	struct hfp_key				key;
} hfp_msg;


//=================================================================
struct set_hsp{
	short flags;
	pthread_t user_thread;
};


#define	HSP_MSG_RSP_OK				0
#define	HSP_MSG_RSP_ERR				1

#define	HSP_MSG_SVC_CONNECTED		0x11		//HS Servise connected
#define	HSP_MSG_SVC_DISCONNECTED	0x12		//HS Servise disconnected

#define	HSP_MSG_CONNECTED			0x16		//HS audio connection established
#define	HSP_MSG_DISCONNECTED		0x17		//HS audio connection released

#define	HSP_RING					0x18		//

#define	HSP_VOICE_START				0x1E		//Start HS SCO audio channal
#define	HSP_VOICE_STOP				0x1F		//Stop  HS SCO audio channal

#define	HSP_MIC_GAIN				0x22
#define	HSP_SPK_GAIN				0x23

#define	HSP_KEY_PRESS				0x24

typedef union {
	struct hfp_generic_agw	hsp;
	struct hfp_generic_agw	call;
	struct hfp_conn_agw 	conn;
	struct hfp_gain 		gain;
} hsp_msg;


int _bt_server(char *, char , char , void * );
int bt_add_hfp_profile(char * path, char portn, char *init, pthread_attr_t *attr, uint_8 mode);
int bt_add_hsp_profile(char * path, char portn, char *init, pthread_attr_t *attr, uint_8 mode);
int bt_add_spp_profile(char * path, uint_8 portn_in, uint_8 portn_out, char *init_in, char *init_out, pthread_attr_t *attr);

int hfp_snd_msg(hfp_msg * msg);
void hfp_del_msg(hfp_msg * msg);
hfp_msg * hfp_rcv_msg(int mstimeout);

int hsp_snd_msg(hsp_msg * msg);
void hsp_del_msg(hsp_msg * msg);
hsp_msg * hsp_rcv_msg(int mstimeout);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	//__BLUETOOTH_H__
