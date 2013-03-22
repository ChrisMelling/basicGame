#include "StateManager.h"
#include "MainGame.h"

StateManager::StateManager()
{
	index = 0;
	currentState = NULL;
}


StateManager::~StateManager()
{

}

void StateManager::Init()
{
	
}

// Returns the current active state.
GameState* StateManager::getState()
{
	return currentState;
}

// The method for adding a new state into the manager.
void StateManager::newGameState(GameState *screen)
{		
	screen->Init();

	gameStates.insert(std::pair<int,GameState*>(index,screen));
	index++;
}

void StateManager::removeState(GameState::Statename name)
{
	for (auto itr = gameStates.begin(); itr != gameStates.end(); itr++)
	{
		if(itr->second->getStateName() == name)
		{
			// Delete the pointer
			delete itr->second;
			
			// Delete from array
			gameStates.erase(itr);
		}
	}
}

void StateManager::changeState(GameState::Statename name)
{
	for (auto itr = gameStates.begin(); itr != gameStates.end(); itr++)
	{
		// Search through the array, checking if the state name equals the parameter "name"
		if(itr->second->getStateName() == name)
		{
			// If found, the state is made the currentState.
			currentState = itr->second;
			currentState->Enable();

			// If the states content has not been loaded, load it.
			if(!currentState->getLoaded())
			{
				currentState->Init();
			}
		}
	}
}

void StateManager::Active(sf::RenderWindow& renderWindow, float elapsedTime)
{
	currentState->Update(elapsedTime);
	currentState->Render(renderWindow);		
}



