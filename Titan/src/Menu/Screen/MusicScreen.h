#pragma once

#include "Screen.h"
#include "Menu/Graphics/ScreenSettings.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>


class MusicScreen : public Screen
{

private:
    ScreenSettings scrSet;
    bool isFullScreen;

public:
    MusicScreen();
    ~MusicScreen();

    int run(sf::RenderWindow &window);
};