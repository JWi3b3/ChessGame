#include "Chessboard.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(50);

	Chessboard chessboard("Images", window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		auto mousePos = sf::Mouse::getPosition(window);
		bool lmbDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
		chessboard.setMouse(mousePos.x, mousePos.y, lmbDown);

		window.clear();
		chessboard.draw();
		window.display();
	}

	return 0;
}