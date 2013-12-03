#pragma once

#include "Shape.h"
#include "Vector2D.h"
#include "Matrix2D.h"

class Triangle2D
{
private:
	Vector2D vertex[3] ;

public:
	Triangle2D() ;
	Triangle2D( Vector2D& v1, Vector2D& v2, Vector2D& v3 ) ;
   ~Triangle2D() ;

	virtual void Translate( Vector2D T ) ;
	virtual void Render( const Appearance* ) const ;

	Vector2D Centroid()  ;
	void operator *= ( const Matrix2D& ) ;
} ;
