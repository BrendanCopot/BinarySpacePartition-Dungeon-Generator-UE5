#pragma once

class BinaryRoom
{
	// The current room's width
	int RoomRows;
	// The current room's height
	int RoomCols;
	// The location in world space of the current room
	FVector RoomOrigin;

	// Binary Tree Variables
	// The current room's parent room
	BinaryRoom* Parent = nullptr;
	// The current room's left leaf after being split
	BinaryRoom* LeftLeaf = nullptr;
	// The current room's right leaf after being split
	BinaryRoom* RightLeaf = nullptr;

	// Variable to determine if a room is able to be split
	bool bCanSplit = true;
	
public:
	BinaryRoom(int Rows, int Cols, FVector Origin);
	~BinaryRoom();

	// Returns the width of the current room as number of rows
	int GetRoomWidth()	const { return RoomRows; }
	// Returns the height of the current room as number of columns
	int GetRoomHeight()	const { return RoomCols; }
	// Returns the location in world space of the current room
	FVector GetRoomOrigin() const { return RoomOrigin; }
	// Returns the state of the bCanSplit variable
	bool GetCanSplit() const { return bCanSplit; }
	
	// Returns the current room's parent
	BinaryRoom* GetParent()		const { return Parent; }
	// Returns the current room's left leaf
	BinaryRoom* GetLeftLeaf()	const { return LeftLeaf; }
	// Returns the current room's right leaf
	BinaryRoom* GetRightLeaf()	const { return RightLeaf; }

	// Sets the parent room of the current room 
	void SetParent(BinaryRoom* NewParent)		{ Parent = NewParent; }
	// Sets the left leaf of the current room
	void SetLeftLeaf(BinaryRoom* NewLeftLeaf)	{ LeftLeaf = NewLeftLeaf; }
	// Sets the right leaf of the current room 
	void SetRightLeaf(BinaryRoom* NewRightLeaf) { RightLeaf = NewRightLeaf; }
	// Sets the state of the bCanSplit variable
	void SetCanSplit(const bool State) { bCanSplit = State; }

	// Returns true if the current rooms parent is not nullptr
	bool HasParent()	const { return Parent != nullptr; }
	// Returns true if the current left leaf parent is not nullptr
	bool HasLeftLeaf()	const { return LeftLeaf != nullptr; }
	// Returns true if the current rooms right leaf is not nullptr
	bool HasRightLeaf() const { return RightLeaf != nullptr; } 
};
