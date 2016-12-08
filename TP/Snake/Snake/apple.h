#pragma once


#include <SFML/Graphics.hpp>
#include "snake.h"

using namespace sf;



class Apple
{
private:
	Vector2i pos;
	Texture texture;
	Sprite sprite;
	Snake snake;
	vector<Vector2i> parts;
public:
	Apple();
	void SpawnNewApple(vector<Vector2i> &parts);
	bool CheckEventApple(vector<Vector2i> &parts);
	void DrawApple(RenderWindow & window);
};