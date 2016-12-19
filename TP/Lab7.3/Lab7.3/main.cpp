#include <SFML/Graphics.hpp>
#include "pendulum.h"

void main()
{

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Pendulum", sf::Style::Default, settings);

	Clock frameClock;
	int timeLastFrame;
	Pendulum pendulum;

	while (window.isOpen())
	{
		timeLastFrame = frameClock.getElapsedTime().asMilliseconds();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		if (timeLastFrame >= TIME_PER_FRAME)
		{
			frameClock.restart();

			pendulum.Physics();
			pendulum.UpdatePendulum();

			window.clear(Color::White);
			pendulum.Draw(window);
			window.display();
		}
	}
}