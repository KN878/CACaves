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

void FCell::SetGroupNumber(int GroupNumber)
{
	this->CellGroupNumber = GroupNumber;
}

void FCell::ChangeCellType(ECellType NewCellType)
{
	this->CellType = NewCellType;
}
