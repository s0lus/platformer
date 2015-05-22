#pragma once

#include "Screen.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class OptionsScreen: public Screen
{
public:
	OptionsScreen();
	~OptionsScreen();

	int run(sf::RenderWindow &window);
};