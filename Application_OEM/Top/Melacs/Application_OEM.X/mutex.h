/* 
 * File:   spiMutex.h
 * Author: Bala
 *
 * Created on October 28, 2015, 5:13 PM
 */

#ifndef MUTEX_H
#define	MUTEX_H

#ifdef	__cplusplus
extern "C" {
#endif
typedef enum
{ 
    FREE,
    CSLAN,
    CSSD,
    CSRTCADC,
    CSDISPLAY,
    NUM_OF_ID
            
  
}Mutex_Identifier_t;

void spiMutexInit();
void spiLockMutex();
void spiUnlockMutex();
int spiTrylockMutex();

//bool SpiLockMutex(Mutex_Identifier_t ID);
//bool SpiUnlockMutex(Mutex_Identifier_t ID);
bool SpiLockMutex();
bool SpiUnlockMutex();

void bufWriteMutexInit();
void bufWriteLockMutex();
void bufWriteUnlockMutex();

void bufReadMutexInit();
void bufReadLockMutex();
void bufReadUnlockMutex();

void speedControlMutexInit();
void speedControlLockMutex();
void speedControlUnlockMutex();



#ifdef	__cplusplus
}
#endif

#endif	/* MUTEX_H */

