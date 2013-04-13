
#include "GameObjectManager.h"
#include <iostream>
#include "Quadtree.h"

GameObjectManager::GameObjectManager() : ID(0)
{
	tree = new Quadtree( 0.0f, 0.0f, 1270, 720, 0, 3 );
}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::Add(std::unique_ptr<Entity> gameObject)
{
	_gameObjects.insert(std::make_pair(ID, std::move(gameObject)));
	ID++;
}

void GameObjectManager::Add(Entity* temp)
{
	_gameObjects.insert(std::make_pair(ID, std::move(std::unique_ptr<Entity>(temp))));
	ID++;
}


std::unique_ptr<Entity>& GameObjectManager::Get(int number)
{
    auto it = _gameObjects.find(number);
    if (it == _gameObjects.end()) throw std::invalid_argument("entry not found");
    return it->second;
}

std::unique_ptr<Entity>& GameObjectManager::Get(Entity::entityName name)
{
	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
		if(itr->second->getEntityName() == name)
		{
			return Get(itr->second->getID());
		}
	}
	return std::unique_ptr<Entity>(nullptr);
}

void GameObjectManager::Remove(int ID)
{
	auto results = _gameObjects.find(ID);
	if(results != _gameObjects.end() )
	{
		_gameObjects.erase(results);
	}
}

int GameObjectManager::getObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::drawAll(sf::RenderWindow& renderWindow)
{
	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
		itr->second->Draw(renderWindow);
	}
}

void GameObjectManager::updateAll(float frametime)
{	
	checkAlive();

	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
		itr->second->Update(frametime);

		if(itr->second->isCollidable())
		{
			tree->AddObject(itr->second.get());
		}	
	}	

	for (auto x = _gameObjects.begin(); x != _gameObjects.end(); x++)
	{
		std::unique_ptr<Entity>& object = x->second;

		if(object->isCollidable())
		{
			vector<Entity*> returnObjects = tree->GetObjectsAt(object->GetPosition().x, object->GetPosition().y );		

			for ( int n = 0; n < (int)returnObjects.size(); n++ ) 
			{
				Entity* collided = returnObjects[n];

				if(object->getEntityName() != collided->getEntityName())
				{
					if(object->GetBoundingRect().intersects(collided->GetBoundingRect()))

					{
						object->Touch(collided);
					}
				}
			}
		}
	}	
	tree->Clear();
}

void GameObjectManager::checkAlive()
{
	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end();)
	{
		std::unordered_map<int, std::unique_ptr<Entity>>::iterator toDelete = itr;
		itr++;

		if(!toDelete->second->alive)
		{
			_gameObjects.erase(toDelete);
		}
	}
}
