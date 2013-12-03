/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/13/13											*
*Behaviors.cpp											*
*This file contains the implementation for the different*
*steering behaviors.									*
*-------------------------------------------------------*/

#include "pch.h"
#include "Behaviors.h"

Seek::Seek(CharacterUnit& chara, CharacterUnit& tar) //Initialize the object
{
	character = chara;
	target = tar;
}

SteeringOutput Seek::GetSteering() //Steers the character towards its target at full speed
{
	SteeringOutput steering;

	steering.linear = target.kinematic.position - character.kinematic.position; //Find the direction to the target

	//Make the acceleration equal to the max
	steering.linear.Normalize();
	steering.linear *= steering.maxLinAcceleration;

	steering.angular = 0;
	return steering;
}

Flee::Flee(CharacterUnit& chara, CharacterUnit& tar) //Initialize the object
{
	character = chara;
	target = tar;
}

SteeringOutput Flee::GetSteering() //Steers the character away from its target at full speed
{
	SteeringOutput steering;

	steering.linear = target.kinematic.position - character.kinematic.position; //Find the direction to the target

	//Make the acceleration equal to the max and flip the vector to make it opposite
	steering.linear.Normalize();
	steering.linear *= -steering.maxLinAcceleration;

	steering.angular = 0;
	return steering;
}

Arrive::Arrive(CharacterUnit& chara, CharacterUnit& tar) //Initialize the object
{
	character = chara;
	target = tar;

	targetRadius = 10;
	slowRadius = 100;
	timeToTarget = 0.1;
}

SteeringOutput Arrive::GetSteering() //Steers the character towards its target at full speed, and slows when it reaches it
{
	SteeringOutput steering;
	Kinematic kin;

	Vector3D direction = target.kinematic.position - character.kinematic.position; //Find the direction to the target
	Scalar distance = direction.Length(); //Find the distance to the target
	Scalar targetSpeed;

	//If we are arrived, do not accelerate
	if(distance < targetRadius)
		return steering;
	//If we are not near the target, go the max speed
	if (distance > slowRadius)
		targetSpeed = kin.maxSpeed;
	//If we are near the target, slow down
	else
		targetSpeed = kin.maxSpeed * distance / slowRadius;

	//make the target velocity using the speed
	Vector3D targetVelocity = direction;
	targetVelocity.Normalize();
	targetVelocity *= targetSpeed;

	//create the acceleration using the velocities we have
	steering.linear = targetVelocity - character.kinematic.velocity;
	steering.linear /= timeToTarget;

	if (steering.linear.Length() > steering.maxLinAcceleration)
	{
		steering.linear.Normalize();
		steering.linear *= steering.maxLinAcceleration;
	}

	steering.angular = 0.0;
	return steering;
}

Wander::Wander(CharacterUnit& chara) //Initialize the object
{
	character = chara;

	wanderOffset = 0.5;
	wanderRadius = 100;
	wanderRate = 50;
	wanderOrientation = 0;
}

SteeringOutput Wander::GetSteering() //Steers the character in a semi-random direction
{
	SteeringOutput steering;

	wanderOrientation += randomBinomial() * wanderRate; //find the rate of wandering

	Scalar targetOrientation = wanderOrientation + character.kinematic.orientation;
	Vector3D targetDirection = Vector3D(cos(targetOrientation),sin(targetOrientation),0); //find the target direction

	target = character.kinematic.position + wanderOffset * character.kinematic.direction; 

	target += wanderRadius * targetDirection;

	Vector3D distance = target - character.kinematic.position;  //find the target distance
	distance.Normalize();

	steering.linear = steering.maxLinAcceleration * distance;
	
	return steering;
}

Scalar Wander::randomBinomial() //Returns a random binomial
{
	Scalar x;
	x = (rand()%101)-(rand()%101);
	x/100.0;
	return x;
}

CollisionAvoidance::CollisionAvoidance(CharacterUnit& chara, CharacterUnit& tar) //Initialize the object
{
	character = chara;
	target = tar;
}

SteeringOutput CollisionAvoidance::GetSteering() //Steers the character away from the target's projected collision with the character
{
	SteeringOutput steering;

	Scalar radius = 20;

	Vector3D relativePos = target.kinematic.position - character.kinematic.position; //find the relative position
	Scalar targetDirection = atan2(relativePos[Y],relativePos[X]);  //find the direction to the target
	Scalar direction = character.kinematic.orientation; //find the direction the character is facing
	Scalar relativeDirection = targetDirection - direction;  //find the relative direction from the direction the character faces to the target
	//if the direction is greater than pi, it should be switched to negative, and same with being less than negative pi.
	if (relativeDirection > Math::PI)
		relativeDirection -= 2 * Math::PI;
	else if (relativeDirection <= Math::PI)
		relativeDirection += 2 * Math::PI;

	Vector3D relativeVel = target.kinematic.velocity - character.kinematic.velocity;  //find the relative velocities
	Scalar relativeSpeed = relativeVel.Length();  //find the relative speed
	//if they are moving parallel and the same speed, or not moving, do not steer
	if (relativeSpeed == 0)
		return steering;
	
	Scalar timeToCollision = (abs(relativePos * relativeVel))/(relativeSpeed * relativeSpeed); //find the time until they collide

	Scalar distance = relativePos.Length(); //find the distance between them
	Scalar minSeparation = distance - relativeSpeed * timeToCollision;

	if (minSeparation > 2*radius)
		return steering;

	//If there is already a collision
	if (minSeparation <= 0 || distance < 2*radius)
		relativePos = target.kinematic.position - character.kinematic.position;
	//If there is going to be a collision
	else
		relativePos = relativePos + relativeVel * timeToCollision;

	//Turn the character away
	Scalar collisionDirection = atan2(character.kinematic.velocity[Y],character.kinematic.velocity[X]);
	if (relativeDirection > 0)
		collisionDirection -= Math::PI/2;
	else
		collisionDirection += Math::PI/2;
	
	relativePos = Vector3D(cos(collisionDirection),sin(collisionDirection),0);

	steering.linear = relativePos * character.steering.maxLinAcceleration;

	return steering;
}

LookWhereYoureGoing::LookWhereYoureGoing(CharacterUnit& chara) //Initialize the object
{
	character = chara;
}

Kinematic LookWhereYoureGoing::GetSteering() //Rotates the character to look where it's moving
{
	Kinematic kinematic;
	Scalar targetRadius = 0.1;
	Scalar slowRadius = 2;
	Scalar targetRotation;
	Scalar timeToTarget = 0.1;

	//If the character is not moving, don't do anything
	if (character.kinematic.velocity.Length() == 0)
		return kinematic;
	
	//Find where the velocity is facing
	Vector3D direction = character.kinematic.velocity.Normalized();
	Scalar orientation = atan2(direction[Y],direction[X]);
	
	//Make the character rotate to reach the desired orientation
	Scalar rotation = orientation - character.kinematic.orientation;
	
	//Fix the rotation so it is never greater than pi or less than -pi
	if (rotation > Math::PI)
	{
		rotation -= 2 * Math::PI;
	}
	else if (rotation < -Math::PI)
	{
		rotation += 2 * Math::PI;
	}
	Scalar rotationSize = abs(rotation);

	//If we are facing the right direction do nothing
	if (rotationSize < targetRadius)
		return kinematic;
	//If we are not close to the right direction, go the max speed
	if (rotationSize > slowRadius)
		targetRotation = character.kinematic.maxRotation;
	//If we are getting close to the right direction, slow down
	else
		targetRotation = character.kinematic.maxRotation *
						 rotationSize / slowRadius;

	targetRotation *= rotation / rotationSize;

	kinematic.rotation = targetRotation;
	kinematic.rotation /= timeToTarget;
	Scalar rotationSpeed = abs(kinematic.rotation);

	if (rotationSpeed > kinematic.maxRotation)
	{
		kinematic.rotation /= rotationSpeed;
		kinematic.rotation *= kinematic.maxRotation;
	}

	return kinematic;
}