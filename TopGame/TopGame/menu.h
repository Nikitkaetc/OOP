#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuBackground.loadFromFile("images/menu.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(220, 290);
	menu2.setPosition(220, 350);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(220, 290, 160, 48).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(220, 350, 160, 48).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
}

void menuGameOver(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuBackground.loadFromFile("images/gameOver.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	menu1.setPosition(center.x - size.x / 2 + 220, center.y - size.y / 2 + 290);
	menu2.setPosition(center.x - size.x / 2 + 220, center.y - size.y / 2 + 350);
	menuBg.setPosition(center.x - size.x / 2, center.y - size.y / 2);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(220, 290, 160, 48).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(220, 350, 160, 48).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
}