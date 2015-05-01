#pragma once

#include "Screen.h"

#include <iostream>

#include <SFML/Graphics.hpp>

class GraphicsScreen: public Screen
{
public:
	GraphicsScreen();
	~GraphicsScreen();

	virtual int Run(sf::RenderWindow &window);
};