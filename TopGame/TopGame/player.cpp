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
	state = stay; obj = lev.GetAllObjects(); isRightDirection = true; doesAttack = false; currentFrame = 0;
	if (name == "Player1") 
	{
		sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
	}
	lastDamageTime = -3;
}

void Player::Animation(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		isRightDirection = false;
		if (!Keyboard::isKeyPressed(Keyboard::W))
		{
			currentFrame += 0.005f*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(191 + (40 * int(currentFrame)), 8, -size.x, size.y));
		}
		else 
		{
			sprite.setTextureRect(IntRect(118, 74, -31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) 
	{
		isRightDirection = true;
		if (!Keyboard::isKeyPressed(Keyboard::W))
		{
			currentFrame += 0.005f*time;
			if (currentFrame > 4) currentFrame -= 4;
			sprite.setTextureRect(IntRect(151 + (40 * int(currentFrame)), 8, size.x, size.y));
		}
		else 
		{
			sprite.setTextureRect(IntRect(87, 74, 31, 63));
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (isRightDirection) 
		{
			sprite.setTextureRect(IntRect(320, 8, 50, size.y));
		}
		else 
		{
			sprite.setTextureRect(IntRect(370, 8, -50, size.y));
		}
	}
	if (state == stay) 
	{
		doesAttack = false;
		if (isRightDirection) 
		{
			sprite.setTextureRect(IntRect(151, 8, size.x, size.y));
		}
		else
		{
			sprite.setTextureRect(IntRect(151 + size.x, 8, -size.x, size.y));
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
		sprite.setTextureRect(IntRect(302 + (43 * int(currentShot)), 80, 43, size.y));
	}
	if (state == bulletleft)
	{
		currentShot += 0.003f*time;
		if (currentShot > 3)
		{
			currentShot -= 3; isShot = false;
			oneShot = true;
		}
		sprite.setTextureRect(IntRect(345 + (43 * int(currentShot)), 80, -43, size.y));
	}
}
void Player::Control(float time)
{
	if (!isShot)
	{
		state = stay;
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			isRightDirection = false;
			state = left; speed = 0.1f; doesAttack = false;
			goingSide = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			isRightDirection = true;
			state = right; speed = 0.1f; doesAttack = false;
			goingSide = 2;
		}
		if ((Keyboard::isKeyPressed(Keyboard::W)) && (isOnGroud))
		{
			state = jump; doesAttack = false; isOnGroud = false;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			state = hit;
			doesAttack = true;
		}
		if (state == stay)
		{
			doesAttack = false;
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
					position.y = obj[i].rect.top - size.y;  velocity.y = 0; isOnGroud = true;
				}
				if (Dy < 0) 
				{ 
					position.y = obj[i].rect.top + obj[i].rect.height;   velocity.y = 0;
				}
				if (Dx > 0) 
				{
					position.x = obj[i].rect.left - size.x;
				}
				if (Dx < 0) 
				{
					position.x = obj[i].rect.left + obj[i].rect.width;
				}
			}
			if (obj[i].name == "thorns")
			{
				sound_damage.play();
				health -= 5; velocity.y = -0.4f;
			}
		}
	}
}

void Player::Update(float time)
{
	if (alive)
	{
		Control(time);
		Animation(time);
		switch (state)
		{
		case right:velocity.x = speed; break;
		case left:velocity.x = -speed; break;
		case stay: velocity.x = 0; break;
		case hit: velocity.x = 0; break;
		case jump: velocity.y = -0.6f; break;
		case bulletleft: velocity.x = 0; break;
		case bulletright: velocity.x = 0; break;
		}
		SoundPlayer(time);
		position.x += velocity.x*time;
		CheckCollisionWithMap(velocity.x, 0);
		position.y += velocity.y*time;
		CheckCollisionWithMap(0, velocity.y);
	}
	sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
	if (health <= 0) 
	{ 
		alive = false;
	}
	velocity.y = velocity.y + 0.0015f*time;
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