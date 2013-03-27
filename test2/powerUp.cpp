#include "powerUp.h"

#include "Application.h"

powerUp::powerUp(GameState *state,float x, float y) : Entity(state, true)
{ 
	name =  entityPowerUp;
	GetSprite().setPosition(x,y);
	GetSprite().setScale(0.4f,0.4f);

	buffer.loadFromFile("Content/playershield.wav");

	sound.setBuffer(buffer);

	sound.setVolume(60.0f);
	sound.play();

	pickupBuffer.loadFromFile("Content/ingame_powerup.wav");

	pickupSound.setBuffer(pickupBuffer);

	pickupSound.setVolume(20.0f);
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
		pickupSound.play();
		onPickup(Other);
		alive = false;
	}
}

void powerUp::onPickup(Entity* object){}


