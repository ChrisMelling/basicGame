#pragma once
#include "Particle.h"

class blueParticle :public Particle
{
public:
	blueParticle(float x, float y, float dirx, float diry,GameState *state);
	virtual ~blueParticle();

protected:

};
