#pragma once

typedef unsigned char byte ;
#define ROUND( x ) int( x + 0.5 )

/*** This is a namespace, because there is only a single drawing surface per window ***/
namespace DrawingSurface
{
	void Initialize_Graphics( void* window_handle, char* title, int left, int top, int width, int height ) ;
	void Sample_Input( float* elapsed_time, bool* game_over ) ;
	void Display_Graphics() ;

	void Construct_DrawingSurface( int width, int height ) ;
	void Destruct_DrawingSurface() ;

	void Set_Background_Color( byte r, byte g, byte b ) ;
	void Draw_Background() ;

	void Draw_Point( int xi, int yi, byte r, byte g, byte b ) ;

	void Draw_Edge( int x1, int y1, int x2, int y2, byte r, byte g, byte b ) ;
	void Draw_Scanline( int y, int x1, int x2,  byte r, byte g, byte b ) ;
	void Draw_Circle( int x, int y, int radius, bool solid, byte r, byte g, byte b ) ;
	void Draw_Triangle( int x1, int y1, int x2, int y2, int x3, int y3, byte r, byte g, byte b ) ;

	bool GetMouse( int &x, int &y ) ;
} ; // DrawingSurface

