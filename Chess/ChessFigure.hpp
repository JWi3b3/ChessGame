#include "Position.hpp"
#include "Move.hpp"
#include "FigureType.hpp"
#include "FigureColor.hpp"

#include <vector>


class ChessFigure
{
public:
	ChessFigure(FigureType type, FigureColor color, int figureIndex);

	std::vector<Move> getValidMoves(std::vector<ChessFigure> const& otherFigures);
	void setDefaultPosition(int index);
	void move(Move move, std::vector<ChessFigure>& otherFigures);
	void setPosition(Position position);
	Position getPosition() const;
	void setColor(FigureColor figureColor);
	FigureColor getColor() const;
	void setMovesCount(int moves);
	int getMovesCount() const;

private:
	Position _position;
	FigureColor _figureColor;
	FigureType _figureType;
	int _movesCount = 0;
	int _getFigureOnPosition(Position position, std::vector<ChessFigure> const& otherFigures);

	std::vector<Move> _getValidMovesKing(std::vector<ChessFigure> const& otherFigures);
	std::vector<Move> _getValidMovesQueen(std::vector<ChessFigure> const& otherFigures);
	std::vector<Move> _getValidMovesBishop(std::vector<ChessFigure> const& otherFigures);
	std::vector<Move> _getValidMovesKnight(std::vector<ChessFigure> const& otherFigures);
	std::vector<Move> _getValidMovesRook(std::vector<ChessFigure> const& otherFigures);
	std::vector<Move> _getValidMovesPawn(std::vector<ChessFigure> const& otherFigures);

	void _setDefaultPositionKing(int index);
	void _setDefaultPositionQueen(int index);
	void _setDefaultPositionBishop(int index);
	void _setDefaultPositionKnight(int index);
	void _setDefaultPositionRook(int index);
	void _setDefaultPositionPawn(int index);

};