#pragma once

#include <SFML/Audio.hpp>

#include <string>

class GameMusic
{
private:
    sf::Music gameTheme;

public:
    GameMusic();

    ~GameMusic();

    void loadMusic(float &volume, std::string path);

    void playMusic();

    void playMusic(bool loop);

    void stopMusic(std::string which);

    void gameVolume(float &volume);
};