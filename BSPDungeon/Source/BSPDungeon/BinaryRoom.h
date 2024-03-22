#pragma once

class BinaryRoom
{
	// The current room's width
	int RoomRows;
	// The current room's height
	int RoomCols;
	// The location in world space of the current room
	FVector RoomOrigin;
	
public:
	BinaryRoom(int Rows, int Cols, FVector Origin);
	~BinaryRoom();

	// Returns the width of the current room as number of rows
	int GetRoomWidth()	const { return RoomRows; }
	// Returns the height of the current room as number of columns
	int GetRoomHeight()	const { return RoomCols; }
	// Returns the location in world space of the current room
	FVector GetRoomOrigin() const { return RoomOrigin; }
};
