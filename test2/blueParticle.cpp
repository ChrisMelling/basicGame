
#include "blueParticle.h"
#include "Application.h"

blueParticle::blueParticle(float x, float y, float dirx, float diry,GameState *state) : Particle(dirx,diry,state)
{	
	Load(state->getApp()->gettextureManager().Get("Content/particle.png"));

	_colour = sf::Color(139,137,137,180);

	SetPosition(x,y);

	life_time_ = random_number( 0.08f, 0.3f );

	direction = sf::Vector2f(dirx,diry);

	speed = rand() % 40 + 90;     // v2 in the range 1 to 100
}

blueParticle::~blueParticle()
{
	
}