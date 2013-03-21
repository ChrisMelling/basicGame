#ifndef MAIN_H_
#define MAIN_H_

#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "MainGame.h"
#include "MainMenu.h"

#include "gameoverState.h"
#include "textureManager.h"
#include "StateManager.h"

class Application 
{
private:
	bool	b_running_;
	std::string 					title_;
	float							width_;
	float							height_;
	int								bpp_;
	bool							_fullscreen;
	bool							_loading;
	sf::RenderWindow				_window;
	textureManager					_textureManager;
	StateManager*					_stateManager;
	sf::Clock						_clock;
	sf::Color						colour;
	

public:
									Application() { _fullscreen = true; }
									Application(std::string title, float width, float height, int bpp, bool b_fullscreen);
	void							Create( std::string title, float width, float height, int bpp, bool b_fullscreen );
	textureManager&					gettextureManager();
	void							Init();
	void							Update();
	void							Draw();
	void							Exit();
	sf::Vector2i					getMousePos();
	void							changeState(GameState::Statename name);
	StateManager					getStateManger();
	bool							isRunning();
	float							getElapsed();
	void 							ChangeResolution( float width, float height, int bpp, bool b_fullscreen );
	std::string 					GetTitle();
	GameState*  					GetState();
	float							GetWidth();
	float							GetHeight();
	int								GetBpp();
	bool							IsFullscreen();
	void							setColour(int r, int g, int b, int a);
	void							setColour(sf::Color colour);
	sf::RenderWindow&				getWindow();
	bool							keyboardControl;
	bool							xboxControl;
	int								numPlayers;

	void							setXbox();
	void							setMouse();
};

#endif