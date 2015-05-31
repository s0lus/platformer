#pragma once

#include <iostream>

#include "Screen.h"
#include "Graphics/ScreenSettings.h"

#include <SFML/Graphics.hpp>

class GameOverScreen : public Screen
{

private:
	ScreenSettings scrSet;
	bool isFullScreen;

public:
	GameOverScreen();
	~GameOverScreen();

	int run(sf::RenderWindow &window);

};