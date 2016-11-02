#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "level.h"

using namespace sf;
using namespace std;

class Entity 
{
public:
	std::vector<Object> obj;
	float dx;
	float dy;
	float x;
	float y;
	float speed;
	float currentFrame;
	int w;
	int h;
	int health;
	int goingSide;
	int damage;
	bool life;
	bool isHit;
	bool isRight;
	bool onGround;
	enum state
	{
		right, left, stay, hit, jump
	};
	state state;
	Texture texture;
	Sprite sprite;
	String name;
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

	Entity(Image &image, String Name, float X, float Y, int W, int H);
	FloatRect GetRect();
	virtual void Update(float time) = 0;
};