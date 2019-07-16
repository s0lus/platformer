#pragma once

#include "Screen.h"
#include "Menu/Graphics/ScreenSettings.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


class OptionsScreen : public Screen
{

private:
    ScreenSettings scrSet;
    bool isFullScreen;

public:
    OptionsScreen();

    ~OptionsScreen();

    int run(sf::RenderWindow &window);
};