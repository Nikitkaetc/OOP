#include "enemy.h"

Enemy::Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
{
	obj = lvl.GetObjects("solid");
	goingSide = 0;
	currentFrame = 0;
	if (name == "easy_enemy") 
	{
		sprite.setTextureRect(IntRect(170, 11, w, h));
		sprite.setOrigin((float)w / 2.f, (float)h / 2.f);
		state = right;
		damage = 10;
	}
	if (name == "hard_enemy") 
	{
		sprite.setTextureRect(IntRect(312, 19, -w, h));
		sprite.setOrigin((float)w / 2.f, (float)h / 2.f);
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
				y = obj[i].rect.top - h;  dy = 0; onGround = true;
			}
			if (Dy < 0) 
			{
				y = obj[i].rect.top + obj[i].rect.height;   dy = 0;
			}
			if (Dx > 0) 
			{
				x = obj[i].rect.left - w; state = left; goingSide = 1; 
			}
			if (Dx < 0) 
			{
				x = obj[i].rect.left + obj[i].rect.width;  state = right; goingSide = 2; 
			}
		}
		else 
		{ 
			onGround = false;
		}
	}
}

void Enemy::AnimationEasyEnemy(float time)
{
	if (state == right)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(170 + (39 * int(currentFrame)), 11, w, h));
	}
	if (state == left)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 4) currentFrame -= 4;
		sprite.setTextureRect(IntRect(209 + (39 * int(currentFrame)), 11, -w, h));
	}
	if (state == hit)
	{
		if (goingSide == 1)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(56 + (49 * int(currentFrame)), 74, -49, h));
			}
		}
		else if (goingSide == 2)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(7 + (49 * int(currentFrame)), 74, 49, h));
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
		sprite.setTextureRect(IntRect(356 + (44 * int(currentFrame)), 19, -w, h));
	}
	if (state == right)
	{
		currentFrame += 0.005f*time;
		if (currentFrame > 3) currentFrame -= 3;
		sprite.setTextureRect(IntRect(312 + (44 * int(currentFrame)), 19, w, h));
	}
	if (state == hit)
	{
		if (goingSide == 1)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(122 + (54 * int(currentFrame)), 94, -54, h));
			}
		}
		else if (goingSide == 2)
		{
			currentFrame += 0.003f*time;
			if (currentFrame > 2) currentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(68 + (54 * int(currentFrame)), 94, 54, h));
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
		case left: dx = -0.1f; break;
		case right: dx = 0.1f; break;
		case hit:  dx = 0; break;
		case stay: break;
		}
		x += dx*time;
		CheckCollisionWithMap(dx, 0);
		y += dy*time;
		CheckCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) 
		{ 
			life = false; 
		}
		if (!onGround) 
		{
			dy = dy + 0.0015f*time;
		}
	}
	if (name == "hard_enemy") 
	{
		AnimationHardEnemy(time);
		switch (state)
		{
		case left: dx = -0.1f; break;
		case right: dx = 0.1f; break;
		case hit:  dx = 0; break;
		case stay: break;
		}
		x += dx*time;
		CheckCollisionWithMap(dx, 0);
		y += dy*time;
		CheckCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) 
		{ 
			life = false;
		}
		if (!onGround)
		{
			dy = dy + 0.0015f*time;
		}
	}
}