/*------------------------------------------------------*
*CREATED BY:											*
*Name: David Tiscareno									*
*Class: GSP315											*
*Course Project											*
*Date: 3/27/13											*
*EntityManager.h										*
*This header file contains the classes for managing	the	*
*entities which exist in the game.						*
*-------------------------------------------------------*/

#include <ctime>
#include "BlendedSteering.h"
#include "Items.h"

#define MAX_ENTITIES 100

class EntityManager //Entity manager class creates and manages all entities
					//It also sends and recieves messages from entities
{
protected:
	EntityManager()
	{
		playerExist = false; //The player starts out not existing
		playerNum = -1;
		pillNum = -1;
		deleteNum = -1;
		superNum = -1;
		speedNum = -1;
		deleteCount = 0;
		lives = 0;
		fastEnemies = false;
		wanderer = false;
		pill = false;
		dCube = false;
		sCube = false;
		diam = false;
		blend = BlendedSteering();
	};
private:
	static EntityManager* _instance; //The singleton instance

	AIUnit entity[MAX_ENTITIES-1]; //Holds the AI units
	Player player; //Holds the player unit

	//Create the items
	ScatterPill scatterPill;
	DeleteCube deleteCube;
	SuperCube superCube;
	SpeedDiamond speedDiamond;
	BlendedSteering blend;

	bool playerExist; //shows if the player exists
	int types[MAX_ENTITIES]; //holds the types for each entity
	int idNums; //holds the number of entities
	int playerNum, pillNum, deleteNum, superNum, speedNum; //holds the entity number for the different units
	int windowSize; //holds the data for the window size
	int lives; //holds the number of lives the player has
	int deleteCount; //holds the number of enemies which should be deleted
	float steerTimer; //holds the timer for the blended steering
public:
	int numCreated,numDeleted; //holds the number of entities created or deleted
	bool fastEnemies; //checks if the AI characters are going fast
	bool wanderer; //checks if the AI should wander
	bool pill,dCube,sCube,diam; //checks if one of the items exists

	EntityManager* getInstance(); //this is how you access the singleton
	~EntityManager();

	int Lives(); //Returns the number of lives
	void SetWindowSize(int size); //Sets the window size
	void SetLives(int life); //Sets the number of lives
	void Create(int type, Vector3D pos, Scalar orient); //Creates an entity
	void Delete(int idNum); //Deletes an entity
	void Update(Scalar delta_t); //Updates all entities
	void Render(); //Renders all entities
};

EntityManager* EntityManager::_instance =  NULL; //The instance starts as NULL

EntityManager* EntityManager::getInstance() //this is how you access the singleton
{
	if (_instance == NULL) //If it doesn't exist, create it
	{
		_instance = new EntityManager;
		//initialize variables
		_instance->idNums = 0;
		_instance->numCreated = 0;
		_instance->numDeleted = 0;
	}
	return _instance; //return the singleton instance
}

int EntityManager::Lives() //Returns the number of lives
{
	return lives;
}

void EntityManager::SetWindowSize(int size) //Sets the window size
{
	windowSize = size;
}

void EntityManager::SetLives(int life) //Sets the number of lives
{
	lives = life;
}

void EntityManager::Create(int type, Vector3D pos, Scalar orient) //Creates an entity
{
	if (_instance->idNums >= MAX_ENTITIES) //If we reach the max number of entities, do not create any
		return;
	if (type == 0) //If the entity will be the player
	{
		_instance->player = Player(pos, orient, Vector3D::Zero_Vector(), 0, windowSize);
		_instance->playerExist = true;
		if (_instance->playerNum == -1)
		{
			_instance->playerNum = _instance->idNums;
			_instance->types[_instance->idNums] = type; //Save its type
			_instance->idNums++; //Increase the number of entities
		}
	}
	else if (type == 1) //If the entity will be an AI
	{
		deleteCount = 0;
		_instance->entity[_instance->idNums] = AIUnit(pos, orient, Vector3D::Zero_Vector(), 0, windowSize);
		_instance->numCreated++; //Increase the total number of entities created
		_instance->types[_instance->idNums] = type; //Save its type
		_instance->idNums++; //Increase the number of entities
	}
	else if (type == 2) //If the entity will be a scatter pill
	{
		_instance->scatterPill = ScatterPill(pos, windowSize);
		if (_instance->pillNum == -1)
		{
			_instance->pillNum = _instance->idNums;
			_instance->types[_instance->idNums] = type; //Save its type
			_instance->idNums++; //Increase the number of entities
		}
		pill = true;
	}
	else if (type == 3) //If the entity will be a delete cube
	{
		_instance->deleteCube = DeleteCube(pos, windowSize);
		if (_instance->deleteNum == -1)
		{
			_instance->deleteNum = _instance->idNums;
			_instance->types[_instance->idNums] = type; //Save its type
			_instance->idNums++; //Increase the number of entities
		}
		dCube = true;
	}
	else if (type == 4) //If the entity will be a super cube
	{
		_instance->superCube = SuperCube(pos, windowSize);
		if (_instance->superNum == -1)
		{
			_instance->superNum = _instance->idNums;
			_instance->types[_instance->idNums] = type; //Save its type
			_instance->idNums++; //Increase the number of entities
		}
		sCube = true;
	}
	else if (type == 5) //If the entity will be a speed diamond
	{
		_instance->speedDiamond = SpeedDiamond(pos, windowSize);
		if (_instance->speedNum == -1)
		{
			_instance->speedNum = _instance->idNums;
			_instance->types[_instance->idNums] = type; //Save its type
			_instance->idNums++; //Increase the number of entities
		}
		diam = true;
	}
	else
		return;
}

void EntityManager::Delete(int idNum) //Deletes an entity
{
	if (_instance->idNums <= 1) //If there is only one (or less) entities left
	{
		_instance->idNums = 0; //Set the number of entities to zero
		return;
	}
	else if (_instance->playerNum == idNum) //If we are deleting the player
	{
		_instance->player = Player(); //Just replace it with an empty player
		_instance->playerExist = false;
	}
	else if (_instance->pillNum == idNum)
	{
		_instance->scatterPill = ScatterPill();
		pill = false;
	}
	else if (_instance->deleteNum == idNum)
	{
		_instance->deleteCube = DeleteCube();
		dCube = false;
	}
	else if (_instance->superNum == idNum)
	{
		_instance->superCube = SuperCube();
		sCube = false;
	}
	else if (_instance->speedNum == idNum)
	{
		_instance->speedDiamond = SpeedDiamond();
		diam = false;
	}
	else
	{
		for (int i = idNum; i < _instance->idNums-1; i++) //move all of the entities to fill the gap
			_instance->entity[i] = _instance->entity[i+1];

		//Move the other item id numbers
		if (_instance->pillNum > idNum)
			_instance->pillNum--;
		if (_instance->deleteNum > idNum)
			_instance->deleteNum--;
		if (_instance->superNum > idNum)
			_instance->superNum--;
		if (_instance->speedNum > idNum)
			_instance->speedNum--;

		_instance->idNums--; //decrease the number of entities
		_instance->numDeleted++; //increase the total number of entities deleted
	}
	return;
}

void EntityManager::Update(Scalar delta_t) //Updates all entities
{
	if (_instance->idNums == 0) //If there are no entities, do nothing
		return;
	for (int i = 0; i < _instance->idNums; i++) //For each entity
	{
		if (i == _instance->playerNum && _instance->playerExist) //If it is the player, update the player
		{
			_instance->player.Update(delta_t);
			if (_instance->player.loseLife)
			{
				lives--;
				_instance->player.loseLife = false;
			}
		}
		else if (i == _instance->pillNum && _instance->scatterPill.Exists()) //If it is a scatter pill, update the item
		{
			_instance->scatterPill.Update(_instance->player);
			if (_instance->scatterPill.dying)
			{
				_instance->scatterPill.dying = false;
				_instance->Delete(i);
				steerTimer = 50.0;
				wanderer = true;
				pill = false;
			}
		}
		else if (i == _instance->deleteNum && _instance->deleteCube.Exists()) //If it is a delete cube, update the item
		{
			_instance->deleteCube.Update(_instance->player);
			if (_instance->deleteCube.dying)
			{
				_instance->deleteCube.dying = false;
				_instance->Delete(i);
				_instance->deleteCount = 2;
				dCube = false;
			}
		}
		else if (i == _instance->superNum && _instance->superCube.Exists()) //If it is a super cube, update the item
		{
			_instance->superCube.Update(_instance->player);
			if (_instance->superCube.dying)
			{
				_instance->superCube.dying = false;
				_instance->Delete(i);
				_instance->deleteCount = 5;
				sCube = false;
			}
		}
		else if (i == _instance->speedNum && _instance->speedDiamond.Exists()) //If it is a speed diamond, update the item
		{
			_instance->speedDiamond.Update(_instance->player);
			if (_instance->speedDiamond.dying)
			{
				_instance->speedDiamond.dying = false;
				_instance->Delete(i);
				_instance->player.fastTimer = 15.0;
				_instance->player.faster = true;
				diam = false;
			}
		}
		else if (_instance->types[i] == 1) //If it is the AI, update the AI and perform checks
		{
			if (deleteCount == 0)
			{
				if (steerTimer != 0)
				{
					blend = BlendedSteering(_instance->entity[i],_instance->player,steerTimer);
					steerTimer -= delta_t;
					if (steerTimer <= 0)
					{
						steerTimer = 0;
						wanderer = false;
					}
				}
				if (_instance->fastEnemies)
					_instance->entity[i].fast = true;
				else
					_instance->entity[i].fast = false;
				if (_instance->wanderer)
					_instance->entity[i].wanderer = true;
				else
					_instance->entity[i].wanderer = false;

				_instance->entity[i].Update(delta_t,_instance->player,&blend);

				//Send message
				if (_instance->entity[i].defeatPlayer) 
				{
					_instance->entity[i].defeatPlayer = false;
					_instance->player.dying = true;
				}
				//If the entity should die, delete it
				if (_instance->entity[i].dying)
				{
					_instance->entity[i].dying = false;
					_instance->Delete(i);
				}
				//If a new entity should spawn, create one
				if (_instance->entity[i].spawnNewAI)
				{
					_instance->entity[i].spawnNewAI = false;

					Scalar x,y,orient;
					x = rand()%(windowSize+1);
					y = rand()%(windowSize+1);
					orient = rand()%(360+1);
					orient *= Math::PI/180;
					orient -= Math::PI;

					_instance->Create(1,Vector3D(x,y,0),orient);
				}
			}
			else
			{
				_instance->Delete(i);
				deleteCount--;
			}
		}
	}
}

void EntityManager::Render() //Renders all entities
{
	if (_instance->idNums == 0) //If there are no entities, do nothing
		return;
	for (int i = 0; i < _instance->idNums; i++) //For each entity, render it
	{
		if (i == _instance->playerNum && _instance->playerExist)
			_instance->player.Render();
		else if (i == _instance->pillNum && _instance->scatterPill.Exists())
			_instance->scatterPill.Render();
		else if (i == _instance->deleteNum && _instance->deleteCube.Exists())
			_instance->deleteCube.Render();
		else if (i == _instance->superNum && _instance->superCube.Exists())
			_instance->superCube.Render();
		else if (i == _instance->speedNum && _instance->speedDiamond.Exists())
			_instance->speedDiamond.Render();
		else
		{
			if(_instance->fastEnemies)
				_instance->entity[i].RndRender();
			else
				_instance->entity[i].Render();
		}
	}
	for(int i = 0; i < lives; i++)
		DrawingSurface::Draw_Circle(10+20*i,10,5,true,0,255,0);
}