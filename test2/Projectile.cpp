#include "Projectile.h"
#include "Entity.h"
#include "Weapon.h"
#include "Math.h"
#include "Application.h"

Projectile::Projectile(Entity* emitter, const sf::Vector2f& position, float angle,
        const sf::Texture& image, int speed, int damage) :
		Entity(emitter->_state, true, entityName::entityBullet, speed)
{
		Load(_state->getApp()->gettextureManager().Get("Content/ball.png"));
        GetSprite().setRotation(angle);

        m_speed.x = std::cos(angle) * speed;
        m_speed.y = -std::sin(angle) * speed;

		SetPosition(position.x,position.y);
		GetSprite().setScale(0.4f,0.4);
}


Projectile* Projectile::clone() const
{
        return new Projectile(*this);
}


void Projectile::Update(float frametime)
{
	if(GetPosition().x < 0) { alive = false; }
	if(GetPosition().y < 0) { alive = false; }

	if(GetPosition().x > _state->getApp()->GetWidth()) { alive = false; }
	if(GetPosition().y > _state->getApp()->GetHeight()) { alive = false; }

	double radian = math::to_rad(GetSprite().getRotation());

	sf::Vector2f direction = sf::Vector2f((float)cos(radian), (float)sin(radian));

	GetSprite().move(direction * speed * frametime);
}
