#include "textureManager.h"
#include <iostream>

textureManager::textureManager()
{
	
}

textureManager::~textureManager()
{
	
}

void textureManager::Add(sf::String textureName)
{
	sf::Texture _texture;

	if(_texture.loadFromFile(textureName))
	{
		_textures.insert(std::pair<sf::String, sf::Texture>(textureName,_texture));
	}
	else
	{
		std::cout << "failed to load" << "\n";
	}
}


sf::Texture& textureManager::Get(sf::String textureName)
{
	std::map<sf::String, sf::Texture>::iterator  results = _textures.find(textureName);
	if(results == _textures.end() )
		std::cout << "texture not found";
	return results->second;	
}