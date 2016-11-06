#include "menu.h"
#include <iostream>
using namespace std;


MenuGame::MenuGame()
{
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuBackground.loadFromFile("images/menu.jpg");
	menuGameOver.loadFromFile("images/gameOver.jpg");
	menu1.setTexture(menuTexture1);
	menu2.setTexture(menuTexture2);
	menuBg.setTexture(menuBackground);
	menuGO.setTexture(menuGameOver);
	menuNum = 0;
}

void MenuGame::Draw(RenderWindow & window, bool & isMenu)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	menu1.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 454);
	menu2.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 514);
	menuBg.setPosition(center.x - size.x / 2, center.y - size.y / 2);
	menu1.setColor(Color::White);
	menu2.setColor(Color::White);
	menuNum = 0;
	window.clear(Color(129, 181, 221));
	if (IntRect(603, 454, 160, 48).contains(Mouse::getPosition(window))) 
	{ 
		menu1.setColor(Color::Red); menuNum = 1;
	}
	if (IntRect(603, 514, 160, 48).contains(Mouse::getPosition(window))) 
	{
		menu2.setColor(Color::Red); menuNum = 2;
	}
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (menuNum == 1) 
		{ 
		isMenu = false;
		}
		if (menuNum == 2)
		{
			window.close(); isMenu = false; 
		}
	}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
}

void MenuGame::DrawGameOver(RenderWindow & window, bool & isMenu)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	menu1.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 454);
	menu2.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 514);
	menuGO.setPosition(center.x - size.x / 2, center.y - size.y / 2);
	menu1.setColor(Color::White);
	menu2.setColor(Color::White);
	menuNum = 0;
	window.clear(Color(129, 181, 221));
	if (IntRect(603, 454, 160, 48).contains(Mouse::getPosition(window)))
	{
		menu1.setColor(Color::Red); menuNum = 1;
	}
	if (IntRect(603, 514, 160, 48).contains(Mouse::getPosition(window)))
	{
		menu2.setColor(Color::Red); menuNum = 2;
	}
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (menuNum == 1)
		{
			isMenu = false;
		}
		if (menuNum == 2)
		{
			window.close(); isMenu = false;
		}
	}
	window.draw(menuGO);
	window.draw(menu1);
	window.draw(menu2);
}