#include "pendulum.h"

Pendulum::Pendulum()
{
	firstWheel.texture.loadFromFile("resources/detail.png");
	secondWheel.texture = firstWheel.texture;
	firstWheel.sprite.setTexture(firstWheel.texture);
	secondWheel.sprite.setTexture(firstWheel.texture);

	float wheelRadius = firstWheel.sprite.getGlobalBounds().width / 2;
	firstWheel.sprite.setPosition(FIRST_WHEEL_POS);
	firstWheel.sprite.setOrigin(wheelRadius, wheelRadius);
	firstWheel.rotation = 0;
	secondWheel.sprite.setPosition(SECOND_WHEEL_POS);
	secondWheel.sprite.setOrigin(wheelRadius, wheelRadius);
	secondWheel.rotation = 0;
	speed = 0;
	rotation = START_ROTATION;
	turn.setPointCount(4);
	turn.setPoint(0, sf::Vector2f(0, 200));
	turn.setPoint(1, sf::Vector2f(100, 100));
	turn.setPoint(2, sf::Vector2f(200, 200));
	turn.setPoint(3, sf::Vector2f(100, 100));
	turn.setFillColor(Color::Black);
	turn.setOrigin(100, 100);
	turn.setPosition(PENDULUM_POS);
	weight.setPointCount(5);
	weight.setPoint(0, sf::Vector2f(100, 100));
	weight.setPoint(1, sf::Vector2f(120, 400));
	weight.setPoint(2, sf::Vector2f(160, 440));
	weight.setPoint(3, sf::Vector2f(40, 440));
	weight.setPoint(4, sf::Vector2f(80, 400));
	weight.setFillColor(Color::Black);
	weight.setOrigin(100, 100);
	weight.setPosition(PENDULUM_POS);
};

void Pendulum::UpdatePendulum()
{
	weight.setRotation(rotation);
	turn.setRotation(rotation);
	firstWheel.sprite.setRotation(firstWheel.rotation);
	secondWheel.sprite.setRotation(secondWheel.rotation);
};

void Pendulum::Physics()
{
	if (rotation > 0)
	{
		speed -= ACCELERATION;
	}
	else speed += ACCELERATION;

	rotation += speed;
	firstWheel.rotation += speed / 2.f;
	secondWheel.rotation = -firstWheel.rotation;
};

void Pendulum::Draw(RenderWindow & window)
{
	window.draw(weight);
	window.draw(turn);
	window.draw(firstWheel.sprite);
	window.draw(secondWheel.sprite);
};