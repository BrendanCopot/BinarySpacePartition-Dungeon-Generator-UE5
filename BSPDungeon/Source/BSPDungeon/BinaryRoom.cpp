#include "BinaryRoom.h"

BinaryRoom::BinaryRoom(int Left, int Right, int Top, int Bottom)
{
	RoomLeft = Left;
	RoomRight = Right;
	RoomTop = Top;
	RoomBottom = Bottom;

	Parent = nullptr;
	LeftLeaf = nullptr;
	RightLeaf = nullptr;
}

BinaryRoom::~BinaryRoom()
{
	
}
