#ifndef util_HPP
#define util_HPP
#include <iostream>

#include <SFML/System.hpp>

namespace util
{
	inline sf::String toString(int newInt)
	{
		std::stringstream p1;
		p1 << newInt;
		
		return p1.str().c_str();
	}
}

#endif // MATH_HPP