#pragma once
#include "FGrid.h"

class FCellularAutomata
{
public:
	void IterateThroughGrid(FGrid*);

private:
	const int Iterations = 3;
	const int RockThreshold = 5;
	const int MooreNeighborhood = 1;
	const int WallsThreshold = 7;

	//perform one CA iteration
	void RunOneIteration(FGrid*);
	//iterates over the grid and turns rocks into walls under the stated condition
	void CreateWalls(FGrid*);
	int CalculateNeighborhoodValue(FGrid*, int, int);
};
