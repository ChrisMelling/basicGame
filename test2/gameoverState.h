#pragma once

#include "GameState.h"

class gameoverState : public GameState
{
public:
	gameoverState(Application *App);
	~gameoverState();
	void Init();
	void Update(float elapsedTime);
	void Render(sf::RenderWindow& renderWindow);
private:
	sf::Text gameover;
	sf::Text enemies;
	sf::Text waves;
	sf::Text total;
	int num;
	int test;
	sf::Clock clock;
};
