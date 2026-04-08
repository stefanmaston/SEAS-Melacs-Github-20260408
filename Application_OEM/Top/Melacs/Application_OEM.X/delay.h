/* 
 * File:   delay.h
 * Author: Bala
 *
 * Created on December 15, 2014, 4:18 PM
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <peripheral/timer.h>    

#define GetSystemClock()    (72000000ULL) //Same as sysclk
    
typedef int32_t Timer_t;

static inline void __attribute__((always_inline)) DelayUs(uint32_t delay_in_us ) 
{
     uint32_t tWait = ( GetSystemClock() / 2000000 ) * delay_in_us;
     uint32_t tStart = ReadCoreTimer();
     while( ( ReadCoreTimer() - tStart ) < tWait ); 
}

Timer_t Timer_Reset(void);
int32_t Timer_GetMS(Timer_t *timer);
int32_t Timer_GetUS(Timer_t *timer);

//11 = 305ns
//9 = 250ns by calculation and in practical 500ns, we need a delay of more that 250ns, but to have a buffer, its good to have 500ns
//1 = gives 350ns in practice, this should be sufficient but may be some speed optimisation could reduce this further
static inline void __attribute__((always_inline)) DelayADC()
{
     uint32_t tWait = 9;
     uint32_t tStart = ReadCoreTimer();
     while( ( ReadCoreTimer() - tStart ) < tWait );
}
static inline void __attribute__((always_inline)) DelayNs(uint32_t delay_in_ns ) 
{
     uint32_t tWait = ( GetSystemClock() / 2000000000 ) * delay_in_ns;
     uint32_t tStart = ReadCoreTimer();
     while( ( ReadCoreTimer() - tStart ) < tWait ); 
}


#define DelayNOP() asm("nop")

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

