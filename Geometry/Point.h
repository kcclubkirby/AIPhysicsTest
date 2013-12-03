#pragma once

#include "Shape.h"

class Point3D : public Shape
{
public:
	float x, y, z ;

public:
	Point3D( void ) ;
	Point3D( float x, float y, float z ) ;
   ~Point3D( void ) ;

	double Distance( const Point3D& ) const ;

	virtual void Translate( double Tx, double Ty, double Tz ) ;
	virtual void Render( const Appearance* ) const ;
};

#include "Appearance.h"

class Point2D
{
public:
	float x, y ;
	Color color ;

	Point2D() ;
	Point2D( double x, double y ) ;
	Point2D( double x, double y, Color color ) ;

	void Set_Position( double x, double y ) ;
	void Set_Color( byte red, byte green, byte blue ) ;
	void Translate( double Tx, double Ty ) ;
	void Render() const ;
	double Distance( const Point2D& pt ) const ;
	static Point2D Interpolate( Point2D& p0, Point2D& p1, double t ) ;
} ;
