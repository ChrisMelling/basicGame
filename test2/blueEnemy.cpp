#include "blueEnemy.h"
#include "blueParticle.h"
#include "MainGame.h"
#include "Application.h"


blueEnemy::blueEnemy(float speed, float x, float y,GameState *state) : Enemy(speed, state)
{
	Load(state->getApp()->gettextureManager().Get("Content/blueorb.png"));
	SetPosition(x,y);
	pointValue = 10;
}

blueEnemy::~blueEnemy()
{

}

//void blueEnemy::onDeath()
//{
//	for (int i = 0; i < 20; i++)
//	{
//		reinterpret_cast<MainGame*>(_state)->getGameObjectManager().Add(new blueParticle(GetSprite().getPosition().x,GetSprite().getPosition().y,random_number(-1, 1),random_number(-1, 1),_state));
//	}
//}
