// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonGenerator.h"
#include "DungeonRoom.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create new UHierarchicalInstancedStaticMeshComponent that holds the mesh instance used for the floor of the dungeon grid.
	FloorMeshInstance = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("GridInstancedMesh"));
	FloorMeshInstance->SetupAttachment(Cast<USceneComponent>(this));

	// Set the Origin of the grid.
	Origin = this->GetActorLocation();

	// Dynamically load the Static Mesh used for the floor at construction.
	FloorMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Art/SM_Pavement_1"));

	// Safety check ensuring FloorMesh is set before running the next lines of code.
	if (FloorMesh != nullptr)
	{
		// Set the Mesh Instances static mesh to the static mesh we just loaded.
		FloorMeshInstance->SetStaticMesh(FloorMesh);
	}
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	// Clear Previous Instances.
	ClearMeshInstance(FloorMeshInstance);
	
	// Recursively split a grid into smaller grids to make up rooms for the dungeon.
	BSPSplit();
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::BSPSplit()
{
	// Create the Initial Binary Room using dungeon parameters for GridRows, GridColumns, and GridOrigin.
	FDungeonRoom* InitialBinaryRoom = new FDungeonRoom(Rows, Columns, RoomTrim, Origin);

	// Queue of rooms that still need to be split.
	TQueue<FDungeonRoom*> RoomSplitQueue;
	// Array of rooms after they can no longer be split.
	TArray<FDungeonRoom*> BinaryRooms;
	
	// Add the Initial Binary Room to the array of binary rooms and RoomSplitQueue.
	RoomSplitQueue.Enqueue(InitialBinaryRoom);

	// Iterate over RoomSplitQueue until the splitting process is complete or the maximum number of rooms is reached.
	while (!RoomSplitQueue.IsEmpty())
	{
		// The current room being processed.
		FDungeonRoom* Room;
		// Remove next room from the RoomSplitQueue and store as variable Room.
		RoomSplitQueue.Dequeue(Room);

		// Check if the maximum number of rooms has been reached.
		if (BinaryRooms.Num() >= MaxRooms)
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
					HorizontalSplit(Room, RoomSplitQueue);
				// Check if the room can be split vertically.
				else if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue);
				// If the room cannot be split further, add it to the array of final binary rooms.
				else
					BinaryRooms.Add(Room);
			}
			else
			{
				// Check if the room can be split vertically.
				if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue);
				// Check if the room can be split horizontally.
				else if (Room->GetRoomHeight() >= MinRoomSizeY * 2)
					HorizontalSplit(Room, RoomSplitQueue);
				// If the room cannot be split further, add it to the array of final binary rooms.
				else
					BinaryRooms.Add(Room);
			}
		}
	}

	// Draw the final set of binary rooms.
	DrawInstancedMesh(BinaryRooms);
}

void ADungeonGenerator::VerticalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue) const
{
	// Determine the point at which the room will be split vertically.
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeX, RoomToSplit->GetRoomWidth() - MinRoomSizeX);

	// Calculate the origin of the right leaf after the split.
	const FVector RightOrigin = FVector(RoomToSplit->GetRoomOrigin().X + (RoomTrim + SplitPoint) * GetMeshWidth(FloorMesh, FloorMeshScale) , RoomToSplit->GetRoomOrigin().Y, 0);

	// Create new binary rooms representing the left and right leaf resulting from the split.
	FDungeonRoom* LeftLeaf  = new FDungeonRoom(SplitPoint, RoomToSplit->GetRoomHeight(), RoomTrim, RoomToSplit->GetRoomOrigin());
	FDungeonRoom* RightLeaf = new FDungeonRoom(RoomToSplit->GetRoomWidth() - SplitPoint, RoomToSplit->GetRoomHeight(), RoomTrim, RightOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}

void ADungeonGenerator::HorizontalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue) const
{
	// Determine the point at which the room will be split horizontally.
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeY, RoomToSplit->GetRoomHeight() - MinRoomSizeY);

	// Calculate the origin of the right leaf after the split.
	const FVector UpOrigin = FVector(RoomToSplit->GetRoomOrigin().X, RoomToSplit->GetRoomOrigin().Y + RoomTrim + SplitPoint * GetMeshHeight(FloorMesh, FloorMeshScale), 0);

	// Create new binary rooms representing the left and right leaf resulting from the split.
	FDungeonRoom* LeftLeaf  = new FDungeonRoom(RoomToSplit->GetRoomWidth(), SplitPoint, RoomTrim, RoomToSplit->GetRoomOrigin());
	FDungeonRoom* RightLeaf = new FDungeonRoom(RoomToSplit->GetRoomWidth(), RoomToSplit->GetRoomHeight() - SplitPoint, RoomTrim, UpOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}

void ADungeonGenerator::ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance)
{
	MeshInstance->ClearInstances();
	
	UE_LOG(LogTemp, Warning, TEXT("Cleared Mesh Instances"));
}

void ADungeonGenerator::DrawInstancedMesh(TArray<FDungeonRoom*>& BinaryRoomsArray)
{
	// Iterate through BinaryRooms array.
	for (int Index = 0; Index < BinaryRoomsArray.Num(); Index++)
	{
		// Retrieve a pointer to the current room.
		const FDungeonRoom* Room = BinaryRoomsArray[Index];		

		// Iterate through each cell of the room using rows and columns.
		for (int i = RoomTrim; i <= Room->GetRoomWidth() - RoomTrim; i++)
		{
			for (int j = RoomTrim; j <= Room->GetRoomHeight() - RoomTrim; j++)
			{
				// Calculate the spawn position of the static mesh instance within the room.
				// The position is determined based on the room's origin, mesh width, height, and iteration indices.
				const float SpawnPosX = Room->GetRoomOrigin().X + (i + GetMeshWidth(FloorMesh, FloorMeshScale) * i);
				const float SpawnPosY = Room->GetRoomOrigin().Y + (j + GetMeshHeight(FloorMesh, FloorMeshScale) * j);

				// Create a vector representing the spawn position.
				FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
				// Define the scale of the static mesh instance.
				FVector Scale = FVector(FloorMeshScale, FloorMeshScale, 1);

				// Add an instance of the static mesh to the grid at the calculated position and scale.
				// The instance is added to the GridMeshInstance object.
				FloorMeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);
			}
		}
	}
}

