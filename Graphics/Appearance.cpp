#include "pch.h"
#include "Appearance.h"

Color::Color(void)
{
	r = g = b = 0 ;
}

Color::~Color(void)
{
}

Color::Color( ColorComponent r, ColorComponent g, ColorComponent b )
{
	this->r = r ;
	this->g = g ;
	this->b = b ;
}

Color Color::operator + ( const Color& other ) const
{
	return Color( r + other.r, g + other.g, b + other.b ) ;
}

void Color::operator += ( const Color& other )
{
	r += other.r ;
	g += other.g ;
	b += other.b ;
}

void Color::operator *= ( ColorComponent scale_factor )
{
	r *= scale_factor ;
	g *= scale_factor ;
	b *= scale_factor ;
}


Appearance::Appearance()
{
	solid = false ;
}

Appearance::Appearance( Color& color, bool solid )
{
	this->color = color ;
	this->solid = solid ;
}


void Appearance::Set_Color( const Color& color )
{
	this->color = color ;
}

void Appearance::Set_Solid( bool solid )
{
	this->solid = solid ;
}

void Appearance::Get_RGB( byte& red, byte& green, byte& blue ) const
{
	red   = byte( color.r * 255 ) ;
	green = byte( color.g * 255 ) ;
	blue  = byte( color.b * 255 ) ;
}


