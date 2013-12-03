#pragma once

#include "Shape.h"
#include "Matrix3D.h"
#include "RenderState.h"

class Triangle3D : public Shape
{
public:
	Vector3D vertex[3] ;
	Vector3D normal ;

protected:
	void Compute_Normal() ;

public:
	Triangle3D() ;
	Triangle3D( Vector3D& v1, Vector3D& v2, Vector3D& v3 ) ;
   ~Triangle3D() ;

	// implementation of the Shape interface
	virtual void Translate( double Tx, double Ty, double Tz ) ;
	virtual void Render( const Appearance* ) const ;

	void Render( const RenderState& ) const ;
	void Translate( Vector3D& T ) ;
	void operator *= ( const Matrix3D& ) ;
} ;
