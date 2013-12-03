#pragma once

#include "Shape.h"
#include "Point.h"

class Sphere : public Shape
{
protected:
	Point3D center ;
	float   radius ;

public:
	Sphere() ;
   ~Sphere() ;
    Sphere( Point3D& center, float radius ) ;

	void Set_Center( Point3D ) ;
	Point3D Center() ;
	float Radius() ;

	// implementation of the Shape interface
	virtual void Translate( double Tx, double Ty, double Tz ) ;
	virtual void Render( const Appearance* ) const ;
};

class Circle : public Sphere
{
	Appearance appearance ;

public:
	Circle() { radius = 0 ; } 

	Circle( Point2D center2D, float radius, Color color ) 
	{
		center = Point3D( center2D.x, center2D.y, 0 ) ;
		this->radius = radius ;
		appearance = Appearance( color, true ) ;
	}

	void Set_Center( double x, double y )
	{
		Sphere::Set_Center( Point3D( float(x), float(y), 0 ) ) ;
	}

	void Render() const
	{
		Sphere::Render( &appearance ) ;
	}

} ;
