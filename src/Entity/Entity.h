//Класс сущность
//Содержит информацию об объкте окружающего мира
//Основа для классов персонажа, врагов, любых других движущихся объектов

#pragma once


#include <SFML/Graphics.hpp>

#include "Animation/Animation.h"
#include "Animation/AnimationManager.h"
#include "Level/Level.h"


class Entity
{
public:
    Entity(AnimationManager &A, int X, int Y);

    virtual ~Entity();

    // Обновить состояние сущности (поведение сущности)
    // Поведение каждого потомка должно быть реализовано отдельно
    virtual void update(float time) = 0;

    void draw(sf::RenderWindow &window);

    // Установка параметров сущности:
    // имя, 
    // начальная скорость, 
    // очки здоровья, 
    // начальная анимация
    void option(sf::String NAME, float SPEED = 0, int HEALTH = 10, sf::String FIRST_ANIM = "");

    // Характеристики сущности:
    // положение, размеры, мгновенная скорость
    float x, y, dx, dy, w, h;

    AnimationManager animationManager;

    // Набор объектов, с которыми может взаимодействовать данная сущность
    std::vector<Object> obj;

    // Характеристика: 
    // направления движения сущности
    // параметр существования сущности
    bool dir, life;

    // timer - переменные для временной анимации сущности
    // timer_end - переменная для временного отображения сущности
    float timer, timer_end;

    sf::String Name;
    int Health;

    sf::FloatRect getRect() const;
};