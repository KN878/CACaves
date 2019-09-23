#include "FGrid.h"

FGrid::FGrid(int Seed, float RockPercentage)
{
	this->Seed = Seed;

	for (int y = 0; y < 50; y++) {
		std::vector<FCell> GridRow;
		for (int x = 0; x < 50; x++) {
			FCell Cell(x, y);
			if (RandomFloat() <= RockPercentage) {
				Cell.ChangeCellType(ECellType::ROCK);
			}

			GridRow.push_back(Cell);
		}
		this->CellsGrid.push_back(GridRow);
	}
}

int FGrid::GetSeed() const
{
	return Seed;
}

const FCell* FGrid::GetConstCellAtPosition(int x, int y) const
{
	return &CellsGrid[y][x];
}

bool FGrid::IsRockCell(int x, int y) const
{
	return GetConstCellAtPosition(x, y)->GetCellType ()== ECellType::ROCK;
}

bool FGrid::IsWallCell(int x, int y) const
{
	return GetConstCellAtPosition(x, y)->GetCellType() == ECellType::WALL;
}

FCell* FGrid::GetCellAtPosition(int x, int y)
{
	return &CellsGrid[y][x];
}

FGrid* FGrid::GetNorthGrid()
{
	return NorthGrid;
}

FGrid* FGrid::GetSouthGrid()
{
	return SouthGrid;
}

FGrid* FGrid::GetEastGrid()
{
	return EastGrid;
}

FGrid* FGrid::GetWestGrid()
{
	return WestGrid;
}

void FGrid::SetNorthGrid(FGrid* Grid)
{
	this->NorthGrid = Grid;
}

void FGrid::SetSouthGrid(FGrid* Grid)
{
	this->SouthGrid = Grid;
}

void FGrid::SetWestGrid(FGrid* Grid)
{
	this->WestGrid = Grid;
}

void FGrid::SetEastGrid(FGrid* Grid)
{
	this->EastGrid = Grid;
}

float FGrid::RandomFloat() {
	std::random_device Source;
	std::mt19937 Engine(Source());
	std::uniform_real_distribution<float> Distribution(0.0, 1.0);
	return Distribution(Engine);
}

std::ostream& operator<<(std::ostream& os, const FGrid& Grid)
{
	for (int y = 0; y < 50; y++) {
		for (int x = 0; x < 50; x++) {
			ECellType CellType = Grid.GetConstCellAtPosition(x, y)->GetCellType();
			switch (CellType)
			{
			case ECellType::FLOOR:
				os << "F";
				break;
			case ECellType::WALL:
				os << "W";
				break;
			case ECellType::ROCK:
				os << "R";
				break;
			default:
				break;
			}
		}
		os << std::endl;
	}
	return os;
}
