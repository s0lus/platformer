#pragma once

#include "Entity.hpp"

class Enemy: public Entity
{
public:
	Enemy(AnimationManager &a, Level &lev, int x, int y);
	~Enemy();


	void update(float time);
    void Collision(int dir);
};

