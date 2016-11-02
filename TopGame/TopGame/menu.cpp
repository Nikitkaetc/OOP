#include "menu.h"


void Menu(RenderWindow & window, Music& music_menu)
{
	music_menu.openFromFile("music/menu.ogg");
	music_menu.play();
	music_menu.setLoop(true);

	Texture menuTexture1;
	Texture menuTexture2;
	Texture menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuBackground.loadFromFile("images/menu.jpg");
	Sprite menu1(menuTexture1);
	Sprite menu2(menuTexture2);
	Sprite menuBg(menuBackground);
	menu1.setPosition(603, 454);
	menu2.setPosition(603, 514);
	menuBg.setPosition(0, 0);

	IsMenu(window, menuBg, menu1, menu2);
	music_menu.stop();
}

void MenuGameOver(RenderWindow & window, Music& music_menu) 
{
	music_menu.openFromFile("music/gameover.ogg");
	music_menu.play();
	music_menu.setLoop(true);
	Texture menuTexture1;
	Texture menuTexture2;
	Texture menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuBackground.loadFromFile("images/gameOver.jpg");
	Sprite menu1(menuTexture1);
	Sprite menu2(menuTexture2);
	Sprite menuBg(menuBackground);
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	menu1.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 454);
	menu2.setPosition(center.x - size.x / 2 + 603, center.y - size.y / 2 + 514);
	menuBg.setPosition(center.x - size.x / 2, center.y - size.y / 2);
	IsMenu(window, menuBg, menu1, menu2);
	music_menu.stop();
}

void Draw(RenderWindow & window, Sprite & menuBg, Sprite & menu1, Sprite & menu2)
{
	window.draw(menuBg);
	window.draw(menu1);
	window.draw(menu2);
}

void IsMenu(RenderWindow & window, Sprite & menuBg, Sprite & menu1, Sprite & menu2)
{
	bool isMenu = 1;
	int menuNum = 0;
	while (isMenu)
	{
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

		Draw(window, menuBg, menu1, menu2);

		window.display();
	}
}