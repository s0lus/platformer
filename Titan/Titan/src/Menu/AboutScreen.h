#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "Screen.h"

class AboutScreen: public Screen
{
public:
	AboutScreen();
	~AboutScreen();

	int Run(sf::RenderWindow &window);
};