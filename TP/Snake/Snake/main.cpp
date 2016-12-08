#include <SFML/Graphics.hpp>
#include "game.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Snake");
	GameMode gameMode = GameMode::MENU;
	Game Game(window);
	Game.DoGameLoop(window, gameMode);
	return 0;
}
