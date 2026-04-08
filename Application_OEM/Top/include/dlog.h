/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2010 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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

#ifndef _dlog_h_
#define _dlog_h_

#ifdef __cplusplus
extern "C" {
#endif

// log group
#define KERNEL_EVENT        0
#define INTERRUPT_EVENT     1
#define USER_EVENT          2
#define IOLIB_EVENT         3


// kernel log events mask
#define DLOG_MASK_MALLOC            (1 << 0)
#define DLOG_MASK_POOL              (1 << 1)
#define DLOG_MASK_PT                (1 << 2)
#define DLOG_MASK_MQ                (1 << 3)
#define DLOG_MASK_MR                (1 << 4)
#define DLOG_MASK_BARRIER           (1 << 5)
#define DLOG_MASK_CANCEL            (1 << 6)
#define DLOG_MASK_COND              (1 << 7)
#define DLOG_MASK_PTHREAD_STATE     (1 << 8)
#define DLOG_MASK_MUTEX             (1 << 9)
#define DLOG_MASK_SEM               (1 << 10)
#define DLOG_MASK_SLEEP             (1 << 11)
#define DLOG_MASK_TIMER             (1 << 12)
#define DLOG_MASK_CLOCK             (1 << 13)
#define DLOG_MASK_KERNEL_ALL		(DLOG_MASK_MALLOC | DLOG_MASK_POOL | DLOG_MASK_PT | DLOG_MASK_MQ | \
									DLOG_MASK_MR | DLOG_MASK_BARRIER | DLOG_MASK_CANCEL | DLOG_MASK_COND | \
									DLOG_MASK_PTHREAD_STATE | DLOG_MASK_MUTEX | DLOG_MASK_SEM | DLOG_MASK_SLEEP | \
									DLOG_MASK_TIMER | DLOG_MASK_CLOCK)

// user log events mask
#define DLOG_MASK_USER              (1 << 14)

// iolib log events mask
#define DLOG_MASK_SOCKET            (1 << 15)
#define DLOG_MASK_FS                (1 << 16)
#define DLOG_MASK_RDWR              (1 << 17)
#define DLOG_MASK_IOLIB_ALL			(DLOG_MASK_SOCKET | DLOG_MASK_FS | DLOG_MASK_RDWR)

#define DLOG_MASK_INTERRUPT         (uint)(1 << 31)

#define DLOG_MASK_NONE				0x00000000
#define DLOG_MASK_ALL				0xFFFFFFFF



/*
 * trigger control
 */

// trigger mask
#define TRIG_LT_VAL		0x01
#define TRIG_EQ_VAL		0x02
#define TRIG_GT_VAL		0x04
#define VALS_AND		0x08

// sequence mask
#define TRIG_VAL3		0x01
#define TRIG_VAL2		0x02
#define TRIG_VAL1		0x04
#define TRIG_USER		0x08
#define TRIGS_AND		0x10

// buffer location
#define TRIG_BUFF_BEFORE	0
#define TRIG_BUFF_AFTER		1
#define TRIG_BUFF_MIDDLE	2

// log mode
#define LOG_OFF				0
#define LOG_NOSEND			1
#define LOG_AUTOLOG			2
#define LOG_TRIG_SINGLE		3
#define LOG_TRIG_CONTINUE	4


/* Event structure */
#ifdef __ICCARM__          // IAR 
#pragma pack(1)  /* pack struct members on byte boundaries */
#define __attribute__(...) // GCC 
#elif defined __RX          // Renesas RX
#define __attribute__(X) // GCC 
#pragma pack  	/* pack struct members on byte boundaries */
#endif

struct timespec_dlog
{
  time_t tv_sec; 	 /* seconds */
  long tv_nsec;		 /* nanoseconds */
}__attribute__((__packed__));

struct _dlog_event
{
	uint_16 ev_group;
	uint_16 ev_type;
	pthread_t ev_thread;
	struct timespec_dlog ev_time;			//Some compiler require _packed_ structure type, so will define timespec_dlog instead of timespec  
	uint_32 ev_data1;
	uint_32 ev_data2;
	uint_32 ev_data3;
	uint_32 ev_data4;
	uint_32 ev_data5;
	uint_32 ev_data6;
}__attribute__((__packed__));
#ifdef __ICCARM__          // IAR 
#pragma pack()  /* restore default packing */
#undef __attribute__       // GCC 
#elif defined __RX          // Renesas RX
#pragma unpack  /* pack struct members on byte boundaries */
#undef __attribute__       // GCC 
#endif

#define DLOG_EVENT_SIZE sizeof(struct _dlog_event)


/*
 * dlog initialization structure
 */
struct dlog_settings
{
	int log_buff_size;			// events buffer - events count
	uint_32 polling_interval;	// events polling interval - ms
	int flush_edge;				// minimum flush events count

	uint_32 event_mask;			// logging events - global mask
	char threads_flow_log;		// log or not threads flow

	char *log_file;				// write log in file
	uint_32 file_len;			// maximum log file length

	char *remote_ip;			// send log to remote host
	u_short remote_port;
};


/*
 * functions structure for RCS support
 */
struct dlog_ctrl_funcs
{
	int (*dlog_ForceSendLog)(void);
	int (*dlog_SetTrigVal)(uint_8 TrigNum,
							uint_32 lt_val, uint_32 *lt_ptr,
							uint_32 eq_val, uint_32 *eq_ptr,
							uint_32 gt_val, uint_32 *gt_ptr,
							uint_8 valMask);
	int (*dlog_SetTrigUsr)(int(*func)(void));
	int (*dlog_SetSeqMasks)(uint_8 SeqMask1, uint_8 SeqMask2, uint_8 SeqMask3, uint_8 SeqMask4, uint_8 TrigBufLoc);
	int (*dlog_GetTrigs)(char *trigs);
	int (*dlog_SetLogMode)(uint_8 Mode);
	int (*dlog_GetLogMode)(uint_8 *Mode);
};

extern struct dlog_ctrl_funcs dlog_ctrl_funcs;


extern uint_32 _dlog_event_mask;
extern char _dlog_threads_flow_log;

// User functions
THREAD dlog(struct dlog_settings *dlog_init);
int dlog_thread_mask(pthread_t id, uint_32 mask);
int dlog_interrupt_mask(int vector, uint_32 mask);
void dlog_set_thread_name(pthread_t id, char *name);
void dlog_set_interrupt_name(int vector, char *name);
void dlog_data(uint_32 d1, uint_32 d2, uint_32 d3, uint_32 d4, uint_32 d5, uint_32 d6);
void dlog_str(char *str);
void dlog_raw(uchar *raw, int num);


// Trigger control
int dlog_SetTrigVal(uint_8 TrigNum,
					uint_32 lt_val, uint_32 *lt_ptr,
					uint_32 eq_val, uint_32 *eq_ptr,
					uint_32 gt_val, uint_32 *gt_ptr,
					uint_8 valMask);
int dlog_SetTrigUsr(int(*func)(void));
int dlog_SetSeqMasks(uint_8 SeqMask1, uint_8 SeqMask2, uint_8 SeqMask3, uint_8 SeqMask4, uint_8 TrigBufLoc);
int dlog_SetLogMode(uint_8 Mode);
int dlog_GetLogMode(uint_8 *Mode);
int dlog_ForceSendLog(void);
#if defined (__RX)       // Renesas RX
void dlog_int_start (unsigned int vector);
void dlog_int_end (unsigned int vector);
int GetIntNumber(void);
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _dlog_h_ */
