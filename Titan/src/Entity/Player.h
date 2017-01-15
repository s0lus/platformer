#pragma once

#include "Animation/Animation.h"
#include "Level/Level.h"
#include "Entity.h"

#include "Config.h"

#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:
    Player(AnimationManager &a, Level &lev, int x, int y);
    ~Player();

    enum
    {
        stay, walk, duck, jump, climb, swim
    } STATE;

    //Управление персонажем
    void keyCheck();
    //Просчет столкновений
    void collision(int num);
    //Обновление состояния персонажа
    void update(float time);


    bool onLadder, shoot, hit;
    bool canShoot = true;
    //Конфигурация управления персонажем
    std::map<std::string, bool> key;

};