#pragma once
#include "Entity.h"

class Bullet :public Entity
{
public:
	Bullet(float speed, float x, float y, float rotation,GameState *state);
	virtual ~Bullet();
	virtual void Update(float frametime);

protected:
	float speed;
	float timeAcc;
};
