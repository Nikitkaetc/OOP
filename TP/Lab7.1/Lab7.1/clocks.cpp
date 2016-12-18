#include "Clocks.h"


Clocks::Clocks(RenderWindow & window)
{
	circle.setRadius(float(CIRCLE_RADIUS));
	circle.setPosition(CIRCLE_POS);
	circle.setFillColor(Color::White);
	circle.setOutlineThickness(10);
	circle.setOutlineColor(Color::Black);
	circle.setPointCount(60);
	centerCircle.setRadius(10);
	centerCircle.setPosition(Vector2f(193, 193));
	centerCircle.setFillColor(Color::Black);
	Vector2f bigMarkerSize = { 12,4 }; 
	Vector2f smallMarkerSize = { 4,2 };
	float radius = 160;
	for (int i = 0; i < 12; i++)
	{
		float angle = (360 - (float(i) * float(360) / float(12))) - 90;
		Vector2f pos = { CLOCK_CENTER.x + cos(float(angle) * float(M_PI) / float(180)) * radius + 3, CLOCK_CENTER.y + sin(float(angle) * float(M_PI) / float(180)) * radius + 3 };
		if (i % 3 == 0)	markers[i].setSize(bigMarkerSize);
		else markers[i].setSize(smallMarkerSize);
		markers[i].setPosition(pos);
		markers[i].setRotation(angle - 180);
		markers[i].setFillColor(Color::Black);
	}
}

void Clocks::Draw(RenderWindow & window)
{
	window.draw(circle);
	for (int i = 0; i < 12; i++)
	{
		window.draw(markers[i]);
	}
	hands.DrawHands(window);
	window.draw(centerCircle);
}

void Clocks::DoProgramLoop(RenderWindow & window)
{
	Clock frameClock;
	float timeSinceLastFrame;
	while (window.isOpen())
	{
		timeSinceLastFrame = frameClock.getElapsedTime().asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		if (timeSinceLastFrame >= 1)
		{
			window.clear(Color::White);
			frameClock.restart();

			hands.UpdateClockTime();
			hands.ComputeHandsPosition();
			Draw(window);

			window.display();
		}
	}
}