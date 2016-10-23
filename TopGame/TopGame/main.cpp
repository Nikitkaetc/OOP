#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

#include "game.h"
//Улучшение кода(Player update).Объединить menu and menugameover. Оптимизация. - баги(типа меню), все красиво(дедлайн)! 
using namespace sf;
using namespace std;

bool startGame(RenderWindow &window, int &numberLevel) 
{
	
	Game game(window, numberLevel);
	return game.DoGameLoop(window, numberLevel);
	
}

void gameRunning(RenderWindow &window, int &numberLevel) 
{
	if (startGame(window, numberLevel)) 
	{ 
		gameRunning(window, numberLevel); 
	}
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;
	gameRunning(window, numberLevel);
	return 0;
}