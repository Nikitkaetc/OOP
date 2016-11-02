#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"

using namespace std;
using namespace sf;

class Enemy :public Entity 
{
public:
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);

private:
	void CheckCollisionWithMap(float Dx, float Dy);
	void AnimationEasyEnemy(float time);
	void AnimationHardEnemy(float time);
	void Update(float time);
};