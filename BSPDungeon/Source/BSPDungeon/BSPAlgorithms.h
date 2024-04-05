// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FDungeonRoom;
/**
 * 
 */
class BSPDUNGEON_API FBSPAlgorithms
{

protected:
	void VerticalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue, int MinRoomSizeX, int RoomTrim, int MeshWidth) const;
	void HorizontalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue, int MinRoomSizeY, int RoomTrim, int MeshHeight) const;
	
public:
	FBSPAlgorithms();
	~FBSPAlgorithms();

	TArray<FDungeonRoom*> BSPSplit(TArray<FDungeonRoom*> DungeonRooms, int Rows, int Columns, int RoomTrim,
	FVector Origin, int MaxRooms, int MinRoomSizeX, int MinRoomSizeY, int MeshWidth, int MeshHeight) const;
	
	
};
