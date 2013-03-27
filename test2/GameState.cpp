#include "GameState.h"
#include "Application.h"

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


void GameState::SetView( sf::View NewView )
{
	getApp()->getWindow().setView(NewView);
}

void GameState::SetViewOn( Entity* TargetActor )
{
	sf::Vector2f Center(TargetActor->GetPosition());
	sf::Vector2f Size( static_cast<float>( GetWindowWidth() ), static_cast<float>( GetWindowHeight() ));
	sf::View NewView( Center, Size );
	SetView( NewView );
}

void GameState::SetDefaultView()
{
	SetView( GetDefaultView() );
}

const sf::View& GameState::GetDefaultView()
{
	return getApp()->getWindow().getDefaultView();
}

Application* GameState::getApp()
{
	return app;
}

int GameState::GetWindowWidth()
{
	return getApp()->GetWidth();
}

int GameState::GetWindowHeight()
{
	return getApp()->GetHeight();
}