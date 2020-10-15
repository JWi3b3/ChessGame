#include "Coordinate.hpp"

sf::Vector2f Coordinate::getVector2f() const
{
	sf::Vector2f vec;

	vec.x = this->xPosition;
	vec.y = this->yPosition;

	return vec;
}
