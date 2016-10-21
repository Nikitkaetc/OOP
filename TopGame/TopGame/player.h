#pragma once
#include <SFML\Graphics.hpp>
#include "entity.h"

using namespace sf;

class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, hit } state;// ¿œ—
	int playerScore; 
	float CurrentFrame;
	bool isShot, tolchok, isHit, isRigth;
	float lastDamageTime;

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H);
	void animation(float time);
	void control(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	void update(float time);
};