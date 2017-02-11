#include "MenuMusic.h"

MenuMusic::MenuMusic()
{}

MenuMusic::~MenuMusic()
{}

void MenuMusic::loadMusic(float &volume, std::string path)
{
    menuTheme.openFromFile(path);
    menuTheme.setVolume(volume);
}

void MenuMusic::playMusic(std::string music)
{
    if (music == "menu") {
        menuTheme.play();
        menuTheme.setLoop(true);
    }
}

void MenuMusic::stopMusic(std::string which)
{
    if (which == "menu") {
        menuTheme.stop();
    }
}

void MenuMusic::menuVolume(float &volume)
{
    menuTheme.setVolume(volume);
}