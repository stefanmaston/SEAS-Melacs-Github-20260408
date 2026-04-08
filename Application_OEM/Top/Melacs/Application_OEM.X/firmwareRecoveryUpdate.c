#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include <sys.h>
#include <sys/stat.h>
#include <fsysinit.h>
#include <device.h>
#include <sys/mount.h>
#include <fsys.h>
#include <fcntl.h>

#include <mrendez.h>
#include <iorqst.h>
#include <sys/ioctl.h>

#include <tcpinit.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <p32xxxx.h>
#include <plib.h>

#include "main.h"
#include "sd_spi.h"
#include "appheader.h"

unsigned short get_application_crc(void)
{
	app_header * apphdr;
	unsigned short crc;
	
	apphdr = (app_header *)APPLICATION_HEAD_ADDRESS;
	crc = apphdr->crc_binary_file;
	
	return 	crc;
}


void bootloader_recovery_second_step(void)
{
	int offset;
	int fd1;
	int fd2;
	unsigned short CRC_application;
	unsigned short CRC_firmware;
	
	if(( fd1 = open(FW_PATH, O_RDWR, 0666)) == -1)
	{	
		xprintf("file %s not found\n", FW_NAME);
		return;
	}
	else
	{
		if(( fd2 = open(OLD_FW_PATH, O_RDWR, 0666)) == -1)
		{
			close(fd1);
			xprintf("file %s found rename it on %s\n", FW_NAME, OLD_FW_NAME);
			rename(FW_PATH, OLD_FW_PATH);
		}
		else
		{
			CRC_application =  get_application_crc();
			offset = lseek(fd1, 0,SEEK_END);			
			offset = lseek(fd1, (offset - 8) ,SEEK_SET);
			read(fd1,&CRC_firmware, 2);
			
			xprintf("CRC appl=0x%x, CRC firmware =0x%x\n",CRC_application,CRC_firmware);			
				
			if(CRC_application == CRC_firmware)
			{
				close(fd1);				
				close(fd2);				
				xprintf("Delete %s\n", OLD_FW_NAME);
				remove(OLD_FW_PATH);
				xprintf("file %s found, rename it to %s\n", FW_NAME, OLD_FW_NAME);
				rename(FW_PATH, OLD_FW_PATH);
			}
			else
			{
				close(fd1);
				close(fd2);				
				xprintf("Delete %s\n", FW_NAME);
				remove(FW_PATH);
			}
		}						
	}
	
}
