#define _SUPPRESS_PLIB_WARNING

#include "main.h"

#ifdef _SENSOR_VALUE_CONV_FUNC_

#include "stdint.h"

//const uint16_t hexThermocouple[68] = {0, 33, 66, 83, 100, 133, 167, 201, 270, 338, 406, 473, 540, 605, 671, 737, 804, 871, 939, 1007, 1075, 1144, 1213, 1283, 1352, 1422, 1492, 1562, 1632, 1702, 1772, 1843, 1913, 1983, 2053, 2123, 2193, 2263, 2332, 2402, 2471, 2540, 2574, 2608, 2676, 2744, 2811, 2879, 2945, 3012, 3078, 3143, 3209, 3274, 3338, 3403, 3467, 3530, 3594, 3657, 3719, 3782, 3843, 3905, 3966, 4026, 4086, 4145};
//const uint16_t tempThermocouple[68] = {0, 10, 20, 25, 30, 40, 50, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 260, 280, 300, 320, 340, 360, 380, 400, 420, 440, 460, 480, 500, 520, 540, 560, 580, 600, 620, 640, 660, 680, 700, 720, 740, 750, 760, 780, 800, 820, 840, 860, 880, 900, 920, 940, 960, 980, 1000, 1020, 1040, 1060, 1080, 1100, 1120, 1140, 1160, 1180, 1200, 1220, 1240};

//Board Temperature, MCP9700
int getMC9700TempFromHex(int hexTemperature)
{
    int boardTemp = 0;
    float boardTempVolt;
    boardTempVolt = hexTemperature*3300.0/1023.0;
    boardTempVolt = boardTempVolt - 500;
    boardTemp = boardTempVolt/10;
    return boardTemp;
}

//Thermocouple
const float hexTempConst = 3.357;

int getTChexToTemp(int hexTemperature)
{
    return hexTemperature/hexTempConst;
}

#if UNUSED
//Pressure Sensor
int getMLH060BGB01BhexToBar(int hexPressure)
{
    float pressureTop = 0.0;
    pressureTop = (((float)hexPressure - 834.0) * 60.0)/3336.0;
    return pressureTop;
}

//0.5v = 0bar
//0.5v + 0.0667v = 1bar
//3.3v = 41.97bar
//4.5v = 60bar

int getMLH060BGB01AhexToBar_(int hexPressure)
{
    float pressureTop = 0.0;
    pressureTop = (((float)hexPressure - 620.0)/82.76);
    return pressureTop;
}
#endif
//0 bar = 335mv = 416
//60 bar = 3025mv = 3754
// 3300mv = 4095
//1bar =  335mv  + 44.83 mv = 416 + 55.63 hex per bar
int getMLH060BGB01AhexToBar(int hexPressure)
{
    float pressureTop = 0.0;
    pressureTop = (((float)hexPressure - 416.0)/55.63);
    return pressureTop;
}


const uint16_t hexTemperatureNTC[25] = {4751, 3971, 3300, 2732, 2257, 1860, 1534, 1267, 1048, 873, 732, 611, 511, 432, 367, 310, 263, 225, 194, 166, 144, 125, 108, 95, 83};
const int8_t temperatureNTC[25] = {-20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};

//Heater Temperature
int getES120_0034TempFromHex(int hexTemperature)
{
    int j = 0;
    float tempSensor = 0.0;
    float tmp1 = 0.0;
    float tmp2 = 0.0;

    for(j = 0; j < 25; j++)
    {
        if(hexTemperature >= hexTemperatureNTC[j])
            break;
    }

    if(25 == j)
    {
        tempSensor = 100;
    }
    else
    {
        tmp1 = ((float)(temperatureNTC[j] - temperatureNTC[j-1])/(float)(hexTemperatureNTC[j] - hexTemperatureNTC[j-1]));
        tmp2 = (float)(hexTemperature - hexTemperatureNTC[j - 1])* tmp1;
        tempSensor = (float)temperatureNTC[j - 1] + tmp2;
    }

    return tempSensor;
}

#endif