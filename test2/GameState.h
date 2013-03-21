#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SFML/Graphics.hpp>

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

	virtual void Init();
	virtual void Update(float elapsedTime);
	virtual void Render(sf::RenderWindow& renderWindow);
	virtual void Enable();
	virtual void Disable();
	
	bool getLoaded();
	void toggleActive();
	bool getActive();
	Statename getStateName();
	Application* getApp();
	protected:

	bool active;
	bool loaded;
	Statename name;

	Application *app;
};

#endif