#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"
#include "level.h"

class Bullet :public Entity
{
public:
	float castTime;
	int direction;

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir)
		: Entity(image, Name, X, Y, W, H)
	{
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		speed = 0.8f;
		w = h = 16;
		life = true;
		direction = dir;

	}


	void Update(float time)
	{
		castTime += time;
		if (castTime > 2000)
		{
				switch (direction)
				{
				case 0: dx = speed; dy = 0; break;
				case 1: dx = -speed; dy = 0; break;
				}

				x += dx*time;
				y += dy*time;

				if (x <= 0) x = 1;
				if (y <= 0) y = 1;

				for (int i = 0; i < obj.size(); i++)
				{
					if (GetRect().intersects(obj[i].rect))
					{
						life = false;
					}
				}
		}
			sprite.setPosition(x + w / 2, y + h / 2);
		}
};