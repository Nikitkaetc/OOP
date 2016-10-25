#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "entity.h"

using namespace sf;

class Player :public Entity {
public: 
	float lastDamageTime;

	Player(Image &image, String Name, Level &lvl, float X, float Y, int W, int H);

	void Animation(float time);
	void Control(float time);
	void CheckCollisionWithMap(float Dx, float Dy);
	void update(float time);
	void SoundPlayer(float time);
};