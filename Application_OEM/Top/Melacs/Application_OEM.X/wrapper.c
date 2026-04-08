//#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _WRAPPER_BASE_
#include <stdio.h>
#include <time.h>
#include "onBoardADC.h"
#include "onBoardRTCC.h"
#include "sd_spi.h"
#include "display.h"
#include "delay.h"
#include "log.h"
#include "math.h"
#include "pinDefines.h"
#include "wrapper.h"

void Melacs_PinInit()
{

    CNEN = 28; //Weak Pull up on CN2, CN3, CN4
    AD1PCFG = 0xffff; //Make all port B pin as digital

    TRIS_SIP0 = 0;
    LAT_SIP0 = 0;

    TRIS_SIP1 = 0;
    LAT_SIP1 = 0;

  //  TRIS_SIP2 = 0; Cleared in order to use these for UART5 purpose
    //LAT_SIP2 = 0;

    TRIS_SIP3 = 0;
    LAT_SIP3 = 0;

    TRIS_SIP4 = 0;
    LAT_SIP4 = 0;
    TRIS_DIO0 = 1;
    TRIS_DIO1 = 1;
    TRIS_DIO2 = 1;
    TRIS_DIO3 = 1;
    TRIS_DIO4 = 0;
    TRIS_DIO5 = 0;
    TRIS_DIO6 = 0;
    TRIS_DIO7 = 0;
    TRIS_SIP5 = 0;
    LAT_SIP5 = 0;

    TRIS_SIP6 = 0;
    LAT_SIP6 = 0;

    TRIS_SIP7 = 0;
    LAT_SIP7 = 0;

    //M1DIS to enable HBridge
    TRIS_M1DIS = 0;
    LAT_M1DIS = 0;

    //Set M1AHI as output
    TRIS_M1AHI = 0;
    LAT_M1AHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1ALI = 0;
    LAT_M1ALI = 0;

    //Set M1AHI as output and to low
    TRIS_M1BHI = 0;
    LAT_M1BHI = 0;

    //Set M1ALI as output and to low
    TRIS_M1BLI = 0;
    LAT_M1BLI = 1;

    //M2DIS to enable HBridge
    TRIS_M2DIS = 0;
    LAT_M2DIS = 0;

    //Set M2BHI as output
    TRIS_M2AHI = 0;
    LAT_M2AHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2ALI = 0;
    LAT_M2ALI = 0;

    //Set M2BHI as output and to low
    TRIS_M2BHI = 0;
    LAT_M2BHI = 0;

    //Set M2BLI as output and to low
    TRIS_M2BLI = 0;
    LAT_M2BLI = 1;
}

void Melacs_Init()
{
    Melacs_PinInit();

    OpenOC1( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenOC3( OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE, 0, 0);
    OpenTimer2( T2_ON | T2_PS_1_1 | T2_SOURCE_INT, 0x2FFF);
}

void Melacs_SetDirection_DIO0(bool direction)
{
    TRIS_DIO0 = direction;
}

void Melacs_SetDirection_DIO1(bool direction)
{
    TRIS_DIO1 = direction;
}

void Melacs_SetDirection_DIO2(bool direction)
{
    TRIS_DIO2 = direction;
}

void Melacs_SetDirection_DIO3(bool direction)
{
    TRIS_DIO3 = direction;
}

void Melacs_SetDirection_DIO4(bool direction)
{
    TRIS_DIO4 = direction;
}

void Melacs_SetDirection_DIO5(bool direction)
{
    TRIS_DIO5 = direction;
}

void Melacs_SetDirection_DIO6(bool direction)
{
    TRIS_DIO6 = direction;
}

void Melacs_SetDirection_DIO7(bool direction)
{
    TRIS_DIO7 = direction;
}

int Melacs_clock_gettime(struct melacs_timespec *time)
{
    return clock_gettime(CLOCK_REALTIME, (struct timespec *)time);
}

int Melacs_clock_settime(const struct melacs_timespec *time)
{
    return clock_settime(CLOCK_REALTIME, (const struct timespec *)time);
}

void Melacs_Read_AN()
{
        SPI_Disable();
        ReadSignals();
        SPI_Enable();
}

int Melacs_Get_AN0()
{
    return adcresult[0];
}

int Melacs_Get_AN1()
{
    return adcresult[1];
}

int Melacs_Get_AN2()
{
    return adcresult[2];
}

int Melacs_Get_AN3()
{
    return adcresult[3];
}

int Melacs_Get_AN4()
{
    return adcresult[4];
}

int Melacs_Get_AN5()
{
    return adcresult[5];
}

int Melacs_Get_AN6()
{
    return adcresult[6];
}

int Melacs_Get_AN7()
{
    return adcresult[7];
}

bool Melacs_Get_DIO0()
{
    return DIO0_IN;
}

bool Melacs_Get_DIO1()
{
    return DIO1_IN;
}

bool Melacs_Get_DIO2()
{
    return DIO2_IN;
}

bool Melacs_Get_DIO3()
{
    return DIO3_IN;
}

bool Melacs_Get_DIO4()
{
    return DIO4_IN;
}

bool Melacs_Get_DIO5()
{
    return DIO5_IN;
}

bool Melacs_Get_DIO6()
{
    return DIO6_IN;
}

bool Melacs_Get_DIO7()
{
    return DIO7_IN;
}

// Alf Gisslen har gissat att det kanske ser ut så här
void Melacs_Set_DIO0(bool value)
{
    DIO0_IN = value;
}

void Melacs_Set_DIO1(bool value)
{
    DIO1_IN = value;
}

void Melacs_Set_DIO2(bool value)
{
    DIO2_IN = value;
}

void Melacs_Set_DIO3(bool value)
{
    DIO3_IN = value;
}

void Melacs_Set_DIO4(bool value)
{
    DIO4_IN = value;
}

void Melacs_Set_DIO5(bool value)
{
    DIO5_IN = value;
}

void Melacs_Set_DIO6(bool value)
{
    DIO6_IN = value;
}

void Melacs_Set_DIO7(bool value)
{
    DIO7_IN = value;
}

void Melacs_Set_JP3(bool value)
{
    LAT_SIP1 = value;
}

void Melacs_Set_JP4(bool value)
{
    LAT_SIP0 = value;
}

void Melacs_Set_JP5(bool value)
{
    LAT_SIP3 = value;
}

/*void Melacs_Set_JP6(bool value)
{
    LAT_SIP2 = value;
}*/

void Melacs_Set_JP7(bool value)
{
    LAT_SIP4 = value;
}

void Melacs_Set_JP8(bool value)
{
    LAT_SIP5 = value;
}

void Melacs_Set_JP9(bool value)
{
    LAT_SIP6 = value;
}

void Melacs_Set_JP10(bool value)
{
    LAT_SIP7 = value;
}

int Melacs_getBoardTemperature()
{
    return getBoardTemperature();
}

void Melacs_Set_RTC(const struct melacs_rtc* rtc_values)
{
    yr = rtc_values->year;
    mt = rtc_values->month;
    dy = rtc_values->mday;
    hr = rtc_values->hour;
    mn = rtc_values->minute;
    sc = rtc_values->second;
    wd = rtc_values->wday;

    SPI_Disable();
    RTC_Write_Clock();
    SPI_Enable();
}

//To add a structure and put all the values in the structure
void Melacs_Get_RTC(struct melacs_rtc * rtc_values)
{
    SPI_Disable();
    RTC_Read_Clock();
    SPI_Enable();
    
    rtc_values->year = yr;
    rtc_values->month = mt;
    rtc_values->mday = dy;
    rtc_values->hour = hr;
    rtc_values->minute = mn;
    rtc_values->second = sc;
    rtc_values->wday = wd;
}

#endif