#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class MenuGame
{
private:
	Texture menuTexture1;
	Texture menuTexture2;
	Texture menuBackground;
	Texture menuGameOver;
	Sprite menu1;
	Sprite menu2;
	Sprite menuBg;
	Sprite menuGO;

	int menuNum;

public:
	MenuGame();
	void Draw(RenderWindow & window, bool & isMenu);
	void DrawGameOver(RenderWindow & window, bool & isMenu);
};