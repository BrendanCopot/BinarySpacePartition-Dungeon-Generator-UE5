#include "DungeonRoom.h"

FDungeonRoom::FDungeonRoom(int Rows, int Cols, int Trim, FVector Origin)
{
	RoomRows = Rows;
	RoomCols = Cols;
	RoomTrim = Trim;
	RoomOrigin = Origin;
}

FDungeonRoom::~FDungeonRoom()
{
	
}
