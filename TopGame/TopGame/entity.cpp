#include "entity.h"

Entity::Entity(Image &image, String Name, float X, float Y, int W, int H) 
{
	x = X; y = Y; w = W; h = H; name = Name;
	speed = 0; health = 100; dx = 0; dy = 0;
	dead = false;
	life = true; onGround = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin((float)w / 2.f, (float)h / 2.f);
}

FloatRect Entity::GetRect()
{
	return FloatRect((float)x, (float)y, (float)w, (float)h);
}