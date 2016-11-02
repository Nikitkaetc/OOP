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

	Game Game(window, numberLevel);
	return Game.DoGameLoop(window, numberLevel, music_menu);
	
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
	RenderWindow window(VideoMode(1366, 768), "Game", Style::Fullscreen);
	Music music_menu;
	Menu(window, music_menu);
	int numberLevel = 1;
	try
	{
		GameRunning(window, numberLevel, music_menu);
	}
	catch (const invalid_argument &err)
	{
		cout << err.what() << endl;
		return 1;
	}
	return 0;
}