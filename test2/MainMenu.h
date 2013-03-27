#ifndef MAINMENU_H_
#define MAINMENU_H_


#include "GameState.h"
#include "GameObjectManager.h"

class MainMenu : public GameState
{
public:
	MainMenu(Application *App);
	~MainMenu();
	void Init();
	void Update(float elapsedTime);
	void Render(sf::RenderWindow& renderWindow);
	float random_number(float low, float high);


private:
	sf::Sprite _sprite;
	sf::Sprite _xbox;
	sf::Sprite _mouse;
	sf::Texture _texture;
	sf::Clock clock;
};

#endif