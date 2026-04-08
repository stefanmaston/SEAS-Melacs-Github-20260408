/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2008 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
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
#define _SUPPRESS_PLIB_WARNING
#include <sys.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
//#include <string.h>
#include "onBoardADC.h"
#include "onBoardRTCC.h"
#include "log.h"
#include "common.h"
#include "main.h"
#include "sd_spi.h"
#include "stdlib.h"
#include "modbus_data_storage.h"

#ifdef LOGGING
static char filenamestring[MAXSTRINGLEN];
static char buf[DIRSIZE];  
static int fLogFile;
static int fileSize = 0;
static int fileSuffix = 0;
static int oldFileSuffix = -1;
static int timeIndex = 0;

extern time_t previousLoggedTime; //Should be initialised during the start of the time, clock_init
extern Mode_Reading_t Mode_Reading;
extern int itoa(char*, int, int);

LOGDATA logData;

#if defined(LOG_GENERAL)
//Initialise the log data parameters.
void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.DIO0 = 0;
    logData.DIO1 = 0;
    logData.DIO2 = 0;
    logData.DIO3 = 0;
    logData.DIO4 = 0;
    logData.DIO5 = 0;
    logData.DIO6 = 0;
    logData.DIO7 = 0;
    logData.SIP0 = 0;
    logData.SIP1 = 0;
    logData.SIP2 = 0;
    logData.SIP3 = 0;
    logData.SIP4 = 0;
    logData.SIP5 = 0;
    logData.SIP6 = 0;
    logData.SIP7 = 0;
    logData.M1DIS = 0;
    logData.M1ALI = 0;
    logData.M1BLI = 0;
    logData.M1AHI_PWM = 0;
    logData.M1BHI_PWM = 0;
    logData.M2DIS = 0;
    logData.M2ALI = 0;
    logData.M2BLI = 0;
    logData.M2AHI_PWM = 0;
    logData.M2BHI_PWM = 0;
    logData.boardTemp = 0;
    logData.pressure = 0;
    logData.engineTemperature = 0;
    logData.heaterTemperature = 0;
    logData.valueFloat = 3.14;
    strcpy(logData.message,"NoMessage");
}


#define LENGTH_LOG_STRING 250

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif

    itoa(paraValChar, logData.AD0, 10);
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO0, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.DIO7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP0, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.SIP7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M1DIS, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M1ALI, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M1BLI, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M1AHI_PWM, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M1BHI_PWM, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M2DIS, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M2ALI, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M2BLI, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M2AHI_PWM, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.M2BHI_PWM, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.boardTemp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.pressure, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.engineTemperature, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.heaterTemperature, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    floatToAscii(paraValChar, logData.valueFloat, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    strncat(logString, logData.message, strlen(logData.message) + 1);

    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}


#elif defined(LOG_STIRLING_GASKIT)

void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.burnerPotEnable = 0;
    logData.keyStatus = 0;
    logData.radiatorPotEnable = 0;
    logData.pageChangeEnable = 0;
    logData.circulationPump = 0;
    logData.fuelFeed = 0;
    logData.radiatorFanVoltage = 0;
    logData.burnerFanVoltage = 0;
    logData.boardTemp = 0;
    logData.maxPressure = 0;
    logData.minPressure = 0;
    logData.pressureNow = 0;
    logData.engineTemperature = 0;
    logData.heaterTemperature = 0;
    logData.tcLowerHystersisThreshold = 0;
    logData.tcHigherHystersisThreshold = 0;    
}


#define LENGTH_LOG_STRING 160

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD0);
    
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD1);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD2);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD3);    
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD4);    
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD5);  
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD6); 
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.AD7); 
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.burnerPotEnable);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.keyStatus);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.radiatorPotEnable);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.pageChangeEnable);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.circulationPump);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.fuelFeed);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    floatToAscii(paraValChar, logData.radiatorFanVoltage, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    floatToAscii(paraValChar, logData.burnerFanVoltage, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.boardTemp);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.maxPressure);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.minPressure);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.pressureNow);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.engineTemperature);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.heaterTemperature);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.tcLowerHystersisThreshold);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    snprintf(paraValChar, sizeof(paraValChar), "%d", logData.tcHigherHystersisThreshold);     
    strncat(logString, paraValChar, strlen(paraValChar) + 1);

    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}

#elif defined(LOG_OEM)


void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.keyStatus = 0;
    logData.circulationPump = 0;
    logData.boardTemp = 0;
    logData.maxPressure = 0;
    logData.minPressure = 0;
    logData.pressureNow = 0;
    logData.engineTemperature = 0;
    logData.heaterTemperature = 0;
    logData.releaseValve = 0;
    logData.fillValve = 0;
    logData.error = 0;
    logData.ErrorCode = 0;
}


#define LENGTH_LOG_STRING 160

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif
    itoa(paraValChar, Mode_Reading.POWERUP_COUNTER, 10);
    itoa(paraValChar, logData.AD0, 10);
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.keyStatus, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.circulationPump, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.boardTemp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.maxPressure, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.minPressure, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.pressureNow, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.engineTemperature, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.heaterTemperature, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.releaseValve, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.fillValve, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.error, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.ErrorCode, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}


#elif defined(LOG_TESTRIG)


void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.AD0_Temp = 0;
    logData.AD1_Temp = 0;
    logData.AD2_Temp = 0;
    logData.AD3_Temp = 0;
    logData.AD4_Temp = 0;
    logData.AD5_Temp = 0;
    logData.AD6_Temp = 0;
    logData.AD7_Temp = 0;
}


#define LENGTH_LOG_STRING 160

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif

    itoa(paraValChar, logData.AD0, 10);
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD0_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD0_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}



#elif defined(LOG_TESTRIGMELACS1)


void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.AD0_Temp = 0;
    logData.AD1_Temp = 0;
    logData.AD2_Temp = 0;
    logData.AD3_Temp = 0;
    logData.AD4_Temp = 0;
    logData.AD5_Temp = 0;
    logData.AD6_Temp = 0;
    logData.AD7_Temp = 0;
    logData.gf1 = 0.0;
    logData.gf2 = 0.0;    
    logData.gf3 = 0.0;   
    logData.dio3 = 0;
    logData.dio4 = 0;
    logData.dio5 = 0;
    logData.dio6 = 0;
}


#define LENGTH_LOG_STRING 160

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif

    itoa(paraValChar, logData.AD0, 10);
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD0_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD0_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7_Temp, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);
    
    floatToAscii(paraValChar, logData.gf1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    floatToAscii(paraValChar, logData.gf2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    
    
    floatToAscii(paraValChar, logData.gf3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);       
    
    itoa(paraValChar, logData.dio3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    

    itoa(paraValChar, logData.dio4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    

    itoa(paraValChar, logData.dio5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    

    itoa(paraValChar, logData.dio6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    
    
    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}


#elif defined(LOG_TESTRIGMELACS2)


void logDataInit()
{
    logData.AD0 = 0;
    logData.AD1 = 0;
    logData.AD2 = 0;
    logData.AD3 = 0;
    logData.AD4 = 0;
    logData.AD5 = 0;
    logData.AD6 = 0;
    logData.AD7 = 0;
    logData.maxTopPressure = 0;
    logData.minTopPressure = 0;
    logData.pressAvg = 0;
    logData.tempSensor = 0;
    logData.tcAvg = 0;
    logData.powerKWH = 0.0;
    logData.cpStatus = 0;
}


#define LENGTH_LOG_STRING 160

char * getLogString(char * logString)
{
    char paraValChar[MAX_INTEGER_LENGTH];

#ifdef LOG_TIME_STAMP
    itoa(paraValChar, yr, 10);
    strcpy( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mt, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, dy, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, hr, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, mn, 10);
    strcat( logString, paraValChar);
    strcat( logString, ":");

    itoa(paraValChar, sc, 10);
    strcat( logString, paraValChar);
    strcat( logString, ",");
#endif

    itoa(paraValChar, logData.AD0, 10);
#ifdef LOG_TIME_STAMP
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
#else
    strncpy(logString, paraValChar, strlen(paraValChar) + 1);
#endif
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD1, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD2, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD3, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD4, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD5, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD6, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.AD7, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.maxTopPressure, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.minTopPressure, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.pressAvg, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.tempSensor, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);

    itoa(paraValChar, logData.tcAvg, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);
   
    floatToAscii(paraValChar, logData.powerKWH, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);  
    
    itoa(paraValChar, logData.cpStatus, 10);
    strncat(logString, paraValChar, strlen(paraValChar) + 1);
    strncat(logString, ",", 1);    
   
    //Write a new line after the last parameter has been written
    strncat(logString, ";\n",3);
    //strcpy(logString,"This is the string to log");

    return logString;
}


#endif

void logInit()
{

        //previousLoggedTime = sc;
        /* first create a directory and then fill it with the number of requried files */
        /* note that the execute permission on the directory is required */
	if(mkdir(DIRSTRING, S_IRWXU) == -1)
	{
            if(EEXIST == errno)
            {
                xprintf("Directory already exists, %d\n", errno);
            }
            else
            {
                xprintf("Creating directory failed, the error is, %d\n", errno);
                return;
            }
	}
	else
        {
            xprintf("mkdir ok %s\n", DIRSTRING);
        }

        logDataInit();
}

#ifndef LOG_RUN

void logRun(void)
{
	int writechars;
	struct timespec currentTime;
        
	xprintf("logRun function!\n");

	clock_gettime(CLOCK_REALTIME, &currentTime);
	xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);

        if(currentTime.tv_sec < previousLoggedTime)
        {
            if((currentTime.tv_sec + 60) < (previousLoggedTime + SAMPLE_PERIOD)) //Check Bala, untested
            {
                xprintf("Not ready to log yet");
                return;
            }
        }
        else if(currentTime.tv_sec < (previousLoggedTime + SAMPLE_PERIOD))
        {
            xprintf("Not ready to log yet");
            return;
        }

        previousLoggedTime = currentTime.tv_sec;

        if(oldFileSuffix != fileSuffix)
        {
            while(1)
            {
                memset((void*)filenamestring, 0, MAXSTRINGLEN);
                memset((void*)buf, 0, DIRSIZE);

                strcpy( filenamestring, DIRSTRING);
                strcat( filenamestring, LOG_FIRST);

                char tmpBuff[MAX_INTEGER_LENGTH];
                itoa(tmpBuff, yr, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, mt, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, dy, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, hr, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, mn, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, sc, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                strcat( filenamestring, "T");
                itoa(tmpBuff, timeIndex, 10);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                itoa(tmpBuff, fileSuffix, 10);
                strcat( filenamestring, tmpBuff);

                strcat( filenamestring, LOG_EXTENSION);

                xprintf("openingx§ %s\n", filenamestring);
                if((fLogFile = open( filenamestring, O_RDWR, 0)) == -1)
                {
                        //File does not exist, we can create a new one
                        break;
                }
                else
                {
                        //File is already existing
                        timeIndex++;
                }
            }
            
            xprintf("opening %s\n", filenamestring);
            if((fLogFile = open( filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", fLogFile, errno, MAXOPENFILES);
                return;
            }

            if(-1 == lseek(fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", fLogFile, errno);
                return;
            }

            oldFileSuffix = fileSuffix;
        }
        else
        {
            xprintf("openingx§ %s\n", filenamestring);
            if((fLogFile = open( filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", fLogFile, errno, MAXOPENFILES);
                return;
            }

            if(-1 == lseek(fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", fLogFile, errno);
                return;
            }            
        }

        char lineString[100];
        int i = 0;
        for(i = 0; i < 8; i++)
        {
            char paraValChar[MAX_INTEGER_LENGTH];
#ifdef _ONBOARD_ADC_FUNC_
            itoa(paraValChar, adcresult[i], 10);
#endif
            if(0 == i)
            {
                strncpy(lineString, paraValChar, strlen(paraValChar) + 1);
            }
            else
            {
                strncat(lineString, paraValChar, strlen(paraValChar) + 1);
            }

            if(7 == i)
            {
                strncat(lineString, ";\n",3);
            }
            else
            {
                strncat(lineString, ",", 1);
            }
        }

        xprintf("writing %s\n", lineString);
        if((writechars = write(fLogFile, lineString, strlen(lineString))) == -1)
        {
            xprintf("number of bytes written = %d, file = %d, errno = %d\n", writechars, fLogFile, errno);
            if(-1 == close(fLogFile))
            {
                xprintf("File Close failed");
            }
            return;
        }
        else
        {
            fileSize += writechars;
            xprintf("number of bytes written = %d, file = %d\n", writechars, fLogFile);
        }

        if(fileSize > MAX_FILE_SIZE_BYTES)
        {
            fileSize = 0;
            fileSuffix++;
        }

        //write(fLogFile, "\n", sizeof(char));

        if(-1 == close(fLogFile))
        {
            xprintf("File Close failed");
            return;
        }
}

#endif

static uint32_t avg_adcresult[8];
static int numLogs = 0;

int logRunAvg(int samplePeriod, int numOfSamplesInEachLog)
{
	int writechars;
	struct timespec currentTime;

	xprintf("logRun function!\n");

	clock_gettime(CLOCK_REALTIME, &currentTime);
	xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);

        if(currentTime.tv_sec < previousLoggedTime)
        {
            if((currentTime.tv_sec + 60) < (previousLoggedTime + samplePeriod))
            {
                xprintf("Not ready to log yet");
                return 0;
            }
        }
        else if(currentTime.tv_sec < (previousLoggedTime + samplePeriod))
        {
            xprintf("Not ready to log yet");
            return 0;
        }

        previousLoggedTime = currentTime.tv_sec;

        int i;
#ifdef _ONBOARD_ADC_FUNC_
        for(i = 0; i < 8; i++)
        {
            avg_adcresult[i] += adcresult[i];
        }
#endif 
        numLogs++;

        if(numLogs < numOfSamplesInEachLog)
        {
            return 0;
        }

        //Save the average to the log data
        {
            logData.AD0 = avg_adcresult[0]/numLogs;
            logData.AD1 = avg_adcresult[1]/numLogs;
            logData.AD2 = avg_adcresult[2]/numLogs;
            logData.AD3 = avg_adcresult[3]/numLogs;
            logData.AD4 = avg_adcresult[4]/numLogs;
            logData.AD5 = avg_adcresult[5]/numLogs;
            logData.AD6 = avg_adcresult[6]/numLogs;
            logData.AD7 = avg_adcresult[7]/numLogs;
        }

        numLogs = 0;

        //Set the avg value to zero, after we have enough samples
        avg_adcresult[0] = 0;
        avg_adcresult[1] = 0;
        avg_adcresult[2] = 0;
        avg_adcresult[3] = 0;
        avg_adcresult[4] = 0;
        avg_adcresult[5] = 0;
        avg_adcresult[6] = 0;
        avg_adcresult[7] = 0;

        if(oldFileSuffix != fileSuffix)
        {
            while(1)
            {
                memset((void*)filenamestring, 0, MAXSTRINGLEN);
                memset((void*)buf, 0, DIRSIZE);

                strcpy( filenamestring, DIRSTRING);
                strcat( filenamestring, LOG_FIRST);

                char tmpBuff[MAX_INTEGER_LENGTH];
                snprintf(tmpBuff, sizeof(tmpBuff), "%d", yr);                     
                
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", mt);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", dy);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", hr);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", mn);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", sc);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                strcat( filenamestring, "T");
                snprintf(tmpBuff, sizeof(tmpBuff), "%d", timeIndex);
                strcat( filenamestring, tmpBuff);
                strcat( filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", fileSuffix);
                strcat( filenamestring, tmpBuff);

                strcat( filenamestring, LOG_EXTENSION);
                xprintf("openingx§ %s\n", filenamestring);

                if((fLogFile = open( filenamestring, O_RDWR, 0)) == -1)
                {
                        //File does not exist, we can create a new one
                        break;
                }
                else
                {
                        //File is already existing
                        timeIndex++;
                }
            }
            
            xprintf("opening %s\n", filenamestring);
            if((fLogFile = open( filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", fLogFile, errno, MAXOPENFILES);
                return -1;
            }

            if(-1 == lseek(fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", fLogFile, errno);
                return -2;
            }

            oldFileSuffix = fileSuffix;

            //Write the Title String in Each File
            
            xprintf("writing %s\n", LOG_TITLE_STRING);
            if((writechars = write(fLogFile, LOG_TITLE_STRING, strlen(LOG_TITLE_STRING))) == -1)
            {
                xprintf("number of bytes written = %d, file = %d, errno = %d\n", writechars, fLogFile, errno);
                if(-1 == close(fLogFile))
                {
                    xprintf("File Close failed");
                }
                return -3;
            }
            else
            {
                fileSize += writechars;
                xprintf("number of bytes written = %d, file = %d\n", writechars, fLogFile);
            }
            
        }
        else
        {
            xprintf("openingx§ %s\n", filenamestring);
            if((fLogFile = open( filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", fLogFile, errno, MAXOPENFILES);
                return -4;
            }

            if(-1 == lseek(fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", fLogFile, errno);
                return -5;
            }
        }

        char logString[LENGTH_LOG_STRING] = {0};

        getLogString(logString);

        xprintf("writing %s\n", logString);
        if((writechars = write(fLogFile, logString, strlen(logString))) == -1)
        {
            xprintf("number of bytes written = %d, file = %d, errno = %d\n", writechars, fLogFile, errno);
            if(-1 == close(fLogFile))
            {
                xprintf("File Close failed");
            }
            return -6;
        }
        else
        {
            fileSize += writechars;
            xprintf("number of bytes written = %d, file = %d\n", writechars, fLogFile);
        }

        if(fileSize > MAX_FILE_SIZE_BYTES)
        {
            fileSize = 0;
            fileSuffix++;
        }

        //write(fLogFile, "\n", sizeof(char));

        if(-1 == close(fLogFile))
        {
            xprintf("File Close failed");
            return -7;
        }

        return writechars;
}

static int logBurstCounter = 0;
static char burst_filenamestring[BURST_MAXPATHLEN];
static char burst_buf[DIRSIZE];
static int burst_fLogFile;
static int burst_fileSize = 0;
static int burst_fileSuffix = 0;
static int burst_oldFileSuffix = -1;
extern time_t burst_previousLoggedTime; //Should be initialised during the start of the time, clock_init
static int burst_timeIndex = 0;

void burstlogInit()
{

    //previousLoggedTime = sc;
    /* first create a directory and then fill it with the number of requried files */
    /* note that the execute permission on the directory is required */
	if(mkdir(BURST_DIRSTRING, S_IRWXU) == -1)
	{
            if(EEXIST == errno)
            {
                xprintf("Directory already exists, %d\n", errno);
            }
            else
            {
                xprintf("Creating directory failed, the error is, %d\n", errno);
                return;
            }
	}
	else
    {
        xprintf("mkdir ok %s\n", DIRSTRING);
    }

}

void logBurst(int AD_Chn_nr, int timeToBurstLog, int numOfSamplesInBurstLog)
{
	int writechars;
	struct timespec currentTime;
    //uint16_t burst_read_value[numOfSamplesInBurstLog];
    uint16_t *burst_read_value;
    int i;

	xprintf("logRun function!\n");

	clock_gettime(CLOCK_REALTIME, &currentTime);
	xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);

        if(currentTime.tv_sec < burst_previousLoggedTime)
        {
            if((currentTime.tv_sec + 60) < (burst_previousLoggedTime + LOGBURST_PERIOD))
            {
                xprintf("Not ready to increment counter");
                return;
            }
        }
        else if(currentTime.tv_sec < (burst_previousLoggedTime + LOGBURST_PERIOD))
        {
            xprintf("Not ready to increment counter");          
            return;
        }

        burst_previousLoggedTime = currentTime.tv_sec;

        logBurstCounter++;
        if(logBurstCounter < (timeToBurstLog/LOGBURST_PERIOD))
        {
            xprintf("Not ready to log");     
            return;
        }

        logBurstCounter = 0;
        
        burst_read_value = malloc(numOfSamplesInBurstLog * sizeof *burst_read_value); 

        SPI_Disable();
#ifdef _ONBOARD_ADC_FUNC_
        for(i = 0; i < numOfSamplesInBurstLog; i++)
        {
            ReadSignals();
            burst_read_value[i] = adcresult[AD_Chn_nr];
        }
#endif
        SPI_Enable();

        if(burst_oldFileSuffix != burst_fileSuffix)
        {
            while(1)
            {
                memset((void*)burst_filenamestring, 0, MAXSTRINGLEN);
                memset((void*)burst_buf, 0, DIRSIZE);

                strcpy( burst_filenamestring, BURST_DIRSTRING);
                strcat( burst_filenamestring, BURST_LOG_FIRST);

                char tmpBuff[MAX_INTEGER_LENGTH];
                snprintf(tmpBuff, sizeof(tmpBuff), "%d", yr);                
                
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", mt);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", dy);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", hr);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", mn);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", sc);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                strcat( burst_filenamestring, "AD");
                snprintf(tmpBuff, sizeof(tmpBuff), "%d", AD_Chn_nr);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                strcat( burst_filenamestring, "T");
                snprintf(tmpBuff, sizeof(tmpBuff), "%d", burst_timeIndex);
                strcat( burst_filenamestring, tmpBuff);
                strcat( burst_filenamestring, ".");

                snprintf(tmpBuff, sizeof(tmpBuff), "%d", burst_fileSuffix);
                strcat( burst_filenamestring, tmpBuff);

                strcat( burst_filenamestring, LOG_EXTENSION);

                xprintf("openingx§ %s\n", burst_filenamestring);
                if((burst_fLogFile = open( burst_filenamestring, O_RDWR, 0)) == -1)
                {
                    //File does not exist, we can create a new one
                    break;
                }
                else
                {
                    //File is already existing
                    burst_timeIndex++;
                }
            }

            xprintf("openingx§ %s\n", burst_filenamestring);
            if((burst_fLogFile = open( burst_filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", burst_fLogFile, errno, MAXOPENFILES);
                free(burst_read_value);                
                return;
            }

            if(-1 == lseek(burst_fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", burst_fLogFile, errno);
                free(burst_read_value);                
                return;
            }

            burst_oldFileSuffix = burst_fileSuffix;
        }
        else
        {
            xprintf("openingx§ %s\n", burst_filenamestring);
            if((burst_fLogFile = open( burst_filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
            {
                xprintf("files opened = %d, errno = %d, files should be %d\n", burst_fLogFile, errno, MAXOPENFILES);
                return;
            }

            if(-1 == lseek(burst_fLogFile, 0 , SEEK_END))
            {
                xprintf("files seek to end failed, fileno = %d, errno = %d\n", burst_fLogFile, errno);
                free(burst_read_value);                
                return;
            }
        }

        char lineString[numOfSamplesInBurstLog*5 + 2];

        for(i = 0; i < numOfSamplesInBurstLog; i++)
        {
            char paraValChar[MAX_INTEGER_LENGTH];

            snprintf(paraValChar, sizeof(paraValChar), "%d", burst_read_value[i]);            
            if(0 == i)
            {
                strncpy(lineString, paraValChar, strlen(paraValChar) + 1);
            }
            else
            {
                strncat(lineString, paraValChar, strlen(paraValChar) + 1);
            }

            if((numOfSamplesInBurstLog-1) == i)
            {
                strncat(lineString, ";\n",3);
            }
            else
            {
                strncat(lineString, ",", 1);
            }
        }

        xprintf("writing %s\n", lineString);
        if((writechars = write(burst_fLogFile, lineString, strlen(lineString))) == -1)
        {
            xprintf("number of bytes written = %d, file = %d, errno = %d\n", writechars, burst_fLogFile, errno);
            if(-1 == close(burst_fLogFile))
            {
                xprintf("File Close failed");
            }
            free(burst_read_value);
            return;
        }
        else
        {
            burst_fileSize += writechars;
            xprintf("number of bytes written = %d, file = %d\n", writechars, burst_fLogFile);
        }

        if(burst_fileSize > MAX_FILE_SIZE_BYTES)
        {
            burst_fileSize = 0;
            burst_fileSuffix++;
        }

        //write(burst_fLogFile, "\n", sizeof(char));
        
        free(burst_read_value);

        if(-1 == close(burst_fLogFile))
        {
            xprintf("File Close failed");
            return;
        }
}


#ifdef LOG_RUN_SAMPLE

extern void logRunSample(void)
{
	int writechars;
	struct timespec currentTime;

	xprintf("logRun function!\n");

	clock_gettime(CLOCK_REALTIME, &currentTime);
	xprintf("TIME %lu.%09u\n", (unsigned long)currentTime.tv_sec, (unsigned long)currentTime.tv_nsec);

        if(currentTime.tv_sec < previousLoggedTime)
        {
            if((currentTime.tv_sec + 60) < (previousLoggedTime + SAMPLE_PERIOD))
            {
                xprintf("Not ready to log yet");
                return;
            }
        }
        else if(currentTime.tv_sec < (previousLoggedTime + SAMPLE_PERIOD))
        {
            xprintf("Not ready to log yet");
            return;
        }

        previousLoggedTime = sc;

        memset((void*)filenamestring, 0, MAXSTRINGLEN);
	memset((void*)buf, 0, DIRSIZE);

        /* first create a directory and then fill it with the number of requried files */
        /* note that the execute permission on the directory is required */
	if(mkdir(DIRSTRING, S_IRWXU) == -1)
	{
            if(EEXIST == errno)
            {
                xprintf("Directory already exists, %d\n", errno);
            }
            else
            {
                xprintf("Creating directory failed, the error is, %d\n", errno);
                return;
            }
	}
	else
        {
            xprintf("mkdir ok %s\n", DIRSTRING);
        }

        strcpy( filenamestring, DIRSTRING);
        strcat( filenamestring, LOG_FIRST);


        xprintf("openingx§ %s\n", filenamestring);
        if((fLogFile = open( filenamestring, O_CREAT | O_RDWR | O_APPEND, 0)) == -1)
        {
            xprintf("files opened = %d, errno = %d, files should be %d\n", fLogFile, errno, MAXOPENFILES);
            return;
        }

        if(-1 == lseek(fLogFile, 0 , SEEK_END))
        {
            xprintf("files seek to end failed, fileno = %d, errno = %d\n", fLogFile, errno);
            return;
        }

        write(fLogFile, "\n", sizeof(char));

        xprintf("writing %s\n", "Pliable");
        if((writechars = write(fLogFile, "Pliable", strlen("Pliable"))) == -1)
        {
            xprintf("number of bytes written = %d, file = %d, errno = %d\n", writechars, fLogFile, errno);
            if(-1 == close(fLogFile))
            {
                xprintf("File Close failed");
            }
            return;
        }
        else
        {
            xprintf("number of bytes written = %d, file = %d\n", writechars, fLogFile);
        }

        write(fLogFile, "\n", sizeof(char));

        if(-1 == close(fLogFile))
        {
            xprintf("File Close failed");
            return;
        }
}

#endif
#endif //LOGGING