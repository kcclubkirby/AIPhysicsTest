/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*Items.cpp												*
*This file contains the implementation for the			*
*different item classes									*
*-------------------------------------------------------*/

#include "pch.h"
#include "Items.h"

void Object::Update(CharacterUnit& character) //Checks if the character is collected
{
	Vector3D distance = character.kinematic.position - location.position;
	if(abs(distance.Length()) <= 30)
		dying = true;
}

ScatterPill::ScatterPill(Vector3D pos, int size) //Specific constructor
{
	windowSize = size; //set the window size

	//Keep the object inside the game
	Vector3D position = pos;
	if (position[X] < 20)
		position[X] = 20;
	if (position[X] > windowSize - 20)
		position[X] = windowSize - 20;
	if (position[Y] < 20)
		position[Y] = 20;
	if (position[Y] > windowSize - 20)
		position[Y] = windowSize - 20;

	body = Sphere(Point3D(position[X],position[Y],position[Z]),10); //Initialize the sphere using the position

	location = Location(position,0); //Initializes the physics for the character

	appearance = Appearance(Color(1,1,0),true); //Starts the color as yellow

	exists = true;
	dying = false;
}

void ScatterPill::Render() //Renders the character on the screen
{
	body.Render(&appearance); //Render the item
}

bool ScatterPill::Exists() //Tells if the object exists
{
	return exists;
}

DeleteCube::DeleteCube(Vector3D pos, int size) //Specific constructor
{
	windowSize = size; //set the window size

	//Keep the object inside the game
	Vector3D position = pos;
	if (position[X] < 20)
		position[X] = 20;
	if (position[X] > windowSize - 20)
		position[X] = windowSize - 20;
	if (position[Y] < 20)
		position[Y] = 20;
	if (position[Y] > windowSize - 20)
		position[Y] = windowSize - 20;

	body[0] = Triangle3D(Vector3D(position[X]+7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]-7.07,0)); //Initialize the triangle using the position
	body[1] = Triangle3D(Vector3D(position[X]+7.07,position[Y]-7.07,0),
						 Vector3D(position[X]+7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]-7.07,0)); //Initialize the triangle using the position

	location = Location(position,0); //Initializes the physics for the character

	appearance = Appearance(Color(0,0,1),true); //Starts the color as blue

	exists = true;
	dying = false;
}

void DeleteCube::Render() //Renders the character on the screen
{
	body[0].Render(&appearance); //Render the item
	body[1].Render(&appearance);
}

bool DeleteCube::Exists() //Tells if the object exists
{
	return exists;
}

SuperCube::SuperCube(Vector3D pos, int size) //Specific constructor
{
	windowSize = size; //set the window size

	//Keep the object inside the game
	Vector3D position = pos;
	if (position[X] < 20)
		position[X] = 20;
	if (position[X] > windowSize - 20)
		position[X] = windowSize - 20;
	if (position[Y] < 20)
		position[Y] = 20;
	if (position[Y] > windowSize - 20)
		position[Y] = windowSize - 20;

	body[0] = Triangle3D(Vector3D(position[X]+7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]-7.07,0)); //Initialize the triangle using the position
	body[1] = Triangle3D(Vector3D(position[X]+7.07,position[Y]-7.07,0),
						 Vector3D(position[X]+7.07,position[Y]+7.07,0),
						 Vector3D(position[X]-7.07,position[Y]-7.07,0)); //Initialize the triangle using the position

	location = Location(position,0); //Initializes the physics for the character

	appearance = Appearance(Color(1,0,1),true); //Starts the color as purple

	exists = true;
	dying = false;
}

void SuperCube::Render() //Renders the character on the screen
{
	body[0].Render(&appearance); //Render the item
	body[1].Render(&appearance);
}

bool SuperCube::Exists() //Tells if the object exists
{
	return exists;
}

SpeedDiamond::SpeedDiamond(Vector3D pos, int size) //Specific constructor
{
	windowSize = size; //set the window size

	//Keep the object inside the game
	Vector3D position = pos;
	if (position[X] < 20)
		position[X] = 20;
	if (position[X] > windowSize - 20)
		position[X] = windowSize - 20;
	if (position[Y] < 20)
		position[Y] = 20;
	if (position[Y] > windowSize - 20)
		position[Y] = windowSize - 20;

	body[0] = Triangle3D(Vector3D(position[X]+10,position[Y],0),
						 Vector3D(position[X],position[Y]+10,0),
						 Vector3D(position[X]-10,position[Y],0)); //Initialize the triangle using the position
	body[1] = Triangle3D(Vector3D(position[X],position[Y]-10,0),
						 Vector3D(position[X]+10,position[Y],0),
						 Vector3D(position[X]-10,position[Y],0)); //Initialize the triangle using the position

	location = Location(position,0); //Initializes the physics for the character

	appearance = Appearance(Color(1,0.6,0),true); //Starts the color as orange

	exists = true;
	dying = false;
}

void SpeedDiamond::Render() //Renders the character on the screen
{
	body[0].Render(&appearance); //Render the item
	body[1].Render(&appearance);
}

bool SpeedDiamond::Exists() //Tells if the object exists
{
	return exists;
}