#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "Graphics/ScreenSettings.h"

#include "Screen.h"

class AboutScreen: public Screen
{

private:
	ScreenSettings scrSet;
	bool isFullScreen;

public:
	AboutScreen();
	~AboutScreen();

	int run(sf::RenderWindow &window);
};