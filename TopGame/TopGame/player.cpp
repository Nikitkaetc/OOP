#include "player.h"

Player::Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	state = stay; obj = lev.GetAllObjects(); isRight = true; isHit = false; currentFrame = 0;
	if (name == "Player1") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	lastDamageTime = -3;
}

void Player::Animation(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		isRight = false;
		if (!Keyboard::isKeyPressed(Keyboard::W)) {
			currentFrame += 0.005*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(191 + (40 * int(currentFrame)), 8, -w, h));
		}
		else {
			sprite.setTextureRect(IntRect(118, 74, -31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		isRight = true;
		if (!Keyboard::isKeyPressed(Keyboard::W)) {
			currentFrame += 0.005*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(151 + (40 * int(currentFrame)), 8, w, h));
		}
		else {
			sprite.setTextureRect(IntRect(87, 74, 31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (isRight) {
			sprite.setTextureRect(IntRect(320, 8, 50, h));
		}
		else {
			sprite.setTextureRect(IntRect(370, 8, -50, h));
		}
	}
	if (state == stay) {
		isHit = false;
		if (isRight) {
			sprite.setTextureRect(IntRect(151, 8, w, h));
		}
		else
		{
			sprite.setTextureRect(IntRect(151 + w, 8, -w, h));
		}
	}
}
void Player::Control(float time) {
	state = stay;
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		isRight = false;
		state = left; speed = 0.1; isHit = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		isRight = true;
		state = right; speed = 0.1; isHit = false;
	}

	if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
		state = jump; isHit = false; onGround = false;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Space)) {
		state = hit;
		isHit = true;
	}
	if (state == stay) {
		isHit = false;
	}
}



void Player::CheckCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i<obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w; }
				if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
			if (obj[i].name == "thorns")
			{
				health -= 5; dy = -0.3;
			}
		}
}

void Player::update(float time)
{
	if (life)
	{
		Control(time);
		Animation(time);
		switch (state)
		{
		case right:dx = speed; break;
		case left:dx = -speed; break;
		case stay: dx = 0; break;
		case hit: dx = 0; break;
		case jump: dy = -0.6; break;
		}
		x += dx*time;
		CheckCollisionWithMap(dx, 0);
		y += dy*time;
		CheckCollisionWithMap(0, dy);
	}
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) { life = false; }
	dy = dy + 0.0015*time;
}