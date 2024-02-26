#pragma once

class BinaryRoom
{
	BinaryRoom(int Left, int Right, int Top, int Bottom);
	~BinaryRoom();

	int RoomLeft;
	int RoomRight;
	int RoomTop;
	int RoomBottom;
	
public:

	int GetRoomLeft(BinaryRoom Room)	const { return RoomLeft; };
	int GetRoomRight(BinaryRoom Room)	const { return RoomRight; };
	int GetRoomTop(BinaryRoom Room)		const { return RoomTop; };
	int GetRoomBottom(BinaryRoom Room)	const { return RoomBottom; };
	
};
