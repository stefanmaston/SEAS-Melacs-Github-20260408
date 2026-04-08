


/*
 * File:   alarmCode.h
 * Author: Bala
 *
 * Created on November 9, 2015, 1:59 PM
 */

#ifndef ALARMCODE_H
#define	ALARMCODE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ALARM_A0    0 //No Alarm
#define ALARM_A1	1
#define ALARM_A2	2
#define ALARM_A3	3
#define ALARM_A4	4
#define ALARM_A5	5
#define ALARM_A6	6
#define ALARM_A7	7
#define ALARM_A8	8
#define ALARM_A9	9
#define ALARM_A10	10
#define ALARM_A11	11
#define ALARM_A12	12
#define ALARM_A13	13
#define ALARM_A14	14
#define ALARM_A15	15
#define ALARM_A16	16
#define ALARM_A17	17
#define ALARM_A18	18
#define ALARM_A19	19
#define ALARM_A20	20
#define ALARM_A21	21
#define ALARM_A22	22
#define ALARM_A23	23
#define ALARM_A24	24
#define ALARM_A25	25
#define ALARM_A26	26
#define ALARM_A27	27
#define ALARM_A28	28
#define ALARM_A29	29
#define ALARM_A30	30
#define ALARM_A31	31
#define ALARM_A32	32
#define ALARM_A33	33
#define ALARM_A34	34
#define ALARM_A35	35
#define ALARM_A36	36
#define ALARM_A37	37
#define ALARM_A38	38
#define ALARM_A39	39
#define ALARM_A40	40
#define ALARM_A41	41
#define ALARM_A42	42
#define ALARM_A43	43
#define ALARM_A44	44
#define ALARM_A45	45
#define ALARM_A46	46
#define ALARM_A47	47
#define ALARM_A48	48

    
#define ERROR_IN_COMBUSTION 101
#define ERROR_OVERCURRENT_RADIATORFAN 102
#define ERROR_OVERCURRENT_BURNERFAN 103
#define ERROR_SD_CORRUPTION 104
#define ERROR_GAS_COMBUSTION 105    

#define UNUSUAL_PRESSURE_VALUE 111 
#define UNUSUAL_ENGINE_TEMPERATURE 112
#define UNUSUAL_HEATER_TEMPERATURE 113
    
char * getErrorString(int errorCode);
        
#ifdef	__cplusplus
}
#endif

#endif	/* ALARMCODE_H */

