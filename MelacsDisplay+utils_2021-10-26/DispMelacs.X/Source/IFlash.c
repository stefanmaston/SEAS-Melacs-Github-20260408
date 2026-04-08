#include "Common.h"
#include "IFlash.h"

// Perform FLASH erase or write operation
static void Flash_Execute(void)
{
	// Disable interrupts
	INTCONbits.GIE = 0;

	// Enable writes
	EECON1bits.WREN = 1;

	// Write the magic sequence to EECON2
	EECON2 = 0x55;
	EECON2 = 0xAA;

	// Start the erase and stall the CPU while it's being performed
	EECON1bits.WR = 1;

	// Prevent any further writes
	EECON1 = 0x00;

	// Reenable interrupts
	INTCONbits.GIE = 1;
}

// Erase a 1024-byte block of FLASH
void Flash_Erase(void far rom *ptr)
{
	// Load TBLPTR with the base address of the memory block
	TBLPTR = (uint24_t) ptr;

	// Perform the erase operation
	EECON1bits.FREE = 1;
	Flash_Execute();
}

// Write a 64-byte block of FLASH
void far rom *Flash_Write(void far rom *dst, const void *src)
{
	unsigned char len;

	// Load TBLPTR with target
	TBLPTR = (uint24_t) dst;
	// Load FSR0 with the source address of the data to be written
	FSR0 = (uint16_t) src;
	
	// Write the bytes from RAM into the FLASH buffer
	len = IFLASH_WRITE_BLOCK;
	do
	{
		TABLAT = POSTINC0;
		_asm TBLWTPOSTINC _endasm;
	}
	while(--len);

	// Decrement the table pointer to keep it within the page
	_asm TBLRDPOSTDEC _endasm;

	// Perform the write operation
	EECON1bits.WR = 1;
	Flash_Execute();

	// Return a pointer to the next block to be written
	_asm TBLRDPOSTINC _endasm;
	return (void far rom *) TBLPTR;
}