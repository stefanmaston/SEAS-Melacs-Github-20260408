//Communication with display
#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef DISPLAY
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING

#include <plib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "display.h"
#include "onBoardRTCC.h"
#include "common.h"
#include "uart.h"

bool firstKey = 0;
bool secondKey = 0;
bool thirdKey = 0;
bool fourthKey = 0;

bool getFirstKey()
{
    return firstKey;
}

bool getSecondKey()
{
    return secondKey;
}

bool getThirdKey()
{
    return thirdKey;
}

bool getFourthKey()
{
    return fourthKey;
}

void setDataAsOutput()
{
    TRIS_DATA0 = 0;
    TRIS_DATA1 = 0;
    TRIS_DATA2 = 0;
    TRIS_DATA3 = 0;
}

void setDataAsInput()
{
    TRIS_DATA0 = 1;
    TRIS_DATA1 = 1;
    TRIS_DATA2 = 1;
    TRIS_DATA3 = 1;
}

void DisplayPortInit() {
    //Set bits for communication
    //TRIS_D_CLK = 0;

    TRIS_D_ATN = 0;
    TRIS_D_ACK1 = 0;

    TRIS_DATA0 = 0;
    TRIS_DATA1 = 0;
    TRIS_DATA2 = 0;
    TRIS_DATA3 = 0;

    //This is the input pin, Acknowledgement from the color display
    TRIS_D_ACK2 = 1;

    //LAT_D_CLK = 0;
    LAT_D_ACK1 = 0;
    LAT_D_ATN = 0;

    LAT_DATA0 = 0;
    LAT_DATA1 = 0;
    LAT_DATA2 = 0;
    LAT_DATA3 = 0;
}

void DisplayTransmitNibble(int value) 
{
     while (1 == D_ACK2) 
     {
     }
     
    LAT_DATA0 =  value & 0x01;
    LAT_DATA1 = (value >> 1) & 0x01;
    LAT_DATA2 = (value >> 2) & 0x01;
    LAT_DATA3 = (value >> 3) & 0x01;

    //change D_ACK1 to high, asking the receiver to grab the data
    LAT_D_ACK1 = 1;
    
    //Wait for D_ACK2 to go low
    while (0 == D_ACK2) 
    {
        //SIP1 =~SIP1;
    }

    //change D_ACK1 to low
    LAT_D_ACK1 = 0;

}

void DisplayTransmitChar(char character) {
    int ascii = (int) character;
    int send = ascii >> 4;

    DisplayTransmitNibble(send);

    send = (ascii & 0xF);

    DisplayTransmitNibble(send);
    //DisplayTransmitNibble(character);
}
void DisplayTransmitUnChar(char character)
{
    unsigned char hex_value[2];
    sprintf(hex_value, "%02X", character);
    DisplayTransmitNibble(hex_value[0]);
    DisplayTransmitNibble(hex_value[1]);

}
void DisplayStartCommunication()
{
    LAT_D_ATN = 1;
    setDataAsOutput();
}

void DisplayRestartScreen()
{
    DisplayStartCommunication();
    DisplayTransmitNibble(10);
    DisplayEndCommunication();
}

void DisplayStartByteToScreen() 
{
    DisplayStartCommunication();
    DisplayTransmitNibble(10);
    DisplayEndCommunication();
}

void DisplayEndCommunication ()
{
    LAT_D_ATN = 0;
    setDataAsInput();
}

void DisplayReceiveKeys()
{
    LAT_D_ATN = 0;
    setDataAsInput();

    firstKey = FIRST_KEY;
    secondKey = SECOND_KEY;
    thirdKey = THIRD_KEY;
    fourthKey = FOURTH_KEY;
}

void DisplayTransmitString(char * string) {
    char * tmp;
    tmp = string;

    DisplayStartCommunication();
    while ('\0' != *tmp) 
    {
        DisplayTransmitChar(*tmp);
        tmp++;
    }
    DisplayEndCommunication();
}

void DisplayParameterAndIntValue(char * parameterName, int parameterValue) 
{
    char lineString[SCREEN_WIDTH + 10];
    char paraValChar[MAX_INTEGER_LENGTH];
    int numSpaces = 0;
    int charRemaining = SCREEN_WIDTH + 10;

    if(charRemaining >= (strlen(parameterName) + 1))
    {
        /* copy to sized buffer (overflow safe): */
        strncpy(lineString, parameterName, strlen(parameterName) + 1);
        charRemaining -= (strlen(parameterName) + 1);
    }
    else
    {
        return;
    }

    if(charRemaining >= 3)
    {    
        strncat(lineString, " : ", 3);
        charRemaining -= 3;
    }    
    else
    {
        return;
    }

    snprintf(paraValChar, sizeof(paraValChar), "%d", parameterValue);     
    if(charRemaining >= strlen(paraValChar))
    {
        strncat(lineString, paraValChar, strlen(paraValChar));
        charRemaining -= strlen(paraValChar);        
    }
    else
    {
        return;
    }    

    numSpaces = SCREEN_WIDTH - strlen(lineString);

    if(numSpaces > 0)
    {    
        while (numSpaces--) {
            strncat(lineString, " ", 1);
        }
    }
    lineString[SCREEN_WIDTH] = 0;
    DisplayTransmitString(lineString);
}

void DisplayParameterAndFloatValue(char * parameterName, float parameterValue) 
{
    char lineString[SCREEN_WIDTH + 10];
    char paraValChar[MAX_FLOAT_LENGTH];
    int numSpaces = 0;
    int charRemaining = SCREEN_WIDTH + 10;

    if(charRemaining >= (strlen(parameterName) + 1))
    {
        /* copy to sized buffer (overflow safe): */
        strncpy(lineString, parameterName, strlen(parameterName) + 1);
        charRemaining -= (strlen(parameterName) + 1);
    }
    else
    {
        return;
    }    

    if(charRemaining >= 3)
    {    
        strncat(lineString, ": ", 3);
        charRemaining -= 3;
    }    
    else
    {
        return;
    }

    floatToAscii(paraValChar, parameterValue, 10);
    
    if(charRemaining >= strlen(paraValChar))
    {
        strncat(lineString, paraValChar, strlen(paraValChar));
        charRemaining -= strlen(paraValChar);        
    }
    else
    {
        return;
    }      

    numSpaces = SCREEN_WIDTH - strlen(lineString);

    if(numSpaces > 0)
    {   strncat(lineString, " V", 2);
        while (numSpaces--) {
            strncat(lineString, " ", 1);
        }
    }

    lineString[SCREEN_WIDTH] = 0;
    DisplayTransmitString(lineString);
}

void DisplaySendClearScreen() {
    int i = 0;
    for (i = 0; i < SCREEN_HEIGHT; i++) {
        DisplayTransmitString("                       ");
    }

    DisplayRestartScreen();
}

#if 0
int mainDisplay(void) {
    //Set LD1 through LD4 as digital output
    DisplayDeviceInit();

    DisplayStartCommunication();

    DisplaySendClearScreen();

    //Transmit 10 at the start, to indicate start of communication or to reset the display
    DisplayStartByteToScreen();

    /*
    while(1)
    {
            DisplayParameterAndIntValue("AN1", 1);
            DisplayParameterAndIntValue("AN2", 2);
            DisplayParameterAndIntValue("AN3", 3);
            DisplayParameterAndIntValue("AN4", 4);
            DisplayParameterAndIntValue("AN5", 5);
            DisplayParameterAndIntValue("AN6", 6);
            DisplayParameterAndIntValue("AN7", 7);
            DisplayParameterAndIntValue("AN8", 8);
            DisplayParameterAndIntValue("AN9", 9);
            DisplayParameterAndIntValue("AN10", 10);
            DisplayParameterAndIntValue("AN11", 11);
    }
     */

    while (1) {
        DisplayParameterAndIntValue("Pressure", 43);
        DisplayParameterAndIntValue("Voltage", -230);
        DisplayParameterAndFloatValue("Frequency", 50.567);
        DisplayTransmitNibble(10);
    }

    DisplayEndCommunication();

    //sleep(1);
}
#endif 


#ifdef UNUSED
void DisplayDate()
{
	char lineString[SCREEN_WIDTH];
	char paraValChar[MAX_INTEGER_LENGTH];
	int numSpaces = 0;

	/* copy to sized buffer (overflow safe): */
	strncpy(lineString, "Date", 5);
	strncat(lineString, " : ", 3);

	itoa(paraValChar,dy,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, "/", 1);

	itoa(paraValChar,mt,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, "/", 1);

	itoa(paraValChar,yr,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	numSpaces = SCREEN_WIDTH - strlen(lineString);

	while(numSpaces--)
	{
		strncat(lineString, " ", 1);
	}

	DisplayTransmitString(lineString);
}

void DisplayTime()
{
	char lineString[SCREEN_WIDTH];
	char paraValChar[MAX_INTEGER_LENGTH];
	int numSpaces = 0;

	/* copy to sized buffer (overflow safe): */
	strncpy(lineString, "Time", 5);
	strncat(lineString, " : ", 3);

	itoa(paraValChar,hr,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, ":", 1);

	itoa(paraValChar,mn,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, ":", 1);

	itoa(paraValChar,sc,10);
	strncat(lineString, paraValChar , strlen(paraValChar));

	numSpaces = SCREEN_WIDTH - strlen(lineString);

	while(numSpaces--)
	{
		strncat(lineString, " ", 1);
	}

	DisplayTransmitString(lineString);
}

#endif

void DisplayDateTime()
{
	char lineString[SCREEN_WIDTH + 10];
	char paraValChar[MAX_INTEGER_LENGTH];
	int numSpaces = 0;

	/* copy to sized buffer (overflow safe): */
	strncpy(lineString, "DT", 5);
	strncat(lineString, ": ", 3);

    snprintf(paraValChar, sizeof(paraValChar), "%02d", dy);     
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, "/", 1);

	snprintf(paraValChar, sizeof(paraValChar), "%02d", mt);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, "/", 1);

	snprintf(paraValChar, sizeof(paraValChar), "%02d", yr);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, " ", 2);

	snprintf(paraValChar, sizeof(paraValChar), "%02d", hr);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, ":", 1);

	snprintf(paraValChar, sizeof(paraValChar), "%02d", mn);
	strncat(lineString, paraValChar , strlen(paraValChar));

	strncat(lineString, ":", 1);

	snprintf(paraValChar, sizeof(paraValChar), "%02d", sc);
	strncat(lineString, paraValChar , strlen(paraValChar));

        if(strlen(lineString) < SCREEN_WIDTH)
        {
            numSpaces = SCREEN_WIDTH - strlen(lineString);

            while(numSpaces--)
            {
                    strncat(lineString, " ", 1);
            }
        }
        else
        {
            lineString[SCREEN_WIDTH - 1] = 0;
        }

	DisplayTransmitString(lineString);
}

void DisplayDeviceInit()
{
    //Set LD1 through LD4 as digital output
    DisplayPortInit();

    DisplaySendClearScreen();
    //Transmit 10 at the start, to indicate start of communication or to reset the display
    DisplayStartByteToScreen();
}

#endif