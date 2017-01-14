#pragma once

#include <SFML/Graphics.hpp>

#include "tinyxml.h"


// -------------------------- Animation --------------------------//

class Animation
{
public:
	Animation();
	~Animation();

	void tick(float time);

	std::vector<sf::IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop;	// loop ��������� ��������� �� ��������. �������� �������� ������ ������ ����������� ���� ��� � ������������, loop=false
	bool flip, isPlaying;
	sf::Sprite sprite;

};


// -------------------------- Animation Manager --------------------------//

class AnimationManager
{

public:
	AnimationManager();
	~AnimationManager();

	sf::String currentAnim;
	std::map<sf::String, Animation> animList;

	// �������� �������� �� ����� XML
	void loadFromXML(std::string fileName, sf::Texture &t);

	void set(sf::String name);

	void draw(sf::RenderWindow &window, int x = 0, int y = 0);

	void flip(bool b = 1);
	void tick(float time);
	void pause();
	void play();
	void play(sf::String name);
	bool isPlaying();

	float getHeight();
	float getWidht();
};