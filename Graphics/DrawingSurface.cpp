#include "pch.h"

#include "DrawingSurface.h"
#include "GI.h"
#include <math.h>

using namespace GI;

const double PI = 3.14159265358979323846 ;

namespace DrawingSurface
{
	int drawing_surface_image;
	int id ;
	int origin_x ;
	int origin_y ;
	int XSIZE ;
	int YSIZE ;
	byte background_color[3] ;

	const int CURSOR_OFFSET_X =  3 ;
	const int CURSOR_OFFSET_Y = -3 ;
} ;

void DrawingSurface::Initialize_Graphics( void* window_handle, char* title, int left, int top, int width, int height )
{
	GI::Initialize_Graphics( HINSTANCE(window_handle), title, left, top, width, height ) ;
}

void DrawingSurface::Sample_Input( float* elapsed_time, bool* game_over )
{
	GI::Sample_Input( elapsed_time, game_over ) ;
}

void DrawingSurface::Display_Graphics()
{
	GI::Render_Graphics() ;
}



void DrawingSurface:: Construct_DrawingSurface( int width, int height )
{
	XSIZE = width ;
	YSIZE = height ;
	drawing_surface_image = CreateImage( XSIZE, YSIZE, true, true ) ;
	id = NewSprite( drawing_surface_image ) ;
	origin_x = - ( XSIZE >> 1 ) + 3 ;
	origin_y = - ( YSIZE >> 1 ) - 3 ;
}

void DrawingSurface:: Destruct_DrawingSurface()
{
	DeleteSprite( id ) ;
	DeleteImage( drawing_surface_image ) ;
}


void DrawingSurface:: Set_Background_Color( byte r, byte g, byte b )
{
	background_color[0] = r ;
	background_color[1] = g ;
	background_color[2] = b ;
}

void DrawingSurface:: Draw_Background()
{
	ClearImage( drawing_surface_image, background_color[0], background_color[1], background_color[2] ) ;
}

void DrawingSurface:: Draw_Point( int xi, int yi, byte r, byte g, byte b )
{
	if ( xi >= 0 && xi+1 < XSIZE && yi >= 0 && yi+1 < YSIZE )
	{
		SetImageTexel( drawing_surface_image, xi, yi, r, g, b ) ;
		SetImageTexel( drawing_surface_image, xi+1, yi, r, g, b ) ;
		SetImageTexel( drawing_surface_image, xi+1, yi+1, r, g, b ) ;
		SetImageTexel( drawing_surface_image, xi, yi+1, r, g, b ) ;
	}
}

void DrawingSurface:: Draw_Edge( int x1, int y1, int x2, int y2, byte r, byte g, byte b )
{
	int num_pixels ;
	int delta_x = x2 - x1 ;
	int delta_y = y2 - y1 ;
	double dx, dy ;

	if ( abs( delta_x ) > abs( delta_y ) )
	{
		dx = delta_x > 0 ? 1 : -1 ;
		dy = dx * delta_y / delta_x ;
		num_pixels = abs( delta_x ) ;
	}
	else
	{
		dy = delta_y > 0 ? 1 : -1 ;
		dx = dy * delta_x / delta_y ;
		num_pixels = abs( delta_y ) ;
	}
	double x = x1 ;
	double y = y1 ;
	for ( int count = num_pixels ; count > 0 ; count-- ) 
	{
		int xi = ROUND(x) ;
		int yi = ROUND(y) ;
		if ( xi >= 0 && xi < XSIZE && yi >= 0 && yi < YSIZE )
			SetImageTexel( drawing_surface_image, xi, yi, r, g, b ) ;
		x += dx ;
		y += dy ;
	}
}

void DrawingSurface:: Draw_Scanline( int y, int x1, int x2,  byte r, byte g, byte b )
{
	if ( y < 0 || y >= YSIZE ) return ;
	if ( x1 > x2 ) return ;
	if ( x1 < 0 ) x1 = 0 ;
	if ( x2 >= XSIZE ) x2 = XSIZE - 1 ;

	for ( int x = x1 ; x <= x2 ; x++ )
		SetImageTexel( drawing_surface_image, x, y, r, g, b ) ;
}

void DrawingSurface:: Draw_Circle( int center_x, int center_y, int radius, bool solid, byte r, byte g, byte b )
{
	if ( !solid )
	{
		int num_edges = (int)(radius / 2 ) ;
		double angle = 2 * PI / num_edges, theta = 0.0  ;
		for ( int i = 0 ; i < num_edges ; i++, theta += angle )
		{
			Draw_Edge( ROUND( radius * cos( theta ) + center_x ), ROUND( radius * sin( theta ) + center_y ),
					   ROUND( radius * cos( theta+angle ) + center_x ), ROUND( radius * sin( theta+angle ) + center_y ),
					   r, g, b ) ;
		}
	}
	else
	{
		for ( int y = radius ; y >= 0 ; y-- )
		{
			double x ;
			int x1, x2, yl, yh ;
			x = sqrt( (double)(radius * radius - y * y) ) ;
			x1 = ROUND( center_x - x ) ;
			x2 = ROUND( center_x + x ) ;
			yl = ROUND( center_y - y ) ;
			yh = ROUND( center_y + y ) ;
			DrawingSurface:: Draw_Scanline( yl, x1, x2, r, g, b ) ;
			DrawingSurface:: Draw_Scanline( yh, x1, x2, r, g, b ) ;
		}
	}
}

#define INC(z) ((z+1)%3)
#define DEC(z) ((z+2)%3)
#define LEFT ((iy+move_left)%3)

void DrawingSurface:: Draw_Triangle( int x1, int y1, int x2, int y2, int x3, int y3, byte r, byte g, byte b )
{
#define HALFSPACES 1
#if HALFSPACES
	int x_min, y_min, x_max, y_max ;

	x_min = x1 < x2 ? x1 : x2 ;
	x_min = x3 < x_min ? x3 : x_min ;
	x_min = x_min < 0 ? 0 : x_min ;

	y_min = y1 < y2 ? y1 : y2 ;
	y_min = y3 < y_min ? y3 : y_min ;
	y_min = y_min < 0 ? 0 : y_min ;

	x_max = x1 > x2 ? x1 : x2 ;
	x_max = x3 > x_max ? x3 : x_max ;
	x_max = XSIZE-1 < x_max ? XSIZE-1 : x_max ;

	y_max = y1 > y2 ? y1 : y2 ;
	y_max = y3 > y_max ? y3 : y_max ;
	y_max = YSIZE-1 < y_max ? YSIZE-1 : y_max ;

	struct { double a, b, c ; } line[3] ;
	line[0].a = y1 - y2 ;
	line[0].b = x2 - x1 ;
	line[0].c = - ( x1 * line[0].a + y1 * line[0].b ) ;
	line[1].a = y2 - y3 ;
	line[1].b = x3 - x2 ;
	line[1].c = - ( x2 * line[1].a + y2 * line[1].b ) ;
	line[2].a = y3 - y1 ;
	line[2].b = x1 - x3 ;
	line[2].c = - ( x3 * line[2].a + y3 * line[2].b ) ;

	for ( int xi = x_min ; xi <= x_max ; xi++ )
		for ( int yi = y_max ; yi >= y_min ; yi-- )
		{
			bool inside = true ;
			for ( int i = 0 ; i < 3 ; i++ )
				inside &= 0.0 <= line[i].a * xi + line[i].b * yi + line[i].c ;
			if ( inside )
				SetImageTexel( drawing_surface_image, xi, yi, r, g, b ) ;
		}

#else
	struct { int x, y ; } pt[3] ;
	struct { double x[2], y[2], dx[2], dy[2], m[2]; int idy[2] ; } left, right ;

	pt[0].x = x1 ;
	pt[0].y = y1 ;
	pt[1].x = x2 ;
	pt[1].y = y2 ;
	pt[2].x = x3 ;
	pt[2].y = y3 ;

	int max_y = 0 ;
	for ( int i = 1 ; i < 3 ; i++ )
		if ( pt[i].y > pt[max_y].y ) max_y = i ;

	int move_left = pt[ INC(max_y) ].x < pt[ DEC(max_y) ].x ? 1 : 2 ;
	int move_right = move_left == 1 ? 2 : 1 ;
	int next_left = pt[(max_y+move_left)%3].y < pt[(max_y+move_right)%3].y ? 1 : 2 ;
	int next_right = next_left == 1 ? 2 : 1 ;

	double x_left = pt[max_y].x ;
	double x_right = pt[max_y].x ;

	left.x[0]  = pt[max_y].x ;
	left.y[0]  = pt[max_y].y ;
	right.x[0] = pt[max_y].x ;
	right.y[0] = pt[max_y].y ;

	if ( pt[ INC(max_y) ].x < pt[ DEC(max_y) ].x )
	{
		left.x[1]  = pt[INC(max_y)].x ;
		left.y[1]  = pt[INC(max_y)].y ;
		right.x[1] = pt[DEC(max_y)].x ;
		right.y[1] = pt[DEC(max_y)].y ;
	}
	else
	{
		left.x[1]  = pt[DEC(max_y)].x ;
		left.y[1]  = pt[DEC(max_y)].y ;
		right.x[1] = pt[INC(max_y)].x ;
		right.y[1] = pt[INC(max_y)].y ;
	}

	left.dx[0]  = left.x[1] - left.x[0] ;
	left.dy[0]  = left.y[1] - left.y[0] ;
	if ( left.dy[0] == 0.0 )
	{
		right.x[0] = right.x[1] ;
		right.y[0] = right.y[1] ;
		right.x[1] = left.x[1] ;
		right.y[1] = left.x[1] ;
	}


	for ( int i = 0 ; i < 2 ; i++ )
	{
		left.dx[i]  = left.x[1+i] - left.x[0+i] ;
		left.dy[i]  = left.y[1+i] - left.y[0+i] ;
		right.dx[i] = right.x[1+i] - right.x[0+i] ;
		right.dy[i] = right.y[1+i] - right.y[0+i] ;
		left.m[i]   = left.dx[i] / -left.dy[i] ;
		right.m[i]  = right.dx[i] / -right.dy[i] ;
	//	for ( int y = pt[max_y].y  ; y > pt[(max_y+move_left)%3].y ; y-- )
		for ( int y = ROUND( left.y[i] ), dy = ROUND( -left.dy[i] ) ; dy > 0 ; y--, dy-- )
		{
			Draw_Scanline( y, ROUND( left.x[i] ), ROUND( right.x[i] ), r,g,b ) ;
			left.x[i] += left.m[i] ;
			right.x[i] += right.m[i] ;
		}
	}
#endif
}


bool DrawingSurface:: GetMouse( int &x, int &y )
{
	x = GetMouseX() - origin_x ;
	y = GetMouseY() - origin_y ;
	y = YSIZE - y ;
	return ( x >= 0 && x < XSIZE && y >=0 && y < YSIZE ) ;
}

