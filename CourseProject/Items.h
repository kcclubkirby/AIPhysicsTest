/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 4/15/13											*
*Items.h												*
*This header file contains the Object class, from which	*
*the other item classes are derived. It also includes	*
*the other item class declarations. The implementations	*
*of each are in the Items.cpp file						*
*-------------------------------------------------------*/

#ifndef ITEM_OBJ
#define ITEM_OBJ

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Sphere.h"
#include "Triangle3D.h"
#include "Movement.h"
#include "CharacterUnit.h"

class Object //This class will be the parent class for all objects in the game
{
public:
	Appearance appearance; //Appearance for the color of the character
	Location location; //Holds the physics for the character
	int windowSize; //size of the window
	bool exists; //Tests whether the player exists
	bool dying; //Tests whether the player is dying

	Object(){}; //Default constructor

	void Update(CharacterUnit& character); //Checks if the character is collected
};

class ScatterPill : public Object
{
public:
	Sphere body; //Body for the item

	ScatterPill()
	{
		exists = false;
		dying = false;
	}
	ScatterPill(Vector3D pos, int size); //Specific constructor

	void Render(); //Renders the character on the screen
	bool Exists(); //Tells if the object exists
};

class DeleteCube : public Object
{
public:
	Triangle3D body[2]; //Body for the item

	DeleteCube()
	{
		exists = false;
		dying = false;
	}
	DeleteCube(Vector3D pos, int size); //Specific constructor

	void Render(); //Renders the character on the screen
	bool Exists(); //Tells if the object exists
};

class SuperCube : public Object
{
public:
	Triangle3D body[2]; //Body for the item

	SuperCube()
	{
		exists = false;
		dying = false;
	}
	SuperCube(Vector3D pos, int size); //Specific constructor

	void Render(); //Renders the character on the screen
	bool Exists(); //Tells if the object exists
};

class SpeedDiamond : public Object
{
public:
	Triangle3D body[2]; //Body for the item

	SpeedDiamond()
	{
		exists = false;
		dying = false;
	}
	SpeedDiamond(Vector3D pos, int size); //Specific constructor

	void Render(); //Renders the character on the screen
	bool Exists(); //Tells if the object exists
};

#endif