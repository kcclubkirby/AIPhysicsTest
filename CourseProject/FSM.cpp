/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 4/5/13											*
*FSM.cpp												*
*This file includes the implementation for the Finite	*
*State Machine for the AI								*
*-------------------------------------------------------*/

#include "pch.h"
#include "FSM.h"

int AI_FSM::update(float time)
{
	if(time_elapsed == 0) //If no time has passed, enter the birth state
		currentState.entry();
	currentState.execute(); //Every time, execute the state
	time_elapsed += time; //increase the time in the current state
	if(time_elapsed >= currentState.length) //if that time exceeds the amount of time allowed
	{
		currentState.exit(); //exit the current state
		if(counter == listEnd) //If this is the final state, return 1
			return 1; 
		else //If this is the initial state
		{
			currentState = death; //move the state forward
			counter++; //increase the counter
			time_elapsed = 0; //reset the time
			return death.entry(); //execute the entry method for the state
		}
	}
	return 0;
}