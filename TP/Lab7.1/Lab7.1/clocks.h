#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "hands.h"

#define M_PI 3.14159265

using namespace sf;

const Vector2f CLOCK_CENTER{ float(200), float(200) };
const int CIRCLE_RADIUS = 170;
const Vector2f CIRCLE_POS = { CLOCK_CENTER.x - CIRCLE_RADIUS, CLOCK_CENTER.y - CIRCLE_RADIUS };

class Clocks
{
private:
	CircleShape circle;
	CircleShape centerCircle;
	RectangleShape markers[12];
	Vector2f pos;
	Hands hands;
	void Draw(RenderWindow & window);
public:
	Clocks(RenderWindow & window);
	void DoProgramLoop(RenderWindow & window);
};
