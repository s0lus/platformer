#pragma once

#include <SFML/Audio.hpp>

#include <string>

class MenuMusic
{
private:
    sf::Music menuTheme;

public:
    MenuMusic();

    ~MenuMusic();

    void loadMusic(float &volume, std::string path);

    void playMusic(std::string music);

    void stopMusic(std::string which);

    void menuVolume(float &volume);
};