#include "Cursor.h"

#include "Application.h"

Cursor::Cursor(GameState *state) : Entity(state)
{ 
	Load(state->getApp()->gettextureManager().Get("Content/aim.png"));
	name =  entityCursor;
}

Cursor::~Cursor()
{

}

void Cursor::Update(float frametime)
{
	GetSprite().setPosition((float)_state->getApp()->getMousePos().x, (float)_state->getApp()->getMousePos().y);
}

