#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"
#include "view.h"
#include "level.h"

using namespace sf;

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, hit } state;//ÊÀÏÑ
	int playerScore; 
	float CurrentFrame;
	bool isShot, tolchok, isHit, isRigth;



	float lastDamageTime;

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; isShot = false; obj = lev.GetAllObjects(); tolchok = true; isRigth = true; isHit = false; CurrentFrame = 0;
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
		lastDamageTime = -3;
	}

	void control(float time) {
		state = stay;
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			isRigth = false;
			state = left; speed = 0.1; isHit = false;
			if (!Keyboard::isKeyPressed(Keyboard::W)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(191 + (40 * int(CurrentFrame)), 8, -w, h));
			}
			else {
				sprite.setTextureRect(IntRect(118, 74, -31, 63));
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			isRigth = true;
			state = right; speed = 0.1; isHit = false;
			if (!Keyboard::isKeyPressed(Keyboard::W)) {
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(151 + (40 * int(CurrentFrame)), 8, w, h));
			}
			else {
				sprite.setTextureRect(IntRect(87, 74, 31, 63));
			}
		}

		if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
			state = jump; dy = -0.6; onGround = false; isHit = false;
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			state = down;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space)) {
			state = hit;
				isHit = true;
				if (isRigth) {
					sprite.setTextureRect(IntRect(320, 8, 50, h));
				}
				else {
					sprite.setTextureRect(IntRect(370, 8, -50, h));
				}
		}
		
		if (state == stay) {
			isHit = false;
			sprite.setTextureRect(IntRect(151, 8, w, h));
		}
	}



	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (x >= obj[i].rect.left - 20) { tolchok = false; }
					else { tolchok = true; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
					if (x <= obj[i].rect.left + 20) { tolchok = false; }
					else { tolchok = true; }
				}
			}
	}

	void update(float time)
	{
		if (life)
		{
			control(time);
			switch (state)
			{
			case right:dx = speed; break;
			case left:dx = -speed; break;
			case up: break;
			case down: dx = 0; break;
			case stay: dx = 0; break;
			case hit: dx = 0; break;
			}
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
		}
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		setPlayerCoordinateForView(x, y);
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;
	}
};