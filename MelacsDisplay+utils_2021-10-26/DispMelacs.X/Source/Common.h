/******************************************************************************
 * The basics. Hardware definitions, fundamental types and some useful functions
 ******************************************************************************/
#ifndef _COMMON_H
#define _COMMON_H

// Standard includes
#include <delays.h>
#include <p18cxxx.h>
#include <stddef.h>

#define HW_REVISION 1

// Basic integer types
typedef signed char             int8_t;
typedef unsigned char           uint8_t;
typedef signed short int        int16_t;
typedef unsigned short int      uint16_t;
typedef signed short long int   int24_t;
typedef unsigned short long int uint24_t;
typedef signed long             int32_t;
typedef unsigned long int       uint32_t;
typedef ptrdiff_t               intptr_t;
typedef size_t                  uintptr_t;

typedef enum {
	false,
	true
	/* , FILE_NOT_FOUND */
} bool;

// Some useful macros
#define countof(array) (sizeof(array) / sizeof *(array))
#define endof(array) (&(array)[countof(array)])
#define until(cond) while(!(cond))

#define _B(h, g, f, e, d, c, b, a) \
((h) << 7 | (g) << 6 | (f) << 5 | (e) << 4 | (d) << 3 | (c) << 2 | (b) << 1 | (a))

#define _B0(v)  ((uint8_t)  (v)      )
#define _B1(v)  ((uint8_t)  (v) <<  1)
#define _B2(v)  ((uint8_t)  (v) <<  2)
#define _B3(v)  ((uint8_t)  (v) <<  3)
#define _B4(v)  ((uint8_t)  (v) <<  4)
#define _B5(v)  ((uint8_t)  (v) <<  5)
#define _B6(v)  ((uint8_t)  (v) <<  6)
#define _B7(v)  ((uint8_t)  (v) <<  7)

#define _W0(v)  ((uint16_t) (v)      )
#define _W1(v)  ((uint16_t) (v) <<  1)
#define _W2(v)  ((uint16_t) (v) <<  2)
#define _W3(v)  ((uint16_t) (v) <<  3)
#define _W4(v)  ((uint16_t) (v) <<  4)
#define _W5(v)  ((uint16_t) (v) <<  5)
#define _W6(v)  ((uint16_t) (v) <<  6)
#define _W7(v)  ((uint16_t) (v) <<  7)
#define _W8(v)  ((uint16_t) (v) <<  8)
#define _W9(v)  ((uint16_t) (v) <<  9)
#define _W10(v) ((uint16_t) (v) << 10)
#define _W11(v) ((uint16_t) (v) << 11)
#define _W12(v) ((uint16_t) (v) << 12)
#define _W13(v) ((uint16_t) (v) << 13)
#define _W14(v) ((uint16_t) (v) << 14)
#define _W15(v) ((uint16_t) (v) << 15)

#define REVERSE(n) \
((n) >>  7 & 0x0101U | \
 (n) >>  5 & 0x0202U | \
 (n) >>  3 & 0x0404U | \
 (n) >>  1 & 0x0808U | \
 (n) <<  1 & 0x1010U | \
 (n) <<  3 & 0x2020U | \
 (n) <<  5 & 0x4040U | \
 (n) <<  7 & 0x8080U)

// Pin initialization
void Pins_Init(void);
// Printf-like UART tracing function
void Trace(const char rom *format, ...);

extern const uint8_t Disp_Reverse[];
extern const rom uint8_t EPFlash_Reverse[];

#endif