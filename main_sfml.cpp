//#pragma comment(lib, "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\SFML-2.5.1\lib")
#include <SFML/Graphics.hpp>

int main2()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Lesson 1. kychka-pc.ru");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}