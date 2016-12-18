#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;


class Hand
{
public:
	RectangleShape line;
	Vector2f pos;
	float time;
	float maxTime;
	float angle;
};

class Hands
{
private:
	Hand second;
	Hand minute;
	Hand hour;
public:
	Hands();
	void ComputeHandsPosition();
	void UpdateClockTime();
	void DrawHands(RenderWindow & window);
};
