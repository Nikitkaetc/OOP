#include "hands.h"

Hands::Hands()
{
	Vector2f center = { 200,200 };
	hour.line.setFillColor(Color::Black);
	minute.line.setFillColor(Color::Black);
	second.line.setFillColor(Color::Black);
	hour.line.setPosition(Vector2f(center.x + 5, center.y + 5));
	hour.line.setSize(Vector2f(73, 6));
	hour.maxTime = 12;
	hour.angle = 360 / hour.maxTime;
	minute.line.setPosition(Vector2f(center.x + 2, center.y + 2));
	minute.line.setSize(Vector2f(85, 4));
	minute.maxTime = 60;
	minute.angle = 360 / minute.maxTime;
	second.line.setPosition(Vector2f(center.x + 2, center.y + 2));
	second.line.setSize(Vector2f(105, 3));
	second.maxTime = 60;
	second.angle = 360 / second.maxTime;
};


void Hands::ComputeHandsPosition()
{
	float angle;
	angle = second.time * 360 / second.maxTime - 90;
	second.line.setRotation(angle);
	angle = minute.time * 360 / minute.maxTime + (second.time / second.maxTime) * minute.angle - 90;
	minute.line.setRotation(angle);
	angle = hour.time * 360 / hour.maxTime + (minute.time / minute.maxTime) * hour.angle - 90;
	hour.line.setRotation(angle);
}

void Hands::UpdateClockTime()
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	second.time = time.wSecond;
	minute.time = time.wMinute;
	hour.time = time.wHour + float(3);
}

void Hands::DrawHands(RenderWindow & window)
{
	window.draw(second.line);
	window.draw(minute.line);
	window.draw(hour.line);
}