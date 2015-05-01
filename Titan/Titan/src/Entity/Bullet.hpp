#pragma once

#include "Animation/Animation.hpp"
#include "Level/Level.hpp"
#include "Entity.hpp"

class Bullet: public Entity
{
public:
	Bullet(AnimationManager &a, Level &lev, int x, int y, bool dir);
	~Bullet();

	void update(float time);
};