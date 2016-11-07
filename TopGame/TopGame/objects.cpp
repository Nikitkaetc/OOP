#include "objects.h"

ObjectsMap::ObjectsMap(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) 
	:Entity(image, Name, X, Y, W, H) 
{
	if (name == "apple")
	{
		sprite.setTextureRect(IntRect(32, 128, w, h));
		sprite.setOrigin((float)w / 2.f, (float)h / 2.f);
	}
}


void ObjectsMap::Update(float time)
{
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0) 
	{ 
		life = false; 
	}
}
