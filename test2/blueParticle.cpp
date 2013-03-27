
#include "blueParticle.h"
#include "Application.h"

blueParticle::blueParticle(float x, float y, float dirx, float diry,GameState *state) : Particle(dirx,diry,state)
{	
	Load(state->getApp()->gettextureManager().Get("Content/particle.png"));

	_colour = sf::Color(70,130,180,180);

	SetPosition(x,y);

	life_time_ = random_number( 0.4f, 0.1f );

	direction = sf::Vector2f(dirx,diry);

	speed = rand() % 90 + 150;     // v2 in the range 1 to 100
}

blueParticle::~blueParticle()
{
	
}