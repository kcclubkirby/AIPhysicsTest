#pragma once
#include "pch.h"
#include "MathLib.h"
#include "GraphicsLib.h"
#include "GeometryLib.h"

// These are constants you can adjust to "play" with the simulation

// Cannon Description
const Scalar BARRELL_ANGLE = Scalar( Degrees_to_Radians( 50 ) ) ;
const Vector2D BARREL_DIRECTION = Vector2D( Math::cos( BARRELL_ANGLE ), Math::sin( BARRELL_ANGLE ) ) ;

// Cannonball Description
const Scalar CANNONBALL_MASS = 20 ;

// Firing Explosion
const Scalar INITIAL_SPEED  = 25 ;
const int PIXELS_PER_METER = 10 ;

const Scalar CANNON_FRICTION = Scalar( 0.1 ) ;
const Scalar CANNON_MASS = 200 ;
const Scalar CANNONBALL_RESTITUTION = Scalar( 0.95 ) ;
const Scalar EXPLOSION_FORCE_MAGNITUDE = 5.0e6 ; //strong explosion
const Scalar SHORT_DT = Scalar( 1e-4 ) ; // but for a short time 