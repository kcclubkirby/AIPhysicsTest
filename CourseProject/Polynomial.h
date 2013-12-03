#pragma once

#include "Appearance.h"
#include "../Geometry/Point.h"

class Polynomial
{
private:
	double coef[4] ;
	static double origin_x, origin_y ;

public:
	Polynomial(void);
	Polynomial( double A, double B, double C, double D ) ;

	double     Evaluate( double x ) ;
	Polynomial Derivative() ;
	Polynomial Integral() ;

	// draws the polynomial from 'start' to 'finish' with step size in x for 'delta_x'
	void Draw( double start, double finish, double delta_x, Color color ) ;

	// draws the axes and sets the origin of the axes in screen coordinates
	static void Draw_Axes( double origin_x, double origin_y ) ;
};

//Changed the name of Polygon, because GSP321 would think
//Polygon is a reference to an already-existing item
class GSPPolygon
{
private:
	static const int MAX_VERTICES = 5;
	int num_vertices;
	Point2D verts[MAX_VERTICES];
public:
	GSPPolygon(Point2D theVertices[], int count);
	double Area();
	void Draw();
};