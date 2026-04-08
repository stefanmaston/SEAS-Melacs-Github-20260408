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

#ifndef _local_lim_h_
#define _local_lim_h_

#ifdef __cplusplus
extern "C" {
#endif

/* Set up default and minimum stack sizes. */
#if defined(__PIC24F__) || defined(__dsPIC30F__) || defined(__dsPIC33F__)
	#define PTHREAD_STACK_MIN       128 //better to use exact size that is really required by the structure of 96
	#define PTHREAD_STACK_DEFAULT   300
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"	

#elif defined(__PIC32MX__) || (__PIC32MZ__)
	#define PTHREAD_STACK_MIN       176 //better to use exact size that is really required by the structure of 144
	#define PTHREAD_STACK_DEFAULT   512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff		
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	#define	__REDEFINE_WINT			
	#define	__REDEFINE_WCHAR		

#elif defined(M16C)
	#define PTHREAD_STACK_MIN       40
	#define PTHREAD_STACK_DEFAULT   128
	#define	__SUPPORT_LONG_LONG		0				//1 - enable support for type "long long" and "unsigned long long"

#elif defined(__R32C100__) || defined (NC100)
	#define PTHREAD_STACK_MIN       128 //better to use exact size that is really required by the structure of 80
	#define PTHREAD_STACK_DEFAULT   512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff		
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"

#elif defined(__ARMCORTEXM3__)
	#define PTHREAD_STACK_MIN		184
	#define PTHREAD_STACK_DEFAULT	512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	#define	__REDEFINE_WCHAR		
	#define	__REDEFINE_WINT			
	
#elif defined(__ARMCORTEXM4F__)
	#define PTHREAD_STACK_MIN		184
	#define PTHREAD_STACK_DEFAULT	512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"	
	#define	__REDEFINE_WCHAR		
  	#define	__REDEFINE_WINT			

#elif defined(__CORTEX_A8__)
	#define PTHREAD_STACK_MIN       512 
	#define PTHREAD_STACK_DEFAULT   512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	#define	__REDEFINE_WINT		
	
#elif defined(_SH2A)
	#define PTHREAD_STACK_MIN       128 
	#define PTHREAD_STACK_DEFAULT   512
	#define _BIG_ENDIAN
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	
#elif  defined(_SH2AFPU)
	#define PTHREAD_STACK_MIN       512 
	#define PTHREAD_STACK_DEFAULT   512
	#define _BIG_ENDIAN
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	
#elif defined(__RX)
	#define PTHREAD_STACK_MIN       128 
	#define PTHREAD_STACK_DEFAULT   512
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	#define	__REDEFINE_WCHAR
	#define	__REDEFINE_WINT
	
#elif defined(__MICROBLAZE__)
	#define PTHREAD_STACK_MIN       600
	#define PTHREAD_STACK_DEFAULT   600
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	//#define __NEGATIVE_SEMAPHORE					//ifdef then sem_t->value is "int", else "unsigned int"
	#define	__REDEFINE_WCHAR
	#define	__REDEFINE_WINT

	
#elif defined(__YDFP__)
	#define PTHREAD_STACK_MIN       768
	#define PTHREAD_STACK_DEFAULT   768
	#define PTR_MIN                 0x80000000
	#define PTR_MAX                 0x7fffffff
	#define UPTR_MAX                0xffffffff	
	#define	__SUPPORT_LONG_LONG		1				//1 - enable support for type "long long" and "unsigned long long"
	
#else
	#error You must define the stack parameters for this port!

#endif

#ifdef __cplusplus
} //extern "C" {
#endif

#endif /* _local_lim_h_ */
