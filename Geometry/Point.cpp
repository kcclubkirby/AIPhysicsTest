#include <math.h>

#include "Point.h"
#include "GraphicsLib.h"

Point3D::Point3D( void )
{
	x = y = z = 0.0f ;
}

Point3D::Point3D( float x, float y, float z )
{
	this->x = x ;
	this->y = y ;
	this->z = z ;
}

Point3D::~Point3D(void)
{
}

double Point3D::Distance(const Point3D & other ) const
{
	double result = 0.0 ;

	double delta[3] ;
	delta[0] = x - other.x ;
	delta[1] = y - other.y ;
	delta[2] = z - other.z ;

	result = sqrt( delta[0]*delta[0] + delta[1]*delta[1] + delta[2]*delta[2] ) ;

	return result ;
}

void Point3D::Render( const Appearance* appearance ) const
{
	byte r, g, b ;
	appearance->Get_RGB( r, g, b ) ;
	DrawingSurface::Draw_Point( int( x + 0.5 ), int( y + 0.5 ), r, g, b ) ; // round coordinates to nearest integer
}

void Point3D::Translate(double Tx, double Ty, double Tz)
{
	x += float( Tx ) ;
	y += float( Ty ) ;
	z += float( Tz ) ;
}


		/***       POINT2D       ***/


Point2D:: Point2D()
{
	x = y = 0.0f ;
}

Point2D:: Point2D( double x, double y )
{
	this->x = (float)x ;
	this->y = (float)y ;
}

Point2D:: Point2D( double x, double y, Color color )
{
	this->x = float(x) ;
	this->y = float(y) ;
	color = color ;
}

void Point2D:: Set_Position( double x, double y )
{
	this->x = float(x) ;
	this->y = float(y) ;
}

void Point2D:: Set_Color( byte red, byte green, byte blue )
{
	color.r = red ;
	color.g = green ;
	color.b = blue ;
}

void Point2D:: Translate( double Tx, double Ty )
{
	x += float(Tx) ;
	y += float(Ty) ;
}

void Point2D:: Render() const
{
	DrawingSurface:: Draw_Point( ROUND(x), ROUND(y), byte( color.r * 255 ), byte( color.g * 255 ), byte( color.b * 255 ) ) ;
}


double Point2D:: Distance( const Point2D& pt ) const
{
	double delta_x = this->x - pt.x ;
	double delta_y = this->y - pt.y ;
	double distance = sqrt( delta_x * delta_x + delta_y * delta_y ) ;

	return distance ;
}

Point2D Point2D:: Interpolate( Point2D& p0, Point2D& p1, double t )
{
	Point2D result ;

	result.x = float( p0.x * ( 1.0 - t ) + p1.x * t ) ;
	result.y = float( p0.y * ( 1.0 - t ) + p1.y * t ) ;

	result.color.r = byte( p0.color.r * ( 1.0 - t ) + p1.color.r * t ) ;
	result.color.g = byte( p0.color.g * ( 1.0 - t ) + p1.color.g * t ) ;
	result.color.b = byte( p0.color.b * ( 1.0 - t ) + p1.color.b * t ) ;

	return result ;
}
