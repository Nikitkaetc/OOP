#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LifeBar
{
private:
	Image image;
	Image imageAva;
	Texture t;
	Texture avaText;
	Sprite s;
	Sprite avaSprite;
	int max;
	RectangleShape bar;
public:
	LifeBar();

	void Update(int k);
	void Draw(RenderWindow &window);

};