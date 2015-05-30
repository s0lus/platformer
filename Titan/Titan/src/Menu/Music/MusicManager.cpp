#include "MusicManager.h"

//----------------------- InMenuMusic -----------------------//

InMenuMusic::InMenuMusic()
{}

InMenuMusic::~InMenuMusic()
{}


void InMenuMusic::loadMusic(float &volume, std::string path)
{
	menuTheme.openFromFile(path);
	menuTheme.setVolume(volume);
}

void InMenuMusic::playMusic(std::string music)
{
	if (music == "menu")
	{
		menuTheme.play();
		menuTheme.setLoop(true);
	}
}

void InMenuMusic::stopMusic(std::string which)
{
	if (which == "menu")
	{
		menuTheme.stop();
	}
}


void InMenuMusic::menuVolume(float &volume)
{
	menuTheme.setVolume(volume);
}


//----------------------- InGameMusic -----------------------//

InGameMusic::InGameMusic()
{}

InGameMusic::~InGameMusic()
{}



void InGameMusic::loadMusic(float &volume, std::string path)
{
	gameTheme.openFromFile(path);
	gameTheme.setVolume(volume);
}

void InGameMusic::playMusic()
{
	gameTheme.play();
	gameTheme.setLoop(true);
}

void InGameMusic::playMusic(bool loop)
{
	gameTheme.play();
	gameTheme.setLoop(loop);
}

void InGameMusic::stopMusic(std::string which)
{
	if (which == "game")
	{
		gameTheme.stop();
	}
}


void InGameMusic::gameVolume(float &volume)
{
	gameTheme.setVolume(volume);
}