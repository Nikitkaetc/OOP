#include "game.h"

Game::Game(int& numberLevel)
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

	appleImage.loadFromFile("images/map1.png");

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
	std::vector<Object> apple = lvl.GetObjects("heal");
	for (int i = 0; i < apple.size(); i++)
	{
		entities.push_back(new ObjectsMap(appleImage, "apple", lvl, apple[i].rect.left, apple[i].rect.top, 32, 32));
	}

	//apples = lvl.GetObjects("heal");
	//for (int i = 0; i < apples.size(); i++)
	//{
	//	apples[i].sprite.setTexture(appleTexture);
	//	apples[i].sprite.setPosition(apples[i].rect.left, apples[i].rect.top);
	//}

}

bool Game::DoGameLoop(RenderWindow& window, int& numberLevel)
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

void Game::ChangeLevel(Level &lvl, int &numberLevel) {
	if (numberLevel == 1) { lvl.LoadFromFile("map2.tmx"); }
	if (numberLevel == 2) { lvl.LoadFromFile("map.tmx"); }
	if (numberLevel == 3) { lvl.LoadFromFile("map.tmx"); }
}

void Game::EnemyColiisions(Entity *it, float gameTime)
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
		if ((it)->name == "apple")
		{
			if (p->health <= 90)
			{
				p->health += 10;
				(it)->health = 0;
			}
		}
	}
}

void Game::Collisions(list<Entity*>& entities, const float& time, Player* p, float gameTime)
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

void Game::Update(float time, float gameTime)
{
	lifeBarPlayer.update(p->health);
	p->update(time);
	setPlayerCoordinateForView(p->x, p->y);
	for (auto it = entities.begin(); it != entities.end();)
	{
		Entity *b = *it;
		b->update(time);
		if (b->life == false) { it = entities.erase(it); delete b; }
		else it++;
	}
	Collisions(entities, time, p, gameTime);
}

void Game::Draw(RenderWindow& window)
{
	window.setView(view);
	window.clear(Color(77, 83, 140));
	lvl.Draw(window);
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		window.draw((*it)->sprite);
	}
	//for (auto apple : apples)
	//{
	//	if (apple.GetPropertyInt("isTaken") == 0)
	//	{
	//		appleSprite.setPosition(apple.rect.left, apple.rect.top);
	//		window.draw(appleSprite);
	//	}
	//}
	window.draw(p->sprite);
	lifeBarPlayer.draw(window);
	window.display();
}

void Game::setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 320) tempX = 320;
	if (x > 3490) tempX = 3490;
	if (y > 720) tempY = 720;

	view.setCenter(tempX, tempY);
}

Game::~Game()
{
	delete p;
}
