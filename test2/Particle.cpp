#include "Particle.h"
#define pi 3.14159265

Particle::Particle(float dirx, float diry,GameState *state) : Entity(state,false)
{
	name =  entityParticle;
	GetSprite().setScale( (float)random_number(0.4f, 0.7f), (float)random_number(0.4f, 0.7f) );
	collidable = false;
	double radians = atan2((float)diry,(float)dirx);
	double degrees = (radians/pi) * 180;

	GetSprite().setRotation((float)degrees);

	index = 255;
}

Particle::~Particle()
{ 

}

void Particle::Update(float frametime)
{
	timeAcc += frametime;

	if ( timeAcc > life_time_ )
	{
		index -= 1000 * frametime;
	}

	if(index < 20)
	{
		timeAcc = 0;
		alive = false;
	}

	GetSprite().setColor(sf::Color(_colour.r,_colour.g,_colour.b, static_cast<int>(index)));   

	GetSprite().move(direction * speed * frametime);
}


