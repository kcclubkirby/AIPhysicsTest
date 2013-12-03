#pragma once
#include "MathLib.h"
#include "Appearance.h"

struct RenderState
{
	Appearance appearance ;
	Matrix4D   matrix ;
	Vector3D   light ;

	RenderState(void);
	RenderState( const Appearance&, const Matrix4D&, const Vector3D& light ) ;
};
