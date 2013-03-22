#include "GameState.h"

GameState::GameState(Statename newName, Application *App)
	: name(newName),app(App), active(false), loaded(false)
{ 
                         
}

GameState::~GameState()
{

}

void GameState::Init()
{

}

void GameState::Update(float elapsedTime)
{

}

void GameState::Render(sf::RenderWindow& renderWindow)
{

}

void GameState::Enable()
{

}

void GameState::Disable()
{

}

void GameState::toggleActive()
{
	active = !active;
}

bool GameState::getActive()
{
	return active;
}

GameState::Statename GameState::getStateName()
{
	return name;
}

bool GameState::getLoaded()
{
	return loaded;
}

Application* GameState::getApp()
{
	return app;
}