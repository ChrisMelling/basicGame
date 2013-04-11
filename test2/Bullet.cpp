#include "Bullet.h"
#define pi 3.14159265

#include "Application.h"

Bullet::Bullet(float Speed, float x, float y, float rotation,GameState *state) : Entity(state, true, entityName::entityBullet, Speed)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/ball.png"));
	SetPosition(x,y);
	GetSprite().setRotation(rotation);
	GetSprite().setScale(0.4f,0.4);
}

Bullet::~Bullet()
{

}

void Bullet::Update(float frametime)
{
	if(GetPosition().x < 0) { alive = false; }
	if(GetPosition().y < 0) { alive = false; }

	if(GetPosition().x > _state->getApp()->GetWidth()) { alive = false; }
	if(GetPosition().y > _state->getApp()->GetHeight()) { alive = false; }


	double radian = GetSprite().getRotation() * (pi / 180);

	sf::Vector2f direction = sf::Vector2f((float)cos(radian), (float)sin(radian));

	GetSprite().move(direction * speed * frametime);
}

