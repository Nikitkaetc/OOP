#include "snake.h"
#include <iostream>


Snake::Snake()
{
	size = 1;
	Vector2i part;
	part = { 9 * STEP, 7 * STEP };
	parts.push_back(part);
	dir = NONE;
	dirPast = NONE;
	texture.loadFromFile("texture.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(64, 0, 32, 32));
}

void Snake::Tick()
{
	if (size < parts.size())
	{
		if (parts[size - 1] == parts[parts.size() - 1])
			size += 1;
	}
	for (int i = size - 1; i > 0; i--)
	{
		parts[i] = parts[i - 1];
	}
}

vector<Vector2i> Snake::ReturnParts()
{
	return parts;
}

void Snake::AddNewSnakePart()
{
	Vector2i part = parts[parts.size() - 1];
	parts.push_back(part);
}

void Snake::Update()
{
	switch (dir)
	{
	case UP:
		parts[0].y -= STEP;
		break;
	case DOWN:
		parts[0].y += STEP;
		break;
	case LEFT:
		parts[0].x -= STEP;
		break;
	case RIGHT:
		parts[0].x += STEP;
		break;
	case NONE:
		break;
	}
	dirPast = dir;
}

void Snake::ProcessEvents(RenderWindow & window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && dirPast != RIGHT)
		{
			dir = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && dirPast != LEFT)
		{
			dir = RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && dirPast != DOWN)
		{
			dir = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && dirPast != UP)
		{
			dir = DOWN;
		}
		if (event.type == Event::Closed)
			window.close();
	}
}

void Snake::DrawSnake(RenderWindow & window)
{
	for (int i = 0; i < size; i++)
	{
		sprite.setPosition(float(parts[i].x), float(parts[i].y));
		window.draw(sprite);
	}
}

void Snake::ResetSnake() 
{
	parts.clear();
	size = 1;

	Vector2i part;
	part.x = 9 * STEP; 
	part.y = 7 * STEP;

	parts.push_back(part);
	dir = NONE;
	dirPast = NONE;
}


bool Snake::CheckGameOver()
{
	if (TILEMAP[parts[0].y / STEP][parts[0].x / STEP] == '0')
	{
		return true;
	}
	else
		for (int i = 1; i < size; i++)
			if (parts[0] == parts[i])
			{
				return true;
				break;
			}
	return false;
}

int Snake::ReturnSize()
{
	return size;
}