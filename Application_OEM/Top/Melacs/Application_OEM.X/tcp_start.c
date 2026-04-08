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
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include "main.h"

#ifdef _ETHERNET_

#include <sys.h>
#include <tcpinit.h> 
#include <p32xxxx.h>
#include <plib.h>


#define RTOS_DEBUG			1		//1/0 - enable/disable - support for Remedy RTOS viewer


#define ETH_ADDR		0x01	// PHY addr
#define ETH_INT_VECT	-1 //_EXTERNAL_1_VECTOR
#define ETH_INT_LEVEL	EXT_INT_PRI_5 //(5<<4) | 1	//priority: 5, sub-priority: 1

static char	tcpbuf[1024*18] __attribute__ ((aligned (2048)));
static struct tcpinit tcpinit;




/*************************************************************************
 *  Subroutine  : tcp_shell
 *  Purpose     : Task shell for starting device specific tcpserver
 ************************************************************************/
THREAD tcp_shell(void *arg)
{ 	
    
   	// clear init structure
	memset(&tcpinit, 0, sizeof(tcpinit));

	// memory for server
	tcpinit.tcp_pool_start = tcpbuf;
	tcpinit.tcp_pool_size = sizeof(tcpbuf);

	// device
	tcpinit.dev_type = DEV_ETHERNET;
	tcpinit.dev_unit = 0;
	tcpinit.dev_addr = ETH_ADDR;
	tcpinit.dev_vector = ETH_INT_VECT;
	tcpinit.dev_level = ETH_INT_LEVEL;

	// Set up the MAC-address
	// Type all 0x00 to use Ethernet module preprogrammed MAC
    
	tcpinit.eth_mac[0] = 0x00;
	tcpinit.eth_mac[1] = 0x11;
	tcpinit.eth_mac[2] = 0x22;
	tcpinit.eth_mac[3] = 0x33;
	tcpinit.eth_mac[4] = 0x44;
	tcpinit.eth_mac[5] = 0x55;

	// IPv6
	tcpinit.IPv6.IP_address = NULL;
	tcpinit.IPv6.IP_prefix = 0;
	tcpinit.IPv6_default_gateway = NULL;

	// IPv4
    //tcpinit.IPv4.IP_address = "169.254.28.173";
	//tcpinit.IPv4.IP_address = "192.168.16.160";
    tcpinit.IPv4.IP_address = IPV4STRING;
	tcpinit.IPv4.IP_mask = "255.255.255.0";
	//tcpinit.IPv4_default_gateway = "192.168.16.1";
    
	if(tcpd(&tcpinit) == -1)
        {
          xprintf("tcpd server init fail, ERRNO=%x\n",errno);
          pthread_exit(0);
        }

	return 0;// just to avoid warning
}



/*************************************************************************
 *  Subroutine  : tcp_server_start
 *  Purpose     : function will start TCP server
 ************************************************************************/
int tcp_server_start (void)
{
	pthread_attr_t attr;
	pthread_t pid;
	struct sched_param myNewPriority;
	

	pthread_attr_init(&attr);
	myNewPriority.sched_priority = 5; 
	pthread_attr_setschedparam(&attr, &myNewPriority); 
 	pthread_attr_setstacksize(&attr, 2560);
 
	if(pthread_create(&pid, &attr, &tcp_shell, 0)!=0)
	{
		xprintf("pthread_create = %d\n", errno);
		pthread_attr_destroy(&attr);	
		return -1;
	}	

	pthread_attr_destroy(&attr);	
	
	if(dir_register("/dev/tcpd", pid, TYPE_SERVER)==0)
	{
		xprintf("dir_register = %d\n", errno);
#if RTOS_DEBUG
		dir_deregister("Main thread");
#endif	
		return -1;
	}

	// IPv6 interface need to do DAD (Duplicated Address Detection)
	sleep(3);

	xprintf("\n**********\n");
	xprintf("IPv6 stack uses automatically generated IP address (link-local)\n");
    xprintf("**********\n\n");	
	
	return 0;
}

#endif