
#include "trailParticle.h"

#include "Application.h"

trailParticle::trailParticle(sf::Color Colour,float x, float y, float dirx, float diry,GameState *state) : Particle(dirx,diry,state)
{	
	name =  entityParticle;
	Load(state->getApp()->gettextureManager().Get("Content/particle.png"));

	_colour = Colour;

	SetPosition(x,y);

	life_time_ = random_number( 0.06f, 0.09f );
	direction = sf::Vector2f(dirx,diry);

	speed = 140.0f; // Speed of the Bullet
}

trailParticle::~trailParticle()
{
	
}