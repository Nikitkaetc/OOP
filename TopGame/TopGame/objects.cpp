#include "objects.h"

ObjectsMap::ObjectsMap(Image &image, String Name, Level &lvl, float X, float Y, int W, int H) 
	:Entity(image, Name, X, Y, W, H) 
{
	if (name == "apple")
	{
		sprite.setTextureRect(IntRect(32, 128, size.x, size.y));
		sprite.setOrigin((float)size.x / 2.f, (float)size.y / 2.f);
	}
}


void ObjectsMap::Update(float time)
{
	sprite.setPosition(position.x + size.x / 2, position.y + size.y / 2);
	if (health <= 0) 
	{ 
		alive = false; 
	}
}
