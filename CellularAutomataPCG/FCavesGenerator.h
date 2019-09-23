#pragma once

#include <stdlib.h>
#include <time.h>
#include "FGrid.h"
#include "FCellularAutomata.h"

enum class ETunnelDirection {
	EAST,
	SOUTH
};

class FCavesGenerator
{
public:
	void GenerateCaves();
private:
	const int MAP_SIZE = 3;
	const float ROCKS_PERCENTAGE = 0.35;

	void GenerateAdjacentGrids(FGrid&, FCellularAutomata&);
	void ConnectAdjacentGrids(FGrid&);
	//get grid at position 0,0
	FGrid* GetMostNorthWestGrid(FGrid&); 
	//iterates over the grid border and digs a tunnel if there is no connection with the adjacent grid
	void LocateAndDigTunnel(FGrid*, ETunnelDirection); 
	bool IsFloorCell(FGrid*, int, int);
	void DigTunnelToEast(FGrid*, int);
	void DigTunnelToSouth(FGrid*, int);
};