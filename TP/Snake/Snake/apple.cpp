#include <iostream>
#include "apple.h"


Apple::Apple()
{
	texture.loadFromFile("texture.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(96, 0, 32, 32));
	
}

void Apple::SpawnNewApple(vector<Vector2i> &parts)
{
	
	Vector2i place;
	bool isPlaceFound;
	isPlaceFound = true;
	do
	{
		place.x = (rand() % (WIDTH / STEP));
		place.y = (rand() % (HEIGHT / STEP));
		isPlaceFound = true;

		if (TILEMAP[place.y][place.x] == '0')
		{
			isPlaceFound = false;
		}

		else
			for (int i = 0; i != parts.size(); i++)
				if (parts[i].x == (place.x * STEP) && parts[i].y == (place.y * STEP))
				{
					isPlaceFound = false;
					break;
				}

	} while (isPlaceFound == false);

	pos = { place.x * STEP, place.y * STEP };

	sprite.setPosition(float(place.x * STEP), float(place.y * STEP));
};

bool Apple::CheckEventApple(vector<Vector2i> &parts)
{
	Vector2i posApple;

	posApple.x = int(sprite.getPosition().x);
	posApple.y = int(sprite.getPosition().y);

	Vector2i head;
	head = parts[0];

	
	if (head == posApple)
	{
		SpawnNewApple(parts);
		return true;
	}
	return false;
}


void Apple::DrawApple(RenderWindow & window)
{
	window.draw(sprite);
}