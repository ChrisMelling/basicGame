#pragma once
#include "Entity.h"

class Cursor :public Entity
{
public:
	Cursor(GameState *state);
	virtual ~Cursor();
	virtual void Update(float frametime);

protected:

	float XMove, YMove;
};
