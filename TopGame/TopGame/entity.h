#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "level.h"

using namespace sf;
using namespace std;

class Entity {
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed;
	float currentFrame;
	int w, h, health, goingSide, damage;
	bool life, isHit, isRight, onGround;
	enum state
	{
		right, left, stay, hit, jump
	};
	state state;
	Texture texture;
	Sprite sprite;
	String name;
	SoundBuffer sound_buf_jump, sound_buf_hit, sound_buf_damage, sound_buf_bonus, sound_buf_enemydamage;
	Sound sound_jump, sound_hit, sound_damage, sound_bonus, sound_enemydamage;

	Entity(Image &image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};