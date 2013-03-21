#include "powerUp.h"

#include "Application.h"

powerUp::powerUp(GameState *state,float x, float y) : Entity(state)
{ 
	name =  entityPowerUp;
	GetSprite().setPosition(x,y);
	GetSprite().setScale(0.4f,0.4f);
	collidable = true;
}

powerUp::~powerUp()
{

}

void powerUp::Update(float frametime)
{
	timePassed += frametime;

	if(timePassed > 10)
	{
		alive = false;
	}
}

void powerUp::Touch(Entity *Other)
{
	if(Other->getEntityName() == entityPlayer)
	{
		onPickup(Other);
		alive = false;
	}
}

void powerUp::onPickup(Entity* object){}


