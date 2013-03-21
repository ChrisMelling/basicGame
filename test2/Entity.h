#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class GameState;

class Entity
{
public:
	Entity(GameState *state);
	virtual ~Entity();
	
	void Load(std::string filename);
	void Load(sf::Texture &texture);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float frametime);
	bool isCollidable();

	void SetPosition(float x, float y);
	sf::Vector2f GetPosition() const;
	float GetWidth() const;
	float GetHeight() const;

	bool IsLoaded() const;
	sf::Rect<float> GetBoundingRect() const;
	sf::Sprite& GetSprite();
	void setID(int id);
	int getID();
	float random_number(float low, float high);
	virtual void Touch(Entity *Other);
	virtual void onDeath();
	void toggleDeath();
	
	enum entityName
	{
		entityPowerUp,
		entityPlayer,
		entityBullet,
		entityEnemy,
		entityCursor,
		entityParticle,
	};

	bool collidable;

	entityName getEntityName();
	entityName name;
	bool alive;
	GameState *_state;
	float speed;

private:
	sf::Sprite  _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
	int ID;
	sf::Rect<float> r1;
};

