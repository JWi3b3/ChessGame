#include "ChessFigure.hpp"
#include <iostream>


ChessFigure::ChessFigure(FigureType type, FigureColor color, int figureIndex)
{
	_figureType = type;
	_figureColor = color;

	setDefaultPosition(figureIndex);
}

std::vector<Move> ChessFigure::getValidMoves(std::vector<ChessFigure> const& otherFigures)
{
	switch (_figureType)
	{
	case King:
		return _getValidMovesKing(otherFigures);
	case Queen:
		return _getValidMovesQueen(otherFigures);
	case Bishop:
		return _getValidMovesBishop(otherFigures);
	case Knight:
		return _getValidMovesKnight(otherFigures);
	case Rook:
		return _getValidMovesRook(otherFigures);
	case Pawn:
		return _getValidMovesPawn(otherFigures);
	case UNDEFINED:
		return {};
	default:
		return {};
	}
}

void ChessFigure::setDefaultPosition(int index)
{
	switch (_figureType)
	{
	case King:
		_setDefaultPositionKing(index);
		break;
	case Queen:
		_setDefaultPositionQueen(index);
		break;
	case Bishop:
		_setDefaultPositionBishop(index);
		break;
	case Knight:
		_setDefaultPositionKnight(index);
		break;
	case Rook:
		_setDefaultPositionRook(index);
		break;
	case Pawn:
		_setDefaultPositionPawn(index);
		break;
	case UNDEFINED:
		break;
	default:
		break;
	}
}

void ChessFigure::move(Move move, std::vector<ChessFigure>& otherFigures)
{
	auto validMoves = getValidMoves(otherFigures);
	if (std::find(validMoves.begin(), validMoves.end(), move) == validMoves.end())
	{
		std::cout << "Move is not valid!" << std::endl;
		return;
	}

	setPosition(move.endPosition);
	otherFigures[move.indexOtherFigure].setPosition(move.endPositionOtherFigure);

	if (move.convertOwnTo != FigureType::UNDEFINED)
	{
		_figureType = move.convertOwnTo;
	}

	_movesCount++;
}

void ChessFigure::setPosition(Position position)
{
	this->_position = position;
}

void ChessFigure::setColor(FigureColor figureColor)
{
	_figureColor = figureColor;
}

FigureColor ChessFigure::getColor() const
{
	return _figureColor;
}

Position ChessFigure::getPosition() const
{
	return _position;
}

void ChessFigure::setMovesCount(int moves)
{
	_movesCount = moves;
}

int ChessFigure::getMovesCount() const
{
	return _movesCount;
}

int ChessFigure::_getFigureOnPosition(Position position, std::vector<ChessFigure> const& otherFigures)
{
	for (int i = 0; i < otherFigures.size(); i++)
	{
		if (otherFigures[i].getPosition() == position)
		{
			return i;
		}
	}
	return -1;
}

std::vector<Move> ChessFigure::_getValidMovesKing(std::vector<ChessFigure> const& otherFigures)
{
	return std::vector<Move>();
}

std::vector<Move> ChessFigure::_getValidMovesQueen(std::vector<ChessFigure> const& otherFigures)
{
	return std::vector<Move>();
}

std::vector<Move> ChessFigure::_getValidMovesBishop(std::vector<ChessFigure> const& otherFigures)
{
	return std::vector<Move>();
}

std::vector<Move> ChessFigure::_getValidMovesKnight(std::vector<ChessFigure> const& otherFigures)
{
	return std::vector<Move>();
}

std::vector<Move> ChessFigure::_getValidMovesRook(std::vector<ChessFigure> const& otherFigures)
{
	return std::vector<Move>();
}

std::vector<Move> ChessFigure::_getValidMovesPawn(std::vector<ChessFigure> const& otherFigures)
{
	std::vector<Move> validMoves;

	int direction = 1;
	if (getColor() == FigureColor::Black)
		direction = -1;

	Position stepForward = movePosition(getPosition(), 0, direction);

	if (_getFigureOnPosition(stepForward, otherFigures) == -1)
	{
		// promotion: convert pawn to bishop, knight, queen or rook
		if (getYCoordinate(stepForward) == 7 || getYCoordinate(stepForward) == 0)
		{
			validMoves.push_back(Move(stepForward, Position::UNDEFINED, -1, FigureType::Bishop));
			validMoves.push_back(Move(stepForward, Position::UNDEFINED, -1, FigureType::Knight));
			validMoves.push_back(Move(stepForward, Position::UNDEFINED, -1, FigureType::Queen));
			validMoves.push_back(Move(stepForward, Position::UNDEFINED, -1, FigureType::Rook));
		}
		// simple step forward
		else
		{
			validMoves.push_back(Move(stepForward));
		}
	}

	// two steps forward
	Position twoStepsForward = movePosition(getPosition(), 0, direction * 2);
	if (getMovesCount() == 0 &&
		_getFigureOnPosition(twoStepsForward, otherFigures) == -1 &&
		_getFigureOnPosition(stepForward, otherFigures) == -1)
	{
		validMoves.push_back(Move(twoStepsForward));
	}

	// TODO:
	// - captures to left and right
	// - captures en passant

	return validMoves;
}

void ChessFigure::_setDefaultPositionKing(int index)
{
}

void ChessFigure::_setDefaultPositionQueen(int index)
{
}

void ChessFigure::_setDefaultPositionBishop(int index)
{
}

void ChessFigure::_setDefaultPositionKnight(int index)
{
}

void ChessFigure::_setDefaultPositionRook(int index)
{
}

void ChessFigure::_setDefaultPositionPawn(int index)
{
	if (index < 0 || index > 7)
	{
		std::cout << "FigurePawn::setDefaultPosition(): index has to be between 0 and 7" << std::endl;
		return;
	}

	Position startPosition;
	if (getColor() == FigureColor::White)
	{
		startPosition = Position::A2;
	}
	else
	{
		startPosition = Position::A7;
	}

	setPosition(movePosition(startPosition, index, 0));
}
