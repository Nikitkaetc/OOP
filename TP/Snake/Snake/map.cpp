#include "map.h"

void DrawMap(sf::RenderWindow &window, sf::Sprite &fieldSprite, sf::Sprite &blockSprite)
{
	for (int i = 0; i * STEP < HEIGHT; i += 1)
	{
		for (int j = 0; j * STEP < WIDTH; j += 1)
		{
			if (TILEMAP[i][j] == ' ')
			{
				fieldSprite.setPosition(float(j * STEP), float(i * STEP));
				window.draw(fieldSprite);
			}
			else if (TILEMAP[i][j] == '0')
			{
				blockSprite.setPosition(float(j * STEP), float(i * STEP));
				window.draw(blockSprite);
			}
		}
	}
}