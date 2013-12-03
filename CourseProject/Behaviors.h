/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/11/13											*
*Behaviors.h											*
*This file contains the classes for the different		*
*steering behaviors.									*
*-------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Movement.h"
#include "CharacterUnit.h"

class Seek //Causes the character to seek its target
{
public:
	CharacterUnit character,target;

	Seek(CharacterUnit& chara, CharacterUnit& tar); //Initialize the object
	SteeringOutput GetSteering(); //Steers the character towards its target at full speed
};

class Flee //Causes the character to flee from its target
{
public:
	CharacterUnit character,target;

	Flee(CharacterUnit& chara, CharacterUnit& tar); //Initialize the object
	SteeringOutput GetSteering(); //Steers the character away from its target at full speed
};

class Arrive //Causes the character to arrive at its target
{
public:
	CharacterUnit character,target;
	Scalar targetRadius,slowRadius,timeToTarget;

	Arrive(CharacterUnit& chara, CharacterUnit& tar); //Initialize the object
	SteeringOutput GetSteering(); //Steers the character towards its target at full speed, and slows when it reaches it
};

class Wander //Causes the character to wander
{
public:
	CharacterUnit character;
	Vector3D target;
	Scalar wanderOffset, wanderRadius, wanderRate, wanderOrientation;

	Wander(CharacterUnit& chara); //Initialize the object
	SteeringOutput GetSteering(); //Steers the character in a semi-random direction
	Scalar randomBinomial(); //Returns a random binomial
};

class CollisionAvoidance //Causes the character to avoid colliding with its target
{
public:
	CharacterUnit character,target;

	CollisionAvoidance(CharacterUnit& chara, CharacterUnit& tar); //Initialize the object
	SteeringOutput GetSteering(); //Steers the character away from the target's projected collision with the character
};

class LookWhereYoureGoing //Causes the character to look where it's moving
{
public:
	CharacterUnit character;

	LookWhereYoureGoing(CharacterUnit& chara); //Initialize the object
	Kinematic GetSteering(); //Rotates the character to look where it's moving
};