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
#ifndef	__USB_H__
#define __USB_H__

#include	<iorqst.h>

#ifdef __cplusplus
extern "C" {
#endif


/***************************************************************/

#define _USB_ROLE_MASK  0x7
#define _USB_HOST       0x1
#define _USB_DEV        0x2

#define _USB_DEF_ROLE_A 0x0
#define _USB_DEF_ROLE_B 0x4

#define _USB_OTG		(_USB_HOST | _USB_DEV)
#define _USB_OTG_A		(_USB_OTG | _USB_DEF_ROLE_A)
#define _USB_OTG_B		(_USB_OTG | _USB_DEF_ROLE_B)

#define	_USB_OTG_ID_PIN_DISABLE	0x20

/***************************************************************/

#define _USB_SPEED_MASK 0x18
#define USB_LS		0x0
#define USB_FS		0x8
#define USB_HS		0x10
#define USB_SS		0x18

/***************************************************************/

#define	_USB_STANDALONE_MASK 0x80
#define _USB_SERVER_MODE	 0x0
#define _USB_STANDALONE_MODE 0x80

typedef enum {
	_USBH_CON_EVT      = 0,		//USB HOST detect connected device to its port
	_USBH_DISCON_EVT   = 1,		//USB HOST detect disconnect device from its port
	_USBH_PWR_EVT      = 2,		//USB HOST detect power failure
	_USBH_VBUS_EVT     = 3,		//USB HOST detect vbus error event (overcurrent)
	_USBH_SUSPEND_EVT  = 4,
	_USBH_RESUME_EVT   = 5,
	_USBD_CON_EVT      = 6,		//USB DEVICE was connected to host
	_USBD_DISCON_EVT   = 7,		//USB DEVICE has been disconnected from host
	_USBD_RESUME_EVT   = 8,
	_USBD_SUSPEND_EVT  = 9,
	_USB_ROLE_HOST_EVT = 10,	//role changed to host
	_USB_ROLE_DEV_EVT  = 11		//role changed to dev
} tUSB_event;

/* user notification messages*/
#define	USB_GENERIC_HDR uint_16 type; \
						uint_8 res;	\
						uint_32 * arg; \
						uint_8 core; \
						uint_8 port; \
						void(*destroy)(void * msg)

struct usb_generic{
	USB_GENERIC_HDR;
};

struct USB_conn{
	USB_GENERIC_HDR;
	uint_8 devno;
};

typedef union {
	struct usb_generic		gen_msg;
	struct USB_conn 		conn_msg;
	struct USB_conn 		disconn_msg;
	struct usb_generic		vbus_msg;
	struct usb_generic		power_msg;
	struct usb_generic		otg_role_change;
	struct usb_generic		resume_msg;
	struct usb_generic		suspend_msg;
} usb_usr_msg;

typedef struct
{
	void *host_param;
	void *dev_param;
} usb_list_param;

typedef struct
{
	void(* usb_callback)(tUSB_event evt, void * param);
	signed char CoreID;
	int mode;
	usb_list_param param;
} tUSB_core_conf;

typedef struct
{
	tUSB_core_conf *core_conf;
	pthread_t (* host)(void *);
	pthread_t (* dev) (void *);
} tUSB_config;

#define USB_CLASS_PER_INTERFACE	0	/* for DeviceClass */
#define USB_CLASS_AUDIO			1
#define USB_CLASS_COMM			2
#define USB_CLASS_HID			3
#define USB_CLASS_PHYSICAL		5
#define USB_CLASS_STILL_IMAGE	6
#define USB_CLASS_PRINTER		7
#define USB_CLASS_MASS_STORAGE	8
#define USB_CLASS_HUB			9
#define USB_CLASS_CDC_DATA		0x0a
#define USB_CLASS_CSCID			0x0b	/* chip+ smart card */
#define USB_CLASS_CONTENT_SEC	0x0d	/* content security */
#define USB_CLASS_VIDEO			0x0e
#define USB_CLASS_HEALTHCARE 	0x0F
#define USB_CLASS_DIAGNOSTIC	0xDC
#define USB_CLASS_WIRELESS_CONTROLLER	0xe0
#define USB_CLASS_MISC			0xef
#define USB_CLASS_APP_SPEC		0xfe
#define USB_CLASS_VENDOR_SPEC	0xff

#define USB_SUBCLASS_VENDOR_SPEC 0xff

#define USB_UART_DEVICE			0x02


int usb_server(tUSB_config * config);

int usbh_start(tUSB_core_conf * core_config);
int usbd_start(tUSB_core_conf * core_config);

int usb_set_role(uint_8 core, uint_8 role);
int usb_get_role(uint_8 core);


#ifdef	_USB_OTG_
	#ifndef _USB_HOST_
		#define	_USB_HOST_
	#endif
	
	#ifndef _USB_DEVICE_
		#define _USB_DEVICE_
	#endif
#endif

#ifdef	_USB_HOST_
	#include "usbh.h"
#endif

#ifdef	_USB_DEVICE_
	#include "usbd.h"
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	//__USB_H__
