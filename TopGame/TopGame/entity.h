#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

#include "level.h"

using namespace sf;
using namespace std;

class Entity {
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	float CurrentFrame;
	int w, h, health, goingSide;
	bool life, isMove, onGround;
	enum stateObject
	{
		rigth, left, stay, hit, go, attackleft, attackrigth
	};
	stateObject stateenemy;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};