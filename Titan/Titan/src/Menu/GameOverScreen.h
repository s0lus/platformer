#pragma once

#include <iostream>

#include "Screen.h"

#include <SFML/Graphics.hpp>

class GameOverScreen : public Screen
{

public:
	GameOverScreen();
	~GameOverScreen();

	int run(sf::RenderWindow &window);

};

