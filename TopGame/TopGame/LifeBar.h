#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class lifeBar
{
public:
	Image image, imageAva;
	Texture t, avaText;
	Sprite s, avaSprite;
	int max;
	RectangleShape bar;

	lifeBar();
	void Update(int k);
	void Draw(RenderWindow &window);

};