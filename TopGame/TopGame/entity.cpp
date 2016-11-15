#include "entity.h"

Entity::Entity(Image &image, String Name, float X, float Y, int W, int H) 
{

	position.x = X; position.y = Y; size.x = W; size.y = H; name = Name;
	speed = 0; health = 100; velocity.x = 0; velocity.y = 0;
	shouldDisppear = false;
	alive = true; isOnGroud = false;
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin((float)size.x / 2.f, (float)size.y / 2.f);
}

FloatRect Entity::GetRect()
{
	return FloatRect(position.x, position.y, (float)size.x, (float)size.y);
}