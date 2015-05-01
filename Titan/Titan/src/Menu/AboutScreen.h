#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"

#include "Screen.h"

class AboutScreen: public Screen
{
public:
	AboutScreen();
	~AboutScreen();

	virtual int Run(sf::RenderWindow &window);
};