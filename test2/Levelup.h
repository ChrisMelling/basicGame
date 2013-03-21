#pragma once
#include "Entity.h"

class Levelup :public Entity
{
public:
	Levelup(GameState *state,float x, float y);
	virtual ~Levelup();
	virtual void Update(float frametime);
	sf::Clock clock;
protected:
	int index;
};
