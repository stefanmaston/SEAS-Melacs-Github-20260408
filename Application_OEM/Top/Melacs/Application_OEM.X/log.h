/* 
 * File:   log.h
 * Author: Bala
 *
 * Created on December 1, 2014, 3:58 PM
 */

#ifndef LOG_H
#define	LOG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

void logInit();
void logRun(void);
int logRunAvg(int samplePeriod, int numOfSamplesInEachLog);
void burstlogInit(void);
void logBurst(int AD_Chn_nr, int timeToBurstLog, int numOfSamplesInBurstLog);


#if defined(LOG_GENERAL)

//Write a convertion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    bool DIO0;
    bool DIO1;
    bool DIO2;
    bool DIO3;
    bool DIO4;
    bool DIO5;
    bool DIO6;
    bool DIO7;
    bool SIP0;
    bool SIP1;
    bool SIP2;
    bool SIP3;
    bool SIP4;
    bool SIP5;
    bool SIP6;
    bool SIP7;
    bool M1DIS;
    bool M1ALI;
    bool M1BLI;
    uint16_t M1AHI_PWM; //Set to 0xFFFF/0 if Used in ON/OFF mode
    uint16_t M1BHI_PWM; //Set to 0xFFFF/0 if Used in ON/OFF mode
    bool M2DIS;
    bool M2ALI;
    bool M2BLI;
    uint16_t M2AHI_PWM;  //Set to 0xFFFF if Used in ON/OFF mode
    uint16_t M2BHI_PWM;  //Set to 0xFFFF if Used in ON/OFF mode
    uint8_t boardTemp;
    uint8_t pressure;
    uint8_t engineTemperature;
    uint8_t heaterTemperature;
    float valueFloat;
    char message[50];
    } LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, DIO0, DIO1, DIO2, DIO3, DIO4, DIO5, DIO6, DIO7, SIP0, SIP1, SIP2, SIP3, SIP4, SIP5, SIP6, SIP7, M1DIS, M1ALI, M1BLI, M1AHI_PWM, M1BHI_PWM, M2DIS, M2ALI, M2BLI, M2AHI_PWM, M2BHI_PWM, boardTemp, pressure, engineTemperature, heaterTemperature, valueFloat, message;\n"
#else
#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, DIO0, DIO1, DIO2, DIO3, DIO4, DIO5, DIO6, DIO7, SIP0, SIP1, SIP2, SIP3, SIP4, SIP5, SIP6, SIP7, M1DIS, M1ALI, M1BLI, M1AHI_PWM, M1BHI_PWM, M2DIS, M2ALI, M2BLI, M2AHI_PWM, M2BHI_PWM, boardTemp, pressure, engineTemperature, heaterTemperature, valueFloat, message;\n"
#endif
//#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7;\n"

#elif defined(LOG_STIRLING_GASKIT)

//Write a convertion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    bool burnerPotEnable;
    bool keyStatus;
    bool radiatorPotEnable;
    bool pageChangeEnable;
    bool circulationPump;
    bool fuelFeed;
    float radiatorFanVoltage;
    float burnerFanVoltage;
    uint8_t boardTemp;
    uint8_t maxPressure;
    uint8_t minPressure;
    uint8_t pressureNow;
    uint8_t engineTemperature;
    uint16_t heaterTemperature;
    uint16_t tcLowerHystersisThreshold;
    uint16_t tcHigherHystersisThreshold;
} LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, BurnerPotEnable, KeyStatus, RadiatorPotEnable, tcHysterisPotEnable, PageChangeEnable, CirculationPump, GasFeed, RadiatorFanVoltage, BurnerFanVoltage, BoardTemp, MaxPressure, MinPressure, PressureNow, EngineTemperature, HeaterTemperature, TCLowerHystersisThreshold, TCHigherHystersisThreshold;\n"
#else
#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, BurnerPotEnable, KeyStatus, RadiatorPotEnable, PageChangeEnable, CirculationPump, FuelFeed, RadiatorFanVoltage, BurnerFanVoltage, BoardTemp, MaxPressure, MinPressure, PressureNow, EngineTemperature, HeaterTemperature, TCLowerHystersisThreshold, TCHigherHystersisThreshold;\n"
#endif

#elif defined(LOG_OEM)

//Write a convertion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    bool keyStatus;
    bool circulationPump;
    uint8_t boardTemp;
    uint8_t maxPressure;
    uint8_t minPressure;
    uint8_t pressureNow;
    uint8_t engineTemperature;
    uint16_t heaterTemperature;
    bool releaseValve;
    bool fillValve;
    bool error;
    uint16_t ErrorCode;
} LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, KeyStatus, CirculationPump, BoardTemp, MaxPressure, MinPressure, PressureNow, EngineTemperature, HeaterTemperature, ReleaseValve, FillValve, Error, ErrorCode;\n"
#else
#define LOG_TITLE_STRING  "Time, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, KeyStatus, CirculationPump, BoardTemp, MaxPressure, MinPressure, PressureNow, EngineTemperature, HeaterTemperature, ReleaseValve, FillValve, Error, ErrorCode;\n"
#endif

#elif defined(LOG_TESTRIG)

//Write a convertion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    uint16_t AD0_Temp;
    uint16_t AD1_Temp;
    uint16_t AD2_Temp;
    uint16_t AD3_Temp;
    uint16_t AD4_Temp;
    uint16_t AD5_Temp;
    uint16_t AD6_Temp;
    uint16_t AD7_Temp;

} LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, AD0_Temp, AD0_Temp, AD0_Temp, AD1_Temp, AD2_Temp, AD3_Temp, AD4_Temp, AD5_Temp, AD6_Temp, AD7_Temp;\n"
#else
#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, AD0_Temp, AD0_Temp, AD0_Temp, AD1_Temp, AD2_Temp, AD3_Temp, AD4_Temp, AD5_Temp, AD6_Temp, AD7_Temp;\n"
#endif

#elif defined(LOG_TESTRIGMELACS1)

//Write a convertion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    uint16_t AD0_Temp;
    uint16_t AD1_Temp;
    uint16_t AD2_Temp;
    uint16_t AD3_Temp;
    uint16_t AD4_Temp;
    uint16_t AD5_Temp;
    uint16_t AD6_Temp;
    uint16_t AD7_Temp;
    float gf1;
    float gf2;    
    float gf3;
    bool dio3;
    bool dio4;
    bool dio5;
    bool dio6;

} LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, AD0_Temp, AD0_Temp, AD0_Temp, AD1_Temp, AD2_Temp, AD3_Temp, AD4_Temp, AD5_Temp, AD6_Temp, AD7_Temp, gf1, gf2, gf3, dio3, dio4, dio5, dio6;\n"
#else
#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, AD0_Temp, AD0_Temp, AD0_Temp, AD1_Temp, AD2_Temp, AD3_Temp, AD4_Temp, AD5_Temp, AD6_Temp, AD7_Temp, gf1, gf2, gf3, dio3, dio4, dio5, dio6;\n"
#endif

#elif defined(LOG_TESTRIGMELACS2)

//Write a conversion function, and application part for each type of logData
typedef struct
{
    uint16_t AD0;
    uint16_t AD1;
    uint16_t AD2;
    uint16_t AD3;
    uint16_t AD4;
    uint16_t AD5;
    uint16_t AD6;
    uint16_t AD7;
    uint16_t maxTopPressure;
    uint16_t minTopPressure;
    uint16_t pressAvg;
    uint16_t tempSensor;
    uint16_t tcAvg;
    float powerKWH;
    bool cpStatus;
} LOGDATA;


//The main disadvantage of the #define method is that the string is duplicated
//each time it is used, so you can end up with lots of copies of it in the
//executable, making it bigger.
#ifdef LOG_TIME_STAMP
#define LOG_TITLE_STRING  "TimeStamp, AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, maxTopPressure, minTopPressure, pressAvg, tempSensor, tcAvg, powerKWH, cpStatus;\n"
#else
#define LOG_TITLE_STRING  "AD0, AD1, AD2, AD3, AD4, AD5, AD6, AD7, maxTopPressure, minTopPressure, pressAvg, tempSensor, tcAvg, powerKWH, cpStatus;\n"
#endif

#endif

#ifdef	__cplusplus
}
#endif

#endif	/* LOG_H */

