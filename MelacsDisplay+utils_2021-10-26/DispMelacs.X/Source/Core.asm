;-------------------------------------------------------------------------------
;Functions split off from various modules and implemented in assembly language
;for performance (or convenience)
;-------------------------------------------------------------------------------
			INCLUDE	"P18F67J93.inc"
			INCLUDE	"Pins.h"

			RADIX	DEC


;-------------------------------------------------------------------------------
;void Analog_Interrupt(void)
;void Analog_Value(uint8_t ch : WREG)
;-------------------------------------------------------------------------------
			;These must be kept in sync with the C definitions in Analog.h
A_CHANNELS	equ 1

			CBLOCK	0
A_Average:	2							;uint16_t Average
;										;uint16_t Touch : 1
A_Limit:	2							;uint16_t Limit : 15
A_History: 	1							;uint8_t History
A_Chain:	1							;uint8_t Chain : 6
;										;uint8_t Status : 1
A_Current:	1							;uint8_t Current
A_SizeOf:	0
			ENDC

			CBLOCK 0
A_Scan:		1							;uint8_t Scan
A_Array:	A_CHANNELS*A_SizeOf			;struct _Analog_Channel Channels[]
			ENDC

A_Touch		equ		0
A_Status	equ		6

			EXTERN	_Analog

			;Continual background A/D sampling interrupt. This is triggered by
			;timer #2 and scans through each of the channels in order, filtering
			;the results and doing some capacitive touch handling
analog		CODE

			GLOBAL	Analog_Interrupt
Analog_Interrupt:
			BANKSEL	CTMUCONH			;Drain any previous charge
			bsf		CTMUCONH,IDISSEN

			movff	FSR2L,PREINC1		;Save registers
			movff	FSR2H,PREINC1

			lfsr	FSR2,_Analog		;Rotate the scanning pointer
			movf	[A_Scan],W
 			addlw	-A_SizeOf
			btfss	STATUS,C
			addlw	+A_SizeOf*A_CHANNELS
			movwf	[A_Scan]
			addwf	FSR2L,F,A			;Point FSR2 at the new A/D channel's stucture

			movsf	[A_Chain],ADCON0	;Select the next ADC channel for sampling

			movf	[A_Average+0],W		;Storage averaged ADC reading
			xorwf	[A_Average+1],W		;( avg = avg - avg/16 + ADRES )

			movsf	[A_Current],CTMUICON;Set current calibration

			bcf		CTMUCONH,IDISSEN	;Stop draining the CTMU and start charging,
			btfsc	[A_Limit+0],A_Touch	;though only for the touch channels
			bsf		CTMUCONL,EDG1STAT	;00
										;..
			andlw	0xF0				;01 Continue calculating the average
			xorwf	[A_Average+1],W		;02
			swapf	WREG,W,A			;03
			subwf	[A_Average+0]		;04
			swapf	[A_Average+1],W		;05
			andlw	0x0F				;06
			subwfb	[A_Average+1]		;07
			movf	ADRESL,W,A			;08
			addwf	[A_Average+0]		;09
			movf	ADRESH,W,A			;10
			addwfc	[A_Average+1]		;11
										;..
			movf	[A_Average+0],W		;12 Compare average against the neutral limit
			subwf	[A_Limit+0],W		;13 and shift the result into the history buffer
			movf	[A_Average+1],W		;14
			subwfb	[A_Limit+1],W		;15
			rrcf	[A_History]			;16
			infsnz	[A_History],W		;17 Switch to the pressed or depressed state when
			bsf		[A_Chain],A_Status	;18 the entire history is set or clear
			dcfsnz	WREG,W,A			;19
			bcf		[A_Chain],A_Status	;20
										;..
			movff	POSTDEC1,FSR2H		;22 Restore registers and acknowledge timer interrupt 
			movff	POSTDEC1,FSR2L		;24
			bcf		PIR1,TMR2IF,A		;25
										;..
			bcf		CTMUCONL,EDG1STAT	;26 Stop charging (for touch channels) and
			bsf		ADCON0,GO,A			;   start the A/D conversion before returning
			retfie	FAST

			;Fetch the current average value of a specific channel
			GLOBAL	_Analog_Value
_Analog_Value:
			mullw	A_SizeOf
			lfsr	FSR0,_Analog+(A_Array+A_Average)
			movf	PRODL,W,A
			addwf	FSR0L,F,A

			bcf		PIE1,TMR2IE,A		;Temporarily block out the sampling interrupt
			movff	POSTINC0,PRODL
			movff	POSTINC0,PRODH
			bsf		PIE1,TMR2IE,A
			return


;-------------------------------------------------------------------------------
;Import the active window structure. This must be kept in sync with the C
;definition in Window.h and Font.h!
;-------------------------------------------------------------------------------
#define		WIN(k) (_Win_State+(k))		;The way the assembler handles
										;compile-time expressions makes crap
										;like this necessary

			CBLOCK	0

			;Window structure
W_Flags:	1							;uint8_t Live : 1

W_XPos:		2							;uint16_t XPos
W_YPos:		1							;uint8_t YPos
W_Cols:		1							;uint8_t Cols
W_Rows:		1							;uint8_t Rows

W_Ink: 		1							;uint8_t Ink
W_Paper:	1							;uint8_t Paper
W_Font:		2							;const rom Font *Font

			;Index of the active window
X_CurrentIndex:1						;uint8_t CurrentIndex;

			;Font structure
F_XRes:		1							;uint8_t XRes
F_YRes:		1							;uint8_t YRes
F_Size:		1							;uint8_t Size
F_Align:	1							;int8_t Align
F_Limit:	1							;uint8_t Limit
F_Chars:	2							;const rom uint8_t *const rom *Chars

			;Extra fields
X_Text:		2							;uint16_t *Text
X_Ink:		2							;uint16_t Ink
X_Paper:	2							;uint16_t Paper
X_InkDir:	2							;uint16_t InkDirect;
X_PaperDir:	2							;uint16_t PaperDirect;
X_CursorCol:1							;uint8_t CursorCol
X_CursorRow:1							;uint8_t CursorRow
X_CursorPtr:2							;uint16_t CursorPtr

			;Track how much buffer space has been used
X_BufferTail:2							;uint16_t *BufferTail;

			ENDC

			EXTERN	_Win_State


;-------------------------------------------------------------------------------
;Low-level display I/O
;
;void _Disp_Register(uint8_t regno : WREG)
;uint16_t _Disp_ReadDirect(void)
;void _Disp_CommandDirect(uint8_t regno : WREG, uint16_t value : PROD)
;void _Disp_WriteDirect(uint16_t value : PROD)
;void _Disp_Command(uint8_t regno : WREG, uint16_t value : PROD)
;void _Disp_Write(uint8_t regno : WREG, uint16_t value : PROD)
;-------------------------------------------------------------------------------
			ifdef	HW_REVISION_0
			EXTERN	Disp_Reverse
			endif

dio			CODE

			GLOBAL	_Disp_Register
_Disp_Register:
			bcf		DISP_CTRL,DISP_DC_BIT,A
			clrf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			movwf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_DC_BIT,A
			return

			GLOBAL	_Disp_ReadDirect
_Disp_ReadDirect:
			setf	DISP_TRIS,A
			bcf		DISP_CTRL,DISP_RD_BIT,A
			bra		$+2
			movff	DISP_DATA,PRODH
			bsf		DISP_CTRL,DISP_RD_BIT,A
			bra		$+2
			nop
			bcf		DISP_CTRL,DISP_RD_BIT,A
			bra		$+2
			movff	DISP_DATA,PRODL
			bsf		DISP_CTRL,DISP_RD_BIT,A
			clrf	DISP_TRIS,A
			return

			GLOBAL	_Disp_CommandDirect
_Disp_CommandDirect:
			bcf		DISP_CTRL,DISP_DC_BIT,A
			clrf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			movwf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_DC_BIT,A

			;Fallthrough
			; .
			; .

			GLOBAL	_Disp_WriteDirect
_Disp_WriteDirect:
			movff	PRODH,DISP_DATA
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			movff	PRODL,DISP_DATA
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			return

			GLOBAL	_Disp_Command
_Disp_Command:
			bcf		DISP_CTRL,DISP_DC_BIT,A
			clrf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			movwf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_DC_BIT,A

			;Fallthrough
			; .
			; .

			GLOBAL	_Disp_Write
_Disp_Write:
			ifdef	HW_REVISION_0
			lfsr	FSR0,Disp_Reverse
			movff	PRODH,FSR0L
			movff	INDF0,DISP_DATA
			else
			movff	PRODH,DISP_DATA
			endif
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			ifdef	HW_REVISION_0
			movff	PRODL,FSR0L
			movff	INDF0,DISP_DATA
			else
			movff	PRODL,DISP_DATA
			endif
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			return

			ifdef	HW_REVISION_0
			GLOBAL	_Disp_Direct
_Disp_Direct:
			lfsr	FSR0,Disp_Reverse
			movff	PRODH,FSR0L
			movff	INDF0,PRODH
			movff	PRODL,FSR0L
			movff	INDF0,PRODL
			return
			endif


;-------------------------------------------------------------------------------
;void _Disp_PutSolidChar(const uint8_t *pixels : TBLPTR)
;
;The write window is expected to be set up on entry
;
;12 3/8 cyc/pixel (=> 8.418 Hz)
;-------------------------------------------------------------------------------
psc_len		= PCLATH
psc_mix		= PROD

psc_pix		MACRO	scale
			LOCAL	mix,paper,join

			;This is optimized for the case of transparent pixels
			IF		scale == -1
			decf	TABLAT,F,A
			bnc		paper
			decf	TABLAT,F,A
			bnc		mix
			ELSE
			IF		scale > 0
			movlw	scale
			addwf	TABLAT,F,A
			bc		paper
			addwf	TABLAT,F,A
			bc		mix
			addwf	TABLAT,F,A
			ELSE
			movlw	scale
			addwf	TABLAT,F,A
			bnc		paper
			addwf	TABLAT,F,A
			bnc		mix
			addwf	TABLAT,F,A
			ENDIF
			ENDIF

			ifdef 	HW_REVISION_0
			movff	WIN(X_InkDir+1),DISP_DATA
			movf	WIN(X_InkDir+0),W
			else
			movff	WIN(X_Ink+1),DISP_DATA
			movf	WIN(X_Ink+0),W
			endif
			bra		join
mix:		movff	psc_mix+1,DISP_DATA
			movf	psc_mix+0,W,A
			bra		join
			ifdef 	HW_REVISION_0
paper:		movff	WIN(X_PaperDir+1),DISP_DATA
			movf	WIN(X_PaperDir+0),W
			else
paper:		movff	WIN(X_Paper+1),DISP_DATA
			movf	WIN(X_Paper+0),W
			endif
join:		bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			movwf	DISP_DATA,A
			bcf		DISP_CTRL,DISP_WR_BIT,A
			bsf		DISP_CTRL,DISP_WR_BIT,A
			endm

psc			CODE

			GLOBAL	_Disp_PutSolidChar
_Disp_PutSolidChar:
			BANKSEL	_Win_State

			ifdef	HW_REVISION_0
			lfsr	FSR0,Disp_Reverse	;Bit-flip the ink color
			movff	WIN(X_Ink+0),FSR0L
			movff	INDF0,WIN(X_InkDir+0)
			movff	WIN(X_Ink+1),FSR0L
			movff	INDF0,WIN(X_InkDir+1)
			endif

			rrcf	WIN(X_Ink+1),W		;Blend the paper and ink colors
			andlw	B'01111011'
			movwf	psc_mix+1,A
			rrcf	WIN(X_Ink+0),W
			andlw	B'11101111'
			ifdef	HW_REVISION_0
			movwf	FSR0L,A
			else
			movwf	psc_mix+0
			endif
			rrcf	WIN(X_Paper+1),W
			andlw	B'01111011'
			movwf	TABLAT,A
			rrcf	WIN(X_Paper+0),W
			andlw	B'11101111'
			ifdef	HW_REVISION_0
			addwf	FSR0L,F,A
			movff	INDF0,psc_mix+0
			else
			addwf	psc_mix+0,F
			endif
			movf	TABLAT,W,A
			ifdef	HW_REVISION_0
			addwfc	psc_mix+1,W
			movwf	FSR0L,A
			movff	INDF0,psc_mix+1
			else
			addwfc	psc_mix+1,F
			endif


			tblrd*+

			movff	WIN(F_Size),psc_len	;Prepare the loop counter and handle
			movf	WIN(F_Align),W		;character sizes not an even multiple
			bn		psc_pixel4			;of bytes long by skipping initial
			bz		psc_pixel3			;pixels
			addlw	-2
			bn		psc_pixel2
			bz		psc_pixel1

psc_pixel0:								;Decode each of the five triples in
			psc_pix	-81					;a byte and emit their corresponding
psc_pixel1:								;pixels
			psc_pix	+27
psc_pixel2:
			psc_pix	-9
psc_pixel3:
			psc_pix	+3
psc_pixel4:
			psc_pix	-1
			tblrd*+
			decfsz	psc_len,F,A
			bra		psc_pixel0
			return


;-------------------------------------------------------------------------------
;void Win_Invalidate(void)
;void Win_Clear(char ch : TABLAT);
;-------------------------------------------------------------------------------
window		CODE

w_content:
			BANKSEL	_Win_State
			movf	WIN(W_Cols),W
			mulwf	WIN(W_Rows)
			movff	WIN(X_Text+0),FSR0L
			movff	WIN(X_Text+1),FSR0H
			return

			GLOBAL	Win_Invalidate
Win_Invalidate:
			rcall	w_content
			bra		wi_enter
wi_loop:
			movf	PREINC0,W,A
			bsf		POSTINC0,7,A
wi_enter:
			decf	PRODL,F,A
			bc		wi_loop
			decf	PRODH,F,A
			bc		wi_loop
			return

			GLOBAL	_Win_Clear
_Win_Clear:
			rcall	w_content
			movf	WIN(W_Ink),W
			iorlw	0x80
			bra		wc_enter
wc_loop:
			movff	TABLAT,POSTINC0
			movwf	POSTINC0,A
wc_enter:
			decf	PRODL,F,A
			bc		wc_loop
			decf	PRODH,F,A
			bc		wc_loop
			return


;-------------------------------------------------------------------------------
;uint16_t Math_Mul8x8(uint8_t f1 : PRODL, uint8_t : WREG)
;uint8_t Math_BCDToBin(uint8_t bcd : TABLAT)
;uint8_t Math_BinToBCD(uint8_t bin : TABLAT)
;uint8_t Math_Random(uint8_t range : TABLAT)
;void Math_Enthropy(const void *data : FSR0, uint8_t len : PRODL)
;-------------------------------------------------------------------------------
math_data	IDATA

			GLOBAL	Math_Seed
Math_Seed	dw		0xACE1


math_code	CODE

			GLOBAL	_Math_Mul8x8
_Math_Mul8x8:
			mulwf	PRODL,A
			return

			;Conversion between binary and BCD for the real-time clock
			GLOBAL	_Math_BCDToBin
_Math_BCDToBin:
			swapf	TABLAT,W,A			;bin = bcd >> 4;
			andlw	0x0F
			mullw	10					;bin *= 10;
			movf	TABLAT,W,A
			andlw	0x0F				;bcd &= 15;
			addwf	PRODL,W,A			;bin += bcd;
			return

			GLOBAL	_Math_BinToBCD
_Math_BinToBCD:
			rrcf	TABLAT,W,A			;bcd = bin;
			bcf		WREG,7,A			;bin >>= 1;
			mullw	0x34				;bin = (uint16_t) bin * 0x34 >> 8;
			movf	PRODH,W,A
			mullw	6					;bin *= 16 - 10;
			addwf	TABLAT,W,A			;bcd += bin;
			return

			;Generate a random number (0 <= x < range)
			GLOBAL	_Math_Random
_Math_Random:
			BANKSEL	Math_Seed			;16-bit LFSR
			rrcf	Math_Seed+0,W		;(x^16 + x^14 + x^13 + x^11 + x^0 polynomial)
			btfsc	Math_Seed+0,2
			btg		STATUS,C,A
			btfsc	Math_Seed+0,3
			btg		STATUS,C,A
			btfsc	Math_Seed+0,5
			btg		STATUS,C,A
			rrcf	Math_Seed+1
			rrcf	Math_Seed+0

			movf	TABLAT,W,A			;Treat the random number as a fixed-point
			mulwf	Math_Seed+0			;fraction and multiply with the range to
			movff	PRODH,TABLAT		;get the final result
			mulwf	Math_Seed+1
			movf	PRODL,W,A
			addwf	TABLAT,F,A
			movlw	0
			addwfc	PRODH,W,A
			return

			;Perturb the random seed by hashing it against some source of enthropy
			GLOBAL	_Math_Entropy
me_loop:
			rrcf	Math_Seed+1			;Use CRC-16
			rrcf	Math_Seed+0			;(x^16 + x^12 + x^2 + x^0 polynomial)
			bnc		me_reenter
			btg		Math_Seed+1,7
			btg		Math_Seed+1,5
			btg		Math_Seed+0,0
			bcf		STATUS,C,A
me_reenter:
			rrcf	WREG,F,A
			bnz		me_loop
_Math_Entropy:
			BANKSEL	Math_Seed
			movf	POSTINC0,W,A
			decf	PRODL,F,A
			bc		me_reenter

			movf	Math_Seed+1,W		;Avoid getting stuck at zero
			iorwf	Math_Seed+0,W
			btfsc	STATUS,Z,A
			incf	Math_Seed+0
			return


;-------------------------------------------------------------------------------
;void EPFlash_DisplayPage(uint16_t length : FSR0);
;
;Clock through an array of data from the parallel FLASH straight into display
;memory over the shared bus. Note that the maximum length is limited to 4096
;bytes
;-------------------------------------------------------------------------------
epflash		CODE

			GLOBAL	_EPFlash_DisplayPage
_EPFlash_DisplayPage:
			addfsr	FSR0,15				;Length rounded up and divided by sixteen
			movf	FSR0L,W				;as loop counter
			mullw	0x10
			swapf	FSR0H,W
			addwf	PRODH

			comf	FSR0L,W				;Extract the negated length modulo sixteen
			rlncf	WREG,W				;and multiply by four instruction bytes per
			rlncf	WREG,W				;iteration as the jump table entry offset
			andlw	0x0F<<2

			addlw	ed_loop-ed_push		;Enter the loop by adding the offset to
			push						;the program counter, with a fake stack
ed_push:	addwf	TOSL				;entry as trampoline
			movlw	0
			addwfc	TOSH
			addwfc	TOSU
			retlw	EPFLASH_RE_MASK|DISP_WR_MASK

ed_loop:	xorwf	EPFLASH_RE_PORT,F	;16x bytes 
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;15x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;14x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;13x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;12x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;11x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	;10x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 9x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 8x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 7x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 6x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 5x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 4x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 3x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 2x bytes
			xorwf	EPFLASH_RE_PORT,F
			xorwf	EPFLASH_RE_PORT,F	; 1x byte
			xorwf	EPFLASH_RE_PORT,F
			decfsz	PRODH,F
			bra		ed_loop

			return
			END