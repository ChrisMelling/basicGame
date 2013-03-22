#pragma once

#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"

class FPS
{
public:
	FPS() : m_frame(0), m_fps(0) {}
	void Update();
	const unsigned int  GetFPS() const { return m_fps; }

protected:

private:
	unsigned int m_frame;
	unsigned int m_fps;
	sf::Clock m_clock;
};