#include "wanderEnemy.h"

#include "Player.h"
#include "MainGame.h"
#include "powerUp.h"
#include "powerupRapid.h"
#include "blueParticle.h"
#include "Application.h"
#include "trailParticle.h"
#define pi 3.14159265

wanderEnemy::wanderEnemy(float Speed, float x, float y, GameState *state) : Entity(state, true, entityName::entityEnemy, Speed)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/blueorb.png"));

	pointValue = 5;
	GetSprite().setScale(0.5f,0.5f);
	GetSprite().setPosition(x,y);

	float radians = atan2((float)random_number(-1, 1),random_number(-1, 1));
	double degrees = (radians/pi) * 180;

	GetSprite().setRotation((float)degrees);

	double radian = degrees * (pi / 180);

	direction = sf::Vector2f((float)cos(radian), (float)sin(radian));

}

wanderEnemy::~wanderEnemy()
{

}

void wanderEnemy::Update(float frametime)
{
	if(GetSprite().getPosition().x > _state->getApp()->GetWidth()) {direction.x *= -1;}
	if(GetSprite().getPosition().y > _state->getApp()->GetHeight()) {direction.y *= -1;}
	if(GetSprite().getPosition().y < 0) { direction.y *= -1;}
	if(GetSprite().getPosition().x < 0) { direction.x *= -1;}

	if(clock2.getElapsedTime().asSeconds() > 1)
	{
		GetSprite().move(direction * speed * frametime);
	}
}

void wanderEnemy::Touch(Entity *Other)
{
	if(Other->getEntityName() == entityBullet)
	{
		toggleDeath(); 
		Other->alive = false;

		reinterpret_cast<MainGame*>(_state)->killed += 1;
	}

	if(Other->getEntityName() == entityPlayer)
	{
		toggleDeath(); 
		//reinterpret_cast<Player*>(Other)->removeHealth();
	}
}

void wanderEnemy::seek(float frametime)
{
	
}

void wanderEnemy::onDeath()
{
	for (int i = 0; i < 20; i++)
	{
		reinterpret_cast<MainGame*>(_state)->getGameObjectManager().Add(new blueParticle(GetSprite().getPosition().x,GetSprite().getPosition().y,random_number(-1, 1),random_number(-1, 1),_state));
	}
}
