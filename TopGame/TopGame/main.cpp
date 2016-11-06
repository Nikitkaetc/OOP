#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

#include "game.h"

using namespace sf;
using namespace std;

bool StartGame(RenderWindow &window, int &numberLevel, Music & music_menu, GameMode & gameMode)
{

	Game Game(window, numberLevel);
	return Game.DoGameLoop(window, numberLevel, music_menu, gameMode);
	
}

void GameRunning(RenderWindow &window, int &numberLevel, Music & music_menu, GameMode & gameMode)
{
	if (StartGame(window, numberLevel, music_menu, gameMode))
	{ 
		GameRunning(window, numberLevel, music_menu, gameMode);
	}
}

int main()
{
	RenderWindow window(VideoMode(1366, 768), "Game", Style::Fullscreen);
	int numberLevel = 1;
	Music music_menu;
	GameMode gameMode = GameMode::Menu;
	try
	{
		GameRunning(window, numberLevel, music_menu, gameMode);
	}
	catch (const invalid_argument &err)
	{
		cout << err.what() << endl;
		return 1;
	}
	return 0;
}