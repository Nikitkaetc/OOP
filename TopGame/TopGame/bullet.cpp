#include "bullet.h"

Bullet::Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir)
	: Entity(image, Name, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	x = X;
	y = Y;
	speed = 0.3f;
	w = W;
	h = H;
	life = true;
	direction = dir;
	if (direction == 5)
	{
		sprite.setTextureRect(IntRect(32, 97, -w, h));
	}
	else if (direction == 6)
	{
		sprite.setTextureRect(IntRect(0, 97, w, h));
	}


}

void Bullet::CheckCollisionWithMap()
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (GetRect().intersects(obj[i].rect))
		{
			dead = true;
		}
	}
}

void Bullet::Animation(float time)
{
	if (direction == 5)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(32 + (32 * int(currentFrame)), 97, -w, h));
		goingSide = 2;
	}
	else if (direction == 6)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(32 * int(currentFrame), 97, w, h));
		goingSide = 1;
	}
	if (dead == true)
	{
		speed = 0;
		currentFrame += 0.005f*time;
		if (currentFrame > 3)
		{
			currentFrame -= 3;
			life = false;
		}
		if (goingSide == 1)
		{
			sprite.setTextureRect(IntRect(129 + (32 * int(currentFrame)), 97, w, h));
		}
		if (goingSide == 2)
		{
			sprite.setTextureRect(IntRect(129+w + (32 * int(currentFrame)), 97, -w, h));
		}
	}
}

void Bullet::Update(float time)
{
	castTime += time;
	Animation(time);
	if (castTime > 500)
	{
		switch (direction)
		{
		case 5: dx = -speed; dy = 0; break;
		case 6: dx = speed; dy = 0; break;
		}

		x += dx*time;
		y += dy*time;

		if (x <= 0) x = 1;
		if (y <= 0) y = 1; 
		CheckCollisionWithMap();
	}
	switch (direction)
	{
	case 5: sprite.setPosition(x + w / 2, y + h / 2); break;
	case 6: sprite.setPosition(x + w / 2, y + h / 2); break;
	}
}