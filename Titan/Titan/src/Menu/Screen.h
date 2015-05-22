#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define screenWidth 1024
#define screenHeight 768

class Screen
{

public:
	Screen()
	{

	};

	virtual ~Screen()
	{

	};

	virtual int run(sf::RenderWindow &window) = 0;

};