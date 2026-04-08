#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _COMMON_FUNC_


#include "common.h"
#include <string.h>
#include <stdio.h>

//http://www.microchip.com/forums/m536287.aspx
void floatToAscii(char * buf, float val, int base)
{
    char str[16];
    sprintf(str, "%d.%03d", (int)val, (int)(1000*val - (int)val*1000));
    strncpy(buf, str, 6);    
    buf[6] = 0;
}

#if 0
void floatToAscii_(char * buf, float val, int base)
{
    char paraValChar[MAX_FLOAT_LENGTH];
    int intVal = (int)val;

    float deciPart = val - intVal;
    if (deciPart < 0) {
        deciPart = -deciPart;
    }

    itoa(buf, intVal, base);

    while (1) {
        deciPart = deciPart * 10;

        intVal = deciPart;

        if(intVal > 1000)
            break;

        if (intVal % 10 == 0) {
            intVal = intVal / 10;
            break;
        }
    }

    strncat(buf, ".", 1);

    itoa(paraValChar, intVal, base);

    strncat(buf, paraValChar, strlen(paraValChar));
}

#endif

#endif
