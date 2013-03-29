#pragma once
#include "Entity.h"
#include <vector>

class Quadtree;

class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(Entity* gameObject);

	void Remove(int ID);
	void killEnemies();
	int getObjectCount() const;
	Entity* Get(Entity::entityName name) const;

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll(float frametime);
	void getGroup(Entity::entityName name, std::map<int, Entity*> &list) const;

	void checkAlive();
	std::map<int, Entity*> _gameObjects;

	Quadtree *tree;
private:

	int ID;
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<int,Entity*> & p) const
		{
			delete p.second;
		}
	};
};