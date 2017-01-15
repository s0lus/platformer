#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(AnimationManager &a, Level &lev, int x, int y);
    ~Enemy();


    void update(float time);
    void collision(int dir);
};