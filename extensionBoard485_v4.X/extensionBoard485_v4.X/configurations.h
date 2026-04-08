/* 
 * File:   Configurations.h
 * Author: Bala
 *
 * Created on December 15, 2014, 4:26 PM
 */

#ifndef CONFIGURATIONS_H
#define	CONFIGURATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SYSCLK                  (72000000)
#define PBCLK                   (SYSCLK/2)

#define CLOCK_TIME_PERIOD  2000000                  // nanoseconds per tick - period 2ms
#define CORE_TIMER_PERIOD  ((PBCLK/64)/500)         // (PBCLK / 64) * 0.002s - ticks per 2ms

#define DESIRED_BAUDRATE    	(115200)      		//The desired BaudRate 115200
#define BAUD_VALUE 	((PBCLK/16/DESIRED_BAUDRATE)-1) // calculate actual BAUD generate value.
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGURATIONS_H */

