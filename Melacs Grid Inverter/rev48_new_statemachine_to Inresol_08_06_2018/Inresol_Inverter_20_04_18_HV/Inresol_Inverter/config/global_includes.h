/*
 *  File name: global_includes.h
 *
 *  Description: Global includes file
 *
 *  Author: Future Electronics
 *
 */

#ifndef GLOBAL_INCLUDES_H
#define GLOBAL_INCLUDES_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define INLINE_UNSUPPORTED		// In Free Version of XC16
// -O -finline-functions -Winline

#ifndef STATIC
#define STATIC		static
#endif
#ifndef INLINE
#define INLINE		inline
#endif
#ifndef EXTERN
#define EXTERN		extern
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array)  (sizeof(array) / sizeof(array[0]))
#endif
#ifndef REP_STR
#define REP_STR_0(X)
#define REP_STR_1(X) X
#define REP_STR_2(X) REP_STR_1(X) X
#define REP_STR_3(X) REP_STR_2(X) X
#define REP_STR_4(X) REP_STR_3(X) X
#define REP_STR_5(X) REP_STR_4(X) X
#define REP_STR_6(X) REP_STR_5(X) X
#define REP_STR_7(X) REP_STR_6(X) X
#define REP_STR_8(X) REP_STR_7(X) X
#define REP_STR_9(X) REP_STR_8(X) X
#define REP_STR_10(X) REP_STR_9(X) X
#define REP_STR(HUNDREDS,TENS,ONES,X) \
	REP_STR_##HUNDREDS(REP_STR_10(REP_STR_10(X))) \
	REP_STR_##TENS(REP_STR_10(X)) \
	REP_STR_##ONES(X)
#endif
#ifndef REP_DIG
#define REP_DIG_O_0(X)
#define REP_DIG_O_1(X) X
#define REP_DIG_O_2(X) X, REP_DIG_O_1(X)
#define REP_DIG_O_3(X) X, REP_DIG_O_2(X)
#define REP_DIG_O_4(X) X, REP_DIG_O_3(X)
#define REP_DIG_O_5(X) X, REP_DIG_O_4(X)
#define REP_DIG_O_6(X) X, REP_DIG_O_5(X)
#define REP_DIG_O_7(X) X, REP_DIG_O_6(X)
#define REP_DIG_O_8(X) X, REP_DIG_O_7(X)
#define REP_DIG_O_9(X) X, REP_DIG_O_8(X)
#define REP_DIG_O_10(X) X, REP_DIG_O_9(X)

#define REP_DIG_T_0(X)
#define REP_DIG_T_1(X) REP_DIG_O_10(X),
#define REP_DIG_T_2(X) X, REP_DIG_T_1(X)
#define REP_DIG_T_3(X) X, REP_DIG_T_2(X)
#define REP_DIG_T_4(X) X, REP_DIG_T_3(X)
#define REP_DIG_T_5(X) X, REP_DIG_T_4(X)
#define REP_DIG_T_6(X) X, REP_DIG_T_5(X)
#define REP_DIG_T_7(X) X, REP_DIG_T_6(X)
#define REP_DIG_T_8(X) X, REP_DIG_T_7(X)
#define REP_DIG_T_9(X) X, REP_DIG_T_8(X)
#define REP_DIG_T_10(X) X, REP_DIG_T_9(X)

#define REP_DIG_H_0(X)
#define REP_DIG_H_1(X) REP_DIG_T_10(X),
#define REP_DIG_H_2(X) X, REP_DIG_H_1(X)
#define REP_DIG_H_3(X) X, REP_DIG_H_2(X)
#define REP_DIG_H_4(X) X, REP_DIG_H_3(X)
#define REP_DIG_H_5(X) X, REP_DIG_H_4(X)
#define REP_DIG_H_6(X) X, REP_DIG_H_5(X)
#define REP_DIG_H_7(X) X, REP_DIG_H_6(X)
#define REP_DIG_H_8(X) X, REP_DIG_H_7(X)
#define REP_DIG_H_9(X) X, REP_DIG_H_8(X)
#define REP_DIG_H_10(X) X, REP_DIG_H_9(X)

#define REP_DIG(VAL_HUNDREDS,VAL_TENS,VAL_ONES,X) \
	REP_DIG_H_##VAL_HUNDREDS(X) \
	REP_DIG_T_##VAL_TENS(X) \
	REP_DIG_O_##VAL_ONES(X)
#endif

#define mcuAtomicOr(variable, mask)			\
	__asm__ volatile (						\
		"    ior.w %0, [%1], [%1] \n"		\
		: : "r"(mask), "r"(&(variable))		\
		: "cc"								\
	)
 
#define mcuAtomicAnd(variable, mask)		\
	__asm__ volatile (						\
		"    and.w %0, [%1], [%1] \n"		\
		: : "r"(mask), "r"(&(variable))		\
		: "cc"								\
	)
 
#define mcuAtomicXor(variable, mask)		\
	__asm__ volatile (						\
		"    xor.w %0, [%1], [%1] \n"		\
		: : "r"(mask), "r"(&(variable))		\
		: "cc"								\
	)

#include "types_pwm.h"
#include "types_dds.h"
#include "types_timer.h"
#include "types_uart.h"
#include "types_adc.h"
#include "types_relay.h"
#include "types_tempsens.h"
#include "types_ocp.h"
#include "types_sm.h"
#include "types_dpll.h"
#include "types_system.h"
#include "types_datarec.h"

#include "config_system.h"
#include "config_hardware.h"
#include "config_pwm.h"
#include "config_dds.h"
#include "config_timer.h"
#include "config_uart.h"
#include "config_version.h"
#include "config_adc.h"
#include "config_ocp.h"
#include "config_datarec.h"
#include "config_modbus.h"
#include "config_sm.h"

#include "Functions.h"
#include "dsp.h"
#include "crc.h"
#include "DEE_Emulation_16-bit.h"

#include "BSP_System.h"
#include "BSP_PWM.h"
#include "BSP_Timer.h"
#include "BSP_UART.h"
#include "BSP_IO.h"
#include "BSP_ADC.h"
#include "BSP_Relay.h"

#include "App_PWM.h"
#include "App_DDS.h"
#include "App_SysTick.h"
#include "App_Debug.h"
#include "App_Utils.h"
#include "App_ADC.h"
#include "App_Relay.h"
#include "App_TempSens.h"
#include "App_OCP.h"
#include "App_DataRec.h"
#include "App_DPLL.h"
#include "App_SM.h"
#include "App_MODBUS.h"
#include "App_NVMemory.h"

#endif	// GLOBAL_INCLUDES_H
