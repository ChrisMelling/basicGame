
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.h"


class Projectile: public Entity
{
public:

        Projectile(Entity* emitter, const sf::Vector2f& position, float angle,
                const sf::Texture& image, int speed, int damage);

        // override
        Projectile* clone() const;

        // override
        virtual void Update(float frametime);

        // override
		virtual void Touch(Entity *Other);

        const Projectile* toProjectile() const { return this; }

private:
        sf::Vector2f m_speed;
		sf::Clock timer;
};

#endif // PROJECTILE_HPP