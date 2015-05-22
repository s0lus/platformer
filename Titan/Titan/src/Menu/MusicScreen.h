#pragma once

#include "Screen.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>


class MusicScreen: public Screen
{
public:
	MusicScreen();
	~MusicScreen();

	int run(sf::RenderWindow &window);
};