/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*Player.cpp												*
*This is the implementation of the Player class.		*
*-------------------------------------------------------*/

#include "pch.h"
#include "CharacterUnit.h"

Player::Player(Vector3D pos, Scalar orient, Vector3D vel, Scalar rot, int size)	//This constructor will initialize the values where
																		//pos is a Vector for the triangle's position,
																		//orient is its orientation in radians
																		//vel is its initial velocity
																		//rot is its initial angular velocity
{
	exists = true;
	body = Triangle3D(Vector3D(pos[X]+(20*cos(orient)),pos[Y]+(20*sin(orient)),0),
					  Vector3D(pos[X]+(20*cos(orient+2.5)),pos[Y]+(20*sin(orient+2.5)),0),
					  Vector3D(pos[X]+(20*cos(orient-2.5)),pos[Y]+(20*sin(orient-2.5)),0)); //Initializes a triangle using pos and orient

	kinematic = Kinematic(pos,orient,vel,rot); //Initializes the physics for the character

	appearance = Appearance(Color(0,1,0),true); //Starts the color as green

	steering = SteeringOutput(Vector3D::Zero_Vector(),0.0); //Initializes the steering at zero

	dying = false; //Initialize the booleans
	invincible = false;
	loseLife = false;
	faster = false;

	invincCountdown = 0;
	fastTimer = 0;

	windowSize = size; //set the window size
}

void Player::Update(Scalar delta_t)	//Updates the values for the character, with delta_t as
									//the amount of time passed since the last update
{
	if (fastTimer != 0)
	{
		fastTimer -= delta_t;
		if (fastTimer <= 0)
		{
			fastTimer = 0;
			faster = false;
		}
	}
	if (!exists) //if the player doesn't exist, don't do anything
		return;

	if (invincible) //If the player is invincible
	{
		invincCountdown += delta_t; //Increse the countdown
		if (invincCountdown >= 5.0) //If it reaches 5 seconds
		{
			invincible = false; //It is no longer invincible
			invincCountdown = 0; //Reset the countdown
			appearance = Appearance(Color(0,1,0),true); //change the triangle to be solid
		}
	}

	if (dying) //If the player is supposed to die, just move it somewhere else
	{
		if (!invincible)
		{
			Scalar x,y;
			x = rand()%(windowSize+1);
			y = rand()%(windowSize+1);

			Vector3D currentPos = kinematic.position; //the current position of the character
			kinematic.position[X] = x;
			kinematic.position[Y] = y;

			invincible = true;
			loseLife = true;
			appearance = Appearance(Color(0,1,0),false); //change the triangle to be see-through
		}

		dying = false;
	}

	//Create the different key states
	short left = GetKeyState(VK_LEFT);
	short right = GetKeyState(VK_RIGHT);
	short up = GetKeyState(VK_UP);
	short down = GetKeyState(VK_DOWN);

	bool moving_forward = false;

	//Check each key to see which is being pressed
	if (left < 0)
	{
		if (steering.angular < 0)
		{
			kinematic.rotation = 0;
			steering.angular = 0;
		}
		steering.angular += 3; //Rotate left
		if (faster)
			steering.angular += 3;
	}
	if (right < 0)
	{
		if (steering.angular > 0)
		{
			kinematic.rotation = 0;
			steering.angular = 0;
		}
		steering.angular -= 3; //Rotate right
		if (faster)
			steering.angular -= 3;
	}
	if (right >=0 && left >=0)
	{
		//Stop rotating
		steering.angular = 0;
		kinematic.rotation = 0;
	}

	if (up < 0)
	{
		moving_forward = true;
		//Move forward
		steering.linear = kinematic.direction * steering.maxLinAcceleration;
		kinematic.velocity = kinematic.velocity.Length() * kinematic.direction;
	}
	if (down < 0)
	{
		//If we aren't moving forward...
		if (!moving_forward)
		{
			//..Move backward
			steering.linear = kinematic.direction * -steering.maxLinAcceleration;
			kinematic.velocity = -kinematic.velocity.Length() * kinematic.direction;
		}
	}
	if (up >=0 && down >=0)
	{
		//Stop moving
		steering.linear = Vector3D::Zero_Vector();
		kinematic.velocity = Vector3D::Zero_Vector();
	}

	Vector3D currentPos = kinematic.position; //the current position of the character
	kinematic.Update(steering,delta_t); //Update the physics based on the steering

	Vector3D posDifference = kinematic.position - currentPos; //find the difference between the current position and the next position
	Translate(posDifference); //Translate the triangle that difference
	if (faster)
	{
		Translate(posDifference*0.75);
		kinematic.position += posDifference*0.75;
	}
	
	//Keep the character inside the game
	if (kinematic.position[X] < 20)
		kinematic.position[X] = 20;
	if (kinematic.position[X] > windowSize - 20)
		kinematic.position[X] = windowSize - 20;
	if (kinematic.position[Y] < 20)
		kinematic.position[Y] = 20;
	if (kinematic.position[Y] > windowSize - 20)
		kinematic.position[Y] = windowSize - 20;

	body = Triangle3D(Vector3D(kinematic.position[X]+(20*cos(kinematic.orientation)),
							   kinematic.position[Y]+(20*sin(kinematic.orientation)),0),
					  Vector3D(kinematic.position[X]+(20*cos(kinematic.orientation+2.5)),
							   kinematic.position[Y]+(20*sin(kinematic.orientation+2.5)),0),
					  Vector3D(kinematic.position[X]+(20*cos(kinematic.orientation-2.5)),
							   kinematic.position[Y]+(20*sin(kinematic.orientation-2.5)),0)); //Update the triangle to render
}

void Player::Render() //Renders the character on the screen
{
	if (!exists)
		return;
	body.Render(&appearance);
}