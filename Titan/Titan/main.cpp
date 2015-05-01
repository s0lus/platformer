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
	musicSettings.ReadSoundSettings(volume);

	InMenuMusic menuMusic;
	menuMusic.LoadMusic(volume);
	menuMusic.PlayMusic("menu");

	InGameMusic gameMusic;
	gameMusic.LoadMusic(volume);

	while (screen >= 0)
	{
		// Music
		if (screen == 0)
		{
			gameMusic.StopMusic("game");
			menuMusic.PlayMusic("menu");
		}

		if (screen == 1)
		{
			menuMusic.StopMusic("menu");
			gameMusic.PlayMusic();
		}

		// Change volume
		if (screen != 5)
		{
			musicSettings.ReadSoundSettings(volumeCheck);
			newVolume = (volume != volumeCheck) ? volumeCheck : volume;
			menuMusic.MenuVolume(newVolume);
			gameMusic.GameVolume(newVolume);
		}

		// Main loop for screens
		screen = Screens[screen]->Run(window);
		std::cout << "Returned value: " << screen << std::endl;
	}

	//system("PAUSE");

	return 0;
}