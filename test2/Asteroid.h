#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Entity.h"
#include "GameState.h"
#include "GameObjectManager.h"

/**
 * Asteroid object, can be split on smaller asteroids
 */
class Asteroid: public Entity
{
public:
        enum Size
        {
                SMALL, MEDIUM, BIG
        };

        /**
         * @param pos: initial position
         * @param size: size type
         * @param angle: movement direction
         */
        Asteroid(sf::Vector2f pos, Size size,GameState *state, float angle=180);

        // override
        virtual void Update(float frametime);
		virtual void Touch(Entity *Other);
        // override
		virtual void onDeath();

private:
        /**
         * Set a random image, according to the size
         */
        void SetRandomImage();

        Size size_;
        sf::Vector2f speed_;
        int rotation_speed_;
};

#endif // ASTEROID_HPP