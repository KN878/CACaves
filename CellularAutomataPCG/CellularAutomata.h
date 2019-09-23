#pragma once
#include "FGrid.h"

class FCellularAutomata
{
public:
	void IterateThroughGrid(FGrid*);

private:
	int Iterations = 2;
	int RockThreshold = 5;
	int MooreNeighborhood = 1;

	int CalculateNeighborhoodValue(FGrid*, int, int);
};

