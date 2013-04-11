#pragma once

#include "forward.h"

class Entity
{
public:
	enum entityName
	{
		entityDetault,
		entityPowerUp,
		entityPlayer,
		entityBullet,
		entityEnemy,
		entityCursor,
		entityParticle,
	};

	Entity(GameState *state, bool collidable);
	Entity(GameState *state, bool collidable, entityName _name);
	Entity(GameState *state, bool collidable, entityName _name, float speed);
	Entity(GameState *state, entityName _name, float speed);
	Entity(GameState *state, float speed);

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
	int 									getWindowWidth();
	int 									getWindowHeight();
	entityName getEntityName();
	bool alive;
	GameState *_state;
protected:

	sf::Sprite  _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
	int ID;
	sf::Rect<float> r1;
	float speed;
	bool collidable;

	entityName name;
};

