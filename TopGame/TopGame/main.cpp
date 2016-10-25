#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

#include "game.h"

using namespace sf;
using namespace std;

bool StartGame(RenderWindow &window, int &numberLevel, Music& music_menu)
{

	Game game(window, numberLevel);
	return game.DoGameLoop(window, numberLevel, music_menu);
	
}

void GameRunning(RenderWindow &window, int &numberLevel, Music& music_menu)
{
	if (StartGame(window, numberLevel, music_menu))
	{ 
		GameRunning(window, numberLevel, music_menu);
	}
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	Music music_menu;
	menu(window, music_menu);
	int numberLevel = 1;
	GameRunning(window, numberLevel, music_menu);
	return 0;
}