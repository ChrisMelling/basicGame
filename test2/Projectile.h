
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.h"

/**
 * Bullet entity, emitted by Weapon class
 */
class Projectile: public Entity
{
public:
        /**
         * @param emitter: entity which fired the projectile
         * @param position: initial position
         * @param angle: trajectory angle (radians)
         * @param image: image du projectile
         * @param speed: vitesse du projectile (pixels / seconde)
         * @param damage: dégâts infligés lors d'une collision
         */
        Projectile(Entity* emitter, const sf::Vector2f& position, float angle,
                const sf::Texture& image, int speed, int damage);

        // override
        Projectile* clone() const;

        // override
        virtual void Update(float frametime);

        // override


        const Projectile* toProjectile() const { return this; }

private:
        sf::Vector2f m_speed;
		sf::Clock timer;
};

#endif // PROJECTILE_HPP