#include <stddef.h>
#include <string.h>
#include "Common.h"
#include "Display.h"
#include "Math.h"
#include "Pins.h"
#include "Window.h"

enum { WIN_LIM = 10 };

// Dynamically allocated buffers usesd for storing character arrays and the
// inactive windows
#pragma udata Win_Buffer
uint16_t Win_Palette[];
static struct Window Win_Array[WIN_LIM];
static uint16_t Win_Buffer[(0x600 - sizeof Win_Array - sizeof Win_Palette) / 2];
#pragma udata

// Define the state block and export its variables for easy of access
struct _Win_State _Win_State;

#define _Win              (_Win_State.Win)
#define _Win_CurrentIndex (_Win_State.CurrentIndex)
#define _Win_Font         (_Win_State.Font)
#define _Win_Text         (_Win_State.Text)
#define _Win_Ink          (_Win_State.Ink)
#define _Win_InkDirect    (_Win_State.InkDirect)
#define _Win_Paper        (_Win_State.Paper)
#define _Win_PaperDirect  (_Win_State.PaperDirect)
#define _Win_CursorCol    (_Win_State.CursorCol)
#define _Win_CursorRow    (_Win_State.CursorRow)
#define _Win_CursorPtr    (_Win_State.CursorPtr)
#define _Win_BufferTail   (_Win_State.BufferTail)


/******************************************************************************
 * Basic window allocation functions
 ******************************************************************************/
// Select the active window to work with
static void Win_Activate(void)
{
	// Calculate the text buffer origin
	uint8_t index = Win_GetIndex();
	uint16_t offset = 0;
	while(index--)
	{
		struct Window *win = &Win_Array[index];
		offset += Math_Mul8x8(win->Cols, win->Rows);
	}
	_Win_Text = &Win_Buffer[offset];

	// Cache the font
	memcpypgm2ram((void *) &_Win_Font, (far rom void *) _Win.Font, sizeof _Win_Font);

	// Cache the background color
	_Win_Paper = Win_Palette[_Win.Paper];
#	if HW_REVISION == 0
	_Win_PaperDirect = Disp_Direct(_Win_Paper);
#	endif

	// Reset the write cursor
	Win_Cursor(0, 0);
}

// Reset the windowing system
void Win_Init(void)
{
	// Just clear out everything..
	memset(&_Win_State, 0, sizeof _Win_State);
	_Win_BufferTail = Win_Buffer;
}

// Swap in a new window structure
void Win_Select(uint8_t index)
{
	if(index != _Win_CurrentIndex && index < WIN_LIM)
	{
		memcpy((void *) &Win_Array[_Win_CurrentIndex], (const void *) &_Win, sizeof _Win);
		_Win_CurrentIndex = index;
		memcpy((void *) &_Win, (const void *) &Win_Array[_Win_CurrentIndex], sizeof _Win);
		Win_Activate();
	}
}

// Allocate a new window
bool Win_Create(const rom struct Font *font, uint16_t xpos, uint8_t ypos)
{
	// Try to find an unused window
	struct Window *ptr;
	uint8_t index = -1;
	do
	{
		if(++index == WIN_LIM)
			return false;
		ptr = &Win_Array[index];
	}
	while(ptr->Live);

	// Make sure to mark the new entry as used in case of more allocations
	// before it has been swapped out
	ptr->Live = true;
	
	Win_Select(index);

	// Set up the basic structures
	_Win.Live = true;
	_Win.XPos = xpos;
	_Win.YPos = ypos;
	_Win.Font = font;

	// Derive the additional cached fields
	Win_Activate();
	return true;
}

// Reclaim the current window
void Win_Destroy(void)
{
	// Mark it as free
	_Win.Live = false;

	// Release the buffer
	Win_Size(0, 0);
}

// Change the window size and reallocate the text buffer
void Win_Size(uint8_t cols, uint8_t rows)
{
	// Make sure there's enough character memory left
	size_t sized = Math_Mul8x8(cols, rows);
	void *tail = &_Win_BufferTail[sized - Math_Mul8x8(_Win.Cols, _Win.Rows)];

	if(tail >= (const void *) &Win_Buffer[countof(Win_Buffer)])
		return;

	_Win.Cols = cols;
	_Win.Rows = rows;

	// Shift the reset of the windows to make space for the new buffer
	_Win_BufferTail = tail;
	tail = &_Win_Text[sized];

	memmove
	(
		tail,
		(const void *) _Win_Text,
		(void *) _Win_BufferTail - tail
	);

	// Figure out the buffer origin and reset the cursor
	Win_Activate();

	// Erase (and invalidate) the window content
	Win_Clear(' ');
}


/******************************************************************************
 * Redraw any changed characters in the window
 ******************************************************************************/
void Win_Refresh(void)
{
	uint16_t *text;
	uint16_t xpos;
	uint8_t ypos;
	uint8_t cols;
	uint8_t rows;

	DISP_CS = 0;
	text = _Win_Text;
	ypos = _Win.YPos;
	rows = _Win.Rows;

	do
	{
		xpos = _Win.XPos;
		cols = _Win.Cols;

		do
		{
			int16_t ch = *text;

			if(ch < 0)
			{
				uint8_t bitmap;

				Disp_Command(DISP_REG(R4E_XRAM_ADDR), xpos);
				Disp_Command(DISP_REG(R4F_YRAM_ADDR), ypos);
				Disp_Command(DISP_REG(R45_HRAM_START), xpos);
				Disp_Command(DISP_REG(R46_HRAM_END), xpos + _Win_Font.XRes - 1);
				Disp_Register(DISP_REG(R22_RAM_PORT));

				ch &= ~0x8000;

				_Win_Ink = Win_Palette[(uint16_t) ch >> 8];

				if(bitmap = (uint8_t) ch, bitmap > _Win_Font.Limit)
					bitmap = 0;

				Disp_PutSolidChar(_Win_Font.Chars[bitmap]);
			}

			*text++ = ch;
			xpos += _Win_Font.XRes;
		}
		while(--cols);

		ypos += _Win_Font.YRes;
	}
	while(--rows);

	DISP_CS = 1;
}


/******************************************************************************
 * Printing functions
 ******************************************************************************/
void Win_Paper(uint8_t c)
{
	_Win.Paper = c;
	_Win_Paper = Win_Palette[c];
}

void Win_Cursor(uint8_t col, uint8_t row)
{
	if(row >= _Win.Rows)
	{
		col = _Win.Cols;
		row = _Win.Rows;
	}

	_Win_CursorCol = col;
	_Win_CursorRow = row;
	_Win_CursorPtr = &_Win_Text[col + Math_Mul8x8(row, _Win.Cols)];
}

void Win_PutChar(char ch)
{
	Win_PutRaw((uint16_t) _Win.Ink << 8 | (uint8_t) ch);
}

void Win_PutRaw(uint16_t ch)
{
	if(_Win_CursorCol < _Win.Cols)
	{
		uint16_t *ptr;

		++_Win_CursorCol;

		ptr = _Win_CursorPtr;
		if(*ptr != ch)
			ch |= 0x8000;
		*ptr++ = ch;
		_Win_CursorPtr = ptr;
	}
}

void Win_PutString(const char rom *text)
{
	char ch;
	
	while(ch = *text++, ch)
		Win_PutChar(ch);
}

void Win_PutBuffer(const char *text)
{
	char ch;

	while(ch = *text++, ch)
		Win_PutChar(ch);
}

void Win_ReplaceChar(char ch)
{
	if(_Win_CursorCol < _Win.Cols)
		Win_PutRaw(*_Win_CursorPtr & 0xFF00 | (uint8_t) ch);
}

void Win_ScrollUp(void)
{
	uint16_t ch;

	uint16_t *dst = _Win_Text;
	const uint16_t *src = &_Win_Text[_Win.Cols];
	uint16_t len = Math_Mul8x8(_Win.Cols, _Win.Rows);

	do
	{
		ch = *src++;
		if(*dst != ch)
			ch |= 0x8000;
		*dst++ = ch;
	}
	while(--len);

	len = _Win.Cols;
	
	do
	{
		ch = *dst;
		if(ch != ' ')
			ch = 0x8000 | ' ';
		*dst++ = ch;
	}
	while(--len);
}

void Win_Console(char ch)
{
	uint8_t row = Win_GetRow();

	switch(ch)
	{
	default:
		Win_PutChar(ch);
		if(Win_GetCol() < Win_GetNumCols())
			return;
	case '\n':
		if(++row >= Win_GetNumRows())
		{
			Win_ScrollUp();
			--row;
		}
	case '\r':
		Win_Cursor(0, row);
	}
}

char Win_PeekChar(uint8_t col, uint8_t row)
{
	return (char) Win_PeekRaw(col, row);
}

uint16_t Win_PeekRaw(uint8_t col, uint8_t row)
{
	return _Win_Text[col + Math_Mul8x8(row, _Win.Cols)] & 0x7FFFU;
}