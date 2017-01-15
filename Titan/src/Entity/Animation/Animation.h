#pragma once

#include <SFML/Graphics.hpp>

#include "tinyxml.h"

class Animation
{
public:
    Animation();

    ~Animation();

    void tick(float time);

    std::vector<sf::IntRect> frames, frames_flip;
    float currentFrame, speed;
    bool loop;
    bool flip, isPlaying;
    sf::Sprite sprite;

};
