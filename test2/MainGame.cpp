#include "MainGame.h"
#include <sstream>
#include "Application.h"
#include "trailParticle.h"
#include "blueEnemy.h"
#include "redEnemy.h"
#include "wanderEnemy.h"
#include "triPowerup.h"
#include"powerupRapid.h"
#include <iostream>


MainGame::MainGame(Application *App) : GameState(MainGameState, App)
{

}

MainGame::~MainGame()
{

}

void MainGame::Init()
{
	addEntity(new Player(this));
	fps = new FPS();

	camera.setSize(getApp()->GetWidth(), getApp()->GetHeight());
	camera.zoom(0.8);

	wave = 1;
	index = 0;

	for (int i = 0; i < 2000; i++)
	{		
		addEntity(new wanderEnemy(20.0f + wave * 10, random_number(0, getApp()->GetWidth()),random_number(0, getApp()->GetHeight()),this));
	}


	loaded = true;
}

void MainGame::Enable()
{
	clock.restart();
	clock2.restart();
	clock3.restart();
	powerupTimer.restart();
}


void MainGame::Update(float elapsedTime)
{		
	fps->Update();

	if(clock.getElapsedTime().asMilliseconds() > 300)
	{
		sf::Vector2f temp = getRandomPosition();
		addEntity(new redEnemy(50.0f + wave * 10,temp.x,temp.y,this));
		clock.restart();
	}

	if(powerupTimer.getElapsedTime().asSeconds() > 10)
	{
		// Generate a random number
		float rand = random_number(0,100);

		addEntity(new triPowerUp(this,random_number(100, getApp()->GetWidth() - 100),random_number(100, getApp()->GetHeight()) - 100));

		std::cout << "powerup added!" << "\n";
		powerupTimer.restart();
	}

	std::stringstream p1;
	p1 << fps->GetFPS();
	sf::String temp1("Fps : ");
	fpsText.setString(temp1 + p1.str().c_str());
	fpsText.setCharacterSize(12);
	fpsText.setPosition(0, 0);

	std::stringstream p2;
	p2 << _actors.getObjectCount();
	sf::String temp2("Actors : ");
	_propsText.setString(temp2 + p2.str().c_str());
	_propsText.setCharacterSize(12);
	_propsText.setPosition(0, 14);

	std::stringstream p3;
	p3 << _props.getObjectCount();
	sf::String temp3("Props : ");
	_actorsText.setString(temp3 + p3.str().c_str());
	_actorsText.setCharacterSize(12);
	_actorsText.setPosition(0, 28);



	if(clock2.getElapsedTime().asSeconds() > 15)
	{
		nextWave();
		clock2.restart();
	}

	_actors.updateAll(elapsedTime);
	_props.updateAll(elapsedTime);
}


void MainGame::Render(sf::RenderWindow& renderWindow)
{
	SetView(camera);
	_actors.drawAll(renderWindow);
	_props.drawAll(renderWindow);

	SetDefaultView();
	renderWindow.draw(fpsText);
	renderWindow.draw(_propsText);
	renderWindow.draw(_actorsText);
}

float MainGame::random_number(float low, float high)
{
    return low + ((float)((float)rand() / (float)RAND_MAX) * (float)((high) - (low)));
}

sf::Vector2f MainGame::getRandomPosition()
{

	if(index <= 3)
	{
		index++;
	}
	else
	{
		index = 0;
	}

	sf::Vector2f position;

	switch(index)
	{
	case 0:
		position.x = 0.0f;
		position.y = random_number(0, getApp()->GetHeight());
		break;
	case 1:
		position.x = 2000.0f;
		position.y = random_number(0, getApp()->GetHeight());
		break;
	case 2:
		position.x = random_number(0, getApp()->GetWidth());
		position.y = 0.0f;
		break;
	case 3:
		position.x = random_number(0, getApp()->GetWidth());
		position.y = getApp()->GetHeight();
		break;
	}

	return position;
}


int MainGame::getRandInt(int min, int max)
{
	return  rand()%(max-min)+min; 
}


void MainGame::nextWave()
{
	// Get an array containing all active Enemy in the game
	std::map<int, Entity*> tempArray;
	_actors.getGroup(Entity::entityName::entityEnemy, tempArray);

	//Kill all currently alive enemy
	std::map<int, Entity*>::const_iterator itr = tempArray.begin();

	while(itr != tempArray.end())
	{
		itr->second->alive = false;
		itr++;
	}

	wave++;


	for (int i = 0; i < 2000 + wave * 20; i++)
	{		
		addEntity(new wanderEnemy(20.0f + wave * 10.0f, random_number(0.0f, getApp()->GetWidth()),random_number(0.0f, getApp()->GetHeight()),this));
	}
}