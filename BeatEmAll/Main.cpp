#include <iostream>

#include "SFML\Graphics.hpp"

int main()
{
	sf::RenderWindow rw(sf::VideoMode(500, 500), "SFML Works! YAY!");

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (rw.isOpen())
	{
		sf::Event event;
		while(rw.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				rw.close();
		}

		rw.clear();
		rw.draw(shape);
		rw.display();
	}

	return 0;
}