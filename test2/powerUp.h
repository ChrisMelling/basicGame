#pragma once
#include "Entity.h"

class powerUp :public Entity
{
public:
	powerUp(GameState *state,float x, float y);
	virtual ~powerUp();
	virtual void Update(float frametime);
	virtual void Touch(Entity *Other);
	virtual void onPickup(Entity* object);
protected:

private:
	float pickupTime;
	float timePassed;
	sf::Sound sound;
	sf::SoundBuffer buffer;
	sf::Sound pickupSound;
	sf::SoundBuffer pickupBuffer;
};
