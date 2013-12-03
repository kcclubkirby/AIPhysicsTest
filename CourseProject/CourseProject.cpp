/*------------------------------------------------------*
*MODIFIED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/7/13											*
*CourseProject.cpp										*
*Defines the entry point for the windows application.	*
*I only added the different characters and changed the	*
*application title.										*
*-------------------------------------------------------*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include "MathLib.h"
#include "GraphicsLib.h"
#include "GeometryLib.h"
#include "GameFramework.h"
#include "CharacterUnit.h"
#include "EntityManager.h"

static const int pixels_per_meter = 100 ;
static const int num_systems = 10;
static const int num_particles = 12;
static const int life_time = 100;
static const int window_size = 768;
static const Scalar spread = .2f;

class MathGame : public GameFramework
{
private:
	Player player;
	AIUnit ai;
	EntityManager* manager;
	float timer, endTimer, pillTimer, dTimer, sTimer, diamTimer, spawnCount;
	int counter;
public:
	MathGame()
	{
		//Create the manager singleton by calling it
		manager->getInstance()->SetWindowSize(window_size); //set the window size
		manager->getInstance()->SetLives(3); //set the life count
		manager->getInstance()->Create(0,Vector3D(100,100,0),1); //Create player character
		manager->getInstance()->Create(2,Vector3D(300,300,0),0); //Create scatter pill
		manager->getInstance()->Create(3,Vector3D(100,150,0),0); //Create delete cube
		manager->getInstance()->Create(5,Vector3D(600,700,0),0); //Create speed diamond
		manager->getInstance()->Create(1,Vector3D(window_size-50,window_size-50,0),3); //Create an AI opponent
		timer = 0; //create the timer for adding AI opponents
		endTimer = 0; //create the timer for ending the game
		pillTimer = 0;
		dTimer = 0;
		sTimer = 0;
		diamTimer = 0;
		counter = 0; //count the number of AI opponents in the game
		spawnCount = 8;
		srand (time(NULL));
	}

	void Update_Model()
	{
		//increase the timers
		timer += elapsed_time;
		if (!manager->getInstance()->pill)
		{
			pillTimer += elapsed_time;
			if (pillTimer >= 20)
			{
				pillTimer = 0;

				Scalar x,y;
				x = rand()%(window_size+1);
				y = rand()%(window_size+1);

				manager->getInstance()->Create(2,Vector3D(x,y,0),0); //Create scatter pill
			}
		}
		if (!manager->getInstance()->dCube)
		{
			dTimer += elapsed_time;
			if (dTimer >= 10)
			{
				dTimer = 0;

				Scalar x,y;
				x = rand()%(window_size+1);
				y = rand()%(window_size+1);

				manager->getInstance()->Create(3,Vector3D(x,y,0),0); //Create delete cube
			}
		}
		if (!manager->getInstance()->sCube)
		{
			sTimer += elapsed_time;
			if (sTimer >= 30)
			{
				sTimer = 0;

				Scalar x,y;
				x = rand()%(window_size+1);
				y = rand()%(window_size+1);

				manager->getInstance()->Create(4,Vector3D(x,y,0),0); //Create super cube
			}
		}
		if (!manager->getInstance()->diam)
		{
			diamTimer += elapsed_time;
			if (diamTimer >= 30)
			{
				diamTimer = 0;

				Scalar x,y;
				x = rand()%(window_size+1);
				y = rand()%(window_size+1);

				manager->getInstance()->Create(5,Vector3D(x,y,0),0); //Create speed diamond
			}
		}


		if (timer >= spawnCount && counter < 8) //Every eight seconds, until we have three enemies, create another character
		{
			spawnCount -= 0.1;
			timer = 0;

			//Randomly generate the position

			Scalar x,y,orient;
			x = rand()%(window_size+1);
			y = rand()%(window_size+1);
			orient = rand()%(360+1);
			orient *= Math::PI/180;
			orient -= Math::PI;

			manager->getInstance()->Create(1,Vector3D(x,y,0),orient);
		}

		if (counter >= 10)
			manager->getInstance()->fastEnemies = true;
		else
			manager->getInstance()->fastEnemies = false;

		manager->getInstance()->Update(elapsed_time); //Update the game

		if(manager->getInstance()->numDeleted != 0)
		{
			counter -= manager->getInstance()->numDeleted;
			manager->getInstance()->numDeleted = 0;
		}

		if(manager->getInstance()->numCreated != 0)
		{
			counter += manager->getInstance()->numCreated;
			manager->getInstance()->numCreated = 0;
		}

		if (manager->getInstance()->Lives() < 0) //If you run out of lives, game over
			game_over = true;
	}

	void Render_Model()
	{
		manager->getInstance()->Render(); //Render the models
	}
} ;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd )
{
	MathGame game ;

	game.Open_Window( hInstance, "GSP 315 AI Course Project - SHAPE CHASE", 0, 0, window_size, window_size, 0, 0, 0 ) ;
	game.Run() ;
}