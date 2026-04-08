/******************************************************************************
 * Low-level display functions
 ******************************************************************************/
#ifndef _DISPLAY_H
#define _DISPLAY_H
#include "Common.h"

#define DISPLAY_PGM_VERSION "DISPLAY Revion: P1A"
//                          "1234567890123456789"
// Revision levels P=prel, R=Rel, Number=major change, 
//  Letter= minor backward compatible changes
// When not compiling for production include file pgm_amendment_level
// Also add to Project Customize... in branch Building this line
//      ..\..\utils\changefile Source\pgm_amendment_level.h
// to the field under Execute this line before build
// Uncheck that for production and also comment out the following line
#include "pgm_amendment_level.h"


#define DISP_XRES      320
#define DISP_YRES      240
#define DISP_BACKLIGHT 1000

#define RGB(r, g, b) \
((uint16_t) ((r) & 0xF8) << 8 | (uint16_t) ((g) & 0xFC) << 3 | (b) >> 3)

typedef rom struct Disp_IImage_t
{
	uint16_t XRes;
	uint8_t YRes;
	uint16_t Data[1 /* Variable length array */];
}
Disp_IImage_t;

typedef struct Disp_EImage_t
{
	uint16_t XRes;
	uint8_t YRes;
	uint32_t Address;
}
Disp_EImage_t;

// Functions
void Disp_Init(void);
void Disp_SetBacklight(uint16_t level);
uint16_t Disp_GetBacklight(void);
void Disp_Rect(uint16_t xpos, uint8_t ypos, uint16_t xres, uint8_t yres, uint16_t color);
void Disp_IImage(uint16_t xpos, uint8_t ypos, const Disp_IImage_t *image);
void Disp_EImage(uint16_t xpos, uint8_t ypos, const Disp_EImage_t *image);
/* void Disp_Register(uint8_t regno); */
/* uint16_t Disp_ReadDirect(void); */
/* void Disp_WriteDirect(uint16_t value); */
/* void Disp_CommandDirect(uint8_t regno, uint16_t value); */
/* void Disp_Write(uint16_t value); */
/* void Disp_Command(uint8_t regno, uint16_t value); */
/* uint16_t Disp_Direct(uint16_t value); */

// Accessors
#define Disp_Register(regno) \
(WREG = (regno), _Disp_Register())
#define Disp_ReadDirect() \
(_Disp_ReadDirect())
#define Disp_WriteDirect(value) \
(PROD = (value), _Disp_WriteDirect())
#define Disp_CommandDirect(regno, value) \
(PROD = (value), WREG = (regno), _Disp_CommandDirect())
#define Disp_Write(value) \
(PROD = (value), _Disp_Write())
#define Disp_Command(regno, value) \
(PROD = (value), WREG = (regno), _Disp_Command())
#if HW_REVISION > 0
#	define Disp_Direct(value) ((value))
#else
#	define Disp_Direct(value) (PROD = (value), _Disp_Direct())
#endif
#define Disp_PutSolidChar(ptr) \
(*(ptr), _Disp_PutSolidChar())

extern void _Disp_Register(void);
extern uint16_t _Disp_ReadDirect(void);
extern void _Disp_WriteDirect(void);
extern void _Disp_CommandDirect(void);
extern void _Disp_Write(void);
extern void _Disp_Command(void);
extern uint16_t _Disp_Direct(void);
extern void _Disp_PutSolidChar(void);

#if HW_REVISION > 0
#	define DISP_DIRECT(num) (num)
#	define DISP_REG(reg)    (DISP_##reg)
#else
#	define DISP_DIRECT(num) REVERSE(num)
#	define DISP_REG(reg)    REVERSE(DISP_##reg)
#endif

#endif