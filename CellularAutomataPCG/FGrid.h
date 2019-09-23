#pragma once
#include <vector>
#include <random>
#include <iostream>

#include "FCell.h"

class FGrid
{
public:
	FGrid(int Seed, float RockPercentage);

	int GetSeed() const;
	const FCell* GetConstCellAtPosition(int, int) const;
	bool IsRockCell(int, int) const;
	bool IsWallCell(int, int) const;
	FCell* GetCellAtPosition(int, int);
	FGrid* GetNorthGrid();
	FGrid* GetSouthGrid();
	FGrid* GetEastGrid();
	FGrid* GetWestGrid();

	void SetNorthGrid(FGrid*);
	void SetSouthGrid(FGrid*);
	void SetWestGrid(FGrid*);
	void SetEastGrid(FGrid*);

	friend std::ostream& operator<<(std::ostream& os, const FGrid& Grid);

private:
	std::vector<std::vector<FCell>> CellsGrid;
	int Seed;
	FGrid* NorthGrid;
	FGrid* SouthGrid;
	FGrid* WestGrid;
	FGrid* EastGrid;

	//seeds the number generator and randoms a float between 0.0 and 1.0
	float RandomFloat();
};
