#ifndef FPS_HPP__INCLUDED
#define FPS_HPP__INCLUDED
#include "FPS.h"
#pragma once
 

 
void FPS::Update()
{
	if (m_clock.getElapsedTime().asSeconds() >= 1.f)
	{
		m_fps = m_frame;
		m_frame = 0;
		m_clock.restart();
	}
 
	++m_frame;
}
 
#endif // FPS_HPP__INCLUDED