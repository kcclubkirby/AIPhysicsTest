
#include "Triangle3D.h"
#include "DrawingSurface.h"


Triangle3D::Triangle3D(void)
{
}

Triangle3D:: Triangle3D( Vector3D& v1, Vector3D& v2, Vector3D& v3 )
{
	vertex[0] = v1 ;
	vertex[1] = v2 ;
	vertex[2] = v3 ;

	Compute_Normal() ;
}

Triangle3D::~Triangle3D(void)
{
}

void Triangle3D:: Compute_Normal()
{
	Vector3D e1 = vertex[1] - vertex[0] ;
	Vector3D e2 = vertex[2] - vertex[0] ;

	normal = e1.Cross_Product( e2 ) ;
	normal.Normalize() ;
}




void Triangle3D:: Translate( double Tx, double Ty, double Tz )
{
	Vector3D translation( Tx, Ty, Tz ) ;
	for ( int i = 0 ; i < 3 ; i++ )
		vertex[i] += translation ;
}

void Triangle3D:: Translate( Vector3D& T )
{
	for ( int i = 0 ; i < 3 ; i++ )
		vertex[i] += T ;
}

void Triangle3D:: operator *= ( const Matrix3D& matrix )
{
	for ( int i = 0 ; i < 3 ; i++ )
		vertex[i] *= matrix ;
}

void Triangle3D:: Render( const Appearance* appearance ) const
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

void Triangle3D:: Render( const RenderState& render_state ) const
{
	byte r, g, b ;
	Vector4D vertex[3] ;
	Vector4D normal ;
	Vector4D light ;

	for ( int i = 0 ; i < 3 ; i++ )
		vertex[i] = render_state.matrix * Vector4D( this->vertex[i], Scalar( 1.0 ) ) ;

	normal = render_state.matrix * Vector4D( this->normal, Scalar( 0.0 ) ) ;
	light  = Vector4D( render_state.light, Scalar( 0.0 ) ) ;

	if ( render_state.appearance.solid )
	{
				// backface culling
		if ( normal[Z] < 0.0 ) return ;

		// illumination
		Scalar intensity = normal * light ;
		if ( intensity > 0.0 )
		{
			Color color = render_state.appearance.color ;
			r = byte( intensity * color.r * 255 ) ;
			g = byte( intensity * color.g * 255 ) ;
			b = byte( intensity * color.b * 255 ) ;
		}
		else
		{
			r = g = b = 0 ;
		}

		DrawingSurface:: Draw_Triangle( ROUND( vertex[0][X] ), ROUND( vertex[0][Y] ), ROUND( vertex[1][X] ), ROUND( vertex[1][Y] ), ROUND( vertex[2][X] ), ROUND( vertex[2][Y] ), r, g, b ) ;
	}
	else
	{
		render_state.appearance.Get_RGB( r, g, b ) ;
		for ( int i = 0 ; i < 3 ; i++ )
			DrawingSurface:: Draw_Edge( ROUND( vertex[i][X] ), ROUND( vertex[i][Y] ), ROUND( vertex[(i+1)%3][X] ), ROUND( vertex[(i+1)%3][Y] ), r, g, b ) ;
	}
}