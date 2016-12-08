#pragma once
#include <SFML/Graphics.hpp>

const static int WIDTH = 640;
const static int HEIGHT = 480;
const static int STEP = 32;

const static sf::String TILEMAP[HEIGHT / STEP] =
{
	"00000000000000000000",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"0                  0",
	"00000000000000000000",
};

void DrawMap(sf::RenderWindow &window, sf::Sprite &fieldSprite, sf::Sprite &blockSprite);