#pragma once

#include <iostream>
#include <list>

#include "Screen.h"

#include <Animation.h>
#include <Level.h>
#include <Entity.h>
#include <Enemy.h>
#include <Player.h>
#include <Bullet.h>
#include <Torch.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameScreen: public Screen
{
public:
	GameScreen();
	~GameScreen();

	int Run(sf::RenderWindow &window);

};