#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <sys.h>
#include <p32xxxx.h>
#include <plib.h>
#include <fcntl.h>
#include <mrendez.h>
#include <iorqst.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "main.h"
#include <tcpinit.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcpserverstream.h"
#include <mqueue.h>
#include "queuehandler.h"

char TCPbuffer[512];
char TCPSend [512];
//char buf[512];
int read_len = 0;
int i = 0;
int sock_tcp, conn;

#ifdef _ETHERNET_

THREAD IPv4_thread(void *);
void TcpSender();

void ServerMain (){
    pthread_attr_t attr;
    pthread_t pid;
    struct sched_param myNewPriority;
        
    pthread_attr_init(&attr);
    myNewPriority.sched_priority = 6;
    pthread_attr_setschedparam(&attr, &myNewPriority);
    pthread_attr_setstacksize(&attr, 2048);             
    
    if(pthread_create(&pid, &attr, &IPv4_thread, 0)!=0)
    {
        xprintf("pthread_create = %d\n", errno);
    }

    pthread_attr_destroy(&attr);    
    return; 
}

THREAD IPv4_thread(void *arg)
{
    if (tcp_server_start() < 0)
	{
        xprintf("Failure %d ", errno);
        pthread_exit(0);
    }
	
	struct sockaddr_in client_addr;
	socklen_t addrLen = sizeof(client_addr);
	
   
	struct sockaddr_in addr;
	socklen_t len;
    
    /*Message QUEUE Start*/
    struct mq_attr attr;
    mqd_t mq;
    char msg[8];
    
    attr.mq_flags = 0; 
    attr.mq_maxmsg = 3;
    attr.mq_msgsize = 16;
    sprintf(msg, "EtherFrom");
    
    if((mq =mq_open("TCPQUEUE", O_RDWR, 0, &attr)) == -1)
    { 
        pthread_exit(0);
    }
    
    
	// open socket
	sock_tcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_tcp < 0)
	{
		xprintf("open sock_tcp error\n %d", errno);
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
       
        conn = accept(sock_tcp, (struct sockaddr *)&client_addr, &addrLen);
        if (conn < 0)
        {
                xprintf("accept sock_tcp error %d\n", errno);
        }
    while (1)
	{
		read_len = read(conn, TCPbuffer, 512);
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
		TCPbuffer[read_len] = 0;
		if (!(TCPbuffer[0] - '0'))
            TcpSender();
        else
        {
            if(mq_send(mq,msg,8,0) == -1)
                xprintf("mq_send error");
            read_len = sprintf(TCPSend, "Unison send #%d", i++);
                write(conn, TCPSend, read_len+1);
        }
        
        
		
        }
        if(mq_close(mq) == -1)
            xprintf("mq_close error");

}


void TcpSender()
{
    QUEUE_SEND_t QueueSendState = 0; 
    extern uint8_t sendTCPBuffer[TCP_SEND_BUFFER_SIZE];
    
    QueueSendState = TCPbuffer[1]  - '0';
    switch (QueueSendState)
    {
        
        case TEST2:
        {
         write(conn, sendTCPBuffer, sizeof(sendTCPBuffer));
        
        }break;
        case TEST3:
        {
        
        }break;
        case TEST1:
        default:
        {
            read_len = sprintf(TCPSend, "Unison send #%d", i++);
            write(conn, TCPSend, read_len+1);
        }break;
    }
   
    
}
#endif