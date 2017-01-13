#include "Entity.h"

//Инициализация сущности по анимации и позиции
Entity::Entity(AnimationManager &A, int X, int Y)
{
	anim = A;
	x = X;
	y = Y;
	dir = 0;

	life = true;
	timer = 0;
	timer_end = 0;
	dx = dy = 0;
}


Entity::~Entity()
{
	obj.clear();
}

//Нарисовать сущность на окне
void Entity::draw(sf::RenderWindow &window)
{
	anim.draw(window, x, y + h);
}

//Получить каркас сущности
sf::FloatRect Entity::getRect() const
{
	return sf::FloatRect(x, y, w, h);
}

//Установка параметров сущности:
//имя, начальная скорость, очки здоровья, начальная анимация
//Ширина и высота определяется из кадров анимации
void Entity::option(sf::String NAME, float SPEED, int HEALTH, sf::String FIRST_ANIM)
{
	Name = NAME;
	if (FIRST_ANIM != "") 
		anim.set(FIRST_ANIM);

	w = anim.getWidht();
	h = anim.getHeight();
	dx = SPEED;
	Health = HEALTH;
}
