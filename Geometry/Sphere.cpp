
#include "Sphere.h"
#include "GraphicsLib.h"

Sphere::Sphere(void)
{
	radius = 0.0f ;
}

Sphere::~Sphere(void)
{
}

Sphere:: Sphere( Point3D& center, float radius )
{
	this->center = center ;
	this->radius = radius ;
}

void Sphere:: Set_Center( Point3D center )
{
	this->center = center ;
}

Point3D Sphere:: Center()
{
	return center ;
}

float Sphere:: Radius()
{
	return radius ;
}


void Sphere:: Translate( double Tx, double Ty, double Tz )
{
	center.Translate( Tx, Ty, Tz ) ;
}

void Sphere::Render( const Appearance* appearance ) const
{
	byte r, g, b ;
	appearance->Get_RGB( r, g, b ) ;

	DrawingSurface::Draw_Circle( int( center.x+0.5f ), int( center.y+0.5f ), int( radius+0.5f ), appearance->solid, r, g, b ) ;
}