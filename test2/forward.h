#ifndef FORWARD_H_
#define FORWARD_H_

#include <cassert>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

typedef std::vector<std::string> StringList;

/// Box2D
typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef float float32;
typedef double float64;

#define b2_pi			3.14159265359f

/// SFML
typedef std::shared_ptr<sf::RenderWindow>	PWindow;
typedef std::shared_ptr<sf::Texture>		PTexture;
typedef std::shared_ptr<sf::Font>			PFont;
typedef std::shared_ptr<sf::SoundBuffer>	PSoundBuffer;
typedef std::shared_ptr<sf::Music>			PMusic;

/// Custom
struct Resources;
class InputHandler;
class Game;
class GameState;
class Level;
class Actor;
class QuadTree;

class MenuState;
class MenuLevel;
class Button;
class Page;
class Highlight;
class Pawn;
class Bullet;
class Enemy;
class Particle;
class Sunray;
class Bubble;
class LevelUp;
class GameLevel;
class GameMenu;
class OverMenu;
class PlayState;

typedef std::shared_ptr<Resources>				PResources;
typedef std::shared_ptr<InputHandler>			PInput;
typedef std::shared_ptr<Game>					PGame;
typedef std::shared_ptr<GameState>				PGameState;
typedef std::shared_ptr<Level>					PLevel;
typedef std::shared_ptr<Actor>					PActor;
typedef std::shared_ptr<QuadTree>				PQuadTree;
typedef std::shared_ptr<std::vector<PActor>>	PActors;

typedef std::shared_ptr<MenuState>				PMenuState;
typedef std::shared_ptr<MenuLevel>				PMenuLevel;
typedef std::shared_ptr<Button>					PButton;
typedef std::shared_ptr<Page>					PPage;
typedef std::shared_ptr<Highlight>				PHighlight;
typedef std::shared_ptr<GameLevel>				PGameLevel;
typedef std::shared_ptr<GameMenu>				PGameMenu;
typedef std::shared_ptr<OverMenu>				POverMenu;
typedef std::shared_ptr<Pawn>					PPawn;
typedef std::shared_ptr<Bullet>					PBullet;
typedef std::shared_ptr<Enemy>					PEnemy;
typedef std::shared_ptr<Particle>				PParticle;
typedef std::shared_ptr<Sunray>					PSunray;
typedef std::shared_ptr<Bubble>					PBubble;
typedef std::shared_ptr<LevelUp>				PLevelUp;
typedef std::shared_ptr<PlayState>				PPlayState;

#endif