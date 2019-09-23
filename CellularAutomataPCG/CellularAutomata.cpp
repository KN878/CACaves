#include "FCellularAutomata.h"

void FCellularAutomata::IterateThroughGrid(FGrid* Grid)
{
	int Run = 0;
	while (Run < Iterations) {
		for (int y = 0; y < 50; y++) {
			for (int x = 0; x < 50; x++) {
				int NeighborhoodValue = CalculateNeighborhoodValue(Grid, x, y);
				if (NeighborhoodValue >= RockThreshold) {
					Grid->GetCellAtPosition(x, y)->ChangeCellType(ECellType::ROCK);
				}
			}
		}
		Run++;
	}
}

int FCellularAutomata::CalculateNeighborhoodValue(FGrid* Grid, int x, int y)
{
	int NeighborhoodValue = 0;
	for (int y1 = y - MooreNeighborhood; y1 < y + MooreNeighborhood + 1; y1++) {
		for (int x1 = x - MooreNeighborhood; x1 < x + MooreNeighborhood + 1; x1++) {
			if (x1 >= 0 && x1 != x && x1 < 50
				&& y1 >= 0 && y1 != y && y1 < 50
				&& Grid->GetConstCellAtPosition(x1, y1)->GetCellType == ECellType::ROCK) {
				NeighborhoodValue++;
			}
		}
	}
	
	return NeighborhoodValue;
}
