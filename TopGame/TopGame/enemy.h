#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"
#include "level.h"
#include "bullet.h"

using namespace sf;

class Enemy :public Entity {
public:
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("solid");
		stateenemy = rigth;
		goingSide = 0;
		if (name == "CAEnemy") {
			sprite.setTextureRect(IntRect(175, 11, w, h));
			sprite.setOrigin(w / 2, h / 2);
		}
		if (name == "BulleterEnemy") {
			sprite.setTextureRect(IntRect(250, 92, -w, h));
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; stateenemy = left; goingSide = 1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width;  stateenemy = rigth; goingSide = 2; sprite.scale(-1, 1); }
			}
			else { onGround = false; }
	}

	void update(float time)
	{
		if (name == "CAEnemy") {
			switch (stateenemy)
			{
			case left: dx = -0.1; break;
			case rigth: dx = 0.1; break;
			case hit:  dx = 0; break;
			case stay: break;
			}
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
			if (!onGround) { dy = dy + 0.0015*time; }
		}
		if (name == "BulleterEnemy") {
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}
};