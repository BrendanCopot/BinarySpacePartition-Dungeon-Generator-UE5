#pragma once

class BinaryRoom
{
	// The value of the current room's left bound
	int RoomLeft;
	// The value of the current room's right bound
	int RoomRight;
	// The value of the current room's top bound
	int RoomTop;
	// The value of the current room's bottom bound
	int RoomBottom;

	// The current room's width
	int RoomWidth = RoomRight - RoomLeft;
	// The current room's height
	int RoomHeight = RoomTop - RoomBottom;

	// Binary Tree Variables
	// The current room's parent room
	BinaryRoom* Parent;
	// The current room's left leaf after being split
	BinaryRoom* LeftLeaf;
	// The current room's right leaf after being split
	BinaryRoom* RightLeaf;
	
public:

	BinaryRoom(int Left, int Right, int Top, int Bottom);
	~BinaryRoom();
	
	// Returns the current room's left bound
	int GetRoomLeft()	const { return RoomLeft; }
	// Returns the current room's right bound
	int GetRoomRight()	const { return RoomRight; }
	// Returns the current room's top bound
	int GetRoomTop()	const { return RoomTop; }
	// Returns the current room's bottom bound
	int GetRoomBottom()	const { return RoomBottom; }
	// Returns the width of the current room
	int GetRoomWidth()	const { return RoomWidth; }
	// Returns the height of the current room
	int GetRoomHeight()	const { return RoomHeight; }
	
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

	// Returns true if the current rooms parent is not nullptr
	bool HasParent()	const { return Parent != nullptr; }
	// Returns true if the current left leaf parent is not nullptr
	bool HasLeftLeaf()	const { return LeftLeaf != nullptr; }
	// Returns true if the current rooms right leaf is not nullptr
	bool HasRightLeaf() const { return RightLeaf != nullptr; } 
};
