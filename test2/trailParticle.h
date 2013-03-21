#pragma once
#include "Particle.h"

class trailParticle :public Particle
{
public:
	trailParticle(sf::Color Colour,float x, float y, float dirx, float diry,GameState *state) ;
	virtual ~trailParticle();

protected:

};
