#include "Levelup.h"

#include "Application.h"

Levelup::Levelup(GameState *state,float x, float y) : Entity(state)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/levelup.png"));
	name =  entityCursor;
	GetSprite().setPosition(x,y);
	index = 255;
}

Levelup::~Levelup()
{

}

void Levelup::Update(float frametime)
{
	GetSprite().move(0,-20 * frametime);

	sf::Color colour(255,255,255,index);

	if( index < 50)
	{
		alive = false;
	}

	GetSprite().setColor(colour);

	if(clock.getElapsedTime().asMilliseconds() > 1000)
	{
		index -= 1;
	}
}

