#pragma once

#include "Animation/Animation.hpp"
#include "Level/Level.hpp"
#include "Entity.hpp"

#include "Config.h"

#include <SFML/Graphics.hpp>

class Player: public Entity
{
public:
	Player(AnimationManager &a, Level &lev, int x, int y);
	~Player();

    //Состояние персонажа
	enum { stay, walk, duck, jump, climb, swim } STATE;

	bool onLadder, shoot, hit;

    //Конфигурация управления персонажем
	std::map<std::string, bool> key;

    bool canShoot = true;

    //Управление персонажем
	void keyCheck();

    //Просчет столкновений
	void collision(int num);

    //Обновление состояния персонажа
	void update(float time);

};