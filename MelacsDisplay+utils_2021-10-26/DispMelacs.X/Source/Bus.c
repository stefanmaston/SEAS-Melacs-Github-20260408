/******************************************************************************
 * I/O pins:
 * IDENT (GND/#6 ) - RB0 
 * ATN   (SW4/#4 ) - RB3/#11
 * CLK   (SW3/#3 ) - RB2/#10
 * ACK1  (CS1/#11) - RB4/#12
 * ACK2  ( SI/#8 ) - RB1/#8
 * DATA0 (SCL/#10) - RG0/#1
 * DATA1 ( RS/#12) - RG1/#2
 * DATA2 (SW1/#1 ) - RG2/#3
 * DATA3 (SW2/#2 ) - RG3/#4
 ******************************************************************************/
#include "Bus.h"
#include "Common.h"
#include "Pins.h"

// Configuration and constants
#define BUS_TRACE        1
#define BUS_ERRORS       0

#define BUS_MTU          32
#define BUS_PRIMARY_ID   0x03
#define BUS_SECONDARY_ID 0x0C
#define BUS_NORMAL_CRC   0xFF
#define BUS_RESEND_CRC   0x01

// The main full-page transfer buffer
#pragma udata Bus_Buffer
static volatile uint8_t Bus_Buffer[0x100];
#pragma udata

// Read and write pointers into the transfer buffer
volatile uint8_t _Bus_Head;
volatile uint8_t _Bus_Tail;
static volatile uint8_t Bus_ResumeAt;
// Running checksum counter
static uint8_t Bus_Checksum;
// Primary or secondary identification nibble
static uint8_t _Bus_Identifier;
// Response string
extern volatile uint8_t Bus_Response[];
volatile int8_t Bus_ResponseLen;


/******************************************************************************
 * CRC-8 table
 ******************************************************************************/
static const rom uint8_t Bus_ChecksumTab[] =
{
	0x00, 0x5E, 0xBC, 0xE2, 0x61, 0x3F, 0xDD, 0x83,
	0xC2, 0x9C, 0x7E, 0x20, 0xA3, 0xFD, 0x1F, 0x41,
	0x9D, 0xC3, 0x21, 0x7F, 0xFC, 0xA2, 0x40, 0x1E,
	0x5F, 0x01, 0xE3, 0xBD, 0x3E, 0x60, 0x82, 0xDC,
	0x23, 0x7D, 0x9F, 0xC1, 0x42, 0x1C, 0xFE, 0xA0,
	0xE1, 0xBF, 0x5D, 0x03, 0x80, 0xDE, 0x3C, 0x62,
	0xBE, 0xE0, 0x02, 0x5C, 0xDF, 0x81, 0x63, 0x3D,
	0x7C, 0x22, 0xC0, 0x9E, 0x1D, 0x43, 0xA1, 0xFF,
	0x46, 0x18, 0xFA, 0xA4, 0x27, 0x79, 0x9B, 0xC5,
	0x84, 0xDA, 0x38, 0x66, 0xE5, 0xBB, 0x59, 0x07,
	0xDB, 0x85, 0x67, 0x39, 0xBA, 0xE4, 0x06, 0x58,
	0x19, 0x47, 0xA5, 0xFB, 0x78, 0x26, 0xC4, 0x9A,
	0x65, 0x3B, 0xD9, 0x87, 0x04, 0x5A, 0xB8, 0xE6,
	0xA7, 0xF9, 0x1B, 0x45, 0xC6, 0x98, 0x7A, 0x24,
	0xF8, 0xA6, 0x44, 0x1A, 0x99, 0xC7, 0x25, 0x7B,
	0x3A, 0x64, 0x86, 0xD8, 0x5B, 0x05, 0xE7, 0xB9,
	0x8C, 0xD2, 0x30, 0x6E, 0xED, 0xB3, 0x51, 0x0F,
	0x4E, 0x10, 0xF2, 0xAC, 0x2F, 0x71, 0x93, 0xCD,
	0x11, 0x4F, 0xAD, 0xF3, 0x70, 0x2E, 0xCC, 0x92,
	0xD3, 0x8D, 0x6F, 0x31, 0xB2, 0xEC, 0x0E, 0x50,
	0xAF, 0xF1, 0x13, 0x4D, 0xCE, 0x90, 0x72, 0x2C,
	0x6D, 0x33, 0xD1, 0x8F, 0x0C, 0x52, 0xB0, 0xEE,
	0x32, 0x6C, 0x8E, 0xD0, 0x53, 0x0D, 0xEF, 0xB1,
	0xF0, 0xAE, 0x4C, 0x12, 0x91, 0xCF, 0x2D, 0x73,
	0xCA, 0x94, 0x76, 0x28, 0xAB, 0xF5, 0x17, 0x49,
	0x08, 0x56, 0xB4, 0xEA, 0x69, 0x37, 0xD5, 0x8B,
	0x57, 0x09, 0xEB, 0xB5, 0x36, 0x68, 0x8A, 0xD4,
	0x95, 0xCB, 0x29, 0x77, 0xF4, 0xAA, 0x48, 0x16,
	0xE9, 0xB7, 0x55, 0x0B, 0x88, 0xD6, 0x34, 0x6A,
	0x2B, 0x75, 0x97, 0xC9, 0x4A, 0x14, 0xF6, 0xA8,
	0x74, 0x2A, 0xC8, 0x96, 0x15, 0x4B, 0xA9, 0xF7,
	0xB6, 0xE8, 0x0A, 0x54, 0xD7, 0x89, 0x6B, 0x35
};


/******************************************************************************
 * Prepare the bus receiver interrupt
 ******************************************************************************/
void Bus_Init(void)
{
	uint8_t value;

	// This is the primary slave if the identifiction pin is connected to GND
	// on the main board, and the secondary slave if it's unconnected
	INTCON2bits.NOT_RBPU = 0;

	value = 0;
	while(++value);

	// Control either the ACK1 or ACK2 pin depending on whether this is a master
	// or slave unit
	if(!BUS_IDENT_IN)
	{
		BUS_ACK1_TRIS = 0;
		_Bus_Identifier = BUS_PRIMARY_ID;
	}
	else
	{
		BUS_ACK2_TRIS = 0;
		_Bus_Identifier = BUS_SECONDARY_ID;
	}

	INTCON2bits.NOT_RBPU = 1;

	// Prepare a low-priority interrupt on the falling-edge of the attention pin
	// but don't enable it quite yet
	INTCON2bits.INT3IP = 0;
	INTCON2bits.INTEDG3 = 0;
	INTCON3bits.INT3IF = 0;

	// Reset the checksum
	Bus_Checksum = BUS_NORMAL_CRC;
}


/******************************************************************************
 * Extract characters from the receive buffer
 ******************************************************************************/
unsigned char Bus_Get(void)
{
	uint8_t data;

	// Wait if we've already reached the end of the accepted data
	while(!Bus_Ready())
		; // sleep

	// Fetch the new byte
	FSR0 = (uint16_t) Bus_Buffer;
	FSR0L = _Bus_Tail;
	data = INDF0;
	++_Bus_Tail;

	// If attention is low yet we're outside of the bus interrupt then it must
	// be stalled waiting for buffer space to free up, so retrigger the
	// interrupt if we've freed up enough space to resume
	if(!BUS_ATN_IN && _Bus_Tail == Bus_ResumeAt)
		INTCON3bits.INT3IF = 1;
	return data;
}


/******************************************************************************
 * Receive and transmit packets when prompted by the bus master
 ******************************************************************************/
void Bus_Interrupt(void)
{
	uint8_t data;

	// The attention pin interrupt is edge-triggered is always enabled after
	// start-up, even when out of buffer space
	if(!INTCON3bits.INT3IE || !INTCON3bits.INT3IF)
		return;

	// If the clock is low at the start of the transfer then we're supposed to
	// send a reply
	if(!BUS_CLK_IN)
	{
		uint8_t tris;
		int8_t len;

		// Only set the data direction as output if we're the selected slave
		tris = ~0;
		if((BUS_DATA_IN & BUS_DATA_MASK) == _Bus_Identifier)
			tris = ~BUS_DATA_MASK;

		FSR0 = (uint16_t) Bus_Response;
		len = Bus_ResponseLen;
		Bus_Checksum = BUS_NORMAL_CRC;

		for(;;)
		{
			while(--len >= 0)
			{
				// Transmit the 1st nibble
				BUS_CTRL_OUT |= BUS_ACK_MASK;

				data = INDF0 >> 4;
				data ^= BUS_DATA_OUT;
				data &= BUS_DATA_MASK;

				do
					if(BUS_ATN_IN)
						goto success;
				while(!BUS_CLK_IN);

				BUS_DATA_OUT ^= data;
				BUS_DATA_TRIS &= tris;

				// Transmit the 2nd nibble
				BUS_CTRL_OUT &= ~BUS_ACK_MASK;

				data = INDF0;
				data ^= BUS_DATA_OUT;
				data &= BUS_DATA_MASK;

				Bus_Checksum = Bus_ChecksumTab[Bus_Checksum ^ POSTINC0];

				do
					if(BUS_ATN_IN)
						goto failure;
				while(BUS_CLK_IN);

				BUS_DATA_OUT ^= data;
			}

			// Run a final iteration to transfer the checksum
			FSR0 = (uint16_t) &Bus_Checksum;
			len = 1;
		}
	}

	// Receive input message
	data = _Bus_Head - _Bus_Tail;

	if(data >= sizeof Bus_Buffer - BUS_MTU)
	{
		// Wait for some space to free up if there isn't enough free space to
		// receive the maximum-sized packet
		Bus_ResumeAt = _Bus_Head - BUS_MTU;
		INTCON3bits.INT3IF = 0;
		return;
	}

	FSR0 = (uint16_t) Bus_Buffer;
	FSR0L = _Bus_Head;

	do
	{
		// Receive and acknowledge the 1st nibble, then wait for the next one
		data = BUS_DATA_IN << 4;
		BUS_CTRL_OUT |= BUS_ACK_MASK;

		do
			if(BUS_ATN_IN)
				goto checksum;
		while(BUS_CLK_IN);

		// Receive and acknowledge the 2nd nibble, then wait for the next byte
		data |= BUS_DATA_IN & 0x0F;
		BUS_CTRL_OUT &= ~BUS_ACK_MASK;

		Bus_Checksum = Bus_ChecksumTab[Bus_Checksum ^ data];

		do
			if(BUS_ATN_IN)
				goto failure;
		while(!BUS_CLK_IN);

		// Store the received bytes
		INDF0 = data;
		++FSR0L;
	}
	// Fail if the master tries to send a packet larger than the MTU
	while(FSR0L != _Bus_Tail);

	while(!BUS_ATN_IN);
	goto failure;

checksum:
	// Receive the final nibble and verify the checksum
	data |= BUS_DATA_IN & 0x0F;
	data ^= Bus_Checksum;

#	if BUS_ERRORS
	if(!Math_Random(100))
		data = 0xFF;
#	endif

	if(!data)
	{
		_Bus_Head = FSR0L;
success:
		Bus_Checksum = BUS_NORMAL_CRC;
	}
	else
	{
#		if BUS_TRACE
		uint8_t from = _Bus_Head;
		uint8_t to = FSR0L;

		Trace("CRC %2x/%2x/%u: ",
			(unsigned) Bus_Checksum,
			(unsigned) (data ^ Bus_Checksum),
			(unsigned) (to - from));
		Bus_Checksum = BUS_NORMAL_CRC;

		while(from != to)
		{
			data = Bus_Buffer[from++];
			Bus_Checksum = Bus_ChecksumTab[Bus_Checksum ^ data];
			Trace("%2x ", (unsigned) data);
		}

		Trace("(%2x)\n", (unsigned) Bus_Checksum);
#		endif

failure:
		// Force a retransmission by waiting for the time-out
		Bus_Checksum = BUS_RESEND_CRC;
		while(BUS_CLK_IN && BUS_ATN_IN);
	}

	// Acknowledge the final nibble and prepare for the next message
	INTCON3bits.INT3IF = 0;
	BUS_DATA_TRIS |= BUS_DATA_MASK;
	BUS_CTRL_OUT &= ~BUS_ACK_MASK;
}