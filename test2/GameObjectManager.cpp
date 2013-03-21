
#include "GameObjectManager.h"
#include <iostream>
#include "Quadtree.h"

GameObjectManager::GameObjectManager()
{
	ID = 0;
	tree = new Quadtree( 0.0f, 0.0f, 1270, 720, 0, 3 );
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(),_gameObjects.end(),GameObjectDeallocator());
}

void GameObjectManager::Add(Entity* gameObject)
{
	gameObject->setID(ID);
	_gameObjects.insert(std::pair<int,Entity*>(ID,gameObject));
	ID++;
}

void GameObjectManager::Remove(int ID)
{
	std::map<int, Entity*>::iterator results = _gameObjects.find(ID);
	if(results != _gameObjects.end() )
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

Entity * GameObjectManager::Get(Entity::entityName name) const
{
	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
		if(itr->second->name == name)
		{
			return itr->second;
		}

		if(itr == _gameObjects.end())
		{
			return NULL;
		}
	}
	return NULL;
}

void GameObjectManager::getGroup(Entity::entityName name, std::map<int, Entity*> &list) const
{
    list.clear();
 
	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
        if(itr->second->name == name)
        {
            list.insert(std::pair<int,Entity*>(itr->second->getID(),itr->second));
        }
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

	std::cout << getObjectCount() << "\n";

	for (auto itr = _gameObjects.begin(); itr != _gameObjects.end(); itr++)
	{
		itr->second->Update(frametime);


		if(itr->second->isCollidable())
		{
			tree->AddObject(itr->second);
		}
		
	}	

	for (auto x = _gameObjects.begin(); x != _gameObjects.end(); x++)
	{
		Entity* object = x->second;

		if(object->collidable)
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
		std::map<int, Entity*>::iterator toDelete = itr;
		itr++;

		if(!toDelete->second->alive)
		{
			delete toDelete->second;
			_gameObjects.erase(toDelete);
		}
	}
}
