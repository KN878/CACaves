#include "FMetrics.h"

float FMetrics::GetFloorsToRocksRatio(FGrid* Grid)
{	
	int NumberOfRocks = 0;
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			if (Grid->IsRockCell(x, y) || Grid->IsWallCell(x, y)) {
				NumberOfRocks++;
			}
		}
	}
	return (50 - NumberOfRocks) / 50;
}
