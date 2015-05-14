#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define screenWidth 1280
#define screenHeight 1024

class Screen
{
public:
	Screen()
	{

	};

	~Screen()
	{

	};

	virtual int Run(sf::RenderWindow &window) = 0;

};