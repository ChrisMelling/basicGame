
#include "Entity.h"
#include "GameState.h"
#include "Application.h"

Entity::Entity(GameState *state, bool collidable) 
	:_isLoaded(false), _state(state), alive(true), collidable(collidable), name(entityName::entityDetault) {}

Entity::Entity(GameState *state, bool collidable, entityName _name)
	:_isLoaded(false), _state(state), alive(true), collidable(collidable), name(_name) {} 


Entity::Entity(GameState *state, bool collidable, entityName _name, float speed)
	:_isLoaded(false), _state(state), alive(true), collidable(collidable), name(_name), speed(speed) {}


Entity::Entity(GameState *state, entityName _name, float speed) 
	:_isLoaded(false), _state(state), alive(true), collidable(false), name(_name), speed(speed) {}

Entity::Entity(GameState *state, float speed) 
	:_isLoaded(false), _state(state), alive(true), collidable(false), name(entityName::entityDetault), speed(speed) {}



Entity::~Entity()
{
	
}

void Entity::Load(std::string filename)
{
	if(_texture.loadFromFile(filename) == false)
	{
		_filename =  "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void Entity::Load(sf::Texture &texture)
{
	_sprite.setTexture(texture);
	_isLoaded = true;	
	GetSprite().setOrigin((float) GetSprite().getTextureRect().width / 2, (float)GetSprite().getTextureRect().height / 2);
}

void Entity::Draw(sf::RenderWindow &renderWindow)
{
	if(alive)
	{
		renderWindow.draw(_sprite);	
	}
}

void Entity::Touch(Entity *other){}


void Entity::Update(float frametime)
{
}

void Entity::SetPosition(float x, float y)
{
	_sprite.setPosition(x,y);
}

sf::Vector2f Entity::GetPosition() const
{
	return _sprite.getPosition();
}

float Entity::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float Entity::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::Rect<float> Entity::GetBoundingRect() const
{
	return _sprite.getGlobalBounds();
}

sf::Sprite& Entity::GetSprite()
{
	return _sprite;
}

bool Entity::IsLoaded() const
{
	return _isLoaded;
}

int Entity::getID()
{
	return ID;	
}

void Entity::setID(int id)
{
	ID = id;
}

Entity::entityName Entity::getEntityName()
{
	return name;
}

bool Entity::isCollidable()
{
	return collidable;
}

float Entity::random_number(float low, float high)
{
    return low + ((float)((float)rand() / (float)RAND_MAX) * (float)((high) - (low)));
}

void Entity::toggleDeath()
{
	alive = false;
	onDeath();
}

void Entity::onDeath(){}

int Entity::getWindowHeight()
{
	return _state->GetWindowHeight();
}

int Entity::getWindowWidth()
{
	return _state->GetWindowWidth();
}