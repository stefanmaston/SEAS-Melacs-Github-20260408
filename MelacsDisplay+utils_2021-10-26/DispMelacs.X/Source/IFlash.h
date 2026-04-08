/******************************************************************************
 * Routines for writing to the processor's internal FLASH
 ******************************************************************************/
#ifndef _IFLASH_H
#define _IFLASH_H

#define IFLASH_ERASE_BLOCK 1024
#define IFLASH_WRITE_BLOCK 64
#define IFLASH_UNPROGRAMMED 0xFF

void IFlash_Erase(void far rom *ptr);
void far rom *IFlash_Write(void far rom *dst, const void *src);

#endif