#include <SFML/Graphics.hpp>

#include <iostream>

#include "Menu/Screen/Screens.h"
#include "Menu/Music/GameMusic.h"
#include "Menu/Music/MenuMusic.h"

int main()
{
    ScreenSettings scrSet;
    sf::RenderWindow window;

    if (scrSet.getScreenSettings()) {
        window.create(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
    } else {
        window.create(sf::VideoMode(screenWidth, screenHeight), "Forge of the gods", sf::Style::Default);
    }

    std::vector<Screen*> Screens;
    int screen = 0;

    MenuScreen menuScr;
    Screens.push_back(&menuScr);

    GameScreen gameScr;
    Screens.push_back(&gameScr);

    OptionsScreen optScr;
    Screens.push_back(&optScr);

    GraphicsScreen graScr;
    Screens.push_back(&graScr);

    MusicScreen musScr;
    Screens.push_back(&musScr);

    GameOverScreen gameOverScr;
    Screens.push_back(&gameOverScr);

    // Music settings
    float volume;
    float defaultVolume = 50.0;
    float volumeCheck;
    float newVolume;

    std::ifstream file;

    file.open("settings/musicsettings.txt", std::ios::in);
    if (!file) {
        std::cerr << "Error open file: musicsettings.txt" << std::endl;
    }

    file >> volume;
    file.close();

    MusicSettings musicSettings;
    musicSettings.setSoundSettings(volume >= 0 ? volume : defaultVolume);

    file.open("settings/screensettings.txt", std::ios::in);
    if (!file) {
        std::cerr << "Error open file: screensettings.txt" << std::endl;
    }

    // 0 - window(default), 1 - fullscreen
    bool screenMode;

    file >> screenMode;
    file.close();

    ScreenSettings screenSettings;
    screenSettings.setScreenSettings(screenMode > 0 ? screenMode : false);

    MenuMusic menuMusic;
    menuMusic.loadMusic(volume, "res/music/InMenuMusic.ogg");
    menuMusic.playMusic("menu");

    GameMusic gameMusic;
    gameMusic.loadMusic(volume, "res/music/InGameMusic.ogg");

    while (screen >= 0) {
        // Music
        if (screen == 0) {
            gameMusic.stopMusic("game");
            menuMusic.playMusic("menu");
        }

        if (screen == 1) {
            menuMusic.stopMusic("menu");
            gameMusic.playMusic();
        }

        // Change volume
        if (screen != 4) {
            musicSettings.getSoundSettings(volumeCheck);
            newVolume = (volume != volumeCheck) ? volumeCheck : volume;
            menuMusic.menuVolume(newVolume);
            gameMusic.gameVolume(newVolume);
        }

        // Main loop for screens
        screen = Screens[screen]->run(window);
        std::cout << "Returned value: " << screen << std::endl;
    }

    return 0;
}