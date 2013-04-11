
#include "Application.h"


int main()
{
	Application game = Application();
	game.Create( "My Awesome Game", 1270, 720, 32, false );

	while( game.isRunning())
	{
		game.Update();
		game.Draw();
	}
	return 0;
}

