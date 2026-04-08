#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _SENSOR_VALUE_CONV_FUNC_

#include "stdint.h"
#include "OnboardADC.h"
#include "sensorValueConversion.h"
#include "analogSensor10bit.h"

int getBoardTemperature()
{
    int boardTemp = 0;
    boardTemp = read_board_temperature(); //Board Temperature sensor 10mv per deg cels
    return getMC9700TempFromHex(boardTemp);
}
#ifdef _ONBOARD_ADC_FUNC_
int getEngineTemperature()
{
    return getES120_0034TempFromHex(adcresult[6]);
}

int getCoolantReturnTemperature()
{
    return getES120_0034TempFromHex(adcresult[1]);
}

int getPressureTop()
{
    return getMLH060BGB01AhexToBar(adcresult[5]);
}

int getPressureSecond()
{
    return getMLH060BGB01AhexToBar(adcresult[4]);
}

int getThermocoupleTemp()
{
    return getTChexToTemp(adcresult[7]);
}

int getThermocoupleTempAD(int hexValue)
{
    return getTChexToTemp(hexValue);
}

int getPressure(int port)
{
    return getMLH060BGB01AhexToBar(adcresult[port]);
}

int getTCTemperature(int port)
{
    return getTChexToTemp(adcresult[port]);
}

int getTemperature(int port)
{
    return getES120_0034TempFromHex(adcresult[port]);
}
#endif
#endif