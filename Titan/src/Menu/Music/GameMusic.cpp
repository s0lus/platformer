#include "GameMusic.h"

GameMusic::GameMusic()
{}

GameMusic::~GameMusic()
{}

void GameMusic::loadMusic(float &volume, std::string path)
{
    gameTheme.openFromFile(path);
    gameTheme.setVolume(volume);
}

void GameMusic::playMusic()
{
    gameTheme.play();
    gameTheme.setLoop(true);
}

void GameMusic::playMusic(bool loop)
{
    gameTheme.play();
    gameTheme.setLoop(loop);
}

void GameMusic::stopMusic(std::string which)
{
    if (which == "game") {
        gameTheme.stop();
    }
}

void GameMusic::gameVolume(float &volume)
{
    gameTheme.setVolume(volume);
}