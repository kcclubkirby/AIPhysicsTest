/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*AIUnit.cpp												*
*This is the implementation of the AIUnit class.		*
*-------------------------------------------------------*/

#include "pch.h"
#include "BlendedSteering.h"
#include "CharacterUnit.h"

AIUnit::AIUnit(Vector3D pos, Scalar orient, Vector3D vel, Scalar rot, int size)	//This constructor will initialize the values where
																		//pos is a Vector for the triangle's position,
																		//orient is its orientation in radians
																		//vel is its initial velocity
																		//rot is its initial angular velocity
{
	body = Triangle3D(Vector3D(pos[X]+(20*cos(orient)),pos[Y]+(20*sin(orient)),0),
					  Vector3D(pos[X]+(20*cos(orient+2.5)),pos[Y]+(20*sin(orient+2.5)),0),
					  Vector3D(pos[X]+(20*cos(orient-2.5)),pos[Y]+(20*sin(orient-2.5)),0)); //Initializes a triangle using pos and orient
	
	kinematic = Kinematic(pos,orient,vel,rot); //Initializes the physics for the character

	appearance = Appearance(Color(1,0,0),true); //Starts the color as red

	steering = SteeringOutput(Vector3D(0,0,0),0.0); //Initializes the steering at zero

	steeringNum = 3; //Starts the steering with Blended Steering

	//Initialize the booleans
	defeatPlayer = false;
	dying = false;
	spawnNewAI = false;
	fast = false;
	wanderer = false;

	windowSize = size; //set the window size

	fsm = AI_FSM(); //Initialize the state machine
}

void AIUnit::Update(Scalar delta_t,CharacterUnit& character,BlendedSteering* blender)	//Updates the values for the character, with delta_t as
																						//the amount of time passed since the last update and
																						//character as the target for this character
{
	int stateAction = fsm.update(delta_t); //update the state machine
	if(stateAction == 1) //If the action from the state machine is 1
		dying = true; //Then the AI character should send a message that it needs to die
	if(stateAction == 2) //If the action from the state machine is 2
		spawnNewAI = true; //Then the AI character should send a message that a new character should spawn

	Vector3D currentPos = kinematic.position; //the current position of the character

	//Create the different steering behavior objects
	Arrive arrive(*this,character);
	BlendedSteering* blend = blender;
	LookWhereYoureGoing look(*this);

	//Check each key to see which behavior to use and update the steering
	if (wanderer)
		steering = blend->GetSteering();
	else
		steering = arrive.GetSteering();

	kinematic.rotation = look.GetSteering().rotation; //Make sure the character looks where he is moving
	kinematic.Update(steering,delta_t); //Update the physics based on the steering

	Vector3D posDifference = kinematic.position - currentPos; //find the difference between the current position and the next position
	Translate(posDifference); //Translate the triangle that difference
	if (fast)
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
	
	//If the character gets too close to the player, it kills the player
	if (abs((character.kinematic.position - kinematic.position).Length()) <= 40)
		defeatPlayer = true;
}

void AIUnit::RndRender() //Renders the character on the screen
{
	float red = rand()%10;
	float green = rand()%10;
	float blue = rand()%10;
	red /= 10.0;
	green /= 10.0;
	blue /= 10.0;
	Appearance app = Appearance(Color(red,green,blue),true);
	body.Render(&app);
}