#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "src/Menu/Music/MusicManager.h"
#include "src/Menu/Music/MusicSettings.h"

#include "src/Menu/Graphics/ScreenSettings.h"
#include "src/Menu/Screens.h"


int main()
{
	ScreenSettings scrSet;
	sf::RenderWindow window;

	if (scrSet.getScreenSettigns())
	{
		window.create(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
	}
	else
	{
		window.create(sf::VideoMode(screenWidth, screenHeight), "Titan", sf::Style::Default);
	}

	std::vector<Screen*> Screens;
	int screen = 0;

	MenuScreen menuScr;
	Screens.push_back(&menuScr);

	GameScreen gameScr;
	Screens.push_back(&gameScr);

	AboutScreen aboutScr;
	Screens.push_back(&aboutScr);

	OptionsScreen optScr;
	Screens.push_back(&optScr);

	GraphicsScreen graScr;
	Screens.push_back(&graScr);

	MusicScreen musScr;
	Screens.push_back(&musScr);


	// Music settings
	float volume;
	float volumeCheck = NULL;
	float newVolume = NULL;

	MusicSettings musicSettings;
	musicSettings.readSoundSettings(volume);

	InMenuMusic menuMusic;
	menuMusic.loadMusic(volume);
	menuMusic.playMusic("menu");

	InGameMusic gameMusic;
	gameMusic.loadMusic(volume);

	while (screen >= 0)
	{
		// Music
		if (screen == 0)
		{
			gameMusic.stopMusic("game");
			menuMusic.playMusic("menu");
		}

		if (screen == 1)
		{
			menuMusic.stopMusic("menu");
			gameMusic.playMusic();
		}

		// Change volume
		if (screen != 5)
		{
			musicSettings.readSoundSettings(volumeCheck);
			newVolume = (volume != volumeCheck) ? volumeCheck : volume;
			menuMusic.menuVolume(newVolume);
			gameMusic.gameVolume(newVolume);
		}

		// Main loop for screens
		screen = Screens[screen]->Run(window);
		std::cout << "Returned value: " << screen << std::endl;
	}

	//system("PAUSE");

	return 0;
}