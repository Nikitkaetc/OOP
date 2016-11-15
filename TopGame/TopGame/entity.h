#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "level.h"

using namespace sf;
using namespace std;

class Entity 
{
public:
	vector<Object> obj;
	Vector2f velocity;
	Vector2f position;
	Vector2i size;
	float speed;
	float currentFrame;
	int health;
	int goingSide;
	int damage;
	bool alive;
	bool isOnGroud;
	bool shouldDisppear;
	enum state
	{
		right, left, stay, hit, jump, bulletleft, bulletright
	};
	state state;
	Texture texture;
	Sprite sprite;
	String name;

	Entity(Image &image, String Name, float X, float Y, int W, int H);
	FloatRect GetRect();
	virtual void Update(float time) = 0;
};