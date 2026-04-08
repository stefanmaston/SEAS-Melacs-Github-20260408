/******************************************************************************
*
*                            Unison and DSPnano
*  Copyright 1987-2012 Multiprocessor Toolsmiths, Inc., RoweBots Research Inc.
*                           ALL RIGHTS RESERVED
*
*   This computer program is the property of RoweBots Research Inc.,
*   Kitchener, Ontario Canada. and may not be copied or redistributed in any 
*   form or by any means, whether in part or in whole, except under license 
*   granted by RoweBots Research Inc.
*
*   All copies of this program, whether in part or in whole, and whether 
*   modified or not, must display this and all other embedded copyright and 
*   ownership notices in full.  This notice may not be modified.
*
*   All source code is protected by international copyright laws and license
*   agreements.  Do not break the law.  You can obtain a license and source
*   code at rowebots.com subject to licensing conditions and restrictions.
*   Free development, free source code and free non commercial licenses may
*   be obtained in a few seconds on line without any difficult process.
*
*   All demonstration programs may be redistributed as source code to others  
*   as a small part of a Unison or DSPnano application. 
*
* ******************************************************************************   
*
*
*   Save Time and Money.  If you need modifications to the software to support
*   specific processors or peripherals, RoweBots Research can do this for you
*   quickly and easily at low cost.  If you need help with application develop-
*   ment, again we can solve your embedded development problems quickly and 
*   easily at very attractive prices.  We are tiny tiny embedded Linux* experts,
*   let us reduce your risk, accelerate your development and slash your time 
*   to market.  See rowebots.com - contact us.
*
*
*******************************************************************************/

#ifndef __USB_HID_KEYBOARD_H__
#define __USB_HID_KEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* "Alphabetic Keys"                                                          */
/******************************************************************************/
// Key code for 'a' and 'A'.
#define HID_Key_A                     4
// Key code for 'b' and 'B'.
#define HID_Key_B                     5
// Key code for 'c' and 'C'.
#define HID_Key_C                     6
// Key code for 'd' and 'D'.
#define HID_Key_D                     7
// Key code for 'e' and 'E'.
#define HID_Key_E                     8
// Key code for 'f' and 'F'.
#define HID_Key_F                     9
// Key code for 'g' and 'G'.
#define HID_Key_G                     10
// Key code for 'h' and 'H'.
#define HID_Key_H                     11
// Key code for 'i' and 'I'.
#define HID_Key_I                     12
// Key code for 'j' and 'J'.
#define HID_Key_J                     13
// Key code for 'k' and 'K'.
#define HID_Key_K                     14
// Key code for 'l' and 'L'.
#define HID_Key_L                     15
// Key code for 'm' and 'M'.
#define HID_Key_M                     16
// Key code for 'n' and 'N'.
#define HID_Key_N                     17
// Key code for 'o' and 'O'.
#define HID_Key_O                     18
// Key code for 'p' and 'P'.
#define HID_Key_P                     19
// Key code for 'q' and 'Q'.
#define HID_Key_Q                     20
// Key code for 'r' and 'R'.
#define HID_Key_R                     21
// Key code for 's' and 'S'.
#define HID_Key_S                     22
// Key code for 't' and 'T'.
#define HID_Key_T                     23
// Key code for 'u' and 'U'.
#define HID_Key_U                     24
// Key code for 'v' and 'V'.
#define HID_Key_V                     25
// Key code for 'w' and 'W'.
#define HID_Key_W                     26
// Key code for 'x' and 'X'.
#define HID_Key_X                     27
// Key code for 'y' and 'Y'.
#define HID_Key_Y                     28
// Key code for 'z' and 'Z'.
#define HID_Key_Z                     29
/******************************************************************************/

/******************************************************************************/
/* "Numeric Keys"                                                             */
/******************************************************************************/
// Key code for '1' and '!'.
#define HID_Key_1                     30
// Key code for '2' and '@'.
#define HID_Key_2                     31
// Key code for '3' and '#'.
#define HID_Key_3                     32
// Key code for '4' and '$'.
#define HID_Key_4                     33
// Key code for '5' and '%'.
#define HID_Key_5                     34
// Key code for '6' and '^'.
#define HID_Key_6                     35
// Key code for '7' and '&'.
#define HID_Key_7                     36
// Key code for '8' and '*'.
#define HID_Key_8                     37
// Key code for '9' and '('.
#define HID_Key_9                     38
// Key code for '0' and ')'.
#define HID_Key_0                     39
/******************************************************************************/

/******************************************************************************/
/* "Special Keys"                                                             */
/******************************************************************************/
// Enter key code.
#define HID_Key_ENTER                 40
// Escape key code.
#define HID_Key_ESCAPE                41
// Backspace key code.
#define HID_Key_BACKSPACE             42
// Tab key code.
#define HID_Key_TAB                   43
// Spacebar key code.
#define HID_Key_SPACEBAR              44
// Printscreen key code.
#define HID_Key_PRINTSCREEN           70
// Scroll lock key code.
#define HID_Key_SCROLLLOCK            71
// Num lock key code.
#define HID_Key_NUMLOCK               83
/******************************************************************************/

/******************************************************************************/
/* "Modified Keys"                                                            */
/******************************************************************************/
// Key code for the left 'Control' key.
#define HID_Key_LEFTCONTROL           224
// Key code for the left 'Shift' key.
#define HID_Key_LEFTSHIFT             225
// Key code for the left 'Alt' key.
#define HID_Key_LEFTALT               226
// Key code for the left 'GUI' (e.g. Windows) key.
#define HID_Key_LEFTGUI               227
// Key code for the right 'Control' key.
#define HID_Key_RIGHTCONTROL          228
// Key code for the right 'Shift' key.
#define HID_Key_RIGHTSHIFT            229
// Key code for the right 'Alt' key.
#define HID_Key_RIGHTALT              230
// Key code for the right 'GUI' key.
#define HID_Key_RIGHTGUI              231
/******************************************************************************/

/******************************************************************************/
/* "Error Codes"                                                             */
/******************************************************************************/
// Indicates that too many keys have been pressed at the same time.
#define ERROR_ROLL_OVER               1



/******************************************************************************/
/* "Consumer Page"                                                             */
/******************************************************************************/
#define HID_C_PLAY                  0xB0
#define HID_C_PAUSE                 0xB1
#define HID_C_RECORD                0xB2
#define HID_C_FAST_FORWARD          0xB3
#define HID_C_REWIND                0xB4
#define HID_C_SCAN_NEXT_TRACK       0xB5
#define HID_C_SCAN_PREVIOUS_TRACK   0xB6
#define HID_C_STOP                  0xB7


#define HID_C_VOLUME                0xE0
#define HID_C_BALANCE               0xE1
#define HID_C_MUTE                  0xE2
#define HID_C_BASS                  0xE3
#define HID_C_TREBLE                0xE4
#define HID_C_BASS_BOOST            0xE5
#define HID_C_SURROUND_MODE         0xE6
#define HID_C_LOUNDNESS             0xE7
#define HID_C_MPX                   0xE8
#define HID_C_VOLUME_INCREMENT      0xE9
#define HID_C_VOLUME_DECREMENT      0xEA



#define HID_KEY_SET                 1
#define HID_KEY_CLEAR               0

#ifdef __cplusplus
} //extern "C" {
#endif

#endif //__USB_HID_KEYBOARD_H__