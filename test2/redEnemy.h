#pragma once

#include "Enemy.h"

class redEnemy : public Enemy
{
public:
	redEnemy(float speed,float x, float y,GameState *state);
	~redEnemy();

	virtual void onDeath();

protected:

private:

};