#pragma once

#include "Entity.h"

class Torch: public Entity
{
public:
    Torch(AnimationManager &a, Level &lev, int x, int y);
    ~Torch();


    void update(float time);
};

