#include "Player.h"
#define pi 3.14159265
#include "blueParticle.h"
#include "Bullet.h"
#include "Levelup.h"
#include <iostream>
#include "Application.h"
#include "trailParticle.h"


Player::Player(GameState *state) 
	: Entity(state,true,entityName::entityPlayer, 200), score(0), health(100), xp(0), rank(0), bulletSpeed(600),triShot(false),rapidFire(false),_colour(sf::Color(128,255,86,255))
{ 
	Load(state->getApp()->gettextureManager().Get("Content/bubble.png"));

	SetPosition(getWindowWidth() / 2, getWindowHeight() / 2);

	GetSprite().setScale(0.5f,0.5f);
	GetSprite().setColor(_colour);

	controllerIndex = 0;

	index = 0;

    buffer.loadFromFile("Content/turretshot.wav");

	sound.setBuffer(buffer);

	sound.setVolume(20.0f);


    // init weapons
    m_weapon.setOwner(this);
    m_weapon.setPosition(GetPosition());

}

Player::~Player()
{

}

void Player::Update(float frametime)
{
	if(health > 0)
	{
		Controls(frametime);
		setTarget();
	}

	if(!triShot)
	{
		tri.restart();
	}
	if(!rapidFire)
	{
		rapid.restart();
	}

	if(triShot)
	{
		if(tri.getElapsedTime().asSeconds() > 10)
		{
			triShot = false;
		}
	}

	if(rapidFire)
	{
		if(rapid.getElapsedTime().asSeconds() > 10)
		{
			rapidFire = false;
		}
	}

	m_weapon.onUpdate(frametime);
}

void Player::Controls(float frametime)
{
	sf::Vector2f direction;

	MainGame * game = reinterpret_cast<MainGame*>(_state);

	game->camera.setCenter(GetSprite().getPosition());

	//////////////////////////////////////////////
	//				KEYBOARD UPDATE				//
	//////////////////////////////////////////////

	if(_state->getApp()->keyboardControl == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){direction.x -= 1.0f;}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){direction.x += 1.0f;}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){direction.y -= 1.0f;}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){direction.y += 1.0f;}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_weapon.shoot(GetSprite().getRotation());
			//Fire();
		}
	}

	//////////////////////////////////////////////
	//				CONTROLLER UPDATE			//
	//////////////////////////////////////////////

	if(_state->getApp()->xboxControl == true)
	{
		speed = 4.0f; // Speed of the Player

		if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::X))
		{
			direction.x= sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::X);
		}

		if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::Y))
		{
			direction.y = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::Y);
		}

		if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::Z) > 80)
		{
			 m_weapon.shoot(0);
		}
	}

	GetSprite().move(direction * speed * frametime);

	//if(GetSprite().getPosition().x > _state->getApp()->GetWidth()) { GetSprite().setPosition(0,GetSprite().getPosition().y);}
	//if(GetSprite().getPosition().y > _state->getApp()->GetHeight()) { GetSprite().setPosition(GetSprite().getPosition().x,0);}
	//if(GetSprite().getPosition().y < 0) { GetSprite().setPosition(GetSprite().getPosition().x,_state->getApp()->GetHeight()); }
	//if(GetSprite().getPosition().x < 0) { GetSprite().setPosition(_state->getApp()->GetWidth(),GetSprite().getPosition().y); }
}

void Player::Fire()
{
	if((triShot) && (rapidFire))
	{
		if(clock.getElapsedTime().asMilliseconds() > 100)
		{
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation() - 5,_state));
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation(),_state));
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation() + 5,_state));
			clock.restart();
		}
	}
	else if(triShot)
	{
		if(clock.getElapsedTime().asMilliseconds() > 150)
		{
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation() - 5,_state));
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation(),_state));
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation() + 5,_state));
			clock.restart();
		}
	}
	else if(rapidFire)
	{
		if(clock.getElapsedTime().asMilliseconds() > 100)
		{
			_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,GetSprite().getRotation(),_state));
			clock.restart();
		}
	}
	else
	{
		if(clock.getElapsedTime().asMilliseconds() > 300)
		{
			for(int i = 0; i < 60; i+=10)
			{
				_state->addEntity(new Bullet(bulletSpeed,GetPosition().x,GetPosition().y,i,_state));
			}
			sound.play();
			clock.restart();
		}
	}
}

void Player::Touch(Entity *Other)
{
	//if(Other->getEntityName() == Entity::entityName::entityEnemy)
	//{
	//	Other->toggleDeath(); 
	//	removeHealth();
	//}
}

void Player::rankUp()
{
	resetXP();
	rank += 1;
	bulletSpeed += 50;

	//speed += 30;
}

void Player::setTarget()
{
	float radians;

	sf::Vector2f mousePos = _state->getApp()->getWindow().convertCoords(sf::Mouse::getPosition(_state->getApp()->getWindow()));

	if(_state->getApp()->keyboardControl == true)
	{
		radians = atan2((float)mousePos.y - GetPosition().y,(float)mousePos.x - GetPosition().x);
	}


	if(_state->getApp()->xboxControl == true)
	{
		float x = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::R);
		float y = sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::U);
		radians = atan2((float)x,(float)y);
	}

	double degrees = (radians/pi) * 180;

	GetSprite().setRotation((float)degrees);	
}

void Player::addScore(int newScore)
{
	score += newScore;
}

int Player::getScore()
{
	return score;
}

int Player::getHealth()
{
	return health;
}

void Player::removeHealth()
{
	// if heatlth is already at 0, remove no more health
	if(health >= 0)
	{
		health -= 10;
	}

	// if health is less than 0, make it 0.
	if(health < 0)
	{
		health = 0;
	}
}

int Player::getXP()
{
	return xp;
}

void Player::resetXP()
{
	xp = 0;
}

void Player::addXP(int xpValue)
{
	xp += xpValue;
}

void Player::giveHealth(int newHealth)
{
	health += newHealth;
}

void Player::onDeath()
{


}

