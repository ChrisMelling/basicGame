#pragma once
#include <SFML/Graphics.hpp>


class textureManager
{
public:	
	textureManager();
	~textureManager();

	void Add(sf::String textureName);
	void Remove(int ID);
	int GetObjectCount() const;
	sf::Texture &Get(sf::String textureName);

private:
	std::map<sf::String, sf::Texture> _textures;
	int ID;
};