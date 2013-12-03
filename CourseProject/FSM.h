/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 4/2/13											*
*FSM.h													*
*This file includes the Finite State Machine for the AI	*
*-------------------------------------------------------*/

#ifndef STATE_MACHINE
#define STATE_MACHINE

class State //basic State class
{
public:
	float length;
	State(){};
	int entry(){return 0;};
	int execute(){return 0;};
	int exit(){return 0;};
};

class FiniteStateMachine //basic FSM class
{
public:
	State initialState;
	State currentState;

	float time_elapsed;
};

class AIBirthState : public State //the birth state for the FSM
{
public:
	AIBirthState()
	{
		length = 5; //the length of the state is 5 seconds
	}
	int entry()
	{
		return 0;
	}
	int execute()
	{
		return 0;
	}
	int exit()
	{
		return 0;
	}
};

class AIDeathState : public State //the death state for the FSM
{
public:
	AIDeathState()
	{
		length = 8; //the length of the state is 8 seconds
	}
	int entry()
	{
		return 2; //The entry state triggers an action
	}
	int execute()
	{
		return 0;
	}
	int exit()
	{
		return 0;
	}
};

class AI_FSM : public FiniteStateMachine //The FSM class for the AI
{
public:
	int counter,listEnd; //A counter for the state
	AIBirthState birth;
	AIDeathState death;
	AI_FSM()
	{
		counter = 0;
		listEnd = 1;

		//Start at the birth state
		initialState = birth; 
		currentState = birth;

		time_elapsed = 0;
	}
	int update(float time);
};

#endif