#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include "menu.h"
#include "LifeBar.h"
#include <vector>
#include <list>
//Модульность,толчок от врага!!!
#include "TinyXML/tinyxml.h"


using namespace sf;
class Entity {
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
};
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, hit } state;
	int playerScore; float CurrentFrame;
	bool isShot, tolchok, isHit;

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; isShot = false; obj = lev.GetAllObjects(); tolchok = true; isHit = false; CurrentFrame = 0;
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
		}
	}

	void control(float time) {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::A)) {
				state = left; speed = 0.1;
				if (!Keyboard::isKeyPressed(Keyboard::W)) {
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(191 + (40 * int(CurrentFrame)), 8, -w, h));
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) {
				state = right; speed = 0.1;
				if (!Keyboard::isKeyPressed(Keyboard::W)) {
					CurrentFrame += 0.005*time;
					if (CurrentFrame > 4) CurrentFrame -= 4;
					sprite.setTextureRect(IntRect(151 + (40 * int(CurrentFrame)), 8, w, h));
				}
			}

			if ((Keyboard::isKeyPressed(Keyboard::W)) && (onGround)) {
				state = jump; dy = -0.6; onGround = false;
				sprite.setTextureRect(IntRect(87, 74, 31, 63));
			}

			if (Keyboard::isKeyPressed(Keyboard::S)) {
				state = down;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				isHit = true;
				sprite.setTextureRect(IntRect(320 , 8, 50, h));
			}
		}
	}



	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (obj[i].name == "solid")
				{
					if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
					if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
					if (Dx>0) { x = obj[i].rect.left - w; }
					if (x >= obj[i].rect.left -20) { tolchok = false; } else{ tolchok = true; }
					if (Dx<0) { x = obj[i].rect.left + obj[i].rect.width; }
					if (x <= obj[i].rect.left + 20) { tolchok = false; }
					else { tolchok = true; }
				}
			}
	}

	void update(float time)
	{
		if (life)
		{
			control(time);
			switch (state)
			{
			case right:dx = speed; break;
			case left:dx = -speed; break;
			case up: break;
			case down: dx = 0; break;
			case stay: break;
			}
			x += dx*time;
			checkCollisionWithMap(dx, 0);
			y += dy*time;
			checkCollisionWithMap(0, dy);
		}
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false;}
		if (!isMove) { speed = 0; }
		setPlayerCoordinateForView(x, y);
		if (life) { setPlayerCoordinateForView(x, y); }
		dy = dy + 0.0015*time;
	}
};



class Enemy :public Entity {
public:
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("solid");
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{
		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if (Dy>0) { y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				if (Dy<0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx>0) { x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
			}
	}

	void update(float time)
	{
		if (name == "EasyEnemy") {
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}
};
class Bullet :public Entity {
public:
	int direction;

	Bullet(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H) {//всё так же, только взяли в конце состояние игрока (int dir)
		obj = lvl.GetObjects("solid");
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
	}


	void update(float time)
	{
		switch (direction)
		{
		case 0: dx = -speed; dy = 0;   break;
		case 1: dx = speed; dy = 0;   break;
		}

		x += dx*time;
		y += dy*time;

		if (x <= 0) x = 1;
		if (y <= 0) y = 1;

		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect))
			{
				life = false;
			}
		}

		sprite.setPosition(x + w / 2, y + h / 2);
	}
};

void changeLevel(Level &lvl, int &numberLevel) {
	if (numberLevel == 1) { lvl.LoadFromFile("map.tmx"); }
	if (numberLevel == 2) { lvl.LoadFromFile("map2.tmx"); }
	if (numberLevel == 3) { lvl.LoadFromFile("map.tmx"); }
}

bool startGame(RenderWindow &window, int &numberLevel) {
	view.reset(FloatRect(0, 0, 640, 480));

	Level lvl;
	changeLevel(lvl, numberLevel);

	Image heroImage;
	heroImage.loadFromFile("images/IronMan.png");
	heroImage.createMaskFromColor(Color(186, 254, 202));

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy.png");

	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	BulletImage.createMaskFromColor(Color(0, 0, 0));

	Object player = lvl.GetObject("player");
	std::list<Entity*>  entities;
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;
	std::vector<Object> e = lvl.GetObjects("easyEnemy");
	for (int i = 0; i < e.size(); i++)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 69, 129));

	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 56);
	LifeBar lifeBarPlayer;
	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();

		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (p.isShot == true) { p.isShot = false; entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state)); }
		}

		for (it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false) { it = entities.erase(it); delete b; }
			else it++;
		}
		for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
		{
			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((*it)->name == "EasyEnemy") {
					if (p.isHit)
					{
						(*it)->health = 0;
						p.isHit = false;
					}
					if ((p.dy > 0) && (p.onGround == false)) { (*it)->dx = 0; p.dy = -0.2; (*it)->health = 0; }
					else { p.health -= 20; }
					if ((*it)->dx > 0)
					{
						(*it)->x = p.x - (*it)->w;
						if (p.tolchok) { p.x = (*it)->x + (*it)->w + 20; }
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
					}
					if ((*it)->dx < 0)
					{
						(*it)->x = p.x + p.w;
						if (p.tolchok) { p.x = (*it)->x - p.w - 20; }
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
					}
				}
			}
			for (it2 = entities.begin(); it2 != entities.end(); it2++) {
				if ((*it)->getRect() != (*it2)->getRect()) {
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))
					{
						(*it)->dx *= -1;
						(*it)->sprite.scale(-1, 1);
					}
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "Bullet") && ((*it2)->name == "EasyEnemy"))
					{
						(*it2)->health = 0;
					}
				}
			}
		}
		if (p.x > 1500) { lvl.levelNumber++; numberLevel++; return true; }
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		lifeBarPlayer.update(p.health);
		p.update(time);
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++) {
			window.draw((*it)->sprite);
		}
		window.draw(p.sprite);
		lifeBarPlayer.draw(window);
		window.display();
	}
}

void gameRunning(RenderWindow & window, int & numberLevel) {//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) { gameRunning(window, numberLevel); }//принимает с какого уровня начать игру
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}