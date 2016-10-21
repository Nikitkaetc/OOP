#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar
{
public:
	Image image, imageAva;
	Texture t, avaText;
	Sprite s, avaSprite;
	int max;
	RectangleShape bar;

	LifeBar();
	void update(int k);
	void draw(RenderWindow &window);

};