/*
 * File:   display.h
 * Author: Bala
 *
 * Created on November 10, 2014, 5:01 PM
 */
#define _SUPPRESS_PLIB_WARNING
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <plib.h>
#include "pinDefines.h"
#include <stdbool.h>

#define SCREEN_WIDTH 23
#define SCREEN_HEIGHT 10

void DisplayPortInit();
void DisplayDeviceInit();
void DisplayTransmitNibble(int value);
void DisplayTransmitChar(char character);
void DisplayTransmitUnChar(char character);
void DisplayTransmitString(char * string);
void DisplayParameterAndIntValue(char * parameterName, int parameterValue);
void DisplayParameterAndFloatValue(char * parameterName, float parameterValue);
void DisplaySendClearScreen();
void DisplayRestartScreen();
void DisplayStartByteToScreen();
void DisplayStartCommunication();
void DisplayReceiveKeys();

bool getFirstKey();
bool getSecondKey();
bool getThirdKey();
bool getFourthKey();


//#define DisplayRestartScreen() (DisplayTransmitNibble(10))
//#define DisplayStartByteToScreen() (DisplayTransmitNibble(10))
//#define DisplayStartCommunication() (LAT_D_ATN = 1) //Put D_ATN to HIGH, we start to transmit the data
//#define DisplayEndCommunication() (LAT_D_ATN = 0) //Put D_ATN low, we are done transmitting the data

void DisplayDate();
void DisplayTime();
void DisplayDateTime();
void DisplayEndCommunication();
void DisplayDeviceInit();

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */

