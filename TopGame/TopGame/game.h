#pragma once
#include <list>

#include "level.h"
#include "player.h"
#include "enemy.h"
#include "objects.h"
#include "menu.h"
#include "LifeBar.h"
#include "bullet.h"

using namespace std;
using namespace sf;

class Game
{
private:
	Level lvl;
	Image heroImage;
	Image easyEnemyImage;
	Image hardEnemyImage;
	Image bulletImage;
	Image appleImage;
	vector<Object> bullet;
	Player *p;
	list<Entity*>  entities;
	vector<Object> apples;
	Clock clock;
	LifeBar lifeBarPlayer;
	View view;

	void ChangeLevel(RenderWindow& window, Level &lvl, int &numberLevel);
	void EnemyColiisions(Entity *it, float gameTime);
	void Collisions(list<Entity*>& entities, const float& time, Player* p, float gameTime);
	void Update(float time, float gameTime);
	void Draw(RenderWindow& window);
	void SetPlayerCoordinateForView(float x, float y);

public:
	Game(RenderWindow& window, int& numberLevel);
	bool DoGameLoop(RenderWindow& window, int& numberLevel, Music& music_menu);

	~Game();
};