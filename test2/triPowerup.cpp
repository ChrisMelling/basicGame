#include "triPowerup.h"

#include "Application.h"

triPowerUp::triPowerUp(GameState *state,float x, float y) : powerUp(state,x,y)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/zombie.png"));
}

triPowerUp::~triPowerUp()
{

}

void triPowerUp::onPickup(Entity* object)
{
	//reinterpret_cast<Player*>(object)->triShot = true;
}

