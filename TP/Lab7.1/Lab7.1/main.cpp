#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>
#include "clocks.h"

using namespace sf;

void main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(400, 400), "Clock", Style::Default, settings);
	Clocks Clocks(window);
	Clocks.DoProgramLoop(window);
}