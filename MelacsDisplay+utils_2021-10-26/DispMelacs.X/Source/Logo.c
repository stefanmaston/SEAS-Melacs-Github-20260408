#include <string.h>
#include <stdio.h>
#include "Analog.h"
#include "Common.h"
#include "Display.h"
#include "EPFlash.h"
#include "LED.h"
#include "Math.h"
#include "Numeric.h"
#include "Switch.h"
#include "Logo.h"
#include "Timer.h"
#include "Window.h"
#include "Pins.h"
#include "UART.h"

extern const Disp_IImage_t Image_Logo;

/******************************************************************************
 * Game state
 ******************************************************************************/
enum
{
	T_FIELD_XRES = 8,
	T_FIELD_YRES = 20,
	T_PIECE_XRES = 4,
	T_PIECE_YRES = 4,

	T_CHAR_GRID   = '\00',
	T_CHAR_FIXED  = '\01',
	T_CHAR_ACTIVE = '\02',
	T_CHAR_HOLLOW = '\03',
	T_CHAR_VOID   = '\04'
};

static int8_t T_XPos;
static int8_t T_YPos;
static uint8_t T_Piece;
static uint8_t T_NextPiece;
static Timer_t T_DropTimer;

struct
{
	uint8_t Signature;
	uint32_t Value;
}
T_Hiscore;
static uint32_t T_Score;
static uint8_t T_Level;
static uint32_t T_Lines;
static uint8_t T_DropCounter;

static uint8_t T_WinLeft;
static uint8_t T_WinPlay;
static uint8_t T_WinRight;
static uint8_t T_WinNext;
static uint8_t T_WinMain;

/******************************************************************************
 * Palette colors
 ******************************************************************************/
enum
{
	TC_STATUS_PAPER,
	TC_STATUS_LABEL,
	TC_STATUS_VALUE,
	TC_BORDER,
	TC_PLAY_PAPER,
	TC_PLAY_VOID,

	TC_ACTIVE_PIECES,
	TC_INACTIVE_PIECES = TC_ACTIVE_PIECES + 7
};

static const rom uint16_t T_Palette[] =
{
	// Status background
	RGB(0x00, 0x00, 0x00),
	// Status foreground
	//RGB(0x9D, 0xBB, 0x59),
	//RGB(0x9D, 0xBB, 0x59),
	RGB(0x57, 0x48, 0xCB),	
	RGB(0x57, 0x48, 0xCB),	
	// Border background
	RGB(0xFF, 0x00, 0x00),
	// Playfield background
	RGB(0x20, 0x20, 0x20),
	// Playfield foreground
	RGB(0x40, 0x40, 0x40),

	// Active (moving) piece colors
	RGB( 64, 255, 255), // "I"
	RGB( 64,  64, 255), // "J"
	RGB(255, 224,  64), // "L"
	RGB(255, 255,  64), // "O"
	RGB( 64, 255,  64), // "S"
	RGB(224,  64, 255), // "T"
	RGB(255,  64,  64), // "Z"

	// Inactive (static) piece colors
	RGB(  0, 240, 240), // "I"
	RGB(  0,   0, 240), // "J"
	RGB(240, 160,   0), // "L"
	RGB(240, 240,   0), // "O"
	RGB(  0, 240,   0), // "S"
	RGB(160,   0, 240), // "T"
	RGB(240,   0,   0), // "Z"
};

static void Put_String(const char rom *name, uint8_t col, uint8_t row) {
	Win_Ink(TC_STATUS_LABEL);
	Win_Cursor(col, row);
	Win_PutString(name);
}

static void Put_Character(char ch, uint8_t col, uint8_t row) {
	Win_Ink(TC_STATUS_LABEL);
	Win_Cursor(col, row);
	Win_PutChar(ch);
}

/******************************************************************************
 * Get button input with key-repeat
 ******************************************************************************/
#define T_KeyPress(id) (T_Key[(id)].Press)

// Smoothly fade the backlight to the chosen level
static void T_FadeTo(uint16_t target) {
	Timer_t timer = Timer_Tick();
	uint16_t level = Disp_GetBacklight();

	while(level != target) {
		until(Timer_Check(&timer, 1));

		if(level < target)
			++level;
		else
			--level;

		Disp_SetBacklight(level);

		// Maintain the LED animation while dimming
//		T_LEDs();
	}
}

#define KEYPAD 

// Data I/O
#define TRIS_DATA0 TRISGbits.TRISG0
#define TRIS_DATA1 TRISGbits.TRISG1
#define TRIS_DATA2 TRISGbits.TRISG2
#define TRIS_DATA3 TRISGbits.TRISG3

#define M_DATA0 LATGbits.LATG0
#define M_DATA1 LATGbits.LATG1
#define M_DATA2 LATGbits.LATG2
#define M_DATA3 LATGbits.LATG3

#define DATA0 PORTGbits.RG0
#define DATA1 PORTGbits.RG1
#define DATA2 PORTGbits.RG2
#define DATA3 PORTGbits.RG3

// Keys
#define TRIS_T0 TRISAbits.TRISA0
#define TRIS_T1 TRISAbits.TRISA1
#define TRIS_T2 TRISAbits.TRISA4
#define TRIS_T3 TRISAbits.TRISA5

#define LAT_T0 LATAbits.LATA0
#define LAT_T1 LATAbits.LATA1
#define LAT_T2 LATAbits.LATA4
#define LAT_T3 LATAbits.LATA5

#define T0 PORTAbits.RA0
#define T1 PORTAbits.RA1
#define T2 PORTAbits.RA4
#define T3 PORTAbits.RA5

#define TRIS_OFF    TRISAbits.TRISA0
#define LAT_OFF     LATAbits.LATA0
#define T_OFF       PORTFbits.RF6
#define T_ON        PORTFbits.RF7

#define TRIS_ATN	TRISBbits.TRISB3
#define TRIS_ACK1	TRISBbits.TRISB4
#define TRIS_ACK2	TRISBbits.TRISB1
#define TRIS_CLK	TRISBbits.TRISB2

#define M_ATN	LATBbits.LATB3
#define M_ACK1	LATBbits.LATB4
#define M_ACK2	LATBbits.LATB1
#define M_CLK	LATBbits.LATB2

#define ATN		PORTBbits.RB3
#define ACK1	PORTBbits.RB4
#define ACK2	PORTBbits.RB1
#define CLK		PORTBbits.RB2

void setDataAsInput();
void setDataAsInput() {
	TRIS_DATA0 = 1; //Configure RG0 as input
	TRIS_DATA1 = 1; //Configure RG1 as input
	TRIS_DATA2 = 1; //Configure RG2 as input
	TRIS_DATA3 = 1; //Configure RG3 as input
}

void setDataAsOutput();
void setDataAsOutput() {
	TRIS_DATA0 = 0; //Configure RG0 as input
	TRIS_DATA1 = 0; //Configure RG1 as input
	TRIS_DATA2 = 0; //Configure RG2 as input
	TRIS_DATA3 = 0; //Configure RG3 as input
}

void Show_Logo(void) {
	
	int D_ATN = 0;
	int D_ACK1 = 0;
	
	int xnibble = 0;
	char nibble = 0;
	int lineNum = 0;
	int columnNum = 0;
	int whether2Nibble = 0;
	int startDisp = 0;	
	
	// Fade out before drawing anything
	T_FadeTo(0);
	
	// Create windows
	memcpypgm2ram(Win_Palette, (const far rom void *) T_Palette, sizeof T_Palette);

    // Pluck the image from the mirror in external FLASH instead
    {
        Disp_EImage_t image =
        {
            Image_Logo.XRes,
            Image_Logo.YRes,
            (uint32_t) &Image_Logo.Data
        };
        //Disp_EImage(0,200, &image);
        Disp_EImage(0, 0, &image);
	}
	//Win_Create(&Font_Courier, 0, 0);
	Win_Create(&Font_Courier, 0, 40);	
	Win_Paper(TC_STATUS_PAPER);
	Win_Size(23, 10);
	T_WinMain = Win_GetIndex();

	setDataAsInput();

	TRIS_ATN = 1; //Configure RB3 as input
	TRIS_ACK1 = 1; //Configure RG1 as input
	TRIS_ACK2 = 0; //Configure RB1 as output D_ACK2	

	TRIS_CLK = 0; //Configure RB2 as output D_CLK
 	M_CLK = 1;
	M_ACK2 = 1;		
	
	TRIS_T0 = 1; // Keypad input
	TRIS_T1 = 1;
	TRIS_T2 = 1;
	TRIS_T3 = 1;

#ifdef KEYPAD	
	// Print status
	Win_Select(T_WinMain);
	Put_String("                    ",0, 0);
	Win_Refresh();
	// Fade in fully before starting the game but after the 1st
	// frame has been drawn
	T_FadeTo(1000);
#endif
	Win_Select(T_WinMain);
	Put_String("Dashnyam Ganbat",0, 0);
	Put_String(DISPLAY_PGM_VERSION,0, 2);

#ifdef PGM_AMENDMENT_LEVEL
    Win_PutString(PGM_AMENDMENT_LEVEL);
#endif

	Win_Select(T_WinMain);
	Put_String("Compiled on:",0, 4);
	Put_String(__DATE__, 0, 5);
    Win_PutString(" ");
    Win_PutString(__TIME__);
    
 	Win_Refresh();
	// Fade in fully before starting the game but after the 1st
	// frame has been drawn
	T_FadeTo(1000);
	
	// Continue the game while new pieces can still be placed
	while(1) {
		// Print status
		Win_Select(T_WinMain);
//	UART_PutString (
//		" \n"
//		"Start of loop\n"
//	);
		Win_Refresh();
		// Fade in fully before starting the game but after the 1st
		// frame has been drawn
		T_FadeTo(1000);	
		
		
		D_ATN = ATN; //Read the RB3 bit as D_ATN
		//Put_Character(ATN,0,2);
		if(1 == D_ATN) {
        	UART_PutString ("D_ATN HIGH\n");
			setDataAsInput();
			while(1 == D_ATN) {	
				
				Win_Select(T_WinMain);
//				Put_String("Inside while",0, 2);
				Win_Refresh();
//				 Fade in fully before starting the game but after the 1st
//				 frame has been drawn
				T_FadeTo(1000);	
				
			
				//Set D_ACK2 as low	
				M_CLK = 0;
				M_ACK2 = 0;			
				
				//wait for D_ACK1 to go high
				while(0 == D_ACK1) {
				
					Win_Select(T_WinMain);
//					Put_String("Waiting for D_ACK1",0, 3);
					Win_Refresh();
//					 Fade in fully before starting the game but after the 1st
//					 frame has been drawn
					T_FadeTo(1000);	
					
				
					D_ATN = ATN; //Read the RB3 bit as D_ATN	
					if(0 == D_ATN) {
						//D_ATN was high without intention
//                    	UART_PutString ("D_ATN LOW -> break!!\n");
						break;
					}
					D_ACK1 = ACK1; //Read the RB4 bit as D_ACK1				
				}

//                UART_PutString ("D_ATN LOW or D_ACK1 HIGH\n");

				Win_Select(T_WinMain);
//				Put_String("Out Waiting for D_ACK1",0, 4);
				Win_Refresh();
//				 Fade in fully before starting the game but after the 1st
//				 frame has been drawn
				T_FadeTo(1000);	
				

				//We can read data
				if(1 == whether2Nibble) {
					//First MSB is received and then the LSB
					nibble = (nibble << 4) + (PORTG & 0xF);
					//nibble = PORTG & 0xF;
					xnibble = PORTG & 0xF;				
				} else {
					nibble = PORTG & 0xF;
					xnibble = PORTG & 0xF;
				}
				
				whether2Nibble++;
				
				//Set D_ACK2 as high
				M_CLK = 1;
				M_ACK2 = 1;					

				//wait for D_ACK1 to go low
				while(1 == D_ACK1) {
					D_ATN = ATN; //Read the RB3 bit as D_ATN	
					if(0 == D_ATN) {
						//D_ATN was high without intention
//                        UART_PutString ("D_ATN LOW -> break!!\n");
						break;			
					}		
					
					D_ACK1 = ACK1; //Read the RB4 bit as D_ACK1
				}
                UART_PutString ("Handle data: ");
                UART_PutNumber (nibble, 4, 16);
                UART_PutString ("\n");
 				
				if(10 == nibble) {
					//We have received the First Byte, Start of the Message
					whether2Nibble = 0;
					startDisp = 1;
					columnNum = 0;
					lineNum = 0;			
				}
				
				if((1 == startDisp) && (2 == whether2Nibble)) {	
					// Print status
					Win_Select(T_WinMain);
					Put_Character(nibble,columnNum++,lineNum);
					Win_Refresh();
					// Fade in fully before starting the game but after the 1st
					// frame has been drawn
					T_FadeTo(1000);			

					nibble = 0;
					whether2Nibble = 0;
				}
				
				if(23 == columnNum) {
					columnNum = 0;
					lineNum++;
				}			
				
				if(10 == lineNum) {
					lineNum = 0;
				}
				
				D_ATN = ATN; //Read the RB3 bit as D_ATN	
			}
		} else {
			setDataAsOutput();		
	
            M_DATA0 = T0;
            M_DATA1 = T1;
            M_DATA2 = T2;
            M_DATA3 = T3;
            
//            i= M_DATA0 + 10*M_DATA1+ 100*M_DATA2+ 1000*M_DATA3;
//            if (i != old_i) {
//                UART_PutString ("D_ATN LOW, KEY-value = ");
//                UART_PutNumber (i, 4, 10);
//                UART_PutString ("\n");
//                old_i = i;
//            }
		}
	}

	// Clean up after ourselves
	Win_Destroy();
	Win_Select(T_WinMain);
	Win_Destroy();
}
