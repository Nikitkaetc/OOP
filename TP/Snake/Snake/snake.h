#pragma once
#include "map.h"
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;



class Snake
{
private:
	int size;
	vector<Vector2i> parts;
	enum Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};
	Direction dir;
	Direction dirPast;
	Texture texture;
	Sprite sprite;
public:
	Snake();
	void Tick();
	void AddNewSnakePart();
	void Update();
	void ProcessEvents(RenderWindow & window);
	void DrawSnake(RenderWindow & window);
	void ResetSnake();
	int ReturnSize();
	bool CheckGameOver();
	vector<Vector2i> ReturnParts();
};