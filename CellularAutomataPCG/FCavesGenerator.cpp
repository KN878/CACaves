#include "FCavesGenerator.h"

void FCavesGenerator::GenerateCaves()
{
	srand(time(NULL));

	FCellularAutomata CellularAutomata{};
	FGrid CentralGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(&CentralGrid);
	GenerateAdjacentGrids(CentralGrid, CellularAutomata);
	ConnectAdjacentGrids(CentralGrid);
}

void FCavesGenerator::GenerateAdjacentGrids(FGrid& CentralGrid, FCellularAutomata& CellularAutomata)
{
	FGrid* NorthGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(NorthGrid);
	CentralGrid.SetNorthGrid(NorthGrid);

	FGrid* SouthGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(SouthGrid);
	CentralGrid.SetSouthGrid(SouthGrid);

	FGrid* EastGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(EastGrid);
	CentralGrid.SetEastGrid(EastGrid);

	FGrid* WestGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(WestGrid);
	CentralGrid.SetWestGrid(WestGrid);

	FGrid* NorthEastGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(NorthEastGrid);
	NorthGrid->SetEastGrid(NorthEastGrid);

	FGrid* NorthWestGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(NorthWestGrid);
	NorthGrid->SetWestGrid(NorthWestGrid);

	FGrid* SouthEastGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(SouthEastGrid);
	SouthGrid->SetEastGrid(SouthEastGrid);

	FGrid* SouthWestGrid = new FGrid(rand(), ROCKS_PERCENTAGE);
	CellularAutomata.IterateThroughGrid(SouthWestGrid);
	SouthGrid->SetWestGrid(SouthWestGrid);

	NorthGrid = nullptr;
	delete NorthGrid;
	SouthGrid = nullptr;
	delete SouthGrid;
	EastGrid = nullptr;
	delete EastGrid;
	WestGrid = nullptr;
	delete WestGrid;
	NorthEastGrid = nullptr;
	delete NorthEastGrid;
	NorthWestGrid = nullptr;
	delete NorthWestGrid;
	SouthEastGrid = nullptr;
	delete SouthEastGrid;
	SouthWestGrid = nullptr;
	delete SouthWestGrid;
}

void FCavesGenerator::ConnectAdjacentGrids(FGrid& CentralGrid)
{
	FGrid* CurrentGrid = GetMostNorthWestGrid(CentralGrid);
	while (true) {
		if (CurrentGrid->GetEastGrid()) {
			LocateAndDigTunnel(CurrentGrid, ETunnelDirection::EAST);

			if (CurrentGrid->GetSouthGrid()) {
				LocateAndDigTunnel(CurrentGrid, ETunnelDirection::SOUTH);
			}
			CurrentGrid = CurrentGrid->GetEastGrid();
		}
		else if (CurrentGrid->GetSouthGrid()) {
			LocateAndDigTunnel(CurrentGrid, ETunnelDirection::SOUTH);
			while (CurrentGrid->GetWestGrid()) {
				CurrentGrid = CurrentGrid->GetWestGrid();
			}
			if (CurrentGrid->GetSouthGrid()) {
				CurrentGrid = CurrentGrid->GetSouthGrid();
			}
			else {
				break;
			}
		}
		else {
			break;
		}

	}
}

FGrid* FCavesGenerator::GetMostNorthWestGrid(FGrid& CentralGrid)
{
	FGrid* FirstGrid; // Grid at position 0,0
	FGrid* CurrentGrid = &CentralGrid;
	while (true) {
		if (CurrentGrid->GetWestGrid()) {
			CurrentGrid = CurrentGrid->GetWestGrid();
			continue;
		}
		else if (CurrentGrid->GetWestGrid()) {
			CurrentGrid = CurrentGrid->GetNorthGrid();
			continue;
		}
		else {
			FirstGrid = CurrentGrid;
			break;
		}
	}

	CurrentGrid = nullptr;
	delete CurrentGrid;

	return FirstGrid;
}

void FCavesGenerator::LocateAndDigTunnel(FGrid* Grid, ETunnelDirection TunnelDirection)
{
	bool bHasTunnel = false;
	int possibleTunnelCoordinate = -1;
	if (TunnelDirection == ETunnelDirection::EAST) {
		for (int y = 0; y < 50; y++) {
			if (IsFloorCell(Grid, 49, y) && IsFloorCell(Grid->GetEastGrid(), 0, y)) {
				bHasTunnel = true;
				break;
			} 
			else if (IsFloorCell(Grid, 49, y) && !IsFloorCell(Grid->GetEastGrid(), 0, y)) {
				possibleTunnelCoordinate = y;
			}
		}
		if (!bHasTunnel && possibleTunnelCoordinate != -1) {
			DigTunnelToEast(Grid, possibleTunnelCoordinate);
		}
	}
	else {
		for (int x = 0; x < 50; x++) {
			if (IsFloorCell(Grid, x, 49) && IsFloorCell(Grid->GetEastGrid(), x, 0)) {
				bHasTunnel = true;
				break;
			}
			else if (IsFloorCell(Grid, x, 49) && !IsFloorCell(Grid->GetEastGrid(), x, 49)) {
				possibleTunnelCoordinate = x;
			}
		}
		if (!bHasTunnel && possibleTunnelCoordinate != -1) {
			DigTunnelToSouth(Grid, possibleTunnelCoordinate);
		}
	}
}

bool FCavesGenerator::IsFloorCell(FGrid* Grid, int x, int y)
{
	return !Grid->IsRockCell(x, y) && Grid->IsWallCell(x, y);
}

void FCavesGenerator::DigTunnelToEast(FGrid* Grid, int possibleTunnelCoordinate)
{
	Grid->GetCellAtPosition(49, possibleTunnelCoordinate)->ChangeCellType(ECellType::FLOOR);
	Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate)->ChangeCellType(ECellType::FLOOR);

	if (possibleTunnelCoordinate == 0) {
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate + 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate + 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate + 2)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate + 2)->ChangeCellType(ECellType::FLOOR);
	}
	else if (possibleTunnelCoordinate == 49) {
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate - 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate - 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate - 2)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate - 2)->ChangeCellType(ECellType::FLOOR);
	}
	else {
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate + 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate + 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(49, possibleTunnelCoordinate - 1)->ChangeCellType(ECellType::FLOOR);
		Grid->GetEastGrid()->GetCellAtPosition(0, possibleTunnelCoordinate - 1)->ChangeCellType(ECellType::FLOOR);
	}
}

void FCavesGenerator::DigTunnelToSouth(FGrid* Grid, int possibleTunnelCoordinate)
{
	Grid->GetCellAtPosition(possibleTunnelCoordinate, 49)->ChangeCellType(ECellType::FLOOR);
	Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate, 0)->ChangeCellType(ECellType::FLOOR);

	if (possibleTunnelCoordinate == 0) {
		Grid->GetCellAtPosition(possibleTunnelCoordinate + 1, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate + 1, 0)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(possibleTunnelCoordinate + 2, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate + 2, 0)->ChangeCellType(ECellType::FLOOR);
	}
	else if (possibleTunnelCoordinate == 49) {
		Grid->GetCellAtPosition(possibleTunnelCoordinate - 1, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate - 1, 0)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(possibleTunnelCoordinate - 2, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate - 2, 0)->ChangeCellType(ECellType::FLOOR);
	}
	else {
		Grid->GetCellAtPosition(possibleTunnelCoordinate + 1, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate + 1, 0)->ChangeCellType(ECellType::FLOOR);
		Grid->GetCellAtPosition(possibleTunnelCoordinate - 1, 49)->ChangeCellType(ECellType::FLOOR);
		Grid->GetSouthGrid()->GetCellAtPosition(possibleTunnelCoordinate - 1, 0)->ChangeCellType(ECellType::FLOOR);
	}
}
