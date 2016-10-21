#include "enemy.h"

Enemy::Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	obj = lvl.GetObjects("solid");
	goingSide = 0;
	CurrentFrame = 0;
	if (name == "CAEnemy") {
		sprite.setTextureRect(IntRect(170, 11, w, h));
		sprite.setOrigin(w / 2, h / 2);
		stateenemy = rigth;
	}
	if (name == "BulleterEnemy") {
		sprite.setTextureRect(IntRect(312, 19, -w, h));
		sprite.setOrigin(w / 2, h / 2);
		stateenemy = left;
	}
}

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i<obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
			if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
			if (Dx > 0) { x = obj[i].rect.left - w; stateenemy = left; goingSide = 1; }
			if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width;  stateenemy = rigth; goingSide = 2; }
		}
		else { onGround = false; }

}

void Enemy::animationCA(float time)
{
	if (stateenemy == rigth)
	{
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(170 + (39 * int(CurrentFrame)), 11, w, h));
	}
	if (stateenemy == left)
	{
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(209 + (39 * int(CurrentFrame)), 11, -w, h));
	}
	if (stateenemy == hit)
	{
		if (goingSide == 1)
		{
			CurrentFrame += 0.003*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(56 + (49 * int(CurrentFrame)), 74, -49, h));
			}
		}
		else if (goingSide == 2)
		{
			CurrentFrame += 0.003*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(7 + (49 * int(CurrentFrame)), 74, 49, h));
			}
		}
	}
}

void Enemy::animationBulleter(float time)
{
	if (stateenemy == left)
	{
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(356 + (44 * int(CurrentFrame)), 19, -w, h));
	}
	if (stateenemy == rigth)
	{
		CurrentFrame += 0.005*time;
		if (CurrentFrame > 3) CurrentFrame -= 3;
		sprite.setTextureRect(IntRect(312 + (44 * int(CurrentFrame)), 19, w, h));
	}
	if (stateenemy == hit)
	{
		if (goingSide == 1)
		{
			CurrentFrame += 0.003*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(122 + (54 * int(CurrentFrame)), 94, -54, h));
			}
		}
		else if (goingSide == 2)
		{
			CurrentFrame += 0.003*time;
			if (CurrentFrame > 2) CurrentFrame -= 2;
			{
				sprite.setTextureRect(IntRect(68 + (54 * int(CurrentFrame)), 94, 54, h));
			}
		}
	}
}


void Enemy::update(float time)
{
	if (name == "CAEnemy") {
		animationCA(time);
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
		animationBulleter(time);
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
}