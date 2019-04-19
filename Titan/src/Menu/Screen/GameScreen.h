#pragma once

#include <iostream>
#include <list>

#include "Screen.h"
#include "Menu/Music/MenuMusic.h"
#include "Menu/Music/GameMusic.h"
#include "Menu/Music/MusicSettings.h"

#include "Entity/Animation/Animation.h"
#include "Entity/Level/Level.h"
#include "Entity/Entity.h"
#include "Entity/Enemy.h"
#include "Entity/Player.h"
#include "Entity/Bullet.h"
#include "Entity/Torch.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameScreen : public Screen
{
public:
    GameScreen();

    ~GameScreen();

    int run(sf::RenderWindow &window);

    float getFPS(const sf::Time &time) const
    {
        return (1000000.0f / time.asMicroseconds());
    }
};