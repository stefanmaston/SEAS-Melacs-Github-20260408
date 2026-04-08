/******************************************************************************
 * Text window management and allocation.
 * Character plotting is cached in the window buffers and any actual drawing
 * is deferred until Win_Refresh is called, when the window tries to avoid
 * repainting unchanged characters
 ******************************************************************************/
#ifndef _WINDOW_H
#define _WINDOW_H
#include "Common.h"
#include "Font.h"

// Note: These structures must be kept in sync with the equivalent definition
// in Core.asm
struct Window
{
	// Status flags
	uint8_t Live : 1;

	// Area definition
	uint16_t XPos;
	uint8_t YPos;
	uint8_t Cols;
	uint8_t Rows;

	// Font and colors
	uint8_t Ink;
	uint8_t Paper;
	const rom struct Font *Font;
};

extern struct _Win_State
{
	// Private state variables collected into a single block

	// The currently active window and its index
	struct Window Win;
	uint8_t CurrentIndex;

	// Extra fields kept only for the active window
	struct Font Font;
	uint16_t *Text;
	uint16_t Ink;
	uint16_t Paper;
	uint16_t InkDirect;
	uint16_t PaperDirect;
	uint8_t CursorCol;
	uint8_t CursorRow;
	uint16_t *CursorPtr;

	// Track how much buffer space has been used
	uint16_t *BufferTail;
}
_Win_State;

// Interface functions
void Win_Init(void);
void Win_Select(uint8_t index);
bool Win_Create(const rom struct Font *font, uint16_t xpos, uint8_t ypos);
void Win_Destroy(void);
void Win_Size(uint8_t cols, uint8_t rows);
void Win_Refresh(void);
void Win_Invalidate(void);
void _Win_Clear(void);

void Win_Paper(uint8_t c);
void Win_Cursor(uint8_t col, uint8_t row);
void Win_PutChar(char ch);
void Win_PutRaw(uint16_t ch);
void Win_PutString(const char rom *text);
void Win_PutBuffer(const char *text);
void Win_ReplaceChar(char ch);
void Win_ScrollUp(void);
void Win_Console(char ch);
char Win_PeekChar(uint8_t col, uint8_t row);
uint16_t Win_PeekRaw(uint8_t col, uint8_t row);

#define Win_Clear(ch)    (TABLAT = (ch), _Win_Clear())
#define Win_Ink(c)       (_Win_State.Win.Ink = (c))
#define Win_GetIndex()   (_Win_State.CurrentIndex)
#define Win_GetCol()     (_Win_State.CursorCol)
#define Win_GetRow()     (_Win_State.CursorRow)
#define Win_GetNumRows() (_Win_State.Win.Rows)
#define Win_GetNumCols() (_Win_State.Win.Cols)

extern struct _Win_State _Win_State;
extern uint16_t Win_Palette[32];

#endif