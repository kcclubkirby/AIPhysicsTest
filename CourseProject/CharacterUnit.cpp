/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*CharacterUnit.cpp										*
*This file contains the implementation for the			*
*CharacterUnit class, from which the AIUnit and Player	*
*classes are derived									*
*-------------------------------------------------------*/

#include "pch.h"
#include "CharacterUnit.h"

void CharacterUnit::Translate(Vector3D T) //Translates the triangle a distance of T from its current position
{
	body.Translate(Vector3D(T[X],T[Y],0));
}

void CharacterUnit::Update(Scalar delta_t) //Updates the values for the character
{
	Vector3D currentPos = kinematic.position; //the current position of the character
	kinematic.Update(steering,delta_t); //Update the physics based on the steering
	Vector3D posDifference = kinematic.position - currentPos; //find the difference between the current position and the next position
	Translate(posDifference); //Translate the triangle that difference
}

void CharacterUnit::Render() //Renders the character on the screen
{
	body.Render(&appearance);
}