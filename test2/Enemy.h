#pragma once
#include "Entity.h"


class Enemy :public Entity
{
public:
	Enemy(float speed,GameState *state);
	virtual ~Enemy();
	virtual void Update(float frametime);
	void setTarget(float x, float y);
	void seek(float frametime);
	virtual void onDeath();
	virtual void Touch(Entity *Other);

protected:
	int pointValue;
	sf::Clock clock2;
private:

};
