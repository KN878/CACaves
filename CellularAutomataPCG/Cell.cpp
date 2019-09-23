#include "FCell.h"

FCell::FCell(int X, int Y)
{
	this->X = X;
	this->Y = Y;
	this->CellType = ECellType::FLOOR;
}

ECellType FCell::GetCellType() const
{
	return CellType;
}

int FCell::GetNeighborhoodValue() const
{
	return NeighborhoodValue;
}

void FCell::SetNeignborhoodValue(int Value)
{
	this->NeighborhoodValue = Value;
}

void FCell::SetGroupNumber(int GroupNumber)
{
	this->CellGroupNumber = GroupNumber;
}

void FCell::ChangeCellType(ECellType NewCellType)
{
	this->CellType = NewCellType;
}
