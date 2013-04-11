#include "Application.h"
#include <iostream>



Application::Application( std::string title, float width, float height,int bpp, bool b_fullscreen )
	: title_( title ), width_( width ), height_( height ), bpp_( bpp ), _fullscreen( b_fullscreen )
{
	b_running_ = true;

	_window.create( sf::VideoMode( (int)width, (int)height, bpp ), title_, sf::Style::Close);

	Init();
}

void Application::Create( std::string title, float width, float height, int bpp, bool b_fullscreen )

{
	title_		  = title;
	width_		  = width;
	height_		  = height;
	bpp_		  = bpp;
	_fullscreen = b_fullscreen;


	if ( b_fullscreen )
		_window.create( sf::VideoMode( (int)width, (int)height, bpp ), title_, sf::Style::Fullscreen );
	else
		_window.create( sf::VideoMode( (int)width, (int)height, bpp ), title_, sf::Style::Close);

	b_running_ = true;
	//_window.setFramerateLimit(60);
	setColour(0,0,0,0);

	Init();
}

void Application::Init()
{
	_textureManager.Add("Content/ball.png");
	_textureManager.Add("Content/zombie.png");
	_textureManager.Add("Content/blueorb.png");
	_textureManager.Add("Content/redorb.png");
	_textureManager.Add("Content/aim.png");
	_textureManager.Add("Content/StartGame.png");
	_textureManager.Add("Content/levelup.png");
	_textureManager.Add("Content/health.png");
	_textureManager.Add("Content/particle.png");
	_textureManager.Add("Content/bubble.png");

	_textureManager.Add("Content/asteroid-big.png");
	_textureManager.Add("Content/asteroid-medium.png");
	_textureManager.Add("Content/asteroid-small.png");



	_stateManager = new StateManager();

	_stateManager->newGameState(new MainMenu(this));
	_stateManager->newGameState(new MainGame(this));
	_stateManager->newGameState(new gameoverState(this));

	_stateManager->changeState(GameState::Statename::MainMenuState);
	numPlayers = 2;
}

void Application::Update()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		// Check if window has been closed
		if (event.type == sf::Event::Closed)
			Exit();

		// Escape key pressed
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			Exit();
	}
}

void Application::Draw()
{
	_window.clear(colour);

	_stateManager->Active(_window ,getElapsed());

	_window.display();
}

void Application::Exit()
{
	b_running_ = false;
}

bool Application::isRunning()
{
	return b_running_;
}

float Application::getElapsed()
{
	sf::Time _time = _clock.getElapsedTime();
	float frametime = _time.asSeconds();	
	_clock.restart();
	return frametime;
}

void Application::changeState(GameState::Statename name)
{
	_stateManager->changeState(name);
}

textureManager& Application::gettextureManager()
{
	return _textureManager;
}

sf::Vector2i Application::getMousePos()
{
	return sf::Mouse::getPosition(getWindow());
}

void Application::ChangeResolution( float width, float height, int bpp, bool b_fullscreen )
{
	width_ = width;
	height_ = height;

	if ( b_fullscreen )
		_window.create( sf::VideoMode( (int)width, (int)height, bpp ), title_, sf::Style::Fullscreen );
	else
		_window.create( sf::VideoMode( (int)width, (int)height, bpp ), title_, sf::Style::Close);
}

std::string Application::GetTitle()
{
	return title_;
}

GameState* Application::GetState()
{
	return _stateManager->getState();
}

float	Application::GetWidth()
{
	return width_;
}

float	Application::GetHeight()
{
	return height_;
}

int	Application::GetBpp()
{
	return bpp_;
}

bool Application::IsFullscreen()
{
	return _fullscreen;
}

void Application::setColour(int r, int g, int b, int a)
{
	sf::Color temp(r,g,b,a);
	colour = temp;
}

void Application::setColour(sf::Color temp)
{
	colour = temp;
}

sf::RenderWindow& Application::getWindow()
{
	return _window;
}

void Application::setXbox()
{
	xboxControl = true;
}

void Application::setMouse()
{
	keyboardControl = true;
}