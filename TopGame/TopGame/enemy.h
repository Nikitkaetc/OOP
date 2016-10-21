#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"
//#include "level.h"
//#include "bullet.h"

using namespace std;
using namespace sf;

class Enemy :public Entity {
public:
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);

	void checkCollisionWithMap(float Dx, float Dy);
	void animationCA(float time);
	void animationBulleter(float time);
	void update(float time);
};