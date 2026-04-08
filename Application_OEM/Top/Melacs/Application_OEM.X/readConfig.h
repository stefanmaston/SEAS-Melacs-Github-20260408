/* 
 * File:   readConfig.h
 * Author: Bala
 *
 * Created on June 3, 2015, 4:04 PM
 */

#ifndef READCONFIG_H
#define	READCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PARAMETER_FILE_SIZE 800
#define NUM_OF_PARAMETERS 20
#define LENGTH_VARIABLE_NAME 25
#define LENGTH_VARIABLE_VALUES 16

int readConfig(char * filename);

#ifdef	__cplusplus
}
#endif

#endif	/* READCONFIG_H */

