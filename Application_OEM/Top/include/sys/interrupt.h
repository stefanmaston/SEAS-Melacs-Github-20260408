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
#ifndef _interrupt_h_
#define _interrupt_h_

#ifdef __cplusplus
extern "C" {
#endif

int  i_set_interrupt(uint_32 vector, void (*handler)(uint_32), uint_32 arg);

#if defined(__PIC24F__) || defined(__dsPIC30F__) || defined(__dsPIC33F__)
	#define _DSPEXEC_ISR __attribute__((__interrupt__(__preprologue__("disi #0x3fff\n call _i_prologue")),__auto_psv__))
	Status i_disable(void);
	void i_restore(Status ps);
#elif defined(M16C)
	Status i_disable(void);
	void i_restore(Status ps);
	void isr_prologue(void);
	void isr_epilogue(void);
#elif defined(__PIC32MX__) || defined(__PIC32MZ__)
	#undef _DSPEXEC_ISR
	Status __attribute__((nomips16)) i_disable(void);
	void __attribute__((nomips16)) i_restore(Status ps);
	void _isr_init(int size);
#elif defined(__R32C100__) || defined (NC100)
	#undef _DSPEXEC_ISR
	Status  i_disable(void);
	void i_restore(unsigned int status);
	void isr_prologue (void);
	void isr_epilogue (void);
	void _isr_init(void);	
#elif defined(__ARMCORTEXM3__) || defined(__ARMCORTEXM4F__)
	Status i_disable(void);
	void i_restore(Status ps);
	void SVCHandler(void);	
	void PendSVHandler(void);
	void MainInterrupt (void);
	void _isr_init(void);	
#elif defined(__CORTEX_A8__)
	Status i_disable(void);
	void i_restore(Status ps);
	void _isr_init(void);
	void SetPriorityISR(int isr_num, int isr_prio);
	void DisableISR(int isr_num); 
	void EnableISR(int isr_num); 	
#elif defined(_SH2A) || defined(_SH2AFPU) || defined (__RX)
	Status i_disable(void);
	void i_restore(Status ps);	
	void isr_prologue (void);
	void isr_epilogue (void);
	void nested_interrupt_enable (void);
	void _isr_init(int size);	
#elif defined(__MICROBLAZE__)
	Status i_disable(void);
	void i_restore(Status ps);
	void _isr_init(int size);
	void MainInterrupt (void);
	void nested_interrupt_enable (void);
#elif defined(__YDFP__)
	Status i_disable(void);
	void i_restore(Status ps);
#else
	#error You must define the ISR parameters for this port!
#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _interrupt_h_ */
