#pragma once

#include <SFML/Graphics.hpp>

#include "TinyXML/tinyxml.h"

class Animation
{
public:
	Animation();
	~Animation();

	std::vector<sf::IntRect> frames, frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;   // loop показвает зациклена ли анимация. Например анимация взрыва должна проиграться один раз и остановиться, loop=false
	sf::Sprite sprite;

	void tick(float time);
};


class AnimationManager
{

public:
	AnimationManager();
	~AnimationManager();

	sf::String currentAnim;
	std::map<sf::String, Animation> animList;

   //создание анимаций вручную
	void create(sf::String name, sf::Texture &texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool loop = true);

	//загрузка из файла XML
	void loadFromXML(std::string fileName, sf::Texture &t);

	void set(sf::String name);

	void draw(sf::RenderWindow &window, int x = 0, int y = 0);

	void flip(bool b = 1);
	void tick(float time);
	void pause();
	void play();
	void play(sf::String name);
	bool isPlaying();

	float getH();
	float getW();
};