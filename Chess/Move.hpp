#pragma once
#include "Position.hpp"
#include "FigureType.hpp"

struct Move
{
	inline Move(
		Position endPos,
		Position endPosOther = Position::UNDEFINED,
		int idxOther = -1,
		FigureType convertOwnFigureTo = FigureType::UNDEFINED)
	{
		endPosition = endPos;
		endPositionOtherFigure = endPosOther;
		indexOtherFigure = idxOther;
	}

	Position endPosition;
	Position endPositionOtherFigure = Position::UNDEFINED;
	int indexOtherFigure = -1;
	FigureType convertOwnTo = FigureType::UNDEFINED;
};