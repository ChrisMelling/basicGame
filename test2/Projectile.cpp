#include "Projectile.h"
#include "Entity.h"
#include "Weapon.h"
#include "Math.h"
#include "Application.h"
#include "smokeParticle.h"

Projectile::Projectile(Entity* emitter, const sf::Vector2f& position, float angle,
        const sf::Texture& image, int speed, int damage) :
		Entity(emitter->_state, true, entityName::entityBullet, speed)
{
		Load(_state->getApp()->gettextureManager().Get("Content/ball.png"));
        GetSprite().setRotation(angle);

		SetPosition(position.x,position.y);
		GetSprite().setScale(0.6f,0.6);

		for (int i = 0; i < 5; i++)
		{
			_state->addEntity(new smokeParticle(_state,this));
		}
}


Projectile* Projectile::clone() const
{
        return new Projectile(*this);
}


void Projectile::Update(float frametime)
{
	if(timer.getElapsedTime().asSeconds() > 0.008)
	{
		_state->addEntity(new smokeParticle(_state,this));
		timer.restart();
	}


	if(GetPosition().x < 0) { alive = false; }
	if(GetPosition().y < 0) { alive = false; }

	if(GetPosition().x > _state->getApp()->GetWidth()) { alive = false; }
	if(GetPosition().y > _state->getApp()->GetHeight()) { alive = false; }

	double radian = math::to_rad(GetSprite().getRotation());

	sf::Vector2f direction = sf::Vector2f((float)cos(radian), (float)sin(radian));

	GetSprite().move(direction * speed * frametime);
}
