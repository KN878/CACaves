#pragma once

enum class ECellType {
	FLOOR,
	WALL,
	ROCK
};

class FCell
{
public:
	FCell(int, int);

	ECellType GetCellType() const;
	int GetNeighborhoodValue() const;

	void SetNeignborhoodValue(int);
	void SetGroupNumber(int);
	void ChangeCellType(ECellType);

private:
	ECellType CellType;
	int X, Y;
	int CellGroupNumber = 0;
	int NeighborhoodValue = 0;
};



