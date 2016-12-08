#pragma once
#include <SFML/Graphics.hpp>
#include "snake.h"
#include "apple.h"

using namespace std;
using namespace sf;

const static int TIME_STEP = 200;

enum class GameMode
{
	MENU,
	PLAY,
	END
};

class Game
{
private:
	int current;
	Font font;
	Text text;
	float time;
	Texture texture;
	Sprite fieldSprite;
	Sprite blockSprite;
	Clock clock;
	Snake snake;
	Apple apple;
	ostringstream playerScoreString;
	bool score;
	vector<Vector2i> parts;
public:
	Game(RenderWindow &window);
	void DoGameLoop(RenderWindow& window, GameMode & gameMode);
};
