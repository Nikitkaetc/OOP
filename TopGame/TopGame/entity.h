#pragma once
#include <SFML\Graphics.hpp>
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

	Entity(Image &image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};