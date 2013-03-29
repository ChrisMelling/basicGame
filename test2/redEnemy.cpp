#include "redEnemy.h"
#include "redParticle.h"

#include "MainGame.h"
#include "Application.h"

redEnemy::redEnemy(float speed,float x, float y,GameState *state) : Enemy(speed, state)
{
	Load(state->getApp()->gettextureManager().Get("Content/redorb.png"));
	SetPosition(x,y);
	pointValue = 10;
}

redEnemy::~redEnemy()
{

}


void redEnemy::onDeath()
{
	for (int i = 0; i < 50; i++)
	{
		_state->addEntity(new redParticle(GetSprite().getPosition().x,GetSprite().getPosition().y,random_number(-1, 1),random_number(-1, 1),_state));
	}
}
