#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

#include "game.h"

using namespace sf;
using namespace std;

bool StartGame(RenderWindow &window, int &numberLevel) 
{
	
	Game game(window, numberLevel);
	return game.DoGameLoop(window, numberLevel);
	
}

void GameRunning(RenderWindow &window, int &numberLevel) 
{
	if (StartGame(window, numberLevel)) 
	{ 
		GameRunning(window, numberLevel); 
	}
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;
	GameRunning(window, numberLevel);
	return 0;
}