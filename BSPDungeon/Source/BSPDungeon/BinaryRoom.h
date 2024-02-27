#pragma once

class BinaryRoom
{
	int RoomLeft;
	int RoomRight;
	int RoomTop;
	int RoomBottom;

	BinaryRoom* Parent;
	BinaryRoom* LeftLeaf;
	BinaryRoom* RightLeaf;
	
public:

	BinaryRoom(int Left, int Right, int Top, int Bottom);
	~BinaryRoom();
	
	int GetRoomLeft()	const { return RoomLeft; }
	int GetRoomRight()	const { return RoomRight; }
	int GetRoomTop()	const { return RoomTop; }
	int GetRoomBottom()	const { return RoomBottom; }

	BinaryRoom* GetParent()		const { return Parent; }
	BinaryRoom* GetLeftLeaf()	const { return LeftLeaf; }
	BinaryRoom* GetRightLeaf()	const { return RightLeaf; }

	void SetParent(BinaryRoom* NewParent)		{ Parent = NewParent; }
	void SetLeftLeaf(BinaryRoom* NewLeftLeaf)	{ LeftLeaf = NewLeftLeaf; }
	void SetRightLeaf(BinaryRoom* NewRightLeaf) { RightLeaf = NewRightLeaf; }

	bool HasParent()	const { return Parent != nullptr; }
	bool HasLeftLeaf()	const { return LeftLeaf != nullptr; }
	bool HasRightLeaf() const { return RightLeaf != nullptr; } 
};
