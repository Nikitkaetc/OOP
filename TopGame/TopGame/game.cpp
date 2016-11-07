#include "game.h"

Game::Game(RenderWindow& window, int& numberLevel)
{
	view.reset(FloatRect(0, 0, 1366, 768));
	
	ChangeLevel(window, lvl, numberLevel);

	heroImage.loadFromFile("images/IronMan.png");
	heroImage.createMaskFromColor(Color(186, 254, 202));

	easyEnemyImage.loadFromFile("images/CaptainAmerica.png");
	easyEnemyImage.createMaskFromColor(Color(186, 254, 202));

	hardEnemyImage.loadFromFile("images/bulleter.png");
	hardEnemyImage.createMaskFromColor(Color(255, 0, 255));

	bulletImage.loadFromFile("images/bullet.png");
	bulletImage.createMaskFromColor(Color(255, 0, 255));

	appleImage.loadFromFile("images/map1.png");

	Object player = lvl.GetObject("player");
	std::list<Entity*>::iterator it;
	std::list<Entity*>::iterator it2;

	p = new Player(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 56);

	std::vector<Object> easy_enemy = lvl.GetObjects("easyEnemy");
	for (int i = 0; i < easy_enemy.size(); i++)
	{
		entities.push_back(new Enemy(easyEnemyImage, "easy_enemy", lvl, easy_enemy[i].rect.left, easy_enemy[i].rect.top, 39, 61));
	}
	std::vector<Object> hard_enemy = lvl.GetObjects("hardEnemy");
	for (int i = 0; i < hard_enemy.size(); i++)
	{
		entities.push_back(new Enemy(hardEnemyImage, "hard_enemy", lvl, hard_enemy[i].rect.left, hard_enemy[i].rect.top, 44, 62));
	}
	std::vector<Object> apple = lvl.GetObjects("heal");
	for (int i = 0; i < apple.size(); i++)
	{
entities.push_back(new ObjectsMap(appleImage, "apple", lvl, apple[i].rect.left, apple[i].rect.top, 32, 32));
	}
	isMenu = true;
}

bool Game::DoGameLoop(RenderWindow& window, int& numberLevel, Music & music_menu, GameMode & gameMode)
{
	float gameTime = 0;
		while (window.isOpen())
		{
			auto time = clock.getElapsedTime().asMicroseconds();
			gameTime += clock.getElapsedTime().asSeconds();
			clock.restart();
			time = time / 800;
			switch (gameMode)
			{
			case GameMode::Play:
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
					if ((!p->oneShot) && (p->isShot))
					{
						p->oneShot = true;
						entities.push_back(new Bullet(bulletImage, "Bullet", lvl, p->x, p->y, 32, 30, p->state));
					}
				}
				if (p->x > 3790)
				{
					lvl.levelNumber++; numberLevel++; return true;
				}
				if (p->y > 900)
				{
					p->life = false;
				}
				if (p->life == false)
				{
					gameMode = GameMode::GameOver;
					isNeedRestartMusic = true;
					return true;
				}
				if (numberLevel == 3)
				{
					numberLevel = 1;
					gameMode = GameMode::GameOver;
					isNeedRestartMusic = true;
					return true;
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					return false;
				}

				Update((float)time, gameTime);
				Draw(window,gameMode);
				if (isNeedRestartMusic)
				{
					music_menu.openFromFile("music/game.ogg");
					music_menu.setVolume(10);
					music_menu.play();
					music_menu.setLoop(true);
					isNeedRestartMusic = false;
				}
				break;
			case GameMode::Menu:
				if (isNeedRestartMusic)
				{
					music_menu.openFromFile("music/menu.ogg");
					music_menu.setVolume(10);
					music_menu.play();
					music_menu.setLoop(true);
					isNeedRestartMusic = false;
				}
				Draw(window,gameMode);
				break;
			case GameMode::GameOver:
				if (isNeedRestartMusic)
				{
					music_menu.openFromFile("music/gameover.ogg");
					music_menu.setVolume(10);
					music_menu.play();
					music_menu.setLoop(true);
					isNeedRestartMusic = false;
				}
				Draw(window, gameMode);
				break;
			}
		}
		return true;
}

void Game::ChangeLevel(RenderWindow& window, Level &lvl, int &numberLevel) {
	if (numberLevel == 1) 
	{
		lvl.LoadFromFile("map/map1.tmx"); 
	}
	if (numberLevel == 2)
	{ 
		lvl.LoadFromFile("map/map2.tmx");
	}
	if (numberLevel == 3) 
	{ 
		lvl.LoadFromFile("map/map2.tmx");
	}
}

void Game::EnemyColiisions(Entity & it, float gameTime)
{
	if (it.GetRect().intersects(p->GetRect()))
	{
		if ((it.name == "easy_enemy") || (it.name == "hard_enemy"))
		{
			if (gameTime > p->lastDamageTime + 1)
			{
				if ((!p->isHit) && (it.state == it.hit))
				{
					p->sound_damage.play();
					p->health -= it.damage;
					p->lastDamageTime = gameTime;
					p->sprite.setColor(Color::Red);
				}
			}
			if (p->isHit)
			{
				p->sound_enemydamage.play();
				it.health = 0;
				p->isHit = false;
			}
		}
		if (it.name == "apple")
		{
			if (p->health <= 80)
			{
				p->sound_bonus.play();
				p->health += 10;
				it.health = 0;
			}
		}
	}
}

void Game::Collisions(list<Entity*> & entities, const float& time, Player* p, float gameTime)
{
	if (!p)
	{
		throw(invalid_argument("Player = nullptr"));
	}
	else
	{
		for (auto &entity: entities)
		{
			EnemyColiisions(*entity, gameTime);
			if ((entity->x < p->x + 30) && (entity->x > p->x - 30) && (entity->y < p->y + 7) && (entity->y > p->y - 7))
			{
				entity->state = entity->hit;
			}

			else if ((entity->x < p->x) && (entity->state == entity->hit))
			{
				entity->state = entity->right;
				entity->goingSide = 2;
			}
			else if ((entity->x > p->x) && (entity->state == entity->hit))
			{
				entity->state = entity->left;
				entity->goingSide = 1;
			}
			if (gameTime > p->lastDamageTime + 0.5)
			{
				p->sprite.setColor(Color::White);
			}
			for (auto &entity2 : entities)
			{
				if ((entity->name == "Bullet") && (((entity2)->name == "easy_enemy") || ((entity2)->name == "hard_enemy")))
				{
					if (entity->GetRect().intersects(entity2->GetRect()))
					{
						entity->dead = true;
						entity2->life = false;
					}
				}
			}
		}
	}
}

void Game::Update(float time, float gameTime)
{
	lifeBarPlayer.Update(p->health);
	p->Update(time);
	SetPlayerCoordinateForView(p->x, p->y);
	for (auto it = entities.begin(); it != entities.end();)
	{
		Entity *b = *it;
		b->Update(time);
		if (b->life == false)
		{
			it = entities.erase(it); delete b;
		}
		else it++;
	}
	Collisions(entities, time, p, gameTime);
}

void Game::Draw(RenderWindow& window, GameMode & gameMode)
{
	switch (gameMode)
	{case GameMode::Play:
		window.setView(view);
		window.clear(Color(77, 83, 140));
		lvl.Draw(window);
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			window.draw((*it)->sprite);
		}
		window.draw(p->sprite);
		lifeBarPlayer.Draw(window);
		break;
	case GameMode::Menu:
		menuGame.Draw(window, isMenu);
		if (isMenu == false)
		{
			gameMode = GameMode::Play;
			isNeedRestartMusic = true;
		}
		break;
	case GameMode::GameOver:
		menuGame.DrawGameOver(window, isMenu);
		if (isMenu == false)
		{
			gameMode = GameMode::Play;
			isNeedRestartMusic = true;
		}
		break;
	}
	window.display();
}

void Game::SetPlayerCoordinateForView(float x, float y) 
{
	float tempX = x; float tempY = y;
	if (x < 683) tempX = 683;
	if (x > 3127) tempX = 3127;
	if (y > 576) tempY = 576;
	if (y < 384) tempY = 384;

	view.setCenter(tempX, tempY);
}

Game::~Game()
{
	delete p;
}