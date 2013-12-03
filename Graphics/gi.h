#pragma once
#define DLL __declspec(dllexport)

#include <windows.h>

namespace GI
{
	// InitGraphics
	//   Initialize and create the window. Must be done prior to using any other function calls.
	//
	// Parameters:
	//  
	//   updateRoutine : Function to be called to update the graphics in the window. Receives a float parameter (dt) which is the
	//                   amount of time (in seconds) since the last update and a float parameter (tt) which is the amount of
	//                   time (in seconds) since the first update.
	//   hInstance : The windows instance handle of the application running. Use the value passed in to WinMain.
	//   caption : The text value to display in the window caption bar.
	//   width : Set the pixel width of the new window.
	//   height : Set the pixel height of the new window.
	//
	DLL void Initialize_Graphics( HINSTANCE hInstance, LPCSTR title, int left, int top, int width, int height ) ;
	DLL void Render_Graphics(  ) ;
	DLL void Sample_Input( float* elapsed_time, bool* exit ) ;

	/****  Image Functions ****/
	typedef int ImageID ;
	typedef int Color ;

	DLL ImageID LoadImageFromFile( LPCSTR file_name_path ) ;
	DLL ImageID LoadImageFromFile( LPCSTR file_name_path, byte r, byte g, byte b ) ; // colorkey is fully transparent/invisible color
 	DLL ImageID CreateImage( UINT width, UINT height, bool writeable, bool visible ) ;
	DLL void    ClearImage( ImageID imageID, byte r, byte g, byte b ) ;
	DLL void    CopyImage( ImageID source, ImageID destination ) ;
	DLL void    DeleteImage( ImageID imageId ) ;
	DLL void    SetBackground( ImageID imageId );


	/*************  Sprite functions **********/

	typedef int SpriteID ;

	DLL SpriteID NewSprite( ImageID imageId ) ;
	DLL void     DeleteSprite( SpriteID spriteId ) ;

	DLL ImageID GetSpriteImage( SpriteID spriteId ) ;
	DLL void    SetSpriteImage( SpriteID spriteId, ImageID imageId ) ;

	DLL void SetSpriteX( SpriteID spriteId, int value ) ;
	DLL void SetSpriteY( SpriteID spriteId, int value ) ;
	DLL void SetSpriteDirection( SpriteID spriteId, float value ) ;
	DLL void SetSpriteDepth( SpriteID spriteId, float value ) ;
	DLL void SetSpriteVisible( SpriteID spriteId, bool visible ) ;

	DLL int   GetSpriteX( SpriteID spriteId ) ;
	DLL int   GetSpriteY( SpriteID spriteId ) ;
	DLL float GetSpriteDirection( SpriteID spriteId ) ;
	DLL float GetSpriteDepth( SpriteID spriteId ) ;
	DLL bool  GetSpriteVisible( SpriteID spriteId ) ;

	DLL void  MoveSprite( SpriteID spriteId, float pixels ) ;

	DLL UINT GetSpriteTile( SpriteID spriteId ) ;
	DLL void SetSpriteTile( SpriteID spriteId, UINT tile ) ;
	DLL void SetSpriteTint( SpriteID spriteId, Color color ) ;


	/****   Image functions  ****/

 	DLL UINT GetImageWidth ( ImageID imageId ) ;
 	DLL UINT GetImageHeight( ImageID imageId ) ;

	DLL UINT GetImageTileWidth( ImageID imageId ) ;
	DLL void SetImageTileWidth( ImageID imageId, UINT width ) ;
	DLL UINT GetImageTilesPerRow( ImageID imageId ) ;
	DLL void SetImageTilesPerRow( ImageID imageId, UINT count ) ;
	DLL UINT GetImageTileHeight( ImageID imageId ) ;
	DLL void SetImageTileHeight( ImageID imageId, UINT height ) ;
	DLL UINT GetImageTilesPerColumn( ImageID imageId ) ;
	DLL void SetImageTilesPerColumn( ImageID imageId, UINT count ) ;
	DLL UINT GetImageTilesPerImage( ImageID imageId ) ;

	DLL Color GetImageTexel( ImageID imageId, UINT x, UINT y);  // returns texel color in ARGB format
	DLL void  SetImageTexel( ImageID imageId, UINT x, UINT y, Color color ) ; 
	DLL void  SetImageTexel( ImageID imageId, UINT x, UINT y, byte r, byte g, byte b) ;
	DLL void  SetImageTexel( ImageID imageId, UINT x, UINT y, byte a, byte r, byte g, byte b) ;

	DLL void DrawImageBoundingBox( ImageID imageId ) ;


	/****  Input Functions   *****/
	
	enum MOUSE_BUTTON { LEFT, RIGHT, MIDDLE } ;

	DLL bool IsKeyDown( enum INPUT_KEY key ) ;
	DLL bool IsMouseButtonDown( MOUSE_BUTTON button ) ;
	DLL int GetMouseX();
	DLL int GetMouseY();
	DLL int GetMouseXChange() ;
	DLL int GetMouseYChange() ;

	enum INPUT_KEY
	{
		IK_ESCAPE          = 0x01,
		IK_1               = 0x02,
		IK_2               = 0x03,
		IK_3               = 0x04,
		IK_4               = 0x05,
		IK_5               = 0x06,
		IK_6               = 0x07,
		IK_7               = 0x08,
		IK_8               = 0x09,
		IK_9               = 0x0A,
		IK_0               = 0x0B,
		IK_MINUS           = 0x0C,    /* - on main keyboard */
		IK_EQUALS          = 0x0D,
		IK_BACK            = 0x0E,    /* backspace */
		IK_TAB             = 0x0F,
		IK_Q               = 0x10,
		IK_W               = 0x11,
		IK_E               = 0x12,
		IK_R               = 0x13,
		IK_T               = 0x14,
		IK_Y               = 0x15,
		IK_U               = 0x16,
		IK_I               = 0x17,
		IK_O               = 0x18,
		IK_P               = 0x19,
		IK_LBRACKET        = 0x1A,
		IK_RBRACKET        = 0x1B,
		IK_RETURN          = 0x1C,    /* Enter on main keyboard */
		IK_LCONTROL        = 0x1D,
		IK_A               = 0x1E,
		IK_S               = 0x1F,
		IK_D               = 0x20,
		IK_F               = 0x21,
		IK_G               = 0x22,
		IK_H               = 0x23,
		IK_J               = 0x24,
		IK_K               = 0x25,
		IK_L               = 0x26,
		IK_SEMICOLON       = 0x27,
		IK_APOSTROPHE      = 0x28,
		IK_GRAVE           = 0x29,    /* accent grave */
		IK_LSHIFT          = 0x2A,
		IK_BACKSLASH       = 0x2B,
		IK_Z               = 0x2C,
		IK_X               = 0x2D,
		IK_C               = 0x2E,
		IK_V               = 0x2F,
		IK_B               = 0x30,
		IK_N               = 0x31,
		IK_M               = 0x32,
		IK_COMMA           = 0x33,
		IK_PERIOD          = 0x34,    /* . on main keyboard */
		IK_SLASH           = 0x35,    /* / on main keyboard */
		IK_RSHIFT          = 0x36,
		IK_MULTIPLY        = 0x37,    /* * on numeric keypad */
		IK_LMENU           = 0x38,    /* left Alt */
		IK_SPACE           = 0x39,
		IK_CAPITAL         = 0x3A,
		IK_F1              = 0x3B,
		IK_F2              = 0x3C,
		IK_F3              = 0x3D,
		IK_F4              = 0x3E,
		IK_F5              = 0x3F,
		IK_F6              = 0x40,
		IK_F7              = 0x41,
		IK_F8              = 0x42,
		IK_F9              = 0x43,
		IK_F10             = 0x44,
		IK_NUMLOCK         = 0x45,
		IK_SCROLL          = 0x46,    /* Scroll Lock */
		IK_NUMPAD7         = 0x47,
		IK_NUMPAD8         = 0x48,
		IK_NUMPAD9         = 0x49,
		IK_SUBTRACT        = 0x4A,    /* - on numeric keypad */
		IK_NUMPAD4         = 0x4B,
		IK_NUMPAD5         = 0x4C,
		IK_NUMPAD6         = 0x4D,
		IK_ADD             = 0x4E,    /* + on numeric keypad */
		IK_NUMPAD1         = 0x4F,
		IK_NUMPAD2         = 0x50,
		IK_NUMPAD3         = 0x51,
		IK_NUMPAD0         = 0x52,
		IK_DECIMAL         = 0x53,    /* . on numeric keypad */
		IK_OEM_102         = 0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
		IK_F11             = 0x57,
		IK_F12             = 0x58,
		IK_F13             = 0x64,    /*                     (NEC PC98) */
		IK_F14             = 0x65,    /*                     (NEC PC98) */
		IK_F15             = 0x66,    /*                     (NEC PC98) */
		IK_KANA            = 0x70,    /* (Japanese keyboard)            */
		IK_ABNT_C1         = 0x73,    /* /? on Brazilian keyboard */
		IK_CONVERT         = 0x79,    /* (Japanese keyboard)            */
		IK_NOCONVERT       = 0x7B,    /* (Japanese keyboard)            */
		IK_YEN             = 0x7D,    /* (Japanese keyboard)            */
		IK_ABNT_C2         = 0x7E,    /* Numpad . on Brazilian keyboard */
		IK_NUMPADEQUALS    = 0x8D,    /* = on numeric keypad (NEC PC98) */
		IK_PREVTRACK       = 0x90,    /* Previous Track (IK_CIRCUMFLEX on Japanese keyboard) */
		IK_AT              = 0x91,    /*                     (NEC PC98) */
		IK_COLON           = 0x92,    /*                     (NEC PC98) */
		IK_UNDERLINE       = 0x93,    /*                     (NEC PC98) */
		IK_KANJI           = 0x94,    /* (Japanese keyboard)            */
		IK_STOP            = 0x95,    /*                     (NEC PC98) */
		IK_AX              = 0x96,    /*                     (Japan AX) */
		IK_UNLABELED       = 0x97,    /*                        (J3100) */
		IK_NEXTTRACK       = 0x99,    /* Next Track */
		IK_NUMPADENTER     = 0x9C,    /* Enter on numeric keypad */
		IK_RCONTROL        = 0x9D,
		IK_MUTE            = 0xA0,    /* Mute */
		IK_CALCULATOR      = 0xA1,    /* Calculator */
		IK_PLAYPAUSE       = 0xA2,    /* Play / Pause */
		IK_MEDIASTOP       = 0xA4,    /* Media Stop */
		IK_VOLUMEDOWN      = 0xAE,    /* Volume - */
		IK_VOLUMEUP        = 0xB0,    /* Volume + */
		IK_WEBHOME         = 0xB2,    /* Web home */
		IK_NUMPADCOMMA     = 0xB3,    /* , on numeric keypad (NEC PC98) */
		IK_DIVIDE          = 0xB5,    /* / on numeric keypad */
		IK_SYSRQ           = 0xB7,
		IK_RMENU           = 0xB8,    /* right Alt */
		IK_PAUSE           = 0xC5,    /* Pause */
		IK_HOME            = 0xC7,    /* Home on arrow keypad */
		IK_UP              = 0xC8,    /* UpArrow on arrow keypad */
		IK_PRIOR           = 0xC9,    /* PgUp on arrow keypad */
		IK_LEFT            = 0xCB,    /* LeftArrow on arrow keypad */
		IK_RIGHT           = 0xCD,    /* RightArrow on arrow keypad */
		IK_END             = 0xCF,    /* End on arrow keypad */
		IK_DOWN            = 0xD0,    /* DownArrow on arrow keypad */
		IK_NEXT            = 0xD1,    /* PgDn on arrow keypad */
		IK_INSERT          = 0xD2,    /* Insert on arrow keypad */
		IK_DELETE          = 0xD3,    /* Delete on arrow keypad */
		IK_LWIN            = 0xDB,    /* Left Windows key */
		IK_RWIN            = 0xDC,    /* Right Windows key */
		IK_APPS            = 0xDD,    /* AppMenu key */
		IK_POWER           = 0xDE,    /* System Power */
		IK_SLEEP           = 0xDF,    /* System Sleep */
		IK_WAKE            = 0xE3,    /* System Wake */
		IK_WEBSEARCH       = 0xE5,    /* Web Search */
		IK_WEBFAVORITES    = 0xE6,    /* Web Favorites */
		IK_WEBREFRESH      = 0xE7,    /* Web Refresh */
		IK_WEBSTOP         = 0xE8,    /* Web Stop */
		IK_WEBFORWARD      = 0xE9,    /* Web Forward */
		IK_WEBBACK         = 0xEA,    /* Web Back */
		IK_MYCOMPUTER      = 0xEB,    /* My Computer */
		IK_MAIL            = 0xEC,    /* Mail */
		IK_MEDIASELECT     = 0xED,    /* Media Select */

		/*
		 *  Alternate names for keys, to facilitate transition from DOS.
		 */
		IK_BACKSPACE       = IK_BACK,            /* backspace */
		IK_NUMPADSTAR      = IK_MULTIPLY,        /* * on numeric keypad */
		IK_LALT            = IK_LMENU,           /* left Alt */
		IK_CAPSLOCK        = IK_CAPITAL,         /* CapsLock */
		IK_NUMPADMINUS     = IK_SUBTRACT,        /* - on numeric keypad */
		IK_NUMPADPLUS      = IK_ADD,             /* + on numeric keypad */
		IK_NUMPADPERIOD    = IK_DECIMAL,         /* . on numeric keypad */
		IK_NUMPADSLASH     = IK_DIVIDE,          /* / on numeric keypad */
		IK_RALT            = IK_RMENU,           /* right Alt */
		IK_UPARROW         = IK_UP,              /* UpArrow on arrow keypad */
		IK_PGUP            = IK_PRIOR,           /* PgUp on arrow keypad */
		IK_LEFTARROW       = IK_LEFT,            /* LeftArrow on arrow keypad */
		IK_RIGHTARROW      = IK_RIGHT,           /* RightArrow on arrow keypad */
		IK_DOWNARROW       = IK_DOWN,            /* DownArrow on arrow keypad */
		IK_PGDN            = IK_NEXT,            /* PgDn on arrow keypad */

		/*
		 *  Alternate names for keys originally not used on US keyboards.
		 */
		IK_CIRCUMFLEX      = IK_PREVTRACK,       /* Japanese keyboard */
	} ;	// INPUT_KEY

}	// GI namespace