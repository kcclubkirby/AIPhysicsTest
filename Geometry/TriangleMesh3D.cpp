
#include "TriangleMesh3D.h"


TriangleMesh3D:: TriangleMesh3D(void)
{
	num_triangles = 0 ;
}

TriangleMesh3D:: ~TriangleMesh3D(void)
{
}

bool TriangleMesh3D::Add_Triangle( Triangle3D& triangle )
{
	if ( num_triangles + 1 > MAX_TRIANGLES ) return false ;

	this->triangles[num_triangles++] = triangle ;

	return true ;
}

void TriangleMesh3D::Translate( double Tx, double Ty, double Tz )
{
	for ( int i = 0 ; i < num_triangles ; i++ )
		triangles[i].Translate( Tx, Ty, Tz ) ;
}

void TriangleMesh3D::Translate( Vector3D& T )
{
	for ( int i = 0 ; i < num_triangles ; i++ )
		triangles[i].Translate( T ) ;
}
void TriangleMesh3D:: operator *= ( Matrix3D& matrix )
{
	for ( int i = 0 ; i < num_triangles ; i++ )
		triangles[i] *= matrix ;
}

void TriangleMesh3D::Render( const Appearance* appearance ) const
{
	for ( int i = 0 ; i < num_triangles ; i++ )
		triangles[i].Render( appearance ) ;
}

void TriangleMesh3D::Render( const RenderState& render_state ) const
{
	for ( int i = 0 ; i < num_triangles ; i++ )
		triangles[i].Render( render_state ) ;
}