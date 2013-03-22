#include "powerupRapid.h"

#include "Application.h"

powerupRapid::powerupRapid(GameState *state,float x, float y) : powerUp(state,x,y)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/blueorb.png"));
}

powerupRapid::~powerupRapid()
{

}

void powerupRapid::onPickup(Entity* object)
{
	reinterpret_cast<Player*>(object)->rapidFire = true;
}

