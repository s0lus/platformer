#pragma once

#include "Animation/Animation.h"
#include "Level/Level.h"
#include "Entity.h"

class Bullet: public Entity
{
public:
	Bullet(AnimationManager &a, Level &lev, int x, int y, bool dir);
	~Bullet();

	void update(float time);
};