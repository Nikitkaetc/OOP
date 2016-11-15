#include "bullet.h"

Bullet::Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir)
	: Entity(image, Name, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	position.x = X;
	position.y = Y;
	speed = 0.3f;
	size.x = W;
	size.y = H;
	alive = true;
	direction = dir;
	if (direction == 5)
	{
		sprite.setTextureRect(IntRect(32, 97, -size.x, size.y));
	}
	else if (direction == 6)
	{
		sprite.setTextureRect(IntRect(0, 97, size.x, size.y));
	}


}

void Bullet::CheckCollisionWithMap()
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (GetRect().intersects(obj[i].rect))
		{
			shouldDisppear = true;
		}
	}
}

void Bullet::Animation(float time)
{
	if (direction == 5)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(33 + (33 * int(currentFrame)), 0, -size.x, size.y));
		goingSide = 2;
	}
	else if (direction == 6)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(33 * int(currentFrame), 0, size.x, size.y));
		goingSide = 1;
	}
	if (shouldDisppear == true)
	{
		speed = 0;
		currentFrame += 0.005f*time;
		if (currentFrame > 3)
		{
			currentFrame -= 3;
			alive = false;
		}
		if (goingSide == 1)
		{
			sprite.setTextureRect(IntRect((33 * int(currentFrame)), 38, size.x, size.y));
		}
		if (goingSide == 2)
		{
			sprite.setTextureRect(IntRect(size.x + (33 * int(currentFrame)), 38, -size.x, size.y));
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
		case 5: velocity.x = -speed; velocity.y = 0; break;
		case 6: velocity.x = speed; velocity.y = 0; break;
		}

		position.x += velocity.x*time;
		position.y += velocity.y*time;

		if (position.x <= 0) position.x = 1;
		if (position.y <= 0) position.y = 1;
		CheckCollisionWithMap();
	}
	switch (direction)
	{
	case 5: sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2); break;
	case 6: sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2); break;
	}
}