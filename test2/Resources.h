#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <map>
#include "forward.h"

struct Resources
{
	Resources()
	{
		AddTexture( "mainmenu.png" );
		AddTexture( "highlight.png" );
		AddTexture( "player.png" );
		AddTexture( "health.png" );
		AddTexture( "exp.png" );
		AddTexture( "levelup.png" );
		AddTexture( "bullet.png" );
		AddTexture( "enemy.png" );
		AddTexture( "particle.png" );
		AddTexture( "level.png" );
		AddTexture( "ray1.png" );
		AddTexture( "ray2.png" );
		AddTexture( "gameover.png" );
		AddTexture( "overmenu.png" );
		AddTexture( "bubble.png" );
		AddFont( "DroidSans.ttf" );
		AddSoundBuffer( "hover.wav" );
		AddSoundBuffer( "select.wav" );
		AddSoundBuffer( "shoot.wav" );
		AddSoundBuffer( "explosion.wav" );
		AddSoundBuffer( "levelup.wav" );
		AddMusic( "mainmenu.ogg" );
		AddMusic( "game.ogg" );
	}

	std::map<std::string, PTexture>		textures_;
	std::map<std::string, PFont>		fonts_;
	std::map<std::string, PSoundBuffer> soundbuffers_;
	std::map<std::string, PMusic>		musics_;
	
	PTexture GetTexture( const std::string& filename )
	{
		return textures_[filename];
	}

	PFont GetFont( const std::string& filename )
	{
		return fonts_[filename];
	}

	PSoundBuffer GetSoundBuffer( const std::string& filename )
	{
		return soundbuffers_[filename];
	}

	PMusic GetMusic( const std::string& filename )
	{
		return musics_[filename];
	}

	void AddTexture( const std::string& filename )
	{
		PTexture texture( new sf::Texture );
		texture->loadFromFile( filename );
		textures_[filename] = texture;
	}

	void AddFont( const std::string& filename )
	{
		PFont font( new sf::Font );
		font->loadFromFile( filename );
		fonts_[filename] = font;
	}

	void AddSoundBuffer( const std::string& filename )
	{
		PSoundBuffer soundbuffer = PSoundBuffer( new sf::SoundBuffer );
		soundbuffer->loadFromFile( filename );
		soundbuffers_[filename] = soundbuffer;
	}

	void AddMusic( const std::string& filename )
	{
		PMusic music = PMusic( new sf::Music );
		music->openFromFile( filename );
		musics_[filename] = music;
	}
};

#endif