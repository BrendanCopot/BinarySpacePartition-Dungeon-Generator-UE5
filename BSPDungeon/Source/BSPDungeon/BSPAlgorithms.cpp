// Fill out your copyright notice in the Description page of Project Settings.


#include "BSPAlgorithms.h"

#include "DungeonRoom.h"
#include "Kismet/KismetMathLibrary.h"

FBSPAlgorithms::FBSPAlgorithms()
{
}

FBSPAlgorithms::~FBSPAlgorithms()
{
}

TArray<FDungeonRoom*> FBSPAlgorithms::BSPSplit(TArray<FDungeonRoom*> DungeonRooms, int Rows, int Columns, int RoomTrim,
	FVector Origin, int MaxRooms, int MinRoomSizeX, int MinRoomSizeY, int MeshWidth, int MeshHeight) const
{
	// Create the Initial Binary Room using dungeon parameters for GridRows, GridColumns, and GridOrigin.
	FDungeonRoom* InitialRoom = new FDungeonRoom(Rows, Columns, RoomTrim, Origin);

	// Queue of rooms that still need to be split.
	TQueue<FDungeonRoom*> RoomSplitQueue;
	
	// Add the Initial Binary Room to the array of binary rooms and RoomSplitQueue.
	RoomSplitQueue.Enqueue(InitialRoom);

	// Iterate over RoomSplitQueue until the splitting process is complete or the maximum number of rooms is reached.
	while (!RoomSplitQueue.IsEmpty())
	{
		// The current room being processed.
		FDungeonRoom* Room;
		// Remove next room from the RoomSplitQueue and store as variable Room.
		RoomSplitQueue.Dequeue(Room);

		// Check if the maximum number of rooms has been reached.
		if (DungeonRooms.Num() >= MaxRooms)
			break;

		// Check if the room can still be split based on its Width and Height.
		if (Room->GetRoomWidth() >= MinRoomSizeX && Room->GetRoomHeight() >= MinRoomSizeY)
		{
			// Randomly decide whether to split horizontally or vertically.
			const auto RandomValue = static_cast<double>(rand()) / RAND_MAX;
			if (RandomValue < 0.5)
			{
				// Check if the room can be split horizontally.
				if (Room->GetRoomHeight() >= MinRoomSizeY * 2)
					HorizontalSplit(Room, RoomSplitQueue, MinRoomSizeX, RoomTrim, MeshWidth);
				// Check if the room can be split vertically.
				else if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue, MinRoomSizeY, RoomTrim, MeshHeight);
				// If the room cannot be split further, add it to the array of final binary rooms.
				else
					DungeonRooms.Add(Room);
			}
			else
			{
				// Check if the room can be split vertically.
				if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue, MinRoomSizeY, RoomTrim, MeshHeight);
				// Check if the room can be split horizontally.
				else if (Room->GetRoomHeight() >= MinRoomSizeY * 2)
					HorizontalSplit(Room, RoomSplitQueue, MinRoomSizeX, RoomTrim, MeshWidth);
				// If the room cannot be split further, add it to the array of final binary rooms.
				else
					DungeonRooms.Add(Room);
			}
		}
	}

	return DungeonRooms;
}

void FBSPAlgorithms::VerticalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue, int MinRoomSizeX, int RoomTrim, int MeshWidth) const
{
	// Determine the point at which the room will be split vertically.
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeX, RoomToSplit->GetRoomWidth() - MinRoomSizeX);

	// Calculate the origin of the right leaf after the split.
	const FVector RightOrigin = FVector(RoomToSplit->GetRoomOrigin().X + (RoomTrim + SplitPoint) * MeshWidth , RoomToSplit->GetRoomOrigin().Y, 0);

	// Create new binary rooms representing the left and right leaf resulting from the split.
	FDungeonRoom* LeftLeaf  = new FDungeonRoom(SplitPoint, RoomToSplit->GetRoomHeight(), RoomTrim, RoomToSplit->GetRoomOrigin());
	FDungeonRoom* RightLeaf = new FDungeonRoom(RoomToSplit->GetRoomWidth() - SplitPoint, RoomToSplit->GetRoomHeight(), RoomTrim, RightOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}

void FBSPAlgorithms::HorizontalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue, int MinRoomSizeY, int RoomTrim, int MeshHeight) const
{
	// Determine the point at which the room will be split horizontally.
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeY, RoomToSplit->GetRoomHeight() - MinRoomSizeY);

	// Calculate the origin of the right leaf after the split.
	const FVector UpOrigin = FVector(RoomToSplit->GetRoomOrigin().X, RoomToSplit->GetRoomOrigin().Y + RoomTrim + SplitPoint * MeshHeight, 0);

	// Create new binary rooms representing the left and right leaf resulting from the split.
	FDungeonRoom* LeftLeaf  = new FDungeonRoom(RoomToSplit->GetRoomWidth(), SplitPoint, RoomTrim, RoomToSplit->GetRoomOrigin());
	FDungeonRoom* RightLeaf = new FDungeonRoom(RoomToSplit->GetRoomWidth(), RoomToSplit->GetRoomHeight() - SplitPoint, RoomTrim, UpOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}