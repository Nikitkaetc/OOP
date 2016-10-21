#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include "TinyXML/tinyxml.h"

//#include "level.h"
//#include "menu.h"
//#include "entity.h"
//#include "player.h"
//#include "enemy.h"
//#include "bullet.h"
#include "game.h"

//#include "LifeBar.h"

//Улучшить код с Update в player. Улучшение кода. Создать еще 2 карты. Подбирание объекта!
using namespace sf;
using namespace std;

bool startGame(RenderWindow &window, int &numberLevel) 
{
	
	Game game(numberLevel);
	return game.DoGameLoop(window, numberLevel);
	
}

void gameRunning(RenderWindow & window, int & numberLevel) 
{//ф-ция перезагружает игру , если это необходимо
	if (startGame(window, numberLevel)) 
	{ 
		gameRunning(window, numberLevel); 
	}//принимает с какого уровня начать игру
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;//сначала 1-ый уровень
	gameRunning(window, numberLevel);
	return 0;
}