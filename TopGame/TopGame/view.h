#include <SFML/Graphics.hpp>
using namespace sf;

sf::View view;

void setPlayerCoordinateForView(float x, float y) {
	float tempX = x; float tempY = y;

	if (x < 320) tempX = 320;
	if (x > 3490) tempX = 3490;
	if (y > 720) tempY = 720;

	view.setCenter(tempX, tempY);
}