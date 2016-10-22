#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"


using namespace std;
using namespace sf;

class ObjectsMap :public Entity {
public:
	ObjectsMap(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);

	void update(float time);
};