/******************************************************************************
 * The monospaced fonts used byte the display are stored directly in internal
 * FLASH rom in a rather funky format with five three-color pixels packed into
 * each byte
 ******************************************************************************/
#ifndef _FONT_H
#define _FONT_H

// Note: This structure must be kept in sync with an equivalent definition
// in Core.asm
struct Font
{
	unsigned char XRes;
	unsigned char YRes;
	unsigned char Size;
	signed char Align;
	unsigned char Limit;
	const rom unsigned char *const rom *Chars;
};

extern const rom struct Font Font_Courier;
extern const rom struct Font Font_Icons;

#endif