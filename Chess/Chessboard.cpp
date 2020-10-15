#include "Chessboard.hpp"

#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

Chessboard::Chessboard(std::string imgPath, sf::RenderWindow& window) :
	_window(window)
{
	_loadImages(imgPath);
	createStartSetup();

}

void Chessboard::createStartSetup()
{
	// vec.emplace_back(new Derived())
}

void Chessboard::setFigure(Position position, Figure figure)
{
	_board[static_cast<int>(position)] = figure;
}

Figure Chessboard::getFigure(Position position) const
{
	return _board[static_cast<int>(position)];
}

void Chessboard::setMouse(int xPos, int yPos, bool lmbDown)
{
	_currentMouseCoord.xPosition = xPos;
	_currentMouseCoord.yPosition = yPos;

	bool clicked = false;
	if (!lmbDown && _lmbDown)
	{
		clicked = true;
	}
	_lmbDown = lmbDown;

	for (int i = 0; i < 64; i++)
	{
		auto currentPosition = static_cast<Position>(i);
		auto coord = _getCoordinateForPosition(currentPosition);

		if (xPos > coord.xPosition && xPos <= coord.xPosition + fieldWidth
			&& yPos > coord.yPosition && yPos <= coord.yPosition + fieldWidth)
		{
			_currentMousePosition = currentPosition;
			break;
		}
	}


	if (clicked && !_startIsSelected && getFigure(_currentMousePosition) != Figure::Empty)
	{
		_selectedStart = _currentMousePosition;
		_startIsSelected = true;
	}

	else if (_startIsSelected && !clicked)
	{
		_selectedEnd = _currentMousePosition;
	}

	else if (_startIsSelected && clicked)
	{
		move(_selectedStart, _selectedEnd);
		_startIsSelected = false;
		_selectedStart = Position::UNDEFINED;
		_selectedEnd = Position::UNDEFINED;
	}
}

void Chessboard::move(Position positionStart, Position positionGoal)
{
	if (_isValidMove(positionStart, positionGoal))
	{
		auto figure = getFigure(positionStart);
		setFigure(positionGoal, figure);
		setFigure(positionStart, Figure::Empty);
	}
}

void Chessboard::draw()
{
	// draw figures
	for (int i = 0; i < 64; i++)
	{
		Position const currentPosition = static_cast<Position>(i);
		Coordinate const coord = _getCoordinateForPosition(currentPosition);

		// draw chess field
		{
			sf::Sprite tile;
			if (_isPositionBlack(currentPosition))
			{
				tile.setTexture(_textureChessfieldBlack);
			}
			else
			{
				tile.setTexture(_textureChessfieldWhite);
			}

			tile.setScale(sf::Vector2f(0.6, 0.6));
			tile.setPosition(sf::Vector2f(
				coord.xPosition,
				coord.yPosition));
			_window.draw(tile);
		}

		// draw figure
		{
			Figure currentFigure = getFigure(currentPosition);

			if (currentFigure == Figure::Empty)
				continue;

			sf::Sprite tile;
			tile.setTexture(_texturesFigures[currentFigure]);
			tile.setScale(sf::Vector2f(0.6, 0.6));

			tile.setPosition(sf::Vector2f(coord.xPosition, coord.yPosition));
			_window.draw(tile);
		}
	}

	// draw coordinates
	{
		sf::Font font;
		if (!font.loadFromFile("Autumn.ttf"))
		{
			std::cout << "ERROR in Chessboard::draw(): font could not be loaded!" << std::endl;
		}

		std::vector<std::pair<Position, std::string>> elementsNumbers, elementsChars;
		elementsChars.push_back(std::make_pair(Position::A1, "a"));
		elementsChars.push_back(std::make_pair(Position::B1, "b"));
		elementsChars.push_back(std::make_pair(Position::C1, "c"));
		elementsChars.push_back(std::make_pair(Position::D1, "d"));
		elementsChars.push_back(std::make_pair(Position::E1, "e"));
		elementsChars.push_back(std::make_pair(Position::F1, "f"));
		elementsChars.push_back(std::make_pair(Position::G1, "g"));
		elementsChars.push_back(std::make_pair(Position::H1, "h"));

		elementsNumbers.push_back(std::make_pair(Position::A1, "1"));
		elementsNumbers.push_back(std::make_pair(Position::A2, "2"));
		elementsNumbers.push_back(std::make_pair(Position::A3, "3"));
		elementsNumbers.push_back(std::make_pair(Position::A4, "4"));
		elementsNumbers.push_back(std::make_pair(Position::A5, "5"));
		elementsNumbers.push_back(std::make_pair(Position::A6, "6"));
		elementsNumbers.push_back(std::make_pair(Position::A7, "7"));
		elementsNumbers.push_back(std::make_pair(Position::A8, "8"));


		auto addText = [&](std::string text, sf::Vector2f position) {
			sf::Text textElem(text, font);
			textElem.setPosition(position);
			textElem.setCharacterSize(20);
			_window.draw(textElem);
		};

		for (auto const& elem : elementsChars)
		{
			addText(elem.second, _getCoordinateForPosition(elem.first).getVector2f() + sf::Vector2f(30, 70));
		}

		for (auto const& elem : elementsNumbers)
		{
			addText(elem.second, _getCoordinateForPosition(elem.first).getVector2f() + sf::Vector2f(-18, 20));
		}
	}

	// draw mouse cursor
	{
		sf::RectangleShape rect(sf::Vector2f(fieldWidth, fieldWidth));
		rect.setOutlineColor(sf::Color(100, 250, 50, 150));
		rect.setOutlineThickness(-5);
		rect.setPosition(_getCoordinateForPosition(_currentMousePosition).getVector2f());
		rect.setFillColor(sf::Color(0, 0, 0, 0));
		_window.draw(rect);
	}



	// draw selected start and end
	if (_startIsSelected)
	{
		float constexpr radiusStart = 20.f;
		float constexpr radiusEnd = 15.f;

		auto getOffset = [&](float radius) {
			sf::Vector2f offset;
			offset.x = fieldWidth / 2 - radius;
			offset.y = fieldWidth / 2 - radius;
			return offset;
		};

		sf::Color const moveColor = sf::Color(250, 100, 50);

		// start
		if (_selectedStart != Position::UNDEFINED)
		{
			sf::CircleShape circleStart;
			circleStart.setRadius(20.f);
			circleStart.setFillColor(moveColor);
			circleStart.setPosition(_getCoordinateForPosition(_selectedStart).getVector2f() + getOffset(radiusStart));
			_window.draw(circleStart);
		}

		// end
		if (_selectedStart != _selectedEnd && !_lmbDown && _selectedEnd != Position::UNDEFINED)
		{
			sf::CircleShape circleStart;
			circleStart.setRadius(radiusEnd);
			circleStart.setFillColor(moveColor);
			circleStart.setPosition(_getCoordinateForPosition(_selectedEnd).getVector2f() + getOffset(radiusEnd));
			_window.draw(circleStart);
		}

		// arrow from start to end
		if (_selectedStart != _selectedEnd && !_lmbDown && _selectedEnd != Position::UNDEFINED)
		{
			auto sq = [](float value) {return value * value;};
			auto const cS = _getCoordinateForPosition(_selectedStart);
			auto const cE = _getCoordinateForPosition(_selectedEnd);
			float const lengthOfArrow = std::sqrt(sq(cS.xPosition - cE.xPosition) + sq(cS.yPosition - cE.yPosition));

			float const angle = std::atan2(cS.yPosition - cE.yPosition, cS.xPosition - cE.xPosition) + M_PI;

			sf::RectangleShape line;
			line.setSize(sf::Vector2f(lengthOfArrow, 1));
			line.setOutlineThickness(3);
			line.setRotation(angle * 180. / M_PI);
			line.setPosition(cS.getVector2f() + sf::Vector2f(this->fieldWidth / 2., this->fieldWidth / 2.));
			line.setFillColor(moveColor);
			line.setOutlineColor(moveColor);
			_window.draw(line);
		}
	}





}

void Chessboard::_loadImages(std::string imgPath)
{
	_texturesFigures[Figure::WhiteKing].loadFromFile(imgPath + "/WhiteKing.png");
	_texturesFigures[Figure::WhiteQueen].loadFromFile(imgPath + "/WhiteQueen.png");
	_texturesFigures[Figure::WhiteBishop].loadFromFile(imgPath + "/WhiteBishop.png");
	_texturesFigures[Figure::WhiteKnight].loadFromFile(imgPath + "/WhiteKnight.png");
	_texturesFigures[Figure::WhiteRook].loadFromFile(imgPath + "/WhiteRook.png");
	_texturesFigures[Figure::WhitePawn].loadFromFile(imgPath + "/WhitePawn.png");

	_texturesFigures[Figure::BlackKing].loadFromFile(imgPath + "/BlackKing.png");
	_texturesFigures[Figure::BlackQueen].loadFromFile(imgPath + "/BlackQueen.png");
	_texturesFigures[Figure::BlackBishop].loadFromFile(imgPath + "/BlackBishop.png");
	_texturesFigures[Figure::BlackKnight].loadFromFile(imgPath + "/BlackKnight.png");
	_texturesFigures[Figure::BlackRook].loadFromFile(imgPath + "/BlackRook.png");
	_texturesFigures[Figure::BlackPawn].loadFromFile(imgPath + "/BlackPawn.png");

	_textureChessfieldBlack.loadFromFile(imgPath + "/ChessfieldBlack.png");
	_textureChessfieldWhite.loadFromFile(imgPath + "/ChessfieldWhite.png");
}

bool Chessboard::_isValidMove(Position positionStart, Position positionEnd)
{
	if (getFigure(positionStart) == Figure::Empty)
		return false;

	if (_isFigureWhite(getFigure(positionStart)) == _isFigureWhite(getFigure(positionEnd)))
		return false;

	return true;
}

Coordinate Chessboard::_getCoordinateForPosition(Position position)
{
	if (position == Position::UNDEFINED)
	{
		return {};
	}

	int index = static_cast<int>(position);

	int xCoord = index % 8;
	int yCoord = index / 8;

	Coordinate coord;
	coord.xPosition = xCoord * fieldWidth + fieldOffsetLeft;
	coord.yPosition = (7 - yCoord) * fieldWidth + fieldOffsetTop;
	coord.valid = true;
	return coord;
}

bool Chessboard::_isPositionBlack(Position position)
{
	int index = static_cast<int>(position);

	int xCoord = index % 8;
	int yCoord = index / 8;

	return xCoord % 2 == yCoord % 2;
}

bool Chessboard::_isFigureWhite(Figure figure)
{
	if (figure == Figure::WhiteBishop ||
		figure == Figure::WhiteKing ||
		figure == Figure::WhiteKnight ||
		figure == Figure::WhitePawn ||
		figure == Figure::WhiteQueen ||
		figure == Figure::WhiteRook)
		return true;
	else
		return false;
}
