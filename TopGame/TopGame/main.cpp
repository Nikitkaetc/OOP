#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "iostream"
#include "level.h"
#include "menu.h"

#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "game.h"

#include "LifeBar.h"
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"
//Улучшить код с Update в player. Улучшение кода. Создать еще 2 карты. Подбирание объекта!
using namespace sf;
using namespace std;

struct InitializeData
{
	Level lvl;
	Image heroImage;
	Image easyEnemyImage;
	Image BulleterImage;
	Image BulletImage;
	Player *p;
	list<Entity*>  entities;
	Clock clock;
	LifeBar lifeBarPlayer;
	
	InitializeData(int& numberLevel)
	{
		view.reset(FloatRect(0, 0, 640, 480));

		ChangeLevel(lvl, numberLevel);

		heroImage.loadFromFile("images/IronMan.png");
		heroImage.createMaskFromColor(Color(186, 254, 202));

		easyEnemyImage.loadFromFile("images/CaptainAmerica.png");
		easyEnemyImage.createMaskFromColor(Color(186, 254, 202));

		BulleterImage.loadFromFile("images/bulleter.png");
		BulleterImage.createMaskFromColor(Color(255, 0, 255));

		BulletImage.loadFromFile("images/bullet.png");
		BulletImage.createMaskFromColor(Color(255, 0, 255));

		Object player = lvl.GetObject("player");
		std::list<Entity*>::iterator it;
		std::list<Entity*>::iterator it2;

		p = new Player(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 56);

		std::vector<Object> e1 = lvl.GetObjects("easyEnemy");
		for (int i = 0; i < e1.size(); i++)
		{
			entities.push_back(new Enemy(easyEnemyImage, "CAEnemy", lvl, e1[i].rect.left, e1[i].rect.top, 39, 61));
		}
		std::vector<Object> e = lvl.GetObjects("bulleterEnemy");
		for (int i = 0; i < e.size(); i++)
		{
			entities.push_back(new Enemy(BulleterImage, "BulleterEnemy", lvl, e[i].rect.left, e[i].rect.top, 44, 62));
		}

		
	}

	bool DoGameLoop(RenderWindow& window, int& numberLevel)
	{
		float gameTime = 0;

		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asMicroseconds();
			gameTime += clock.getElapsedTime().asSeconds();
			clock.restart();
			time = time / 800;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				//if (p->isShot == true) { p->isShot = false; entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p->x, p->y, 31, 7, p->state)); }
			}
			if (p->x > 3790) { lvl.levelNumber++; numberLevel++; return true; }
			if (p->y > 900) { p->life = false; }
			if (p->life == false) { menuGameOver(window);  return true; }
			if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }

			Update(time, gameTime);
			Draw(window);
		}
		return true;
		
	}

	void ChangeLevel(Level &lvl, int &numberLevel) {
		if (numberLevel == 1) { lvl.LoadFromFile("map2.tmx"); }
		if (numberLevel == 2) { lvl.LoadFromFile("map.tmx"); }
		if (numberLevel == 3) { lvl.LoadFromFile("map.tmx"); }
	}

	void EnemyColiisions(Entity *it, float gameTime)
	{
		if (it->getRect().intersects(p->getRect()))
		{
			if (((it)->name == "CAEnemy") || ((it)->name == "BulleterEnemy")) {
				if (gameTime > p->lastDamageTime + 1)
				{
					if ((!p->isHit) && ((it)->stateenemy == (it)->hit))
					{
						p->health -= 10;
						p->lastDamageTime = gameTime;
						p->sprite.setColor(Color::Red);
					}
					else if (p->isHit)
					{
						(it)->health = 0;
						p->isHit = false;
					}
				}
				if (p->isHit)
				{
					(it)->health = 0;
					p->isHit = false;
				}
			}
		}
	}

	void Collisions(list<Entity*>& entities, const float& time, Player* p, float gameTime)
	{
		for (auto it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
		{
			EnemyColiisions(*it, gameTime);
				if (((*it)->x < p->x + 30) && ((*it)->x > p->x - 30) && ((*it)->y < p->y + 7) && ((*it)->y > p->y - 7))
				{
					(*it)->stateenemy = (*it)->hit;
				}
			/*if (((*it)->x < p->x + 200) && ((*it)->x < p->x - 200))
			{
				if ((*it)->x < p->x) {
					(*it)->stateenemy = (*it)->left;
				}
				else if ((*it)->x > p->x)
				{
					(*it)->stateenemy = (*it)->rigth;
				}
			}*/
			else if (((*it)->x < p->x) && ((*it)->stateenemy == (*it)->hit))
				{
					(*it)->stateenemy = (*it)->rigth;
					(*it)->goingSide = 2;
				}
			else if (((*it)->x > p->x) && ((*it)->stateenemy == (*it)->hit))
				{
					(*it)->stateenemy = (*it)->left;
					(*it)->goingSide = 1;
				}
			if (gameTime > p->lastDamageTime + 0.5)
			{
				p->sprite.setColor(Color::White);
			}
			for (auto it2 = entities.begin(); it2 != entities.end(); it2++) 
			{
				if ((*it) != (*it2))
				{
					
					if (((*it)->getRect().intersects((*it2)->getRect())))
					{
						
						if ((*it)->stateenemy == (*it)->left)
						{
							//(*it)->stateenemy = (*it)->rigth;
							//(*it2)->stateenemy = (*it2)->left;
							
						}
						else if ((*it)->stateenemy == (*it)->rigth)
						{
							//(*it)->stateenemy = (*it)->left;
							//(*it2)->stateenemy = (*it2)->rigth;
							
						}
						/*
						if ((*it)->stateenemy == (*it)->left)
						{
							(*it2)->stateenemy = (*it2)->rigth;
							//(*it2)->x = (*it2)->x + 2;
						}
						else if ((*it)->stateenemy == (*it)->rigth)
						{
							(*it2)->stateenemy = (*it2)->left;
							//(*it2)->x = (*it2)->x - 2;
						}
						*/
						
						//(*it)->dx = -(*it)->dx;
						//(*it)->sprite.scale(-1, 1);
						//(*it2)->dx = -(*it2)->dx;
						//(*it2)->sprite.scale(-1, 1);
					}
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "Bullet") && ((*it2)->name == "EasyEnemy"))
					{
						(*it2)->health = 0;
					}
				}
			}
		}
	}

	void Update(float time, float gameTime)
	{
		lifeBarPlayer.update(p->health);
		p->update(time);
		for (auto it = entities.begin(); it != entities.end();)
		{
			Entity *b = *it;
			b->update(time);
			if (b->life == false) { it = entities.erase(it); delete b; }
			else it++;
		}
		Collisions(entities, time, p, gameTime);
	}

	void Draw(RenderWindow& window)
	{
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			window.draw((*it)->sprite);
		}
		window.draw(p->sprite);
		lifeBarPlayer.draw(window);
		window.display();
	}

	~InitializeData()
	{
		delete p;
	}

};

bool startGame(RenderWindow &window, int &numberLevel) 
{
	
	InitializeData data(numberLevel);
	return data.DoGameLoop(window, numberLevel);
	
}

void gameRunning(RenderWindow & window, int & numberLevel) 
{//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) 
	{ 
		gameRunning(window, numberLevel); 
	}//принимает с какого уровня начать игру
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}