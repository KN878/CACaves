#pragma once
#include <vector>

#include "FCell.h"

class FGrid
{
public:
	FGrid();

	FCell* GetCellAtPosition(int, int) const;
	FGrid* GetNorthGrid() const;
	FGrid* GetEastGrid() const;
	FGrid* GetSouthGrid() const;
	FGrid* GetWestGrid() const;

	void SetNorthGrid(FGrid*);
	void SetEastGrid(FGrid*);
	void SetSouthGrid(FGrid*);
	void SetWestGrid(FGrid*);


private:
	std::vector<std::vector<FCell>> CellsGrid;
	int seed;
	FGrid* NorthGrid;
	FGrid* EastGrid;
	FGrid* SouthGrid;
	FGrid* WestGrid;
};

