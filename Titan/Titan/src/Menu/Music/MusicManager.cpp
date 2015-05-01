#include "MusicManager.h"

//----------------------- InMenuMusic -----------------------//

InMenuMusic::InMenuMusic()
{}

InMenuMusic::~InMenuMusic()
{}


void InMenuMusic::LoadMusic(float &volume)
{
	menuTheme.openFromFile("res/music/InMenuMusic.ogg");
	menuTheme.setVolume(volume);
}

void InMenuMusic::PlayMusic(std::string music)
{
	if (music == "menu")
	{
		menuTheme.play();
		menuTheme.setLoop(true);
	}
}

void InMenuMusic::StopMusic(std::string which)
{
	if (which == "menu")
	{
		menuTheme.stop();
	}
}


void InMenuMusic::MenuVolume(float &volume)
{
	menuTheme.setVolume(volume);
}


//----------------------- InGameMusic -----------------------//

InGameMusic::InGameMusic()
{}

InGameMusic::~InGameMusic()
{}



void InGameMusic::LoadMusic(float &volume)
{
	gameTheme.openFromFile("res/music/InGameMusic.ogg");
	gameTheme.setVolume(volume);
}

void InGameMusic::PlayMusic()
{
	gameTheme.play();
	gameTheme.setLoop(true);
}

void InGameMusic::StopMusic(std::string which)
{
	if (which == "game")
	{
		gameTheme.stop();
	}
}


void InGameMusic::GameVolume(float &volume)
{
	gameTheme.setVolume(volume);
}