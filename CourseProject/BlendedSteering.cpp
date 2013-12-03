/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/11/13											*
*BlendedSteering.cpp									*
*This file contains the implementation for the Weighted	*
*Blending class											*
*-------------------------------------------------------*/

#include "pch.h"
#include "BlendedSteering.h"

BlendedSteering::BlendedSteering(CharacterUnit& chara, CharacterUnit& tar, float& timer) //Initializes the weights and characters
{
	behaviors[0].weight = (50 - timer)/100.0;
	behaviors[1].weight = timer/50.0;
	behaviors[2].weight = timer/50.0;

	character = chara;
	target = tar;
}

SteeringOutput BlendedSteering::GetSteering() //Gets the steering for each behavior
{
	SteeringOutput steering;

	Arrive arrive(character, target);
	Wander wander(character);
	CollisionAvoidance collisionAvoidance(character, target);

	//Gets the steering for each behavior
	behaviors[0].behavior = arrive.GetSteering();
	behaviors[1].behavior = wander.GetSteering();
	behaviors[2].behavior = collisionAvoidance.GetSteering();

	//Applies the weights to each behavior and adds them all into one combined behavior
	steering = behaviors[0].behavior * behaviors[0].weight;
	steering += behaviors[1].behavior * behaviors[1].weight;
	steering += behaviors[2].behavior * behaviors[2].weight;

	return steering;
}