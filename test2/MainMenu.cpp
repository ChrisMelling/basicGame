#include "MainMenu.h"
#include "blueParticle.h"
#include "redParticle.h"
#include "Application.h"

MainMenu::MainMenu(Application *App) : GameState(MainMenuState, App)
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
	_sprite.setTexture(getApp()->gettextureManager().Get("Content/StartGame.png"));
	_xbox.setTexture(getApp()->gettextureManager().Get("Content/StartGame.png"));
	_mouse.setTexture(getApp()->gettextureManager().Get("Content/StartGame.png"));

	//_sprite.setPosition(500,300);
	//_xbox.setPosition(500,400);
	//_mouse.setPosition(500,500);

	loaded = true;
}




void MainMenu::Update(float elapsedTime)
{		
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{		
		//if(_sprite.getGlobalBounds().contains((float)getApp()->getMousePos().x,(float)getApp()->getMousePos().y))
		//{
		//	app->changeState(MainGameState);
		//}

		//if(_xbox.getGlobalBounds().contains((float)getApp()->getMousePos().x,(float)getApp()->getMousePos().y))
		//{
		//	app->setXbox();
		//	app->changeState(MainGameState);
		//}

		if(_mouse.getGlobalBounds().contains((float)getApp()->getMousePos().x,(float)getApp()->getMousePos().y))
		{
			app->setMouse();
			app->changeState(MainGameState);
		}
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{		
		app->ChangeResolution(1920,1080,64,true);
	}

	if(clock.getElapsedTime().asMilliseconds() > 200)
	{
		sf::Vector2f temp(random_number(40,getApp()->GetWidth() - 40),random_number(40,getApp()->GetHeight() - 40));
		sf::Vector2f temp2(random_number(40,getApp()->GetWidth() - 40),random_number(40,getApp()->GetHeight() - 40));

		for (int i = 0; i < 30; i++)
		{
			addEntity(new blueParticle(temp.x,temp.y,random_number(-1, 1),random_number(-1, 1),this));
			addEntity(new redParticle(temp2.x,temp2.y,random_number(-1, 1),random_number(-1, 1),this));
		}
		clock.restart();
	}

	_actors.updateAll(elapsedTime);
	_props.updateAll(elapsedTime);
}

void MainMenu::Render(sf::RenderWindow& renderWindow)
{
	_actors.drawAll(renderWindow);
	_props.drawAll(renderWindow);
	//renderWindow.draw(_sprite);
	//renderWindow.draw(_xbox);
	renderWindow.draw(_mouse);
}




float MainMenu::random_number(float low, float high)
{
    return low + ((float)((float)rand() / (float)RAND_MAX) * (float)((high) - (low)));
}
