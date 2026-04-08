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

#ifndef	__USBH_LIB_H__
#define __USBH_LIB_H__

#include <iorqst.h>
#include <device.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#define	USBH_SERVER_PATH	"/dev/usbh"

typedef struct
{
	int	(* disk_initialize)(void);
	int (* disk_status)(void);
	int (* disk_read)(char*, long, char);
	int (* disk_write)(const char*, long, char);
	int (* disk_ioctl)(char, void*);
	void (*disk_timerproc)(void);
	char Dev_n;		//Address of USB device
} tUSB_MSC_params;

typedef struct
{
// bus topolgy info
	unsigned long Bus;		//controller number
	char Lev;				//
	char Parent;			//parent hub address
	char Cnt;				//count connected devices on current bus
	char Dev_n;				//device address
	char Speed;				//device speed
	char Max_ch;			//maximum avaible devices on current controller
//device info
	int Class;
	int Subclass;
	char DefEPsize;
	char Cfgs;
	int pdouctID;
	int VendorID;
	int Rev;
} tUSB_dev_info;

#define IO_USBH_CONTROL_REQ		0xA0
#define IO_USBH_BULK_REQ		0xA1
#define IO_USBH_INTERRUPT_REQ	0xA2
#define IO_USBH_ISOCHRONUS_REQ	0xA3
#define	IO_USBH_SUSPEND_REQ		0xA4	//
#define	IO_USBH_WAKEUP_REQ		0xA5	//

struct USBH_CTRL_RQST{
	uint_16		MSG_SIZE;
	int_16		MSG_TYPE;
	
	uint_8	CoreID;
	uint_8	dev_address;
	
	struct {
		int_8		bmRequestType;
		int_8		bRequest;
		int_16		wValue;
		int_16		wIndex;
		int_16		wLength;
	} usbh_device_request;
	
	uint_8	*data;
};

struct USBH_DATA_RQST{
	uint_16		MSG_SIZE;
	int_16		MSG_TYPE;
	
	uint_8	CoreID;
	uint_8	dev_address;
	uint_8	ep_num;
	uint_8	dir_out;
	
	uint_8	*data;
	uint_16 datasize;
};

struct USBH_SUSPEND_RQST{
	uint_16		MSG_SIZE;
	int_16		MSG_TYPE;
	uint_8		coreID;
};

struct USBH_WAKEUP_RQST{
	uint_16		MSG_SIZE;
	int_16		MSG_TYPE;
	uint_8		coreID;
};

union USBH_RQST{
	struct STD_RQST			SV_STANDARD;
	struct USBH_CTRL_RQST	SV_USBH_CTRL;
	struct USBH_DATA_RQST	SV_USBH_BULK;
	struct USBH_DATA_RQST	SV_USBH_INTERRUPT;
	struct USBH_DATA_RQST	SV_USBH_ISOCHRONUS;
	struct USBH_SUSPEND_RQST SV_USBH_SUSPEND;
	struct USBH_WAKEUP_RQST	SV_USBH_WAKEUP;
};

struct USBH_TRANS_RPLY
{
	uint_16		MSG_SIZE;
	uint_16		MSG_padding;
	int 		RESULT;
};

union USBH_RPLY{
	struct STD_RPLY			SV_STD;
	struct ERR_RPLY			SV_ERR;
	struct USBH_TRANS_RPLY	SV_TRANS;
};


int usbh_server(tUSB_core_conf * config);
int usbh_mount(tUSB_dev_info * dev_info, void * params);
int usbh_umount(int dev_addr, int Bus);

int usbh_add_serial_driver(char coren, char *init, pthread_attr_t *attr);
int usbh_add_msc_driver(void);

int usbh_tty_add_drv(int channum,  void * pdev);
int usbh_tty_del_drv(int channum);

unsigned char usbh_get_dev_cnt(void);
int usbh_get_info(char devnum, tUSB_dev_info * info);
int usbh_get_info_ex(int devaddr, int Bus, tUSB_dev_info * info);

uint_8 usbh_control_trans(uint_8 CoreID, uint_8	address, int_8 bmRequestType, int_8 bRequest, int_16 wValue, int_16 wIndex, int_16 wLength, uint_8 *data);
uint_8 usbh_bulk_trans(uint_8 CoreID, uint_8 address, int_8 ep_num, int_8 dir_out, uint_8 *data, uint_16 datasize);
uint_8 usbh_interrupt_trans(uint_8 CoreID, uint_8 address, int_8 ep_num, int_8 dir_out, uint_8 *data, uint_16 datasize);
uint_8 usbh_isohronus_trans(uint_8 CoreID, uint_8 address, int_8 ep_num, int_8 dir_out, uint_8 *data, uint_16 datasize);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	//__USB_LIB_H__
