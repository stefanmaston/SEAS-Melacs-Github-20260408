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

#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
#include "main.h"
#ifdef _ETHEReNET_

#include <sys.h>
#include <p32xxxx.h>
#include <plib.h>
#include <fcntl.h>
#include <mrendez.h>
#include <iorqst.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include <tcpinit.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define RTOS_DEBUG	1

THREAD ServerMain(void *);
THREAD tcp_shell(void *), IPv4_thread(void *);
int tcp_server_start (void);

extern uint8_t sendTCPBuffer[TCP_SEND_BUFFER_SIZE];
extern uint8_t recvTCPBuffer[TCP_RECV_BUFFER_SIZE];
THREAD ServerMain(void *arg)
{
	pthread_t pid;
	pthread_attr_t attr;
	struct sched_param myNewPriority;
    
//	int read_len = 0;
//	int sock_tcp, conn;
//	struct sockaddr_in6 client_addr;
//	char str[INET6_ADDRSTRLEN];
//	socklen_t addrLen = sizeof(client_addr);
//
//	struct sockaddr_in6 addr;
//	socklen_t len;


#if RTOS_DEBUG
	dir_register("ServerMain thread", pthread_self(), TYPE_THREAD);
#endif
	xprintf("\nServerMain\n");

	//
	//setup and start TCP server
	//
	if (tcp_server_start() < 0)
	{
#if RTOS_DEBUG
		dir_deregister("ServerMain thread");
#endif
		pthread_exit(0);
	}

	xprintf("TCP task start\n");
    
    pthread_attr_init(&attr);
	myNewPriority.sched_priority = 2; 
	pthread_attr_setschedparam(&attr, &myNewPriority); 
 	pthread_attr_setstacksize(&attr, 1024);
    
    if(pthread_create(&pid, &attr, &IPv4_thread, 0)!=0)
	{
		xprintf("pthread_create = %d\n", errno);
    #if RTOS_DEBUG
		dir_deregister("IPV4 thread");
    #endif
		pthread_exit(0);
	}
//        // open socket
//	sock_tcp = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
//	if (sock_tcp < 0)
//	{
//		xprintf("open sock_tcp error %x\n",errno);
//	}
//
//        // bind socket
//	len = sizeof(addr);
//        memset(&addr, 0, len);
//
//        addr.sin6_family = AF_INET6;
//        addr.sin6_port = htons(9000);
//
//        if (bind(sock_tcp, (struct sockaddr *) &addr, len) < 0)
//        {
//            xprintf("bind sock_tcp error %d\n", errno);
//        }
//
//	if (listen(sock_tcp, 1) < 0)
//	{
//		xprintf("listen sock_tcp error %d\n", errno);
//	}
//
//
//again:
//        xprintf("\nwait accept...\n");
//
//        conn = accept(sock_tcp, (struct sockaddr *)&client_addr, &addrLen);
//        if (conn < 0)
//        {
//                xprintf("accept sock_tcp error %d\n", errno);
//        }
//
//        inet_ntop(AF_INET6, &(client_addr.sin6_addr), str, INET6_ADDRSTRLEN);
//        xprintf("get connect from: %s", str);
//        xprintf(".%d\n", ntohs(client_addr.sin6_port));
//
//
//	while (1)
//	{
//            bufReadLockMutex();
//            read_len = read(conn, recvTCPBuffer, TCP_RECV_BUFFER_SIZE);
//            bufReadUnlockMutex();
//
//            if (read_len == 0)
//            {
//                    xprintf("disconnect\n");
//                    close(conn);
//                    goto again;
//            }
//            if (read_len == -1)
//            {
//                    xprintf("connect abort! errno=%d\n", errno);
//                    close(conn);
//                    goto again;
//            }
//
//            bufWriteLockMutex();
//            write(conn, sendTCPBuffer, TCP_SEND_BUFFER_SIZE);
//            bufWriteUnlockMutex();
//            
//            usleep(200000);
//	}
    return;
}

THREAD IPv4_thread(void *arg)
{
	int i = 0;
//    int extract_len = 0;
    int read_len = 0;
	int sock_tcp, conn;
    
	struct sockaddr_in client_addr;
	socklen_t addrLen = sizeof(client_addr);
	char buf[512];
  //  char buffer[100];
	struct sockaddr_in addr;
	socklen_t len;
  
    //char buffer_test[2048];
    


#if RTOS_DEBUG
	dir_register("ipv4 thread", pthread_self(), TYPE_THREAD);
#endif
	//DebugMessageOnUART5("\nIpv4 thread\n");

	// open socket
	sock_tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_tcp < 0)
	{
		//DebugMessageOnUART5("open sock_tcp error\n");
	}

        // bind socket
	len = sizeof(addr);
        memset(&addr, 0, len);
    
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        if (bind(sock_tcp, (struct sockaddr *) &addr, len) < 0)
        {
            xprintf("bind sock_tcp error %d\n", errno);
        }

	if (listen(sock_tcp, 1) < 0)
	{
		xprintf("listen sock_tcp error %d\n", errno);
	}


again:
       // DebugMessageOnUART5("\nipv4 wait accept...\n");
        conn = accept(sock_tcp, (struct sockaddr *)&client_addr, &addrLen);
        if (conn < 0)
        {
                xprintf("accept sock_tcp error %d\n", errno);
        }
  
        while (1)
	{
		read_len = read(conn, buf, 512);
		if (read_len == 0)
		{
			xprintf("ipv4 disconnect\n");
			close(conn);
			goto again;
		}
		if (read_len == -1)
		{
			xprintf("connect abort! errno=%d\n", errno);
			close(conn);
			goto again;
		}

		buf[read_len] = 0;
		
		read_len = sprintf(buf, "Unison send #%d", i++);
		write(conn, buf, read_len+1);
    }
}

#if 0
//THREAD Main(void *arg)
//void ServerMain()
THREAD ServerMain(void *arg)
{
	pthread_t pid;
	pthread_attr_t attr;
	struct sched_param myNewPriority;
	char buf[128];
	int i = 0, read_len = 0;
	int sock_tcp, conn;
	struct sockaddr_in6 client_addr;
	char str[INET6_ADDRSTRLEN];
	socklen_t addrLen = sizeof(client_addr);

	struct sockaddr_in6 addr;
	socklen_t len;


#if RTOS_DEBUG
	dir_register("ServerMain thread", pthread_self(), TYPE_THREAD);
#endif
	xprintf("\nServerMain\n");

	//
	//setup and start TCP server
	//
	if (tcp_server_start() < 0)
	{
#if RTOS_DEBUG
		dir_deregister("ServerMain thread");
#endif
		pthread_exit(0);
	}
    
	xprintf("TCP task start\n");
/*
        pthread_attr_init(&attr);
	myNewPriority.sched_priority = 6; 
	pthread_attr_setschedparam(&attr, &myNewPriority); 
 	pthread_attr_setstacksize(&attr, 2048);


	if(pthread_create(&pid, &attr, &IPv4_thread, 0)!=0)
	{
		xprintf("pthread_create = %d\n", errno);
#if RTOS_DEBUG
		dir_deregister("Main thread");
#endif
		pthread_exit(0);
	}
 */
        // open socket
	sock_tcp = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (sock_tcp < 0)
	{
		xprintf("open sock_tcp error %x\n",errno);
	}

        // bind socket
	len = sizeof(addr);
        memset(&addr, 0, len);

        addr.sin6_family = AF_INET6;
        addr.sin6_port = htons(9000);

        if (bind(sock_tcp, (struct sockaddr *) &addr, len) < 0)
        {
            xprintf("bind sock_tcp error %d\n", errno);
        }

	if (listen(sock_tcp, 1) < 0)
	{
		xprintf("listen sock_tcp error %d\n", errno);
	}


again:
        xprintf("\nwait accept...\n");

        conn = accept(sock_tcp, (struct sockaddr *)&client_addr, &addrLen);
        if (conn < 0)
        {
                xprintf("accept sock_tcp error %d\n", errno);
        }

        inet_ntop(AF_INET6, &(client_addr.sin6_addr), str, INET6_ADDRSTRLEN);
        xprintf("get connect from: %s", str);
        xprintf(".%d\n", ntohs(client_addr.sin6_port));

        
	while (1)
	{

            read_len = read(conn, buf, 128);

            if (read_len == 0)
            {
                    xprintf("disconnect\n");
                    close(conn);
                    goto again;
            }
            if (read_len == -1)
            {
                    xprintf("connect abort! errno=%d\n", errno);
                    close(conn);
                    goto again;
            }

            buf[read_len] = 0;
            xprintf("\n  TCP read %d bytes\n", read_len);
            xprintf("  buf: %s\n", buf);
            
            read_len = sprintf(buf, "I hope its easy #%d", i++);
            write(conn, buf, read_len+1);
	}
}



THREAD IPv4_thread(void *arg)
{
	int i = 0, read_len = 0;
	int sock_tcp, conn;
	struct sockaddr_in client_addr;
	socklen_t addrLen = sizeof(client_addr);
	char buf[128];
	struct sockaddr_in addr;
	socklen_t len;


#if RTOS_DEBUG
	dir_register("ipv4 thread", pthread_self(), TYPE_THREAD);
#endif
	xprintf("\nIpv4 thread\n");

	// open socket
	sock_tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_tcp < 0)
	{
		xprintf("open sock_tcp error\n");
	}

        // bind socket
	len = sizeof(addr);
        memset(&addr, 0, len);
    
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        if (bind(sock_tcp, (struct sockaddr *) &addr, len) < 0)
        {
            xprintf("bind sock_tcp error %d\n", errno);
        }

	if (listen(sock_tcp, 1) < 0)
	{
		xprintf("listen sock_tcp error %d\n", errno);
	}


again:
        xprintf("\nipv4 wait accept...\n");
        conn = accept(sock_tcp, (struct sockaddr *)&client_addr, &addrLen);
        if (conn < 0)
        {
                xprintf("accept sock_tcp error %d\n", errno);
        }

        xprintf("ipv4 get connect from: %s", inet_ntoa(client_addr.sin_addr));
        xprintf(".%d\n", ntohs(client_addr.sin_port));

	while (1)
	{
		read_len = read(conn, buf, 128);
		if (read_len == 0)
		{
			xprintf("ipv4 disconnect\n");
			close(conn);
			goto again;
		}
		if (read_len == -1)
		{
			xprintf("connect abort! errno=%d\n", errno);
			close(conn);
			goto again;
		}

		buf[read_len] = 0;
		xprintf("\n  TCP read %d bytes\n", read_len);
		xprintf("  buf: %s\n", buf);

		read_len = sprintf(buf, "Unison send #%d", i++);
		write(conn, buf, read_len+1);
	}

}

#endif
#endif
