#define _SUPPRESS_PLIB_WARNING
#include "main.h"

#ifdef _ONBOARD_RTCC_FUNC_
#include "onBoardRTCC.h"
#include <p32xxxx.h>
#include <time.h>
#include "stddef.h"
#include "stdint.h"
#include "onBoardRTCC.h"
#include "hardwaredefines.h"
//#include "inttypes.h"
#include "unistd.h"


uint_8 SD_SPI_Transfer(uint_8 data);

//** V A R I A B L E S ********************************************************/
struct RTCclk RTCclk;
struct RTCram RTCram;
struct RTCclk RTCclkBuffert;

typedef char RTCramcheck[sizeof(RTCram) <= 31 ? +1 : -1];

void RTCC_SPIinit(void)
{
    CS_RTC = 1; 		CS_RTC_DIR = 0;		// Standby mode
    SPICLK = 0;			SPICLK_DIR = 0;
    SPIMISO = 0;		SPIMISO_DIR = 1;
    SPIMOSI = 0;		SPIMOSI_DIR = 0;
}

#define	offsetof(ty, mem)	((int)&(((ty *)0)->mem))

//** I N T E R N A L  P R O T O T Y P E S *************************************/
static uint8_t RTC_Read_Byte(void);
static void RTC_Write_Byte(uint8_t value);
static void RTC_Command(uint8_t cmd);

//** F U N C T I O N S ********************************************************/
static uint8_t RTC_Read_Byte(void)
{
    uint8_t value;
    uint8_t i = 8;
    do
    {
        SPICLK = 1;					// Create a clock pulse
        usleep(1);
        SPICLK = 0;
        usleep(1);

        value <<= 1;				// Shift over bits to the left by 1
        if(SPIMISO)
                value  |= 0x01;			// Then OR in a 1 if not then leave it a zero
    }
    while(--i);
    return value;
}

static void RTC_Write_Byte(uint8_t value)
{
    uint8_t i = 8;
    
    do
    {
        SPICLK = 1;
        usleep(1);
  
        SPIMOSI = 0;				// Data out Low
        if(value & 0x80)			// Check if MSB of byte is one
                SPIMOSI = 1;			// Data out high
        value <<= 1;				// Move next bit into position of being checked (left shift)

       SPICLK = 0;
        usleep(1);
    }
    while(--i);
}

static void RTC_Command(uint8_t cmd)
{
    SPICLK = 1;						// Initiate High

    CS_RTC = 1; //SPIoff();						// CSSD & CSAD -> Standby(High) | CSRTC -> Standby(High)
    usleep(1);
    CS_RTC = 0; //RTCinit();						// CSSD & CSAD -> Standby(High) | CSRTC -> Ready(Low)
   
    RTC_Write_Byte(cmd);
}

void RTC_Read_Clock(void)
{   
    uint8_t *ptr;
	uint8_t len;  
    ptr = (uint8_t *) &RTCclk;
	len = offsetof(struct RTCclk, protect);
    
	//Burst-Read Clock Fields Command
	RTC_Command(0xBF);				// 0b10111111 (<#Read/Write><Ram/#Clock><1><1><1><1><1><Read/#Write>)
 
        do
        {
            // Automatically convert binary to BCD
            uint8_t value = RTC_Read_Byte();
            value = (value >> 4) * 10 + (value & 15);

            *ptr++ = value;
        }
        while(--len);

        CS_RTC = 1;  //SPIoff(); 
}

void RTC_Write_Clock(void)
{
    const uint8_t *ptr;
    uint8_t len;
    ptr = (const uint8_t *) &RTCclk;
    len = sizeof RTCclk;

    // Disable Write-Protection
    RTC_Command(0x0F);				// Address 0Fh
    RTC_Write_Byte(0x00);

    RTC_Command(0x3F);				// 0b00111111 (<Read/#Write><Ram/#Clock><1><1><1><1><1><Read/#Write>)
    do
    {
        uint8_t bin = *ptr++;
        // This to automatically convert clock fields from binary to BCD
        uint8_t bcd = bin;
        bcd = (bcd / 10) << 4;
        bcd = bcd | (bin % 10);
        RTC_Write_Byte(bcd);
    }
    while(--len);
    RTC_Write_Byte(0x00);
    CS_RTC = 1; //SPIoff();
}
#endif
