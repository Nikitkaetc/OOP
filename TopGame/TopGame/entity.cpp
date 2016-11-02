#include "entity.h"

Entity::Entity(Image &image, String Name, float X, float Y, int W, int H) 
{
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0; health = 100; dx = 0; dy = 0;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

FloatRect Entity::GetRect()
{
	return FloatRect(x, y, w, h);
}