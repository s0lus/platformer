#pragma once

#include "Screen.h"
#include "Menu/Graphics/ScreenSettings.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class MenuScreen : public Screen
{

private:
    ScreenSettings scrSet;
    bool isFullScreen;

public:
    MenuScreen();

    ~MenuScreen();

    int run(sf::RenderWindow &window);
};