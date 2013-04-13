#pragma once
#include "Entity.h"
#include <vector>
#include <unordered_map>

class Quadtree;

class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(std::unique_ptr<Entity> gameObject);
	void Add(Entity* temp);

	void Remove(int ID);
	void killEnemies();
	int getObjectCount() const;

	std::unique_ptr<Entity>& Get(int number);

	std::unique_ptr<Entity>& Get(Entity::entityName name);

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll(float frametime);

	void checkAlive();


	std::unordered_map<int, std::unique_ptr<Entity>> _gameObjects;

	Quadtree *tree;
private:

	int ID;
};