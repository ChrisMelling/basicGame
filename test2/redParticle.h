#pragma once
#include "Particle.h"

class redParticle :public Particle
{
public:
	redParticle(float x, float y, float dirx, float diry,GameState *state);
	virtual ~redParticle();

protected:

};
