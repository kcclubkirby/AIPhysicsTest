#pragma once

typedef unsigned char byte ;

class Color
{
public:
	typedef float ColorComponent ;
	ColorComponent r, g, b ;

public:
	Color(void) ;
   ~Color(void) ;
	Color( ColorComponent r, ColorComponent g, ColorComponent b ) ;

	Color operator +  ( const Color& ) const ;
	void  operator += ( const Color& ) ;
	void  operator *= ( ColorComponent scale_factor ) ;
};

class Appearance
{
public:
	Color color ;
	bool  solid ;

public:
	Appearance() ;
	Appearance( Color&, bool solid ) ;

	void Set_Color( const Color& color ) ;
	void Set_Solid( bool solid ) ;
	void Get_RGB( byte& red, byte& green, byte& blue ) const ;
} ;
