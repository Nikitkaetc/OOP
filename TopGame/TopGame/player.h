#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "entity.h"

using namespace sf;

class Player :public Entity
{
public:
	float lastDamageTime;
	bool isShot;
	bool oneShot;
	bool doesAttack;
	SoundBuffer sound_buf_jump;
	SoundBuffer sound_buf_hit;
	SoundBuffer sound_buf_damage;
	SoundBuffer sound_buf_bonus;
	SoundBuffer sound_buf_enemydamage;
	Sound sound_jump;
	Sound sound_hit;
	Sound sound_damage;
	Sound sound_bonus;
	Sound sound_enemydamage;
	
	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);

	void Update(float time);

private:
	float currentShot;
	bool isRightDirection;
	void Animation(float time);
	void Control(float time);
	void CheckCollisionWithMap(float Dx, float Dy);
	void SoundPlayer(float time);
};