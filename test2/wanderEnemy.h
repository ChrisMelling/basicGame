#pragma once
#include "Entity.h"


class wanderEnemy :public Entity
{
public:
	wanderEnemy(float Speed, float x, float y, GameState *state);
	virtual ~wanderEnemy();
	virtual void Update(float frametime);
	void seek(float frametime);
	virtual void onDeath();
	virtual void Touch(Entity *Other);
protected:
	int pointValue;
	sf::Vector2f direction;
	sf::Clock clock2;
	sf::Music pickup;
private:

};
