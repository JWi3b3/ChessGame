#pragma once
enum class Position
{
	A1,
	B1,
	C1,
	D1,
	E1,
	F1,
	G1,
	H1,
	A2,
	B2,
	C2,
	D2,
	E2,
	F2,
	G2,
	H2,
	A3,
	B3,
	C3,
	D3,
	E3,
	F3,
	G3,
	H3,
	A4,
	B4,
	C4,
	D4,
	E4,
	F4,
	G4,
	H4,
	A5,
	B5,
	C5,
	D5,
	E5,
	F5,
	G5,
	H5,
	A6,
	B6,
	C6,
	D6,
	E6,
	F6,
	G6,
	H6,
	A7,
	B7,
	C7,
	D7,
	E7,
	F7,
	G7,
	H7,
	A8,
	B8,
	C8,
	D8,
	E8,
	F8,
	G8,
	H8,
	UNDEFINED
};

inline int getXCoordinate(Position position)
{
	int index = static_cast<int>(position);
	int xPos = index % 8;
}

inline int getYCoordinate(Position position)
{
	int index = static_cast<int>(position);
	int yPos = index / 8;
}

inline Position coordinateToPosition(int xCoord, int yCoord)
{
	int index = yCoord * 8 + xCoord;
	return static_cast<Position>(index);
}

inline Position movePosition(Position origin, int toRight, int toTop)
{
	int xPos = getXCoordinate(origin);
	int yPos = getYCoordinate(origin);

	xPos += toRight;
	yPos += toTop;

	if (xPos > 7 || xPos < 0)
		return Position::UNDEFINED;

	if (yPos > 7 || yPos < 0)
		return Position::UNDEFINED;

	return coordinateToPosition(xPos, yPos);
}