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

	void LoadMusic(float &volume);
	void PlayMusic(std::string music);
	void StopMusic(std::string which);

	void MenuVolume(float &volume);
};


//----------------------- Game -----------------------//

class InGameMusic
{
private:
	sf::Music gameTheme;

public:
	InGameMusic();
	~InGameMusic();

	void LoadMusic(float &volume);
	void PlayMusic();
	void StopMusic(std::string which);

	void GameVolume(float &volume);
};