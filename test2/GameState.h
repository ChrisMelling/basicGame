#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics.hpp>
#include "GameObjectManager.h"
class Application;
class Entity;

class GameState
{
	public:
	enum Statename
	{
		gameoverState,
		MainMenuState,
		MainGameState
	};

	GameState(Statename state, Application* app);
	~GameState();

	GameObjectManager						_props;
	GameObjectManager						_actors;

	virtual void							Init();
	virtual void							Update(float elapsedTime);
	virtual void							Render(sf::RenderWindow& renderWindow);
	virtual void							Enable();
	virtual void							Disable();

	int 									GetWindowWidth();
	int 									GetWindowHeight();
	void 									SetView( sf::View NewView );
	void 									SetViewOn( Entity* TargetActor );
	void 									SetDefaultView();
	const sf::View & 						GetDefaultView();
	void									addEntity(Entity* object);
	bool									getLoaded();
	void									toggleActive();
	bool									getActive();
	Statename								getStateName();
	Application*							getApp();
	protected:

	bool									active;
	bool									loaded;
	Statename								name;

	Application								*app;
};

#endif