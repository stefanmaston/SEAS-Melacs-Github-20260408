#include "Analog.h"
#include "Bus.h"
#include "Display.h"
#include "Font.h"
#include "Pins.h"
#include "Protocol.h"
#include "Window.h"

#define PROTO_RESPONSE_COOKIE 0x17
#define PROTO_INIT_COOKIE     0x8FE99CD4
#define PROTO_TRACE           1

static uint8_t Proto_Limit;


/******************************************************************************
 * Command IDs and parameters
 ******************************************************************************/
typedef union
{
	uint8_t Cmd;

	struct { uint8_t Cmd; uint32_t Cookie; uint8_t Slaves; } SInit;
	struct { uint8_t Cmd; uint8_t Block; } SWriteFirmware;
	struct { uint8_t Cmd; uint16_t Block; } SWriteFlash;

	struct { uint8_t Cmd; uint16_t Level; } WFade;
	struct { uint8_t Cmd; uint16_t XPos; uint8_t YPos; uint16_t XRes; uint8_t YRes; uint16_t Color; } WRect;
	struct { uint8_t Cmd; uint8_t Index; } WSelect;
	struct { uint8_t Cmd; uint8_t Font; uint16_t XPos; uint8_t YPos; } WCreate;
	struct { uint8_t Cmd; } WDestroy;
	struct { uint8_t Cmd; uint8_t Cols; uint8_t Rows; } WSize;
	struct { uint8_t Cmd; uint8_t Ch; } WClear;
	struct { uint8_t Cmd; } WRefresh;
	struct { uint8_t Cmd; } WInvalidate;
	struct { uint8_t Cmd; uint8_t Index; uint16_t Color; } WPalette;
	struct { uint8_t Cmd; uint8_t Color; } WPaper;
	struct { uint8_t Cmd; uint8_t Color; } WInk;
	struct { uint8_t Cmd; uint8_t Col; uint8_t Row; } WCursor;
	struct { uint8_t Cmd; uint8_t Ch; } WChar;
	struct { uint8_t Cmd; } WString;
}
Proto_Args;

enum
{
	/* 0x00 */ PROTO_S_INIT,
	/* 0x01 */ PROTO_S_WRITE_FIRMWARE,
	/* 0x02 */ PROTO_S_WRITE_FLASH,

	/* 0x03 */ PROTO_W_FADE,
	/* 0x04 */ PROTO_W_RECT,
	/* 0x05 */ PROTO_W_SELECT,
	/* 0x06 */ PROTO_W_CREATE,
	/* 0x07 */ PROTO_W_DESTROY,
	/* 0x08 */ PROTO_W_SIZE,
	/* 0x09 */ PROTO_W_CLEAR,
	/* 0x0A */ PROTO_W_REFRESH,
	/* 0x0B */ PROTO_W_INVALIDATE,
	/* 0x0C */ PROTO_W_PALETTE,
	/* 0x0D */ PROTO_W_PAPER,
	/* 0x0E */ PROTO_W_INK,
	/* 0x0F */ PROTO_W_CURSOR,
	/* 0x10 */ PROTO_W_CHAR,
	/* 0x11 */ PROTO_W_STRING
};

extern Proto_Args _args;

static const rom uint8_t Proto_Payload[] =
{
	/* 0x00 */ sizeof _args.SInit,          // PROTO_S_INIT
	/* 0x01 */ sizeof _args.SWriteFirmware, // PROTO_S_WRITE_FIRMARE
	/* 0x02 */ sizeof _args.SWriteFlash,    // PROTO_S_WRITE_FLASH

	/* 0x03 */ sizeof _args.WFade,          // PROTO_W_FADE
	/* 0x04 */ sizeof _args.WRect,          // PROTO_W_RECT
	/* 0x05 */ sizeof _args.WSelect,        // PROTO_W_SELECT
	/* 0x06 */ sizeof _args.WCreate,        // PROTO_W_CREATE
	/* 0x07 */ sizeof _args.WDestroy,       // PROTO_W_DESTROY
	/* 0x08 */ sizeof _args.WSize,          // PROTO_W_SIZE
	/* 0x09 */ sizeof _args.WClear,         // PROTO_W_CLEAR
	/* 0x0A */ sizeof _args.WRefresh,       // PROTO_W_REFRESH
	/* 0x0B */ sizeof _args.WInvalidate,    // PROTO_W_INVALIDATE
	/* 0x0C */ sizeof _args.WPalette,       // PROTO_W_PALETTE
	/* 0x0D */ sizeof _args.WPaper,         // PROTO_W_PAPER
	/* 0x0E */ sizeof _args.WInk,           // PROTO_W_INK
	/* 0x0F */ sizeof _args.WCursor,        // PROTO_W_CURSOR
	/* 0x10 */ sizeof _args.WChar,          // PROTO_W_CHAR
	/* 0x11 */ sizeof _args.WString         // PROTO_W_STRING
};

// The list of selectable fonts
static const rom struct Font *const rom Proto_FontSet[] =
{
	/* 0x00 */ &Font_Courier
};


/******************************************************************************
 * Response messages
 ******************************************************************************/
enum
{
	/* 0x00 */ PROTO_R_LOCK,
	/* 0x01 */ PROTO_R_STATUS
};

volatile union Proto_Response_t
{
	uint8_t Cmd;

	struct
	{
		uint8_t Cmd;
		uint8_t Cookie;
		uint16_t FirmwareChecksum;
		uint16_t FlashChecksum;
	}
	Lock;

	struct
	{
		uint8_t Cmd;
		uint8_t Cookie;
		uint8_t Buttons;
	}
	Status;
}
Bus_Response;


/******************************************************************************
 * (Re-)initialize the system
 ******************************************************************************/
void Proto_Init(void)
{
	Proto_Limit = 0;
	Bus_Response.Lock.Cookie = PROTO_RESPONSE_COOKIE;
}


/******************************************************************************
 * The main message loop
 ******************************************************************************/
void Proto_Run(void)
{
	// Process incoming messages
	while(Bus_Ready())
	{
		Proto_Args args;
		uint8_t len;
		uint8_t *ptr;
		uint8_t ch;
		uint16_t block;

		// Get the command ID and fetch the argument list
		args.Cmd = Bus_Get();
rewind:
		if(args.Cmd > Proto_Limit)
			goto invalid_message;

#		if PROTO_TRACE
		Trace("%2x", (unsigned) args.Cmd);
#		endif

		len = Proto_Payload[args.Cmd];
		ptr = &args.Cmd;

		while(--len)
		{
			ch = Bus_Get();
			*++ptr = ch;

#			if PROTO_TRACE
			Trace("-%2x", (unsigned) ch);
#			endif

			// Handle initializiation message arriving out-of-phase
			if(ch == PROTO_S_INIT && !Proto_Limit)
				goto rewind;
		}

#		if PROTO_TRACE		
		Trace("\n");
#		endif

		// Implement each command
		switch(args.Cmd)
		{
			char ch;

		// System messages
		case PROTO_S_INIT:
			// Only respond to initialization messages with the proper key on
			// startup or after loosing synchronization
			if(args.SInit.Cookie == PROTO_INIT_COOKIE)
			{
				// Make this particular node is flagged as active
				ch = 0x01;
				if(Bus_IsSecondary())
					ch = 0x02;

				if(args.SInit.Slaves & ch)
				{
					Proto_Limit = countof(Proto_Payload) - 1;
#					if PROTO_TRACE		
					Trace("Unlocked\n");
#					endif

					// Reset the windowing system
					Win_Init();

					// Stop sending the "locked" response as soon as possible
					goto immediate_response;
				}
			}
			break;

//		case PROTO_S_WRITE_FIRMWARE:
//		case PROTO_S_WRITE_FLASH:

		// Windowing messages
		case PROTO_W_FADE:
			Disp_SetBacklight(args.WFade.Level);
			break;
		case PROTO_W_RECT:
			Disp_Rect(args.WRect.XPos, args.WRect.YPos, args.WRect.XRes, args.WRect.YRes, args.WRect.Color);
			break;
		case PROTO_W_SELECT:
			Win_Select(args.WSelect.Index);
			break;
		case PROTO_W_CREATE:
			if(args.WCreate.Font < countof(Proto_FontSet))
				Win_Create(Proto_FontSet[args.WCreate.Font], args.WCreate.XPos, args.WCreate.YPos);
			break;
		case PROTO_W_DESTROY:
			Win_Destroy();
			break;
		case PROTO_W_SIZE:
			Win_Size(args.WSize.Cols, args.WSize.Rows);
			break;
		case PROTO_W_CLEAR:
			Win_Clear(args.WClear.Ch);
			break;
		case PROTO_W_REFRESH:
			Win_Refresh();
			goto immediate_response;
		case PROTO_W_INVALIDATE:
			Win_Invalidate();
			break;
		case PROTO_W_PALETTE:
			if(args.WPalette.Index < countof(Win_Palette))
				Win_Palette[args.WPalette.Index] = args.WPalette.Color;
			break;
		case PROTO_W_PAPER:
			Win_Paper(Win_Palette[args.WPaper.Color]);
			break;
		case PROTO_W_INK:
			Win_Ink(args.WInk.Color);
			break;
		case PROTO_W_CURSOR:
			Win_Cursor(args.WCursor.Col, args.WCursor.Row);
			break;
		case PROTO_W_CHAR:
			Win_Console(args.WChar.Ch);
			break;
		case PROTO_W_STRING:
			while(ch = Bus_Get(), ch)
				Win_Console(ch);
			break;

		// Stop processing messages after the first invalid request
		default:
invalid_message:
#			if PROTO_TRACE
			if(Proto_Limit)
				Trace("Locked (%02x)\n", (unsigned) args.Cmd);
#			endif
			Proto_Init();
			goto immediate_response;
		}
	}

	// Form a new response
immediate_response:
	Bus_LockResponse();

	if(!Proto_Limit)
	{
		// Inform the master that we've lost synchronization
		Bus_Response.Cmd = PROTO_R_LOCK;
		Bus_ResponseLen = sizeof Bus_Response.Lock;
	}
	else
	{
		// Respond with a bit-mask of the buttons while we're online
		Bus_Response.Cmd = PROTO_R_STATUS;
		Bus_Response.Status.Buttons =
			Analog_Touch(0) /* << 0 */ |
			Analog_Touch(1) << 1 |
			Analog_Touch(2) << 2 |
			Analog_Touch(3) << 3;
		Bus_ResponseLen = sizeof Bus_Response.Status;
	}

	Bus_UnlockResponse();
}