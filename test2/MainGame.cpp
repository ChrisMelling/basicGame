#include "MainGame.h"
#include "Application.h"
#include "trailParticle.h"
#include "blueEnemy.h"
#include "redEnemy.h"
#include "wanderEnemy.h"
#include "triPowerup.h"
#include "powerupRapid.h"
#include "FPS.h"
#include "Player.h"
#include "Asteroid.h"
#include "Math.h"
#include "util.h"

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

	for (int i = 0; i < 100; i++)
	{		
		addEntity(new Asteroid(sf::Vector2f(math::random(0, GetWindowWidth()),math::random(0, GetWindowHeight())),Asteroid::BIG,this));
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

	//if(powerupTimer.getElapsedTime().asSeconds() > 10)
	//{
	//	// Generate a random number
	//	float rand = random_number(0,100);

	//	addEntity(new triPowerUp(this,random_number(100, GetWindowWidth() - 100),random_number(100, GetWindowHeight()) - 100));

	//	std::cout << "powerup added!" << "\n";
	//	powerupTimer.restart();
	//}


	fpsText.setString("Fps : " + util::toString(fps->GetFPS()));
	fpsText.setCharacterSize(12);
	fpsText.setPosition(0, 0);


	_propsText.setString("Actors : " + util::toString(_actors.getObjectCount()));
	_propsText.setCharacterSize(12);
	_propsText.setPosition(0, 14);


	_actorsText.setString("Props : " + util::toString(_props.getObjectCount()));
	_actorsText.setCharacterSize(12);
	_actorsText.setPosition(0, 28);


	_actors.updateAll(elapsedTime);
	_props.updateAll(elapsedTime);
}


void MainGame::Render(sf::RenderWindow& renderWindow)
{
	//SetView(camera);
	_props.drawAll(renderWindow);
	_actors.drawAll(renderWindow);

	SetDefaultView();
	renderWindow.draw(fpsText);
	renderWindow.draw(_propsText);
	renderWindow.draw(_actorsText);
}