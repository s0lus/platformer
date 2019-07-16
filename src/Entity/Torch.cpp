#include "Torch.h"

Torch::Torch(AnimationManager &a, Level &lev, int x, int y) : Entity(a, x, y)
{
    option("Torch", 0, 32, "lighting");
}

Torch::~Torch()
{}

void Torch::update(float time)
{
    animationManager.tick(time);
}