#include "pch.h"
#include "RenderState.h"

RenderState:: RenderState(void)
{
}

RenderState:: RenderState( const Appearance& appearance, const Matrix4D& matrix, const Vector3D& light )
{
	this->appearance = appearance ;
	this->matrix     = matrix ;
	this->light      = light ;
	this->light.Normalize() ;
}
