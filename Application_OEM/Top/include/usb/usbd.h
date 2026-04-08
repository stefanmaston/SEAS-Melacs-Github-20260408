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
#ifndef	__USBD_H__
#define __USBD_H__

#include <sys.h>
#include <sys/ioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/
// USB Device Types
/****************************************************************************/
#define USBD_CDC_SERIAL_DEVICE          0x01
#define USBD_CDC_ETHERNET_DEVICE        0x02
#define USBD_MSC_DEVICE                 0x03
#define USBD_HID_MOUSE_DEVICE           0x04
#define USBD_HID_KEYBOARD_DEVICE        0x05
#define USBD_HID_EXT_KEYBOARD_DEVICE    0x06
#define USBD_AUDIO_DEVICE               0x07
#define USBD_AUDIO_CONTROL_DEVICE       0x08



/****************************************************************************/
// USB Device Configuration Attributes
/****************************************************************************/
#define _DEFAULT          (0x01<<7)       // Default Value Bit 7 is set
#define _SELF_POWER       (0x01<<6)       // Self-powered  - Supports if set
#define _REMOTE_WAKEUP    (0x01<<5)       // Remote Wakeup - Supports if set
#define _HNP              (0x01 << 1)     // HNP           - Supports if set
#define _SRP              (0x01)          // SRP           - Supports if set


typedef struct
{
	void                *param;
	char                 type;                // type of interfases
} tUSBD_interface;


typedef struct
{
	tUSBD_interface     *pInterfaces;
	unsigned char        NumInterfaces;       // Number of interfaces for current port
	const char          *pStrConfiguration;   // String Configuration Name
	char                 MaxPower;
	char                 Attributes;

} tUSBD_configuration;


typedef struct
{
	unsigned short       idVendor;            // Vendor ID for the USB product
	unsigned short       idProduct;           // Product ID for the USB product
	unsigned short       bcdDevice;           // Device release number in BCD format
	const char          *pManufacturer;       // Manufacturer string descriptor
	const char          *pProduct;            // Product string descriptor
	const char          *pSerialNumber;       // Serial number string descriptor
	tUSBD_configuration *pConfigurations;     // 
	unsigned char        NumConfigurations;   // Number of configurations for current port
} tUSBD_port_info;





/***************************************************************************************/
/* USB CDC Serial device                                                               */
/***************************************************************************************/
typedef struct
{
	unsigned char        vport_num;
	unsigned short       rx_buf_size; 
	unsigned short       tx_buf_size; 
	char                 ready;
}tUSBD_cdc_serial;

/***************************************************************************************/
/* USB MSC device                                                                      */
/***************************************************************************************/
typedef struct
{
	int_8 (*init) (uchar lun);
	int_8 (*get_capacity)(uchar lun, uint_32 *block_num, uint_32 *block_size);
	int_8 (*is_ready) (uchar lun);
	int_8 (*is_write_protected) (uchar lun);
	int_8 (*read) (uchar lun, uchar *buf, uint_32 blk_addr, uint_16 blk_len);
	int_8 (*write)(uchar lun, uchar *buf, uint_32 blk_addr, uint_16 blk_len);
	int_8 (*get_max_lun)(void);
	int_8 *inquiry_data;
}_usbd_msc_storage;








void usbd_add_serial_driver(void);
void usbd_add_msc_driver(void);
void usbd_add_mouse_driver(void);
void usbd_add_keyboard_driver(void);
void usbd_add_extended_keyboard_driver(void);
void usbd_add_audio_driver(void);
void usbd_add_audio_control_driver(void);


int usbd_get_connect_state(uchar port);
//int usbd_server(_usb_dev_param * config);

/* USB HID Device API functions definition */
int usbd_hid_keyboard_send_keys(char port, unsigned char key, unsigned char press);
int usbd_hid_keyboard_send_keys_extended(char port, unsigned char key, unsigned char press);
int usbd_hid_mouse_send_state(char port, signed char x, signed char y, unsigned char button);

#ifdef __cplusplus
} //extern "C" {
#endif

#endif	//__USBD_H__
