#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _MUTEX_FUNC_
#include <sys.h>
#include "uart.h" //FOR DEBUG PURPOSE REMOVE IT WHEN THE PROBLEM HAS BEEN SOLVED THE PROBLEM IS IN SPI LINE 
#include <stdbool.h>

bool SpiLock = false;
uint8_t ERRORSTATE = 0;
pthread_mutex_t spi_mut;
pthread_mutex_t bufWrite_mut;
pthread_mutex_t bufRead_mut;
pthread_mutex_t speedControl_mut;

void spiMutexInit()
{
#ifdef SPI_MUTEX
  pthread_mutex_init(&spi_mut, 0);
#if RTOS_DEBUG
  dir_register("mutex", (uint)&spi_mut, TYPE_MUTEX);
#endif
#endif
}

void spiLockMutex()
{
#ifdef SPI_MUTEX
    if(pthread_mutex_lock(&spi_mut)!=0)
      ERRORSTATE = errno;
#endif
}

void spiUnlockMutex()
{
#ifdef SPI_MUTEX
 if(pthread_mutex_unlock(&spi_mut) !=0)
     ERRORSTATE = errno;
#endif
}
int spiTrylockMutex()
{
#ifdef SPI_MUTEX
    ERRORSTATE = pthread_mutex_trylock(&spi_mut);
       return ERRORSTATE;
#endif
}

void bufWriteMutexInit()
{
  pthread_mutex_init(&bufWrite_mut, 0);
#if RTOS_DEBUG
  dir_register("mutex", (uint)&bufWrite_mut, TYPE_MUTEX);
#endif
}
void bufWriteLockMutex()
{
  pthread_mutex_lock(&bufWrite_mut);
}

void bufWriteUnlockMutex()
{
  pthread_mutex_unlock(&bufWrite_mut);
}

void bufReadMutexInit()
{
  pthread_mutex_init(&bufRead_mut, 0);
#if RTOS_DEBUG
  dir_register("mutex", (uint)&bufRead_mut, TYPE_MUTEX);
#endif
}

void bufReadLockMutex()
{
  pthread_mutex_lock(&bufRead_mut);
}

void bufReadUnlockMutex()
{
  pthread_mutex_unlock(&bufRead_mut);
}


void speedControlMutexInit()
{
  pthread_mutex_init(&speedControl_mut, 0);
#if RTOS_DEBUG
  dir_register("mutex", (uint)&bufRead_mut, TYPE_MUTEX);
#endif
}

void speedControlLockMutex()
{
  pthread_mutex_lock(&speedControl_mut);
}

void speedControlUnlockMutex()
{
  pthread_mutex_unlock(&speedControl_mut);
}

#endif
//bool SpiLockMutex() Start of the handmade Mutex
//{
//    if(SpiLock)
//    {
//        return false;
//    }
//    else
//    {
//        SpiLock = true;
//        return true;
//    }
//}
//bool SpiUnlockMutex()
//{
//    if(!SpiLock)
//    {
//        return false;
//    }
//    else
//    {
//        SpiLock = false;
//        return true;
//    }
//} End of the Handmade Mutex