#pragma once
#include "Appearance.h"

class Shape // is an abstact class, meaning that you cannot make objects of this class
{
public:
	// assigning 0 to any virtual method makes the entire class "abstract"
	virtual void Translate( double Tx, double Ty, double Tz ) = 0 ;
	virtual void Render( const Appearance* ) const = 0 ;
} ;

