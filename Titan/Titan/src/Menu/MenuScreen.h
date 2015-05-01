#pragma once

#include "Screen.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class MenuScreen: public Screen
{
public:
	MenuScreen();
	~MenuScreen();

	virtual int Run(sf::RenderWindow &window);

private:
	bool playing;
};