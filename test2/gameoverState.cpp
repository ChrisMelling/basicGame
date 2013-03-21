#include "gameoverState.h"
#include "Application.h"
#include "MainGame.h"
#include <sstream>

gameoverState::gameoverState(Application *App) : GameState(Statename::gameoverState, App)
{

}

gameoverState::~gameoverState()
{

}

void gameoverState::Init()
{
	//MainGame* temp = reinterpret_cast<MainGame*>(getApp()->changeState(MainGameState));

	test = 0;

	//sf::String temp1("GAME OVER!");
	//gameover.setString(temp1);
	//gameover.setPosition(550, 100);
	//gameover.setCharacterSize(30);

	//sf::String temp2("Enemies killed: ");
	//std::stringstream p2;
	//p2<< temp->killed;
	//enemies.setString(temp2+ p2.str().c_str());
	//enemies.setPosition(400, 300);
	//enemies.setCharacterSize(20);

	//sf::String temp3("Waves Complete: ");
	//std::stringstream p3;
	//p3 << temp->wave;
	//waves.setString(temp3+ p3.str().c_str());
	//waves.setPosition(400, 350);
	//waves.setCharacterSize(20);

	//
	//sf::String temp4("Total Score: ");
	//total.setString(temp4);
	//total.setPosition(400, 400);
	//total.setCharacterSize(20);

	//num = temp->wave * 500 + temp->killed * 20;

	loaded = true;
}


void gameoverState::Update(float elapsedTime)
{	
	if(test < num)
	{
		if(clock.getElapsedTime().asMilliseconds() > 0.4)
		{
			test++;
			sf::String temp4("Total Score: ");
			std::stringstream p3;
			p3 << test;
			total.setString(temp4+ p3.str().c_str());
			clock.restart();
		}
	}
}

void gameoverState::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(gameover);
	renderWindow.draw(enemies);
	renderWindow.draw(waves);
	renderWindow.draw(total);
}



