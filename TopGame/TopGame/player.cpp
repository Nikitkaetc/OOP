#include "player.h"

Player::Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) 
{
	goingSide = 2;
	currentShot = 0;
	isShot = false;
	oneShot = true;
	sound_buf_hit.loadFromFile("music/hit.ogg");
	sound_hit.setBuffer(sound_buf_hit);
	sound_buf_jump.loadFromFile("music/jump.ogg");
	sound_jump.setBuffer(sound_buf_jump);
	sound_buf_damage.loadFromFile("music/damage.ogg");
	sound_damage.setBuffer(sound_buf_damage);
	sound_buf_bonus.loadFromFile("music/bonus.ogg");
	sound_bonus.setBuffer(sound_buf_bonus);
	sound_buf_enemydamage.loadFromFile("music/enemydamage.ogg");
	sound_enemydamage.setBuffer(sound_buf_enemydamage);
	state = stay; obj = lev.GetAllObjects(); isRight = true; isHit = false; currentFrame = 0;
	if (name == "Player1") 
	{
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
	lastDamageTime = -3;
}

void Player::Animation(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		isRight = false;
		if (!Keyboard::isKeyPressed(Keyboard::W))
		{
			currentFrame += 0.005f*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(191 + (40 * int(currentFrame)), 8, -w, h));
		}
		else 
		{
			sprite.setTextureRect(IntRect(118, 74, -31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) 
	{
		isRight = true;
		if (!Keyboard::isKeyPressed(Keyboard::W))
		{
			currentFrame += 0.005f*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(151 + (40 * int(currentFrame)), 8, w, h));
		}
		else 
		{
			sprite.setTextureRect(IntRect(87, 74, 31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (isRight) 
		{
			sprite.setTextureRect(IntRect(320, 8, 50, h));
		}
		else 
		{
			sprite.setTextureRect(IntRect(370, 8, -50, h));
		}
	}
	if (state == stay) 
	{
		isHit = false;
		if (isRight) 
		{
			sprite.setTextureRect(IntRect(151, 8, w, h));
		}
		else
		{
			sprite.setTextureRect(IntRect(151 + w, 8, -w, h));
		}
	}
	if (state == bulletright)
	{
		currentShot += 0.003f*time;
		if (currentShot > 3) 
		{
			currentShot -= 3; isShot = false;
			oneShot = true;
		}
		sprite.setTextureRect(IntRect(302 + (43 * int(currentShot)), 80, 43, h));
	}
	if (state == bulletleft)
	{
		currentShot += 0.003f*time;
		if (currentShot > 3)
		{
			currentShot -= 3; isShot = false;
			oneShot = true;
		}
		sprite.setTextureRect(IntRect(345 + (43 * int(currentShot)), 80, -43, h));
	}
}
void Player::Control(float time)
{
	if (!isShot)
	{
		state = stay;
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			isRight = false;
			state = left; speed = 0.1f; isHit = false;
			goingSide = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			isRight = true;
			state = right; speed = 0.1f; isHit = false;
			goingSide = 2;
		}
		if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround))
		{
			state = jump; isHit = false; onGround = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			state = hit;
			isHit = true;
		}
		if (state == stay)
		{
			isHit = false;
		}
	}
		if ((Keyboard::isKeyPressed(Keyboard::RShift))&&(oneShot == true) && (isShot == false))
		{
			if (goingSide == 1)
			{
				state = bulletleft;
				isShot = true;
				oneShot = false;
			}
			else if (goingSide == 2)
			{
				state = bulletright;
				isShot = true;
				oneShot = false;
			}
		}
}



void Player::CheckCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (GetRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
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
					x = obj[i].rect.left - w; 
				}
				if (Dx < 0) 
				{
					x = obj[i].rect.left + obj[i].rect.width; 
				}
			}
			if (obj[i].name == "thorns")
			{
				sound_damage.play();
				health -= 5; dy = -0.4f;
			}
		}
	}
}

void Player::Update(float time)
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
		case jump: dy = -0.6f; break;
		case bulletleft: dx = 0; break;
		case bulletright: dx = 0; break;
		}
		SoundPlayer(time);
		x += dx*time;
		CheckCollisionWithMap(dx, 0);
		y += dy*time;
		CheckCollisionWithMap(0, dy);
	}
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) 
	{ 
		life = false;
	}
	dy = dy + 0.0015f*time;
}

void Player::SoundPlayer(float time)
{
	if (state == jump)
	{
		sound_jump.play();
	}
	if (state == hit)
	{
		sound_hit.play();
	}
}