#pragma once

#include <SFML/Audio.hpp>

#include <string>

//----------------------- Menu -----------------------//
class InMenuMusic
{
private:
	sf::Music menuTheme;

public:
	InMenuMusic();
	~InMenuMusic();

	void loadMusic(float &volume, std::string path);
	void playMusic(std::string music);
	void stopMusic(std::string which);

	void menuVolume(float &volume);
};


//----------------------- Game -----------------------//

class InGameMusic
{
private:
	sf::Music gameTheme;

public:
	InGameMusic();
	~InGameMusic();

	void loadMusic(float &volume, std::string path);
	void playMusic();
	void playMusic(bool loop);
	void stopMusic(std::string which);

	void gameVolume(float &volume);
};