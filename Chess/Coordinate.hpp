#pragma once
#include <SFML/System.hpp>

struct Coordinate
{
	int xPosition = 0;
	int yPosition = 0;
	bool valid = false;

	sf::Vector2f getVector2f() const;
};