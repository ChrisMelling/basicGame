#include "Enemy.h"

#include "Player.h"
#include "MainGame.h"
#include "triPowerup.h"
#include "powerupRapid.h"
#include "blueParticle.h"
#include "trailParticle.h"

#define pi 3.14159265

Enemy::Enemy(float Speed, GameState *state) : Entity(state, true,entityName::entityEnemy,Speed)
{ 
	name =  entityEnemy;
	speed = Speed;
	GetSprite().setScale(0.5f,0.5f);
	collidable = true;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float frametime)
{
	sf::Vector2f pos = _state->_actors.Get(entityPlayer)->GetPosition();

	setTarget(pos.x,pos.y);	
	

	seek(frametime);
}

void Enemy::Touch(Entity *Other)
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

void Enemy::setTarget(float x, float y)
{
	float radians = atan2(y - GetPosition().y,x - GetPosition().x);
	double degrees = (radians/pi) * 180;

	GetSprite().setRotation((float)degrees);	
}

void Enemy::seek(float frametime)
{
	double radian = GetSprite().getRotation() * (pi / 180);

	sf::Vector2f direction = sf::Vector2f((float)cos(radian), (float)sin(radian));

	GetSprite().move(direction * speed * frametime);
}

void Enemy::onDeath()
{
	for (int i = 0; i < 10; i++)
	{
		_state->addEntity(new blueParticle(GetSprite().getPosition().x,GetSprite().getPosition().y,random_number(-1, 1),random_number(-1, 1),_state));
	}
}
