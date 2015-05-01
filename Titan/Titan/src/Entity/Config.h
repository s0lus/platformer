#ifndef CONFIG_H
#define CONFIG_H

/*
Обязательные анимации для персонажа:
stay
walk
duck
shoot
jump
hit

Условные обозначения на карте:
enemy
player
wall:
    Если платформа наклонная, то в свойствах объекта указать тип:
        SlopeLeft    подъем влево
        SlopeRight   подъем вправо
    Лестница тоже solid, указать тип:
        ladder
*/

//Скорость игры
const int GameSpeed = 500;

//Время игровой секунды
const int GameTick = 40;

//Ускорение свободного падения для объектов
const float g = 0.0005;

//Скорость передвижения персонажа
const float WalkSpeed = 0.1;

//Скорость подъема персонажа по лестнице
const float ClimbUpSpeed = 0.05;
//Скорость спуска персонажа по лестнице
const float ClimbDownSpeed = 0.05;

//Начальная скорость при прыжке персонажа
const float JumpBoost = 0.35;

//Скорость полета пули персонажа
const float BulletSpeed = 0.2;

//Интервал, с которым стреляет противник
const int ShootInterval = 300;

#endif // CONFIG