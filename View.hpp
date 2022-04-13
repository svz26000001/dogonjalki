#include <SFML/Graphics.hpp>
sf::View view;

void checkingCoord (float x, float y) {
	float tempX = x, tempY = y;

	if (x < 320)tempX = 320;
	if (y < 320)tempY = 320;
	if (y > 640)tempY = 640;
	
	view.setCenter(tempX, tempY);
}