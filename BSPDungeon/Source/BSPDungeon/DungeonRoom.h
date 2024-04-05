#pragma once

class UHierarchicalInstancedStaticMeshComponent;

class FDungeonRoom
{
	// The number of rows used to make the room.
	int RoomRows;
	// The number of columns used to make the room.
	int RoomCols;
	// The location in world space of the room.
	FVector RoomOrigin;
	// The amount or rows and columns trimmed from the outer cells of the room.
	int RoomTrim;

	TArray<FVector> FloorPositions;

	TArray<FVector> NorthWallPositions;
	TArray<FVector> SouthWallPositions;
	TArray<FVector> EastWallPositions;
	TArray<FVector> WestWallPositions;

protected:
	
	

public:
	FDungeonRoom(int Rows, int Cols, int Trim, FVector Origin);
	~FDungeonRoom();

	// Returns the width of the current room as number of rows
	int GetRoomWidth()	const { return RoomRows; }
	// Returns the height of the current room as number of columns
	int GetRoomHeight()	const { return RoomCols; }
	// Returns the location in world space of the current room
	FVector GetRoomOrigin() const { return RoomOrigin; }

	void DrawFloorInstancedMesh(int MeshWidth, int MeshHeight, int MeshScale, UHierarchicalInstancedStaticMeshComponent* MeshInstance) const;
};
