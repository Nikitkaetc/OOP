#include "map.h"
#include "view.h"
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
//Камера вида. ООП
using namespace sf;
using namespace std;
class Player {
private: float x, y;
public:
	float w, h, dx, dy, speed;
	int dir, playerScore, health;
	bool life;
	String File; 
	Image image;
	Texture texture;
	Sprite sprite;
Player(String F, float X, float Y, float W, float H) {
	dir = 0; speed = 0; playerScore = 0; health = 100;
	life = true;
	File = F;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	image.createMaskFromColor(Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(IntRect(0, 0, w, h));
}
void update(float time) 
{
	switch (dir)
	{
	case 0: dx = speed; dy = 0; break;
	case 1: dx = -speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	}

	x += dx*time;
	y += dy*time;

	speed = 0;
	sprite.setPosition(x, y); 
	interactionWithMap();
	if (health <= 0) { life = false; speed = 0; }
}
float getplayercoordinateX() {
	return x;
}
float getplayercoordinateY() {	
	return y;
}
void interactionWithMap()//ф-ция взаимодействия с картой
{

	for (int i = y / 32; i < (y + h) / 32; i++)
		for (int j = x / 32; j<(x + w) / 32; j++)
		{
			if (TileMap[i][j] == '0')
			{
				if (dy>0)
				{
					y = i * 32 - h;
				}
				if (dy<0)
				{
					y = i * 32 + 32;
				}
				if (dx>0)
				{
					x = j * 32 - w;
				}
				if (dx < 0)
				{
					x = j * 32 + 32;
				}
			}

			if (TileMap[i][j] == 's') {
				playerScore++;
				TileMap[i][j] = ' ';
			}
			if (TileMap[i][j] == 'f') {
				health -= 40;
				TileMap[i][j] = ' ';
			}

			if (TileMap[i][j] == 'h') {
				health += 20;
				TileMap[i][j] = ' ';
			}
		}
}
};

int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");

	view.reset(sf::FloatRect(0, 0, 640, 480));

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p("hero.png", 320, 240, 96.0, 96.0);
	float CurrentFrame = 0;
	Clock clock;
	Clock gameTimeClock; 
	int gameTime = 0;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (p.life) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				p.dir = 1; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::D)) {
				p.dir = 0; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			}

			if (Keyboard::isKeyPressed(Keyboard::W)) {
				p.dir = 3; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));

			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				p.dir = 2; p.speed = 0.1;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));

			}
		}
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		p.update(time);
		window.setView(view);
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);

				window.draw(s_map);
			}
		ostringstream playerHealthString, gameTimeString;
		playerHealthString << p.health; gameTimeString << gameTime;
		if (p.life)
		{
			text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str());
			text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);
		}
		else
		{
			text.setString("GAME OVER");
			text.setPosition(view.getCenter().x, view.getCenter().y);
		}
		window.draw(p.sprite);
		window.draw(text);
		window.display();
	}
	return 0;
}