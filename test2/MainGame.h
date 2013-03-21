#ifndef MAINGAME_H_
#define MAINGAME_H_

#include "GameState.h"
#include "GameObjectManager.h"
#include "textureManager.h"
#include "Player.h"
#include "Cursor.h"
#include "FPS.h"

class MainGame : public GameState
{
private:
	 GameObjectManager _gameObjectManager;
	 sf::Font MyFont;
	 sf::Text textScore;
	 sf::Text waveNumner;
	 sf::Text timer;
	 sf::Clock clock;
	 sf::Clock clock2;
	 sf::Clock clock3;
	 sf::Clock powerupTimer;
	 FPS *fps;
	 int score;
	 sf::RectangleShape		healthBar;
	 sf::RectangleShape		xpBar;
	 sf::RenderTexture texture;
	 sf::Sprite _sprite;
	 float time;
	 int index;
	 float roundWave;

public:
	sf::View camera;
	MainGame(Application *App);
	~MainGame();
	void Init();
	void Update(float elapsedTime);
	void Render(sf::RenderWindow& renderWindow);
	void Enable();
	GameObjectManager& getGameObjectManager();
	float random_number(float low, float high);
	sf::Vector2f getRandomPosition();
	void LoadMap();
	void DrawMap();
	void nextWave();
	int getRandInt(int low, int high);
	int wave;
	int killed;
};

#endif