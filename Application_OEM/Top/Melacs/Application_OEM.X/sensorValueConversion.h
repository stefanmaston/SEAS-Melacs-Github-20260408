/* 
 * File:   sensorConversion.h
 * Author: Bala
 *
 * Created on June 2, 2015, 11:47 AM
 */

#ifndef SENSORCONVERSION_H
#define	SENSORCONVERSION_H

#ifdef	__cplusplus
extern "C" {
#endif

int getMC9700TempFromHex(int hexTemperature); //Board Temperature, MCP9700
int getTChexToTemp(int hexTemperature); //Thermocouple
int getMLH060BGB01BhexToBar(int hexPressure); //Pressure Sensor
int getMLH060BGB01AhexToBar(int hexPressure); //Pressure Sensor
int getES120_0034TempFromHex(int hexTemperature); //Heater Temperature

#ifdef	__cplusplus
}
#endif

#endif	/* SENSORCONVERSION_H */

