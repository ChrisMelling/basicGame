#include "Asteroid.h"
#include "Math.h"
#include "Application.h"
#include "GameState.h"
#include "GameObjectManager.h"
#include "blueParticle.h"


#define BIG_SPLIT_INTO     2
#define MEDIUM_SPLIT_INTO  4

#define ROTATION_SPEED_MIN 40
#define ROTATION_SPEED_MAX 160


Asteroid::Asteroid(sf::Vector2f position, Size size,GameState *state, float angle) :
        Entity(state, true)
{
        rotation_speed_ = math::random(ROTATION_SPEED_MIN, ROTATION_SPEED_MAX);
        size_ = size;
        SetRandomImage();

		float BASE_SPEED;

		if(size == Size::BIG)
		{
			 BASE_SPEED = math::random(40,60);
		}
		if(size == Size::MEDIUM)
		{
			 BASE_SPEED = math::random(20,40);
		}

		if(size == Size::SMALL)
		{
			 BASE_SPEED = math::random(10,20);
		}

        angle = math::to_rad(math::random(0, 360));
        speed_.x = std::cos(angle) * BASE_SPEED;
        speed_.y = -std::sin(angle) * BASE_SPEED;

		const sf::IntRect& rect = GetSprite().getTextureRect();
        GetSprite().setOrigin(rect.width / 2, rect.height / 2);

		GetSprite().setPosition(position);
}



void Asteroid::Update(float frametime)
{
	sf::Vector2f direction;
	sf::Vector2f pos = GetSprite().getPosition();

	if(GetSprite().getPosition().x > _state->getApp()->GetWidth()) {speed_.x *= -1;}
	if(GetSprite().getPosition().y > _state->getApp()->GetHeight()) {speed_.y *= -1;}
	if(GetSprite().getPosition().y < 0) { speed_.y *= -1;}
	if(GetSprite().getPosition().x < 0) { speed_.x *= -1;}

	GetSprite().setRotation(rotation_speed_ * frametime);
	GetSprite().move(speed_ * frametime);
}

void Asteroid::Touch(Entity *Other)
{
	if(Other->getEntityName() == entityBullet)
	{
		toggleDeath(); 
		Other->alive = false;
	}
}

void Asteroid::onDeath()
{
        sf::Vector2f pos = GetSprite().getPosition();

        switch (size_)
        {
               case BIG:
                        for (int i = 0; i < BIG_SPLIT_INTO; ++i)
                        {
								_state->addEntity(new Asteroid(pos, MEDIUM,_state, math::random(0, 360)));
                        }
                        break;
                case MEDIUM:
                        for (int i = 0; i < MEDIUM_SPLIT_INTO; ++i)
                        {
                               _state->addEntity(new Asteroid(pos, SMALL,_state, math::random(0, 360)));
                        }
                        break;
        }

	for (int i = 0; i < 5; i++)
	{
		_state->addEntity(new blueParticle(GetSprite().getPosition().x,GetSprite().getPosition().y,random_number(-1, 1),random_number(-1, 1),_state));
	}
}


void Asteroid::SetRandomImage()
{
        int x = 0;
        switch (size_)
		{
                case SMALL:
						Load(_state->getApp()->gettextureManager().Get("Content/asteroid-small.png"));
                        x = math::random(0, 3) * 16;
                        GetSprite().setTextureRect(sf::IntRect(x, 0, 16, 16));
                        break;
                case MEDIUM:

						Load(_state->getApp()->gettextureManager().Get("Content/asteroid-medium.png"));
                        x = math::random(0, 2) * 32;
                         GetSprite().setTextureRect(sf::IntRect(x, 0, 32, 32));
                        break;
                case BIG:
						Load(_state->getApp()->gettextureManager().Get("Content/asteroid-big.png"));
                        x = math::random(0, 2) * 48;
                         GetSprite().setTextureRect(sf::IntRect(x, 0, 48, 48));
                        break;
        }
}