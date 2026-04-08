/* 
 * File:   temp.h
 * Author: Bala
 *
 * Created on November 27, 2014, 10:34 AM
 */

#ifndef ANALOGSENSOR10BIT_H
#define	ANALOGSENSOR10BIT_H

#ifdef	__cplusplus
extern "C" {
#endif

int analog_sensor_10bit_init(void);
unsigned int read_board_temperature();

unsigned int read_analog_DIO7();
unsigned int read_analog_DIO6();
unsigned int read_analog_DIO5();

unsigned int read_analog_M2CUR();
unsigned int read_analog_M1CUR();
unsigned int read_analog_M2VOLT();
unsigned int read_analog_M1VOLT();
unsigned int read_analog_M2CUR_H();
unsigned int read_analog_M1CUR_H();

#ifdef	__cplusplus
}
#endif

#endif	/* ANALOGSENSOR10BIT_H */

