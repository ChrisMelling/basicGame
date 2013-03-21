#ifndef StateManager_H_	
#define StateManager_H_

#include "GameState.h"

class StateManager
{
private:
	int index;
	GameState* currentState;
	std::map<int, GameState*> gameStates;

public:
	StateManager(); 
	~StateManager(); 

	void Init();
	void Update();
	void newGameState(GameState *screen);

	void Active(sf::RenderWindow& renderWindow, float elapsedTime);
	void changeState(GameState::Statename name);
	void removeState(GameState::Statename name);
	GameState* getState();

};

#endif