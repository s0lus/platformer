#pragma once

#include <iostream>
#include <list>

#include "Screen.h"

#include <Animation.hpp>
#include <Level.hpp>
#include <Entity.hpp>
#include <Enemy.hpp>
#include <Player.hpp>
#include <Bullet.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameScreen: public Screen
{
public:
	GameScreen();
	~GameScreen();

	int Run(sf::RenderWindow &window);

};