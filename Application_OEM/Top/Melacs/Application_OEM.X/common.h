/* 
 * File:   common.h
 * Author: Bala
 *
 * Created on November 11, 2014, 4:21 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_INTEGER_LENGTH 8
#define MAX_FLOAT_LENGTH 8

void floatToAscii(char * buf, float val, int base);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

