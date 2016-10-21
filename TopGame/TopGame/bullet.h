#pragma once


/*
#include <SFML\Graphics.hpp>
#include "entity.h"
#include "level.h"

class Bullet :public Entity {
public:
	int direction;

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;
		case 1: dx = speed; dy = 0;   break;
		}

		x += dx*time;
		y += dy*time;

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);
	}
};
*/