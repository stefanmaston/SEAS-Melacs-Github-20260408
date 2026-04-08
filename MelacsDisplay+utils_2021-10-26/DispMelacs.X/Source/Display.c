#include "Common.h"
#include "Display.h"
#include "EPFlash.h"
#include "Pins.h"

// Register read-back does not appear to work on the SSD2119
#define DISP_REGISTER_READBACK 0


/******************************************************************************
 * Initialization code
 ******************************************************************************/
#define DISP_DELAY(msec)        (((msec) * 4UL + 4) / 5)
#define DISP_POKE(regno, value) { DISP_REG(regno), DISP_DIRECT((value)) }
#define DISP_WAIT(msec)         { 0xFF,            DISP_DELAY(msec)     }
#define DISP_END()              { 0xFF,            0x0000               }

typedef struct
{
	uint8_t regno;
	uint16_t value;
}
Disp_CommandList;

// Execute a "script" containing register values and delays
static bool Disp_Execute(const rom Disp_CommandList *cmd)
{
	bool success = true;

	DISP_CS = 0;

	for(;;)
	{
		Disp_CommandList entry = *cmd++;

		if(entry.regno != 0xFF)
		{
			Disp_CommandDirect(entry.regno, entry.value);

			// Verify that the write actually succeeded
#			if DISP_REGISTER_READBACK
			if(Disp_ReadDirect() != entry.value)
			{
				Trace("Mismatch: %2x: %4x != %4x\n",
					(unsigned) entry.regno, entry.value, Disp_Read());
				success = false;
			}
#			endif
		}
		else if(entry.value)
			Delay10KTCYx(entry.value);
		else
			break;
	}

	DISP_CS = 1;
	return success;
}

void Disp_Init(void)
{
	// For PH320240T-022
	static const rom Disp_CommandList commands_SSD2119[] =
	{
		DISP_POKE(R28_VCOM_OTP1,     0x0006),
		DISP_POKE(R00_OSC_START,     0x0001),
		DISP_POKE(R01_DRV_OUT_CTRL,  0x72EF),
		DISP_POKE(R02_DRV_LCD_CTRL,  0x0600),

		// VGH/VGL voltage setting
		DISP_POKE(R03_PWR_CTRL1,     0x6464),
		DISP_POKE(R10_SLEEP_MODE,    0x0000),
		DISP_POKE(R11_ENTRY_MODE,    0x6430),
		DISP_WAIT(20),
		DISP_POKE(R07_DISPLAY_CTRL,  0x0033),
		DISP_WAIT(10),
		DISP_POKE(R25_FRAME_FREQ,    0xE000),
		DISP_POKE(R0B_FRAME_CYCLE,   0x5308),

		// Adjust the gamma curve
		DISP_POKE(R30_GAMMA1,        0xBFBD),
		DISP_POKE(R31_GAMMA2,        0x5247),
		DISP_POKE(R32_GAMMA3,        0xDDBA),
		DISP_POKE(R33_GAMMA4,        0x350E),
		DISP_POKE(R34_GAMMA5,        0xA6BF),
		DISP_POKE(R35_GAMMA6,        0x39BC),
		DISP_POKE(R36_GAMMA7,        0xC520),
		DISP_POKE(R37_GAMMA8,        0x341E),

		// Power on sequence
		DISP_POKE(R0C_PWR_CTRL2,     0x0005),
		DISP_WAIT(30),
		DISP_POKE(R0D_PWR_CTRL3,     0x0012),
		DISP_WAIT(30),

		// VCOMH setup
		DISP_POKE(R1E_PWR_CTRL5,     0x00E6),
		DISP_WAIT(10),

		// VCOML setup
		DISP_POKE(R0E_PWR_CTRL4,     0x2900),
		DISP_WAIT(10),
		DISP_POKE(R26_ANALOG_CTRL,   0x7C00),
		DISP_POKE(R27_UNKNOWN,       0x006D),
		DISP_END()
	};

	const rom Disp_CommandList *initialization;

	uint16_t blink = 0;

	do
	{
		// Normally start out with a blanked display, but try to blink with the
		// backlight if we're have trouble initializing the controller
		Disp_SetBacklight(blink);
		blink ^= DISP_BACKLIGHT;

		// Force reset
unknown:
		DISP_CS = 1;
		Delay10KTCYx(DISP_DELAY(10));
		DISP_RESET = 0;
		Delay10KTCYx(DISP_DELAY(10));
		DISP_RESET = 1;
		Delay10KTCYx(DISP_DELAY(10));

		// Four 8-bit writes to port 0x00 synchronizes the byte I/O
		DISP_CS = 0;
		Disp_Register(DISP_REG(R00_DRV_CODE));
		Disp_Register(DISP_REG(R00_DRV_CODE));

		// Try to detect the display controller and use the appropriate
		// initialization sequence
		switch(Disp_ReadDirect())
		{
		case DISP_DIRECT(0x9999): initialization = commands_SSD2119; break;
		default: goto unknown;
		}
	}
	// Keep trying until all initialization writes succeed
	until(Disp_Execute(initialization));
}


/******************************************************************************
 * Set the backlight intensity (0 <= level <= DISP_BACKLIGHT)
 ******************************************************************************/
void Disp_SetBacklight(uint16_t level)
{
	CCP2CON = (uint8_t) level << 4 | _B0(12);
	CCPR2L = level >> 2;
}

uint16_t Disp_GetBacklight(void)
{
	return (uint16_t) CCPR2L << 2 | CCP2CON >> 4;
}


/******************************************************************************
 * Graphics primitives
 ******************************************************************************/
static uint24_t Disp_Area(uint16_t xpos, uint8_t ypos, uint16_t xres,
	uint8_t yres)
{
	DISP_CS = 0;
	Disp_Command(DISP_REG(R4E_XRAM_ADDR), xpos);
	Disp_Command(DISP_REG(R4F_YRAM_ADDR), ypos);
	Disp_Command(DISP_REG(R45_HRAM_START), xpos);
	Disp_Command(DISP_REG(R46_HRAM_END), xpos + xres - 1);
	Disp_Register(DISP_REG(R22_RAM_PORT));
	return (uint24_t) xres * yres;
}

void Disp_Rect(uint16_t xpos, uint8_t ypos, uint16_t xres, uint8_t yres,
	uint16_t color)
{
	int24_t total;
	uint8_t toggle;
	uint8_t align;
	uint16_t count;

	total = Disp_Area(xpos, ypos, xres, yres);

	color = Disp_Direct(color);
	DISP_DATA = (uint8_t) color;
	toggle = (uint8_t) (color >> 8) ^ DISP_DATA;

	// Transfer the bulk of the pixels in an 8x unrolled loop
	if(count = total >> 3, count)
	{
		do
		{
#			define DISP_RECT_PIXEL      \
			XORWF DISP_DATA,1,0         \
			BCF DISP_CTRL,DISP_WR_BIT,0 \
			BSF DISP_CTRL,DISP_WR_BIT,0 \
			XORWF DISP_DATA,1,0         \
			BCF DISP_CTRL,DISP_WR_BIT,0 \
			BSF DISP_CTRL,DISP_WR_BIT,0

			_asm
			MOVF toggle,0,0
		
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			DISP_RECT_PIXEL
			_endasm
		}
		while(--count, count);
	}

	// Transfer the remainder
	align = (uint8_t) total & 7;

	if(align <<= 1)
	{
		do
		{
			DISP_DATA ^= toggle;
			DISP_WR = 0;
			DISP_WR = 1;
		}
		while(--align);
	}

	DISP_CS = 1;
}

// Render image stored in the internal FLASH
void Disp_IImage(uint16_t xpos, uint8_t ypos, const Disp_IImage_t *image)
{
	uint24_t total = Disp_Area(xpos, ypos, image->XRes, image->YRes);
	uint8_t align;
	uint16_t count;

	*image->Data;

#	define DISP_IMAGE_BYTE      \
	_asm                        \
	TBLRDPOSTINC                \
	MOVFF TABLAT,DISP_DATA      \
	BTG DISP_CTRL,DISP_WR_BIT,0 \
	BTG DISP_CTRL,DISP_WR_BIT,0 \
	_endasm

	// Transfer the bulk of the pixels in an 8x unrolled loop
	if(count = total >> 3, count)
	{
		do
		{
			DISP_IMAGE_BYTE DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE	DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE	DISP_IMAGE_BYTE
			DISP_IMAGE_BYTE	DISP_IMAGE_BYTE
		}
		while(--count, count);
	}

	// Transfer the remainder
	align = (uint8_t) total & 7;

	if(align <<= 1)
	{
		do
			DISP_IMAGE_BYTE
		while(--align);
	}

	DISP_CS = 1;
}

// Render image stored in the external FLASH
void Disp_EImage(uint16_t xpos, uint8_t ypos, const Disp_EImage_t *image)
{
	EPFlash_Display
	(
		image->Address,
		Disp_Area(xpos, ypos, image->XRes, image->YRes) << 1
	);

	DISP_CS = 1;
}