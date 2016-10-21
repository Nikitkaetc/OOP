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

//�������� ��� � Update � player. ��������� ����. ������� ��� 2 �����. ���������� �������!
using namespace sf;
using namespace std;

bool startGame(RenderWindow &window, int &numberLevel) 
{
	
	Game game(numberLevel);
	return game.DoGameLoop(window, numberLevel);
	
}

void gameRunning(RenderWindow & window, int & numberLevel) 
{//�-��� ������������� ���� , ���� ��� ����������
	if (startGame(window, numberLevel)) 
	{ 
		gameRunning(window, numberLevel); 
	}//��������� � ������ ������ ������ ����
}
int main()
{
	RenderWindow window(VideoMode(640, 480), "Game");
	menu(window);
	int numberLevel = 1;//������� 1-�� �������
	gameRunning(window, numberLevel);
	return 0;
}