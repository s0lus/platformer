#pragma once

#include "Screen.h"
#include "Menu/Graphics/ScreenSettings.h"

#include <iostream>

#include <SFML/Graphics.hpp>

class GraphicsScreen : public Screen
{

private:
    ScreenSettings scrSet;
    bool isFullScreen;

public:
    GraphicsScreen();
    ~GraphicsScreen();

    int run(sf::RenderWindow &window);
};