#pragma once

#include "FigureType.hpp"
#include "Position.hpp"
#include "Coordinate.hpp"
#include "ChessFigure.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>


class Chessboard
{
public:
	Chessboard(std::string imgPath, sf::RenderWindow& window);

	void createStartSetup();
	void setMouse(int xPos, int yPos, bool lmbDown);
	void move(Position positionStart, Position positionEnd);
	void draw();

private:
	void _loadImages(std::string imgPath);
	Coordinate _getCoordinateForPosition(Position position);
	bool _isPositionBlack(Position position);

	std::unordered_map<Figure, sf::Texture> _texturesFigures;
	sf::Texture _textureChessfieldBlack;
	sf::Texture _textureChessfieldWhite;
	sf::RenderWindow& _window;
	std::vector<std::unique_ptr<ChessFigure>> _figures;

	int const fieldWidth = 66;
	int const fieldOffsetTop = 20;
	int const fieldOffsetLeft = 20;

	Coordinate _currentMouseCoord;
	Position _currentMousePosition;
	Position _selectedStart;
	Position _selectedEnd;
	bool _startIsSelected;
	bool _lmbDown;
};

