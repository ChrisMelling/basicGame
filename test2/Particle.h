#pragma once

#include "Entity.h"

class Particle : public Entity
{
public:
	Particle(float dirx, float diry,GameState *state);
	virtual ~Particle();
	virtual void Update(float frametime);

protected:
	float life_time_;
	sf::Vector2f direction;
	float timeAcc;
	float index;
	sf::Color _colour;
};
