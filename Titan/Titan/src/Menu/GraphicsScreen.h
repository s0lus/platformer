#pragma once

#include "Screen.h"

#include <iostream>

#include <SFML/Graphics.hpp>

class GraphicsScreen: public Screen
{
public:
	GraphicsScreen();
	~GraphicsScreen();

	int Run(sf::RenderWindow &window);
};