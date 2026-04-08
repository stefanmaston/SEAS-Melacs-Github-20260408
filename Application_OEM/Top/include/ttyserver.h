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
#ifndef __ttyserver_h__
#define	__ttyserver_h__

#include <sys/ioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *	TTY channel descriptor
 */
struct TTY_CHAN {
#if defined (__MICROBLAZE__) || defined (__YDFP__) || defined (__CORTEX_A8__)
	uint_32		base;				/* chip base */
#else
	uint_32		*base;				/* chip base */
#endif
#if defined (__R32C100__)	|| defined(M16C) || defined (NC100)
	uchar		*mode_reg;			//UARTi transmit/receive mode register
	uchar		*control_reg_0;		//UARTi transmit/receive control register 0
	uchar		*control_reg_1;		//UARTi transmit/receive control register 1
	uint_16		*tx_data_reg;		//UARTi transmit buffer
	uint_16		*rx_data_reg;		//UARTi receive buffer
	uchar		*baud_reg;			//UARTi boudrate
	uchar		*rx_int_setup;  	//UARTi receive interrupt and priority level
	uchar		*tx_int_setup;  	//UARTi transmit interrupt and priority level
#elif defined (_SH2A)
	uchar		*mode_reg;			//UARTi serial mode register
	uchar		*baud_reg;			//UARTi bit rate register
	uchar		*control_reg_0;		//UARTi serial control register
	uchar		*tx_data_reg;		//UARTi transmit data register
	uchar		*rx_data_reg;		//UARTi receive data register
	uchar		*status_reg;		//UARTi status register
	uint_16		*int_setup;  		//UARTi interrupt and priority level
#elif defined (_SH2AFPU) || defined (__RX)
	#if defined (_SH7216_)|| defined (__RX)
		uchar		*mode_reg;			//UARTi serial mode register
		uchar		*baud_reg;			//UARTi bit rate register
		uchar		*control_reg;		//UARTi serial control register
		uchar		*tx_data_reg;		//UARTi transmit data register
		uchar		*rx_data_reg;		//UARTi receive data register
		uchar		*status_reg;		//UARTi status register
	#endif
	#if defined (_SH7203_)
	uint_16		*mode_reg;			//UARTi serial mode register
	uchar		*baud_reg;			//UARTi bit rate register
	uint_16		*control_reg;		//UARTi serial control register
	uchar		*tx_data_reg;		//UARTi transmit data register
	uchar		*rx_data_reg;		//UARTi receive data register
	uint_16		*status_reg;		//UARTi status register
	uint_16		*int_setup;  		//UARTi interrupt and priority level
	uint_16		*line_stat_reg;		//
	#endif
#else
	uchar		*data_reg;
	uchar		*control_reg;
	uchar		*baud_reg;
#endif
#if defined (__ARMCORTEXM3__) || defined(__ARMCORTEXM4F__)
	uint		*fifo_status;
#endif
	pthread_t	server_id;
	int			(* next_txchar)(volatile struct TTY_CHAN *);
	void		(* rxchar)(volatile struct TTY_CHAN *, int , void (*_start_output)(volatile struct TTY_CHAN *));

	int_16		flags;

	int_16		ehead;		/* points to next empty buf slot */
	int_16		etail;		/* points to next unread char */

	int_16		ohead;
	int_16		otail;
	int_16		ostate;
	uint_16		ochksum;

	int_16		ihead;		/* points to next empty buf slot */
	int_16		itail;		/* points to next unread char */
	int_16		ilastready;	/* points past last full input, ie.
							after last unread char in RAW or last
							(NOT next unread) newline in TTYL. */
	int_16		istate;
	uint_16		ichksum;

	int_16		channum;
	int_16		mask;

	pthread_t	write_requestor;
	uint_32		write_bufsiz;
	uint_32		write_remaining;
	char 		*write_buffer;
	char 		*write_bufferp;	/* write buffer external address */

	uchar		*ibuff;
	uchar		*ebuff;
	uchar		*obuff;

	uint 		ibuf_xon_pt;
	uint		ibuf_xoff_pt;
	uint		ibuflen;
	uint		obuflen;
	uint		ebuflen;

	int_32 		timeout_write;
	int_32 		count_write_char;
	uchar 		write_start;
	//----- select support -----//
	pthread_t	sel_tid;	//select thread id for mr_sigpost
	int			sel_fd;		//select file descriptor id for mr_sigpost
	//----- RS-485/422 support ----//
	void		(* transmitter_control)(int);
	uint_16		transmitter_mode;	//485 = RS-485, 422 = RS-422, 232 = RS-232, other - reserved.
};


/*
 * Common structure for all tty channel in device
 */
struct TTY_STATE {
	volatile struct TTY_CHAN	** CHAN_INFO;
};


/*
 *	TTY driver low level handlers
 */
typedef struct
{
	int (* dev_initialize)(struct set_tty *, struct TTY_STATE *, char);
	void (* dev_set_tty_mode)(volatile struct TTY_CHAN *, struct set_tty *);
	void (* dev_start_output)(volatile struct TTY_CHAN *);
	int (* dev_interrupt_disable)(int);
	void (* dev_interrupt_restore)(int, int);
}_tty_driver;


/*
 * Bits for the TTY_CHAN->flags field.
 */

/*
 * DEVICE_HELD indicates that XOFF has been typed so we should not send
 * any output to the terminal
 */
#define DEVICE_HELD	0x1

/*
 * TRANSMITTER_BUSY is used by those UART's which interrupt on tx buffer GOING
 * empty, rather than transmit buffer empty. This applies to the i8274.
 * With this type of device, we have to remember whether or not there is a
 * character currently being transmitted, whereas with the other, we let
 * the chip remember for us.
 */
#define TRANSMITTER_BUSY	0x2

/*
 * Used for indicating to the server which event has occurred on a channel.
 */
#define WRITE_FINISHED	0x4
#define READ_FINISHED	0x8

/*
 * Do flow control in RAW mode?
 */
#define FLOW_CONTROL	0x10

/* TOM cal */
/*
 * used for receive flow control
 */
#define RX_FLOWED_OFF	0x20
#define RX_SEND_FLOW	0x40
/* TOM cal */

/* Don't echo (TTYLDISC) */
#define NO_ECHO			0x80

/*Select support mode enable*/
#define SELECT_NOTIFY	0x100

/*Read NONBLOCK support*/
#define READ_NONBLOCK	0x200

/*Device was disconnected */
#define DEVICE_DISCONNECTED	0x400


#define READPORT	1
#define WRITEPORT	2
#define ACCEPT_READERS	(1 << READPORT)
#define ACCEPT_WRITERS	(1 << WRITEPORT)

/*
 * Global functions
 */
int tty_server_core(int_8 *init, int_8 *arg, struct TTY_STATE * st, _tty_driver *drv);
int tty_alloc_buf(volatile struct TTY_CHAN *chan, struct set_tty * settings);
void tty_free_buf(volatile struct TTY_CHAN *chan);
#if defined (__RX)
void uart_receive_isr_body (uchar ch_num);
void uart_transmit_isr_body (uchar ch_num);
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif //__ttyserver_h__
