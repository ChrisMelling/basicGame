#pragma once
#include "powerUp.h"

class powerupRapid :public powerUp
{
public:
	powerupRapid(GameState *state,float x, float y);
	virtual ~powerupRapid();
	virtual void onPickup(Entity* object);
protected:
};
