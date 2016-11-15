#include "enemy.h"

Enemy::Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	goingSide = 0;
	currentFrame = 0;
	if (name == "easy_enemy") 
	{
		sprite.setTextureRect(IntRect(170, 11, size.x, size.y));
		sprite.setOrigin((float)size.x / 2.f, (float)size.y / 2.f);
		state = right;
		damage = 10;
	}
	if (name == "hard_enemy") 
	{
		sprite.setTextureRect(IntRect(312, 19, -size.x, size.y));
		sprite.setOrigin((float)size.x / 2.f, (float)size.y / 2.f);
		state = left;
		damage = 20;
	}
}

void Enemy::CheckCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (GetRect().intersects(obj[i].rect))
		{
			if (Dy > 0)
			{
				position.y = obj[i].rect.top - size.y;  velocity.y = 0; isOnGroud = true;
			}
			if (Dy < 0) 
			{
				position.y = obj[i].rect.top + obj[i].rect.height;   velocity.y = 0;
			}
			if (Dx > 0) 
			{
				position.x = obj[i].rect.left - size.x; state = left; goingSide = 1;
			}
			if (Dx < 0) 
			{
				position.x = obj[i].rect.left + obj[i].rect.width;  state = right; goingSide = 2;
			}
		}
		else 
		{ 
			isOnGroud = false;
		}
	}
}

void Enemy::AnimationEasyEnemy(float time)
{
	if (state == right)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(170 + (39 * int(currentFrame)), 11, size.x, size.y));
	}
	if (state == left)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(209 + (39 * int(currentFrame)), 11, -size.x, size.y));
	}
	if (state == hit)
	{
		if (goingSide == 1)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(56 + (49 * int(currentFrame)), 74, -49, size.y));
			}
		}
		else if (goingSide == 2)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(7 + (49 * int(currentFrame)), 74, 49, size.y));
			}
		}
	}
}

void Enemy::AnimationHardEnemy(float time)
{
	if (state == left)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(356 + (44 * int(currentFrame)), 19, -size.x, size.y));
	}
	if (state == right)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(312 + (44 * int(currentFrame)), 19, size.x, size.y));
	}
	if (state == hit)
	{
		if (goingSide == 1)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(122 + (54 * int(currentFrame)), 94, -54, size.y));
			}
		}
		else if (goingSide == 2)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(68 + (54 * int(currentFrame)), 94, 54, size.y));
			}
		}
	}
}


void Enemy::Update(float time)
{
	if (name == "easy_enemy")
	{
		AnimationEasyEnemy(time);
		switch (state)
		{
		case left: velocity.x = -0.1f; break;
		case right: velocity.x = 0.1f; break;
		case hit:  velocity.x = 0; break;
		case stay: break;
		}
		position.x += velocity.x*time;
		CheckCollisionWithMap(velocity.x, 0);
		position.y += velocity.y*time;
		CheckCollisionWithMap(0, velocity.y);
		sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
		if (health <= 0) 
		{ 
			alive = false; 
		}
		if (!isOnGroud) 
		{
			velocity.y = velocity.y + 0.0015f*time;
		}
	}
	if (name == "hard_enemy") 
	{
		AnimationHardEnemy(time);
		switch (state)
		{
		case left: velocity.x = -0.1f; break;
		case right: velocity.x = 0.1f; break;
		case hit:  velocity.x = 0; break;
		case stay: break;
		}
		position.x += velocity.x*time;
		CheckCollisionWithMap(velocity.x, 0);
		position.y += velocity.y*time;
		CheckCollisionWithMap(0, velocity.y);
		sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
		if (health <= 0) 
		{ 
			alive = false;
		}
		if (!isOnGroud)
		{
			velocity.y = velocity.y + 0.0015f*time;
		}
	}
}