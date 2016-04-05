#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 320) tempX = 320;
	if (x > 1250) tempX = 1250;
	if (y > 624) tempY = 624;

	view.setCenter(tempX, tempY);
}