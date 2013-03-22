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
	_gameObjectManager.Add(new Player(this));

	fps = new FPS();

	texture.create(2000,2000);

	camera.setSize(getApp()->GetWidth(), getApp()->GetHeight());
	
	camera.zoom(0.8);

	healthBar.setPosition(0.05f * getApp()->GetWidth() + 300, 15);
	healthBar.setOutlineColor(sf::Color(18,0,211));
	healthBar.setFillColor(sf::Color(148,0,211));
	healthBar.setOutlineThickness(1);

	xpBar.setPosition(0.5f * getApp()->GetWidth() - 100, 15);
	xpBar.setFillColor(sf::Color(147,112,219));

	score = 0;
	time = 30;
	wave = 1;
	index = 0;
	roundWave = 300;
	killed = 0;



	for (int i = 0; i < 2000; i++)
	{		
		_gameObjectManager.Add(new wanderEnemy(20.0f + wave * 10, random_number(0, getApp()->GetWidth()),random_number(0, getApp()->GetHeight()),this));
	}

	//texture.display();
	//sf::RectangleShape rectangle;
	//rectangle.setSize(sf::Vector2f(20,20));
	//rectangle.setOutlineColor(sf::Color(255,255,255,20));
	//rectangle.setOutlineThickness(1);

	//for(int i = 0; i < getApp()->GetWidth() / 20; i++)
 //   {
	//	for(int j = 0; j < getApp()->GetHeight() / 20; j++)
 //       {  
	//		rectangle.setFillColor(sf::Color(0, 0, 0));		
 //           rectangle.setPosition(i * 20.0f, j * 20.0f);
	//		texture.draw(rectangle);
 //       }
 //   }
	//_sprite.setTexture(texture.getTexture());

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
		_gameObjectManager.Add(new redEnemy(50.0f + wave * 10,temp.x,temp.y,this));
		clock.restart();
	}

	if(powerupTimer.getElapsedTime().asSeconds() > 10)
	{
		// Generate a random number
		float rand = random_number(0,100);


			getGameObjectManager().Add(new triPowerUp(this,random_number(100, getApp()->GetWidth() - 100),random_number(100, getApp()->GetHeight()) - 100));

		std::cout << "powerup added!" << "\n";
		powerupTimer.restart();
	}

	std::stringstream p3;
	p3 << fps->GetFPS();
	sf::String temp3("FPS : ");
	timer.setString(temp3 + p3.str().c_str());
	timer.setCharacterSize(9);
	timer.setPosition(0, 0);
	timer.setCharacterSize(20);


	Player* _player = reinterpret_cast<Player*>(_gameObjectManager.Get(Entity::entityName::entityPlayer));

	if(_player->getHealth() <= 0)
	{
		app->changeState(GameState::Statename::gameoverState);
	}

	camera.setCenter(_player->GetPosition());

	healthBar.setSize(sf::Vector2f(roundWave,15));

	if(clock2.getElapsedTime().asSeconds() > 15)
	{
		nextWave();
		clock2.restart();
	}

	_gameObjectManager.updateAll(elapsedTime);

}


void MainGame::Render(sf::RenderWindow& renderWindow)
{
	getApp()->getWindow().setView(getApp()->getWindow().getDefaultView());
	renderWindow.draw(timer);

	getApp()->getWindow().setView(camera);
	_gameObjectManager.drawAll(renderWindow);
}

GameObjectManager& MainGame::getGameObjectManager()
{
	return _gameObjectManager;
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
	getGameObjectManager().getGroup(Entity::entityName::entityEnemy, tempArray);

	//Kill all currently alive enemy
	std::map<int, Entity*>::const_iterator itr = tempArray.begin();

	while(itr != tempArray.end())
	{
		itr->second->toggleDeath();
		itr++;
	}

	wave++;


	for (int i = 0; i < 2000 + wave * 20; i++)
	{		
		_gameObjectManager.Add(new wanderEnemy(20.0f + wave * 10.0f, random_number(0.0f, getApp()->GetWidth()),random_number(0.0f, getApp()->GetHeight()),this));
	}
}