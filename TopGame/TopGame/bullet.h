#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"
#include "level.h"

class Bullet :public Entity
{
public:
	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir);
	void Update(float time);
private:
	void CheckCollisionWithMap();
	void Animation(float time);
	float castTime;
	int direction;
};