/******************************************************************************
 * Driver for the MT29F2G08 parallel FLASH
 ******************************************************************************/
#ifndef _EPFLASH_H
#define _EPFLASH_H

// The FLASH is programmed (and internally read) in 2kB pages
#define EPFLASH_PAGE_BIT   11
#define EPFLASH_PAGE_SIZE  0x0800
#define EPFLASH_PAGE_MASK  0x07FF
// Erase is performed on entire 128kB blocks
#define EPFLASH_ERASE_BIT  17
#define EPFLASH_ERASE_SIZE 0x20000U
#define EPFLASH_ERASE_MASK 0x1FFFFU
// The total size is 256MB/2Gb
#define EPFLASH_SIZE       0x10000000UL

// Functions
bool EPFlash_Init(void);
bool EPFlash_Erase(uint32_t address);
bool EPFlash_Write(uint32_t address, const uint8_t *data, size_t length);
bool EPFlash_WriteROM(uint32_t address, const far rom uint8_t *data,
	uint24_t length);
void EPFlash_Read(uint32_t address, uint8_t *data, size_t length);
void EPFlash_Display(uint32_t address, uint24_t length);

extern uint8_t EPFlash_ID[5];

#endif