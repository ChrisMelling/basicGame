#pragma once
#include "Entity.h"

class Player :public Entity
{
public:
	Player(GameState *state);
	virtual ~Player();
	virtual void Update(float frametime);
	void setTarget();
	void Controls(float frametime);
	virtual void Touch(Entity *Other);

	void addScore(int newScore);
	int getScore();

	int getHealth();
	void removeHealth();
	void giveHealth(int health);

	int getXP();
	void resetXP();
	void addXP(int xpValue);
	void rankUp();
	void onDeath();
	void Fire();

	int controllerIndex;

	sf::Music Music1;

	
protected:

private:
	int score;
	int health;
	int xp;
	int rank;
	float bulletSpeed;
	bool triShot;
	bool rapidFire;
	sf::Color _colour;

	sf::Clock clock;
	sf::Clock clock2;

	sf::Clock tri;
	sf::Clock rapid;

	float rotation;

	int index;
};
