#pragma once
#include "powerUp.h"

class triPowerUp :public powerUp
{
public:
	triPowerUp(GameState *state,float x, float y);
	virtual ~triPowerUp();
	virtual void onPickup(Entity* object);
protected:
};
