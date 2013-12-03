
#include "Triangle2D.h"
#include "DrawingSurface.h"


Triangle2D::Triangle2D(void)
{
}

Triangle2D:: Triangle2D( Vector2D& v1, Vector2D& v2, Vector2D& v3 )
{
	vertex[0] = v1 ;
	vertex[1] = v2 ;
	vertex[2] = v3 ;
}

Triangle2D::~Triangle2D(void)
{
}

void Triangle2D:: Translate( Vector2D T )
{
	for ( int i = 0 ; i < 3 ; i++ ) vertex[i] += T ;
}


void Triangle2D:: Render( const Appearance* appearance ) const
{
	byte r, g, b ;
	appearance->Get_RGB( r, g, b ) ;

	if ( appearance->solid )
		DrawingSurface:: Draw_Triangle( ROUND( vertex[0][X] ), ROUND( vertex[0][Y] ), ROUND( vertex[1][X] ), ROUND( vertex[1][Y] ), ROUND( vertex[2][X] ), ROUND( vertex[2][Y] ), r, g, b ) ;
	else
	{
		for ( int i = 0 ; i < 3 ; i++ )
			DrawingSurface:: Draw_Edge( ROUND( vertex[i][X] ), ROUND( vertex[i][Y] ), ROUND( vertex[(i+1)%3][X] ), ROUND( vertex[(i+1)%3][Y] ), r, g, b ) ;
	}
}

Vector2D Triangle2D:: Centroid() 
{
	return ( vertex[0] + vertex[1] + vertex[2] ) * Scalar( 1.0/3.0 ) ;
}

void Triangle2D:: operator *= ( const Matrix2D& matrix )
{
	for ( int i = 0 ; i < 3 ; i++ )
		vertex[i] = matrix * vertex[i] ;
}