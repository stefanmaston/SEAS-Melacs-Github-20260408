/* 
 * File:   sensor.h
 * Author: Bala
 *
 * Created on June 1, 2015, 5:09 PM
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define AVG_LENGTH 10

int getBoardTemperature();
int getEngineTemperature();
int getPressureTop();
int getThermocoupleTemp();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

