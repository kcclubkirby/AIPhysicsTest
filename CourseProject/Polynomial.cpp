#include "pch.h"
#include "Polynomial.h"
#include "DrawingSurface.h"
#include "../Geometry/Point.h"


double Polynomial:: origin_x = 0, Polynomial:: origin_y = 0 ;

void Polynomial::Draw_Axes( double origin_x, double origin_y )
{
	Polynomial::origin_x = origin_x ;
	Polynomial::origin_y = origin_y ;

	DrawingSurface::Draw_Edge( 0, ROUND( origin_y ),  500, ROUND( origin_y ), 0, 0, 0 ) ;
	DrawingSurface::Draw_Edge( ROUND( origin_x ), 0, ROUND( origin_x ), 500, 0, 0, 0 ) ;
}

Polynomial::Polynomial()
{
	coef [0] = 0;
	coef [1] = 0;
	coef [2] = 0;
	coef [3] = 0;
}

Polynomial::Polynomial(double A, double B, double C, double D)
{
	coef [0] = A;
	coef [1] = B;
	coef [2] = C;
	coef [3] = D;
}

double Polynomial::Evaluate( double x )
{
	return (coef[0]*x*x*x+
			coef[1]*x*x+
			coef[2]*x+
			coef[3]);
}

void Polynomial::Draw( double start, double finish, double delta_x, Color color )
{
	double x1,x2,y1,y2;
	double xScale = 20;
	for (x1 = start; x1 < finish; x1 += delta_x)
	{
		x2 = x1 + delta_x;
		y1 = Evaluate(x1);
		y2 = Evaluate(x2);
		DrawingSurface:: Draw_Edge( xScale*x1+origin_x,
									y1+origin_y,
									xScale*x2+origin_x,
									y2+origin_y,
									color.r, color.g, color.b ) ;
	}
}

Polynomial Polynomial::Derivative()
{
	return Polynomial(0,coef[0]*3,coef[1]*2,coef[2]);
}

Polynomial Polynomial::Integral()
{
	return Polynomial(coef[1]/3,coef[2]/2,coef[3],0);
}

//This is the constructor for the GSPPolygon class, found in Polynomial.h
GSPPolygon::GSPPolygon(Point2D theVertices[], int count)
{
	//If the number of vertices being brought in are greater than the max
	//we will limit them. Otherwise, the number being brought in will be
	//the number of vertices.
	if (count > MAX_VERTICES)
		num_vertices = MAX_VERTICES;
	else
		num_vertices = count;

	//Initialize vertices
	for (int i = 0; i < num_vertices; i++)
		verts[i] = theVertices[i];
}

//This method will draw the polygon
void GSPPolygon::Draw()
{
	//Start with the egde from the last vertex to the first
	DrawingSurface::Draw_Edge(verts[num_vertices-1].x,
							  verts[num_vertices-1].y,
							  verts[0].x,
							  verts[0].y,
							  0,0,0);
	//For each vertex, draw an edge to the next vertex
	for(int i = 0; (i+1) < num_vertices; i++)
		DrawingSurface::Draw_Edge(verts[i].x,
								  verts[i].y,
								  verts[i+1].x,
								  verts[i+1].y,
								  0,0,0);
}

//This method will find the area, using the trapezoid rule
double GSPPolygon::Area()
{
	double area = 0;

	//Start by finding the area of the trapezoid from the last vertex to the first
	area += (verts[0].x - verts[num_vertices-1].x) *
			((verts[0].y + verts[num_vertices-1].y)/2);

	//For each set of two connected vertices, find the area of the resulting trapezoid
	for (int i = 0; (i+1) < num_vertices; i++)
		area += (verts[i+1].x - verts[i].x) *
			((verts[i].y + verts[i+1].y)/2);

	//If the area is negative, switch it to positive
	if (area < 0)
		area = 0 - area;

	return area;
}