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

#include "main.h"

#ifdef _USB_
#include <sys.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <usb/usb.h>
#include <usb/usbd.h>
#include "usbd_storage.h"
#include "mutex.h"
#include <p32xxxx.h>
#include "pinDefines.h"




#define RTOS_DEBUG              0

#define USB_DEV_PORT_NUM        0	
									
#define RAW_MODE                1         // 0 use tty server in simple tty discipline
                                          // 1 use tty server in RAW line discipline with flow control

//#define USB_CDC_MULTIPLE        0         // 1 - run multiple usbd cdc serial device, "/dev/usbd/ttyUSB1", "/dev/usbd/ttyUSB2"
                                          // 0 - run one usbd cdc serial device  "/dev/usbd/ttyUSB1"


#define USB_MSC_FUNCTION           1             //0 - Run only the serial port
                                                 //1 - Run Serial port and SD card

extern uint8_t sendTCPBuffer[USB_SEND_BUFFER_SIZE];
extern uint8_t recvTCPBuffer[USB_RECV_BUFFER_SIZE];

//THREAD Main();
void USB_event(tUSB_event evt, void *param);

/*
ConfigTableStruct ConfigTable_ = {
	Main, 1024, 4
};
*/

int recv_size = 0;
int send_size = 0;
int errNumber = 0;

THREAD tty_chanel_1(void *arg);

THREAD USBMain(void *arg)
{
	pthread_t pid;
	pthread_attr_t attr;
	struct sched_param myNewPriority;

	/* USB server structs */
	tUSB_config    usb_config;
	tUSB_core_conf usb_cores[2];
  
	/* USB device structs */
	tUSBD_port_info     usbd_port;
	tUSBD_configuration usbd_config;

#if USB_MSC_FUNCTION == 0
	tUSBD_interface     usbd_interface[1];    
	tUSBD_cdc_serial    usbd_cdc_serial;      
#else  
	tUSBD_interface     usbd_interface[2];        
	tUSBD_cdc_serial    usbd_cdc_serial;       
   _usbd_msc_storage    usbd_msc_storage;    
    
#endif    
    

	#if RTOS_DEBUG
		dir_register("Main thread", pthread_self(), TYPE_THREAD);
	#endif
	xprintf("Start USBMain\n");

	usbd_port.idVendor          = 0x0125;                     // Vendor ID for the USB product
#if USB_MSC_FUNCTION == 1        
	usbd_port.idProduct         = 0xE680;                     // Product ID for the USB product
#else
	usbd_port.idProduct         = 0xE681;                     // Product ID for the USB product
#endif    

	usbd_port.bcdDevice         = 0x0001;                     // Device release number in BCD format
	usbd_port.pManufacturer     = "Inresol";                 // Manufacturer string descriptor
	usbd_port.pProduct          = "Inresol Composite Device";   // Product string descriptor
	usbd_port.pSerialNumber     = "111004";                   // Serial number string descriptor
	usbd_port.pConfigurations   = &usbd_config;               // 
	usbd_port.NumConfigurations = 1;                          // Number of configurations for current port

#if USB_MSC_FUNCTION == 0
	usbd_config.NumInterfaces     = 1;
#else
	usbd_config.NumInterfaces     = 2;    
#endif
    
	usbd_config.pInterfaces       = &usbd_interface[0];
	usbd_config.pStrConfiguration = "CDC MSC Configuration";
	usbd_config.MaxPower          = 0x0;
	usbd_config.Attributes        = _DEFAULT | _SELF_POWER;
    

	/* Setup serial device specific parameters*/
	usbd_cdc_serial.vport_num      = 1;  // ttyUSB1 
	usbd_cdc_serial.rx_buf_size    = 512;
	usbd_cdc_serial.tx_buf_size    = 512;
    
#if USB_MSC_FUNCTION == 1    
    
	usbd_msc_storage.init               = (int_8(*)(uchar))sd_disc_init_;
	usbd_msc_storage.get_capacity       = (int_8(*)(uchar,uint_32 *,uint_32 *))sd_disc_get_capacity_;
	usbd_msc_storage.is_ready           = (int_8(*)(uchar))sd_disc_ready_;
	usbd_msc_storage.is_write_protected = (int_8(*)(uchar))sd_disc_write_protected_;
	usbd_msc_storage.read               = (int_8(*)(uchar,uchar *, uint_32 ,uint_16 ))sd_disc_read_;
	usbd_msc_storage.write              = (int_8(*)(uchar,uchar *, uint_32 ,uint_16 ))sd_disc_write_;
	usbd_msc_storage.get_max_lun        = (int_8(*)(void))sd_disc_get_max_lun_;
	usbd_msc_storage.inquiry_data       = (int_8*)&sd_disc_standart_inquiry_data;    
   
 	usbd_interface[0].type   =  USBD_MSC_DEVICE;
    usbd_interface[0].param  = &usbd_msc_storage;     
    
 	usbd_interface[1].type   =  USBD_CDC_SERIAL_DEVICE;
	usbd_interface[1].param  = &usbd_cdc_serial;        
					
	/* Register msc device driver in USB device server */	
	usbd_add_msc_driver();          

#else
    
 	usbd_interface[0].type   =  USBD_CDC_SERIAL_DEVICE;
	usbd_interface[0].param  = &usbd_cdc_serial;        
    
#endif    
	
	/* Register serial device driver in USB device server*/
	usbd_add_serial_driver();


 	/********************
	Start USB server
	********************/
 	usb_config.core_conf = usb_cores;
	usb_config.host      = NULL;
	usb_config.dev       = (void*)usbd_start;

	usb_cores[0].usb_callback = USB_event;
	usb_cores[0].CoreID       = USB_DEV_PORT_NUM;		//physical USB controller number
	usb_cores[0].mode         = _USB_DEV;
	usb_cores[0].param.dev_param = &usbd_port;

	usb_cores[1].CoreID = -1;

	if (usb_server(&usb_config))
	{
		xprintf("pthread_create = %d\n", errno);
#if RTOS_DEBUG
		dir_deregister("Main thread");
#endif
		pthread_exit(0);
	}

	pthread_attr_init(&attr);
	myNewPriority.sched_priority = 5;
	pthread_attr_setschedparam(&attr, &myNewPriority);
	pthread_attr_setstacksize(&attr,1024);


	if (pthread_create(&pid, &attr, (void*(*)(void*))tty_chanel_1, 0)!= 0) 
	{
		xprintf("pthread_create = %d\n", errno);
		pthread_exit(0);
	}
	
	pthread_attr_destroy (&attr);

    return NULL;
}

int debugNumber = 0;

THREAD tty_chanel_1(void *arg)
{
	//char buf[100];
	int fd;
	int ioctl_arg;
	int n;
    int opt = 1;   
    int error = 0;
    int rc = 0;

	xprintf("Start tty_chanel_1\n");
    
RESTART_USB:

	if((fd = open("/dev/usbd/ttyUSB1", O_RDWR | O_NONBLOCK, 0)) == -1)
	{
		xprintf("open = %d\n", errno);
		pthread_exit(0);
	}
        
#if RAW_MODE == 0          
      	// Enable or disable ECHO	
	ioctl_arg = ECHO;	//NOECHO;     
#else        
  	ioctl_arg = NOECHO;
	ioctl( fd, TIOCSETD, &ioctl_arg);	     
                
  	ioctl_arg = RAWLDISC;
	ioctl( fd, TIOCSETD, &ioctl_arg);	
    
    ioctl(fd, FIONBIO, &opt);    
    
#endif

	while(1)
	{
		if (usbd_get_connect_state(USB_DEV_PORT_NUM))
		{     

			//memset(buf,0,sizeof(buf));
			// 1 -  Host has configured this device.
            bufReadLockMutex();    
            if(usbd_get_connect_state(USB_DEV_PORT_NUM))
            {                  
                LAT_SIP1 = 1;
                n = read(fd, recvTCPBuffer, USB_RECV_BUFFER_SIZE); 
                LAT_SIP1 = 0;
            }
            bufReadUnlockMutex();     
            recv_size = n;            
			if(n == -1)
			{  
                usleep(200000);
                errNumber = errno;         
				switch(errNumber)
                {
                    case ENODEV:
                        xprintf("Device disconnected\n");
                        continue;
                    case EAGAIN:	
                        xprintf("No data available yet\n");
                        continue;
                    default:
                    xprintf("error read = %d\n", errno);
                        continue;
                }
			}
                       
			xprintf("ttyUSB1 Read=%d bytes %s",n,recvTCPBuffer);

            bufWriteLockMutex();  
            if(usbd_get_connect_state(USB_DEV_PORT_NUM))
            {
                LAT_SIP0 = 1;                      
                n = write(fd, sendTCPBuffer, USB_SEND_BUFFER_SIZE); 
                LAT_SIP0 = 0;                   
            }
            bufWriteUnlockMutex();            
            send_size = n;               
			if(n == -1)
			{
				xprintf("write error(%d)\n", errno);
				continue; 
			}
            
            //write(fd, "charlie", 7);
			xprintf("ttyUSB1 write (%d) bytes\n", n);           
            usleep(200000);
		}
		else
		{
            LAT_SIP1 = 0;
            LAT_SIP0 = 0;    
             
            /*
            if(1 == usb_serial_exit)
            {
               pthread_exit(0);
            }   
             */

            rc = ioctl(fd, TCFLSH, 0);
            if (rc < 0) 
            {
                LAT_SIP3 = 1;  
            }
            else
            {
                LAT_SIP3 = 0;
            }

            
			// 0  - Cable is not connected or the host does not support this device.
            error = close(fd);
            if(-1 == error)
            {

                LAT_SIP2 = 1;                
            }
            else
            {
              
                LAT_SIP2 = 0;
            }
            usleep(200000); 
            goto RESTART_USB;
		}
	}

}

void USB_event(tUSB_event evt, void *param)
{
	switch (evt)
	{
		case _USBD_CON_EVT:	
		{
			xprintf("usb device connected\n");
			break;
		}
		case _USBD_DISCON_EVT:	
		{
			xprintf("usb device disconnected\n");
			break;
		}
		case _USBD_SUSPEND_EVT:
		{
			xprintf("usb device suspend\n");
			break;
		}
		case _USBD_RESUME_EVT:
		{
			xprintf("usb device resume\n");
			break;
		}
		case _USBH_CON_EVT:
        case _USBH_DISCON_EVT:
        case _USBH_PWR_EVT:
        case _USBH_VBUS_EVT:
        case _USBH_SUSPEND_EVT:
        case _USBH_RESUME_EVT:
        case _USB_ROLE_HOST_EVT:
        case _USB_ROLE_DEV_EVT:        
		{
			xprintf("not handled\n");
			break;
		}        
	}
}

#endif