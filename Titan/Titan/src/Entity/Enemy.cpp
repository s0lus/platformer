#include "Enemy.h"


Enemy::Enemy(AnimationManager &a, Level &lev, int x, int y) : Entity(a, x, y)
{
	option("Enemy", 0.01, 15, "move");
	obj = lev.getObjects("wall");
}


Enemy::~Enemy()
{
	obj.clear();
}


void Enemy::update(float time)
{
	timer += time / 2;
	x += dx * time;

	dy = 0.5;
	y += dy * time;
	collision(1);

	if (timer > 2200)
	{
		dx *= -1;
		//timer = 0;
		dir = !dir;
		anim.flip(dx < 0);
		timer = 0;
	}

	if (Health <= 0)
	{
		anim.set("dead"); dx = 0;
		timer_end += time;
		if (timer_end>4000) life = false;
	}

	anim.tick(time);
}

//ѕадение врага на землю
void Enemy::collision(int dir)
{
	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "wall")
			{
				if (dy > 0 && dir == 1)
				{
					y = obj[i].rect.top - h;
					dy = 0;
				}
			}
		}
}
