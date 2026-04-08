/* 
 * File:   Wrapper.h
 * Author: Bala
 *
 * Created on September 21, 2015, 3:28 PM
 */

#ifndef WRAPPER_H
#define	WRAPPER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "stdbool.h"
#include "stdint.h"

void Melacs_PinInit();

void Melacs_SetDirection_DIO0(bool direction);
void Melacs_SetDirection_DIO1(bool direction);
void Melacs_SetDirection_DIO2(bool direction);
void Melacs_SetDirection_DIO3(bool direction);
void Melacs_SetDirection_DIO4(bool direction);
void Melacs_SetDirection_DIO5(bool direction);
void Melacs_SetDirection_DIO6(bool direction);
void Melacs_SetDirection_DIO7(bool direction);

void Melacs_Set_DIO0(bool value);
void Melacs_Set_DIO1(bool value);
void Melacs_Set_DIO2(bool value);
void Melacs_Set_DIO3(bool value);
void Melacs_Set_DIO4(bool value);
void Melacs_Set_DIO5(bool value);
void Melacs_Set_DIO6(bool value);
void Melacs_Set_DIO7(bool value);

bool Melacs_Get_DIO0();
bool Melacs_Get_DIO1();
bool Melacs_Get_DIO2();
bool Melacs_Get_DIO3();
bool Melacs_Get_DIO4();
bool Melacs_Get_DIO5();
bool Melacs_Get_DIO6();
bool Melacs_Get_DIO7();

void Melacs_Read_AN();

int Melacs_Get_AN0();
int Melacs_Get_AN1();
int Melacs_Get_AN2();
int Melacs_Get_AN3();
int Melacs_Get_AN4();
int Melacs_Get_AN5();
int Melacs_Get_AN6();
int Melacs_Get_AN7();

void Melacs_Set_JP3(bool value);
void Melacs_Set_JP4(bool value);
void Melacs_Set_JP5(bool value);
void Melacs_Set_JP6(bool value);
void Melacs_Set_JP7(bool value);
void Melacs_Set_JP8(bool value);
void Melacs_Set_JP9(bool value);
void Melacs_Set_JP10(bool value);

void Melacs_Enable_Log();
void Melacs_Disable_Log();
void Melacs_Set_LogParameters(int sampling_time, int samples_per_log);

struct melacs_rtc
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t mday;
	uint8_t month;
	uint8_t wday;
	uint8_t year;
};

void Melacs_Set_RTC(const struct melacs_rtc *);
void Melacs_Get_RTC(struct melacs_rtc *);

void Melacs_SetVoltage_JP18();
void Melacs_SetVoltage_JP19();

bool Melacs_getAmpere_JP18();
bool Melacs_getAmpere_JP19();

struct melacs_timespec
{
  time_t tv_sec; 	 /* seconds */
  long tv_nsec;		 /* nanoseconds */
};

int Melacs_clock_gettime(struct melacs_timespec *);
int Melacs_clock_settime(const struct melacs_timespec *);

int Melacs_getBoardTemperature();
#ifdef	__cplusplus
}
#endif

#endif	/* WRAPPER_H */

