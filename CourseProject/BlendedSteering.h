/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/11/13											*
*BlendedSteering.h										*
*This file contains the class for Weighted Blending		*
*for the steering algorithms.							*
*-------------------------------------------------------*/

#ifndef BLENDED_STEER
#define BLENDED_STEER

#include "Movement.h"
#include "CharacterUnit.h"
#include "Behaviors.h"

struct BehaviorAndWeight //The struct to hold behavior weight and behaviors
{
	float weight;
	SteeringOutput behavior;
};

class BlendedSteering //The class to implement blended steering
{
public:
	BehaviorAndWeight behaviors[3]; //The different steering behaviors
	Scalar maxAcceleration, maxAngular;
	CharacterUnit character,target;

	BlendedSteering(){}; //Default constructor
	BlendedSteering(CharacterUnit& chara, CharacterUnit& tar,float& timer); //Specific constructor

	SteeringOutput GetSteering(); //Gets the steering for each behavior
};

#endif