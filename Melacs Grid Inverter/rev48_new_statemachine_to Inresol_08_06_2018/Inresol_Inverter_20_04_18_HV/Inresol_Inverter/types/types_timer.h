/*
 *  File name: types_timer.h
 *
 *  Description: Type definitions for Timer
 *
 *  Author: Future Electronics
 *
 */

#ifndef TYPES_TIMER_H
#define TYPES_TIMER_H

#include "config_system.h"

/*****************/
/* Basic Defines */
/*****************/

// Five 16-Bit (1, 2, 3, 4 and 5) and up to Two 32-Bit (2/3 and 4/5) Timers/Counters

// Timer1 Control Register (T1CON) Bit Defines
#define BSP_TIMER_ON               0xffff      /* Timer1 ON */
#define BSP_TIMER_OFF              0x7fff      /* Timer1 OFF */

#define BSP_TIMER_IDLE_CON         0xdfff      /* operate during sleep */
#define BSP_TIMER_IDLE_STOP        0xffff      /* stop operation during sleep */

#define BSP_TIMER_GATE_ON          0xffff      /* Timer Gate time accumulation enabled */
#define BSP_TIMER_GATE_OFF         0xffbf      /* Timer Gate time accumulation disabled */

#define BSP_TIMER_PS_1_1           0xffcf      /* Prescaler 1:1 */
#define BSP_TIMER_PS_1_8           0xffdf      /*           1:8 */
#define BSP_TIMER_PS_1_64          0xffef      /*          1:64 */
#define BSP_TIMER_PS_1_256         0xffff      /*         1:256 */

#define BSP_TIMER16_SYNC_EXT_ON    0xffff      /* Synch external clk input */
#define BSP_TIMER16_SYNC_EXT_OFF   0xfffb      /* Do not synch external clk input */

#define BSP_TIMER32_32BIT_MODE_ON  0xffff      /* Timer 2 and Timer 3 form a 32 bit Timer */
#define BSP_TIMER32_32BIT_MODE_OFF 0xfff7

#define BSP_TIMER_SOURCE_EXT       0xffff      /* External clock source */
#define BSP_TIMER_SOURCE_INT       0xfffd      /* Internal clock source */

// Defines for Timer Interrupts

#define BSP_TIMER_INT_PRIOR_7      0xffff      /* 111 = Interrupt is priority 7 */
#define BSP_TIMER_INT_PRIOR_6      0xfffe      /* 110 = Interrupt is priority 6 */
#define BSP_TIMER_INT_PRIOR_5      0xfffd      /* 101 = Interrupt is priority 5 */
#define BSP_TIMER_INT_PRIOR_4      0xfffc      /* 100 = Interrupt is priority 4 */
#define BSP_TIMER_INT_PRIOR_3      0xfffb      /* 011 = Interrupt is priority 3 */
#define BSP_TIMER_INT_PRIOR_2      0xfffa      /* 010 = Interrupt is priority 2 */
#define BSP_TIMER_INT_PRIOR_1      0xfff9      /* 001 = Interrupt is priority 1 */
#define BSP_TIMER_INT_PRIOR_0      0xfff8      /* 000 = Interrupt is priority 0 */

#define BSP_TIMER_INT_ON           0xffff      /* Interrupt Enable */
#define BSP_TIMER_INT_OFF          0xfff7      /* Interrupt Disable */

#endif	// TYPES_TIMER_H
