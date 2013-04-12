#include "Math.h"
#include "Weapon.h"
#include "Entity.h"

#include "Application.h"
#include "GameState.h"
#include "GameObjectManager.h"

#include "Projectile.h"

#define ANGLE_VARIATION 6.0


Weapon::Weapon():
        m_fire_rate(0.6),
        m_fire_timer(0.f),
        m_velocity(360),
        m_damage(2),
        m_texture(NULL),
        m_inited(false),
        m_x(0),
        m_y(0),
        m_multiply(3),
		m_owner(NULL)
		
{
}

void Weapon::init(const char* weapon_id)
{
        m_inited = true;
}

bool Weapon::isInited() const
{
        return m_inited;
}

float Weapon::shoot(float angle)
{
        if (m_fire_timer <= 0.f)
        {
				sf::Vector2f offset = m_owner->GetSprite().getPosition();

                switch (m_multiply)
                {
                        case 1:
                                createProjectile(offset, angle);
                                break;
                        case 2:

								float rad;
								offset = m_owner->GetSprite().getPosition();

								rad = math::to_rad(m_owner->GetSprite().getRotation());

								offset.x += 3*sin(rad);
								offset.y += -3*cos(rad);

								createProjectile(offset,m_owner->GetSprite().getRotation());

								offset = m_owner->GetSprite().getPosition();

								offset.x += -3*sin(rad);
								offset.y += 3*cos(rad);

								createProjectile(offset,m_owner->GetSprite().getRotation());


                                break;
                        case 3:
                                createProjectile(offset, angle);
                                createProjectile(offset, angle - ANGLE_VARIATION);
                                createProjectile(offset, angle + ANGLE_VARIATION);
                                break;
                }

                m_fire_timer = m_fire_rate;
                return m_heat_cost;
        }
        return 0.f;
}


float Weapon::shoot(const sf::Vector2f& target)
{
		sf::Vector2f pos = m_owner->GetSprite().getPosition();
        pos.x += m_x;
        pos.y += m_y;
        return shoot(math::angle(target, pos));
}


void Weapon::onUpdate(float frametime)
{
        m_fire_timer -= frametime;
}


void Weapon::setTexture(const sf::Texture* texture)
{
        m_texture = texture;
}


void Weapon::setFireRate(float shot_per_sec)
{
        m_fire_rate = 1 / shot_per_sec;
}


void Weapon::setHeatCost(float heat_cost)
{
        m_heat_cost = heat_cost;
}


void Weapon::setDamage(int damage)
{
        m_damage = damage;
}


void Weapon::setVelociy(int velocity)
{
        m_velocity = velocity;
}

void Weapon::setSound(const sf::SoundBuffer* sound)
{
      
}

void Weapon::setPosition(const sf::Vector2f& pos)
{
        m_x = pos.x;
        m_y = pos.y;
}


void Weapon::setPosition(float x, float y)
{
        m_x = x;
        m_y = y;
}

void Weapon::setOwner(Entity* owner)
{
        m_owner = owner;
}

bool Weapon::isReady() const
{
        return m_fire_timer <= 0;
}

void Weapon::setMultiply(int n)
{
        m_multiply = n;
}

void Weapon::createProjectile(const sf::Vector2f& position, float angle)
{
		m_owner->_state->addEntity(new Projectile(m_owner, position, angle, *m_texture, m_velocity, m_damage));
}