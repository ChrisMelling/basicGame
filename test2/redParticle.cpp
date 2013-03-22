
#include "redParticle.h"

#include "Application.h"

redParticle::redParticle(float x, float y, float dirx, float diry,GameState *state) : Particle(dirx,diry,state)
{	
	Load(state->getApp()->gettextureManager().Get("Content/particle.png"));

	_colour = sf::Color(178,34,34,180);

	SetPosition(x,y);

	life_time_ = random_number( 0.2f, 0.5f );

	direction = sf::Vector2f(dirx,diry);

	speed = 150.0f; // Speed of the Bullet
}

redParticle::~redParticle()
{
	
}
