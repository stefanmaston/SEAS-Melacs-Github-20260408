#include "Common.h"
#include "Pins.h"
#include "EPFlash.h"

// Swizzle the bit-order on newwer revisions where the bus is mirrored.
// In principle the payload may safely be stored in mirrored order without
// adjustment, while the command codes are flipped statically and only the
// address calculations flipped at run-time
#if HW_REVISION > 0
#	define EPFLASH_DIRECT(num) REVERSE(num)
#else
#	define EPFLASH_DIRECT(num) (num)
#endif

// Command code bytes
typedef enum
{
	EPFLASH_CYCLE_1_PAGE_READ                          = EPFLASH_DIRECT(0x00),
	EPFLASH_CYCLE_1_PAGE_READ_CACHE_MODE_SEQUENTIAL    = EPFLASH_DIRECT(0x31),
	EPFLASH_CYCLE_1_PAGE_READ_CACHE_MODE_LAST          = EPFLASH_DIRECT(0x3F),
	EPFLASH_CYCLE_1_PAGE_READ_FOR_INTERNAL_DATA_MOVE   = EPFLASH_DIRECT(0x00),
	EPFLASH_CYCLE_1_RANDOM_DATA_READ                   = EPFLASH_DIRECT(0x05),
	EPFLASH_CYCLE_1_READ_ID                            = EPFLASH_DIRECT(0x90),
	EPFLASH_CYCLE_1_READ_STATUS                        = EPFLASH_DIRECT(0x70),
	EPFLASH_CYCLE_1_PROGRAM_PAGE                       = EPFLASH_DIRECT(0x80),
	EPFLASH_CYCLE_1_PROGRAM_PAGE_CACHE_MODE            = EPFLASH_DIRECT(0x80),
	EPFLASH_CYCLE_1_PROGRAM_FOR_INTERNAL_DATA_MOVE     = EPFLASH_DIRECT(0x85),
	EPFLASH_CYCLE_1_RANDOM_DATA_INPUT                  = EPFLASH_DIRECT(0x85),
	EPFLASH_CYCLE_1_BLOCK_ERASE                        = EPFLASH_DIRECT(0x60),
	EPFLASH_CYCLE_1_RESET                              = EPFLASH_DIRECT(0xFF),
	EPFLASH_CYCLE_1_OTP_DATA_PROGRAM                   = EPFLASH_DIRECT(0xA0),
	EPFLASH_CYCLE_1_OTP_DATA_PROTECT                   = EPFLASH_DIRECT(0xA5),
	EPFLASH_CYCLE_1_OTP_DATA_READ                      = EPFLASH_DIRECT(0xAF),

	EPFLASH_CYCLE_2_PAGE_READ                          = EPFLASH_DIRECT(0x30),
	EPFLASH_CYCLE_2_PAGE_READ_FOR_INTERNAL_DATA_MOVE   = EPFLASH_DIRECT(0x35),
	EPFLASH_CYCLE_2_RANDOM_DATA_READ                   = EPFLASH_DIRECT(0xE0),
	EPFLASH_CYCLE_2_PROGRAM_PAGE                       = EPFLASH_DIRECT(0x10),
	EPFLASH_CYCLE_2_PROGRAM_PAGE_CACHE_MODE            = EPFLASH_DIRECT(0x15),
	EPFLASH_CYCLE_2_PROGRAM_FOR_INTERNAL_DATA_MOVE     = EPFLASH_DIRECT(0x10),
	EPFLASH_CYCLE_2_BLOCK_ERASE                        = EPFLASH_DIRECT(0xD0),
	EPFLASH_CYCLE_2_OTP_DATA_PROGRAM                   = EPFLASH_DIRECT(0x10),
	EPFLASH_CYCLE_2_OTP_DATA_PROTECT                   = EPFLASH_DIRECT(0x10),
	EPFLASH_CYCLE_2_OTP_DATA_READ                      = EPFLASH_DIRECT(0x30)
}
EPFlash_Command_t;

// Signature bytes identifying the part
uint8_t EPFlash_ID[5];


/******************************************************************************
 * Assorted low-level helper functions for performing basic I/O against the
 * chip
 ******************************************************************************/
// Delay to stay within bus timing limits. This is a no-op on this MCU
#define EPFlash_Delay()             ((void) 0)
// Release chip select at the end of a command sequence
#define EPFlash_Deselect()          ((void) (EPFLASH_CE = 1))
// Sense ready/busy feedback
#define EPFlash_Ready()             (EPFLASH_RB)
// Expose optional write-protect signal
#ifdef EPFLASH_WP
#	define EPFlash_WriteProtect()   ((void) (EPFLASH_WP = 0))
#	define EPFlash_WriteUnprotect() ((void) (EPFLASH_WP = 1))
#else
#	define EPFlash_WriteProtect()   ((void) 0)
#	define EPFlash_WriteUnprotect() ((void) 0)
#endif

static void EPFlash_Command(EPFlash_Command_t cmd)
{
	// Set read enabled to true
	EPFLASH_RE = 1;
	// Set address latch enable to false
	EPFLASH_ALE = 0;
	// Set command latch enable to true
	EPFLASH_CLE = 1;
	// Enable the chip
	EPFLASH_CE = 0;
	// Set data port to output
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;
	// Set the data bus
	EPFLASH_DATA = cmd;
	// Set write enable to low
	EPFLASH_WE = 0;
	// Delay before setting write enable
	EPFlash_Delay();
	// Set write enable to high, this will clock in the data
	EPFLASH_WE = 1;
	// Delay before readiness may be sensed
	EPFlash_Delay();
}

static void EPFlash_WriteData(const uint8_t *ptr, size_t len)
{
	uint8_t num;

	// Set command latch enable to false
	EPFLASH_CLE = 0;
	// Set address latch enable to false
	EPFLASH_ALE = 0;
	// Set data port to output
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;

	// Clock through the array of data bytes
	FSR0 = (uintptr_t) ptr;

#	define EPFlash_WriteByte() \
	( \
		/* Set the data bus */ \
		EPFLASH_DATA = POSTINC0, \
		/* Set write enable to low */ \
		EPFLASH_WE = 0, \
		/* Delay before setting write enable */ \
		EPFlash_Delay(), \
		/* Set write enable to high, this will clock in the data */ \
		EPFLASH_WE = 1 \
	)

	// Unroll the innerloop to speed up the transfer
	num = len >> 3;
	if(num)
	{
		do
		{
			/* 1 */ EPFlash_WriteByte();
			/* 2 */ EPFlash_WriteByte();
			/* 3 */ EPFlash_WriteByte();
			/* 4 */ EPFlash_WriteByte();
			/* 5 */ EPFlash_WriteByte();
			/* 6 */ EPFlash_WriteByte();
			/* 7 */ EPFlash_WriteByte();
			/* 8 */ EPFlash_WriteByte();
		}
		while(--num);
	}
	num = (uint8_t) len & 7;
	if(num)
	{
		do
			EPFlash_WriteByte();
		while(--num);
	}
}

static void EPFlash_WriteROMData(const far rom uint8_t *ptr, size_t len)
{
	// Set command latch enable to false
	EPFLASH_CLE = 0;
	// Set address latch enable to false
	EPFLASH_ALE = 0;
	// Set data port to output
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;

	// Clock through the array of data bytes
	do
	{
		// Set the data bus
		EPFLASH_DATA = *ptr++;
		// Set write enable to low
		EPFLASH_WE = 0;
		// Delay before setting write enable
		EPFlash_Delay();
		// Set write enable to high, this will clock in the data
		EPFLASH_WE = 1;
	}
	while(--len);
}

static void EPFlash_Address(void *address, uint8_t len)
{
	// Set command latch enable to false
	EPFLASH_CLE = 0;
	// Set address latch enable to true
	EPFLASH_ALE = 1;
	// Set data port to output
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;

	// Prepare to cycle through the address bytes in little-endian order
	FSR0 = (uintptr_t) address;
#	if HW_REVISION > 0
	TBLPTR = (uint24_t) EPFlash_Reverse;
#	endif

	// Clock through the address bytes
	do
	{
		// Set the data bus, dynamically flipping the bits if required
#		if HW_REVISION > 0
		TBLPTRL = POSTINC0;
		_asm
			TBLRD
		_endasm
		EPFLASH_DATA = TABLAT;
#		else
		EPFLASH_DATA = POSTINC0;
#		endif
		// Set write enable to low
		EPFLASH_WE = 0;
		// Delay before setting write enable
		EPFlash_Delay();
		// Set write enable to high, this will clock in the data
		EPFLASH_WE = 1;
	}
	while(--len);
}

static void EPFlash_ReadData(void *ptr, ptrdiff_t len)
{
	uint8_t num;

	// Set command latch enable to false
	EPFLASH_CLE = 0;
	// Set address latch enable to false
	EPFLASH_ALE = 0;
	// Set the data port to input
	EPFLASH_TRIS = EPFLASH_TRIS_READ;

	// Clock through the array of data bytes
	FSR0 = (uintptr_t) ptr;

#	define EPFlash_ReadByte() \
	( \
		/* Set read enabled to low */ \
		EPFLASH_RE = 0, \
		/* Delay before reading */ \
		EPFlash_Delay(), \
		/* Read flash */ \
		POSTINC0 = EPFLASH_DATA, \
		/* Set read enable to high */ \
		EPFLASH_RE = 1 \
	)

	// Unroll the innerloop to speed up the transfer
	num = len >> 3;
	if(num)
	{
		do
		{
			/* 1 */ EPFlash_ReadByte();
			/* 2 */ EPFlash_ReadByte();
			/* 3 */ EPFlash_ReadByte();
			/* 4 */ EPFlash_ReadByte();
			/* 5 */ EPFlash_ReadByte();
			/* 6 */ EPFlash_ReadByte();
			/* 7 */ EPFlash_ReadByte();
			/* 8 */ EPFlash_ReadByte();
		}
		while(--num);
	}
	num = (uint8_t) len & 7;
	if(num)
	{
		do
			EPFlash_ReadByte();
		while(--num);
	}

	// Reset data port to the output state
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;
}

static uint8_t EPFlash_ReadStatus(void)
{
	uint8_t status;
	EPFlash_Command(EPFLASH_CYCLE_1_READ_STATUS);
	EPFlash_ReadData(&status, sizeof status);
	return status;
}


/******************************************************************************
 * Initialize the FLASH device
 ******************************************************************************/
bool EPFlash_Init(void)
{
	static /* const */ uint8_t address = 0x00;

	// Disable the chip
	EPFLASH_CE = 1;
	// Set address latch enable to false
	EPFLASH_ALE = 0;
	// Set command latch enable to false
	EPFLASH_CLE = 0;
	// Set write enable to low
	EPFLASH_WE = 0;
	// Set read enable to high
	EPFLASH_RE = 1;
	// Enable write protection
	EPFlash_WriteProtect();
	// Reset the data bus
	EPFLASH_TRIS = EPFLASH_TRIS_WRITE;
	EPFLASH_DATA = 0xFF;

	// Read out the device ID number
	EPFlash_Command(EPFLASH_CYCLE_1_READ_ID);
	EPFlash_Address(&address, 2);
	EPFlash_ReadData(EPFlash_ID, sizeof EPFlash_ID);
	EPFlash_Deselect();

	// Todo: Validate the ID
	return true;
}


/******************************************************************************
 * Wipe a block of data
 ******************************************************************************/
bool EPFlash_Erase(uint32_t address)
{
	uint8_t status;

	// Disable write protection
	EPFlash_WriteUnprotect();

	// Send the command and target address
	EPFlash_Command(EPFLASH_CYCLE_1_BLOCK_ERASE);
	address >>= EPFLASH_PAGE_BIT;
	EPFlash_Address(&address, 3);
	EPFlash_Command(EPFLASH_CYCLE_2_BLOCK_ERASE);

	// Wait for the erase to complete
	while(!EPFlash_Ready());
	EPFlash_Deselect();

	// Reenable write protection
	EPFlash_WriteProtect();

	// Check the status code to see whether the erasesucceeded
	status = EPFlash_ReadStatus();
	EPFlash_Deselect();
	return status == EPFLASH_DIRECT(0xE0);
}


/******************************************************************************
 * Write a RAM buffer to the FLASH. The caller is responsible for erasing the
 * pages first
 ******************************************************************************/
// Program a chunk of data within a page
static void EPFlash_WritePagePrepare(uint32_t address, size_t length)
{
	uint16_t offset;

	// Disable write protection
	EPFlash_WriteUnprotect();

	// Send the command and target address
	EPFlash_Command(EPFLASH_CYCLE_1_PROGRAM_PAGE);
	offset = (uint16_t) address & EPFLASH_PAGE_MASK;
	EPFlash_Address(&offset, 2);
	address >>= EPFLASH_PAGE_BIT;
	EPFlash_Address(&address, 3);
}

static bool EPFlash_WritePageCommit(void)
{
	uint8_t status;

	// Launch the write and wait for it to complete
	EPFlash_Command(EPFLASH_CYCLE_2_PROGRAM_PAGE);
	while(!EPFlash_Ready());
	EPFlash_Deselect();

	// Reenable write protection
	EPFlash_WriteProtect();

	// Check the status code to see whether the write succeeded
	status = EPFlash_ReadStatus();
	EPFlash_Deselect();
	return status == EPFLASH_DIRECT(0xE0);
}

// Use the page write function to write a contiguous array of data possibly
// spanning page boundaries
bool EPFlash_Write(uint32_t address, const uint8_t *data, size_t length)
{
	while(length)
	{
		// Split up the operation into smaller chunks not crossing pages
		size_t chunk = -((ptrdiff_t) address | -EPFLASH_PAGE_SIZE);
		if(chunk >= length)
			chunk = length;
		length -= chunk;

		// Write one page of data
		EPFlash_WritePagePrepare(address, chunk);
		EPFlash_WriteData(data, chunk);
		if(!EPFlash_WritePageCommit())
			return false;

		address += chunk;
		data += chunk;
	}

	return true;
}

// Similarly write constant data from the internal FLASH
bool EPFlash_WriteROM(uint32_t address, const far rom uint8_t *data,
	uint24_t length)
{
	while(length)
	{
		// Split up the operation into smaller chunks not crossing pages
		size_t chunk = -((ptrdiff_t) address | -EPFLASH_PAGE_SIZE);
		if(chunk >= length)
			chunk = length;
		length -= chunk;

		// Write one page of data
		EPFlash_WritePagePrepare(address, chunk);
		EPFlash_WriteROMData(data, chunk);
		if(!EPFlash_WritePageCommit())
			return false;

		address += chunk;
		data += chunk;
	}

	return true;
}


/******************************************************************************
 * Read out an array of data from the FLASH into a RAM buffer
 ******************************************************************************/
static void EPFlash_ReadPage(uint32_t address, uint8_t *data, size_t length)
{
	uint16_t offset;

	// Send the command and read address
	EPFlash_Command(EPFLASH_CYCLE_1_PAGE_READ);
	offset = (uint16_t) address & EPFLASH_PAGE_MASK;
	EPFlash_Address(&offset, 2);
	address >>= EPFLASH_PAGE_BIT;
	EPFlash_Address(&address, 3);

	// Wait for the page to be latched into the internal buffer
	EPFlash_Command(EPFLASH_CYCLE_2_PAGE_READ);
	while(!EPFlash_Ready());

	// Finally read out the actual payload
	EPFlash_ReadData(data, length);
	EPFlash_Deselect();
}

void EPFlash_Read(uint32_t address, uint8_t *data, size_t length)
{
	while(length)
	{
		// Split up the operation into smaller chunks not crossing pages
		size_t chunk = -((ptrdiff_t) address | -EPFLASH_PAGE_SIZE);
		if(chunk >= length)
			chunk = length;
		length -= chunk;

		EPFlash_ReadPage(address, data, chunk);
		address += chunk;
		data += chunk;
	}
}


/******************************************************************************
 * Clock through an array of raw data straight from the FLASH onto display
 * memory via the shared bus
 ******************************************************************************/
// Externally optimized helper function unrolling the basic transfer loop
/* void EPFlash_DisplayPage(uint16_t length : 12); */
#define EPFlash_DisplayPage(length) \
(FSR0 = length, _EPFlash_DisplayPage())
extern void _EPFlash_DisplayPage(void);

void EPFlash_Display(uint32_t address, uint24_t length)
{
	if(length)
	{
		uint16_t offset;

		// Send the initial read and address
		EPFlash_Command(EPFLASH_CYCLE_1_PAGE_READ);
		offset = (uint16_t) address & EPFLASH_PAGE_MASK;
		EPFlash_Address(&offset, 2);
		address >>= EPFLASH_PAGE_BIT;
		EPFlash_Address(&address, 3);

		// Wait for the first page to be latched into the internal buffer
		EPFlash_Command(EPFLASH_CYCLE_2_PAGE_READ);
		while(!EPFlash_Ready());

		do
		{
			// Split up the operation into smaller chunks not crossing pages
			size_t chunk = -((ptrdiff_t) offset | -EPFLASH_PAGE_SIZE);
			EPFlash_Command_t cmd = EPFLASH_CYCLE_1_PAGE_READ_CACHE_MODE_SEQUENTIAL;
			if(chunk >= length)
			{
				chunk = length;
				cmd = EPFLASH_CYCLE_1_PAGE_READ_CACHE_MODE_LAST;
			}
			length -= chunk;

			// Latch the previous page into the internal cache while beginning
			// a double-buffered read of the next page in the background, unless
			// this was the last one
			EPFlash_Command(cmd);
			while(!EPFlash_Ready());

			// Use a random data read to set a non-zero offset on the first
			// iteration
			if(offset)
			{
				EPFlash_Command(EPFLASH_CYCLE_1_RANDOM_DATA_READ);
				EPFlash_Address(&offset, 2);
				EPFlash_Command(EPFLASH_CYCLE_2_RANDOM_DATA_READ);
				offset = 0;
			}

			// Now clock through a chunk of data within a page 
			EPFLASH_CLE = 0;
			EPFLASH_ALE = 0;
			EPFLASH_TRIS = EPFLASH_TRIS_READ;
			EPFlash_DisplayPage(chunk);
			EPFLASH_TRIS = EPFLASH_TRIS_WRITE;
		}
		while(length);

		EPFlash_Deselect();
	}
}