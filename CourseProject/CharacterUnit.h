/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*CharacterUnit.h										*
*This header file contains the CharacterUnit class, from*
*which the AIUnit and Player classes are derived. It	*
*also includes the AIUnit and Player class declarations.*
*The implementations of each are in the cpp file with	*
*the name of the corresponding class.					*
*-------------------------------------------------------*/

#ifndef CHARACTER_UNIT
#define CHARACTER_UNIT

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "FSM.h"
#include "Triangle3D.h"
#include "Movement.h"

class BlendedSteering;

class CharacterUnit //This class will be the parent class for all characters in the game
{
public:
	Triangle3D body; //Body for the character
	Appearance appearance; //Appearance for the color of the character
	Kinematic kinematic; //Holds the physics for the character
	SteeringOutput steering; //Holds the steering for the characters
	int windowSize; //size of the window

	CharacterUnit(){}; //Default constructor

	void Translate(Vector3D T); //Translates the triangle
	void Update(Scalar delta_t); //Updates all values for the character
	void Update(Scalar delta_t,CharacterUnit& character){}; //Reserved for AIUnit
	void Render(); //Renders the character on the screen
};

class AIUnit : public CharacterUnit //This is the version of the CharacterUnit controlled by AI
{
public:
	int steeringNum; //This number holds the value of the current steering behavior
	bool defeatPlayer; //Did the AI character defeat the player?
	bool dying; //Is the character going to die?
	bool spawnNewAI; //Spawn a new one?
	bool fast; //Is the AI going fast?
	bool wanderer; //Is the AI wandering?
	AI_FSM fsm; //The AI's State Machine

	AIUnit(){}; //Default constructor
	AIUnit(Vector3D pos, Scalar orient, Vector3D vel, Scalar rot, int size); //Specific constructor

	void Update(Scalar delta_t,CharacterUnit& character,BlendedSteering* blender); //Updates the values for the character
	void RndRender(); //Renders the character on the screen
};

class Player : public CharacterUnit //This is the version of the CharacterUnit controlled by the player
{
public:
	bool exists; //Tests whether the player exists
	bool dying; //Is the player going to die?
	bool invincible; //Is the player invincible?
	float invincCountdown; //The countdown for how long he stays invincible
	bool loseLife; //Tell the manager to decrease the life count
	bool faster; //Speed up the player
	float fastTimer; //The length for the fast state

	Player() //Default constructor
	{
		exists = false; //The player does not exist
	};
	Player(Vector3D pos, Scalar orient, Vector3D vel, Scalar rot, int size); //Specific constructor

	void Update(Scalar delta_t); //Updates the values for the character
	void Render(); //Renders the character on the screen
};

#endif