#pragma once
#include "Triangle3D.h"

class TriangleMesh3D : public Shape
{
private:
	static const int MAX_TRIANGLES = 20 ;
	Triangle3D triangles[MAX_TRIANGLES] ;
	int num_triangles ;

public:
	TriangleMesh3D(void);
   ~TriangleMesh3D(void);

	bool Add_Triangle( Triangle3D& ) ;

	virtual void Translate( double Tx, double Ty, double Tz ) ;
	virtual void Render( const Appearance* ) const ;

	void Render( const RenderState& ) const ;
	void Translate( Vector3D& T ) ;
	void operator *= ( Matrix3D& ) ;
};
