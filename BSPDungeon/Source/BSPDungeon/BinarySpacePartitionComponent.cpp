// Fill out your copyright notice in the Description page of Project Settings.


#include "BinarySpacePartitionComponent.h"

#include "BinaryRoom.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties.
UBinarySpacePartitionComponent::UBinarySpacePartitionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Create new UHierarchicalInstancedStaticMeshComponent that holds the mesh instance used for the floor of the dungeon grid.
	GridMeshInstance = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("GridInstancedMesh"));
	GridMeshInstance->SetupAttachment(Cast<USceneComponent>(this));

	// Set the Origin of the grid.
	GridOrigin = this->GetComponentLocation();

	// Dynamically load the Static Mesh used for the floor at construction.
	GridMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Art/Debug/SM_GridOutliner"));

	// Safety check ensuring FloorMesh is set before running the next lines of code.
	if (GridMesh != nullptr)
	{
		// Set the Mesh Instances static mesh to the static mesh we just loaded.
		GridMeshInstance->SetStaticMesh(GridMesh);
	}
}


// Called when the game starts.
void UBinarySpacePartitionComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the width and height of the static mesh, and scale by MeshScale variable.
	MeshWidth  = GridMesh->GetBoundingBox().GetSize().X * MeshScale;
	MeshHeight = GridMesh->GetBoundingBox().GetSize().Y * MeshScale;
	
	// Clear Previous Instances.
	ClearMeshInstance(GridMeshInstance);

	BSPSplit();
}

void UBinarySpacePartitionComponent::BSPSplit()
{
	// Create the Initial Binary Room using dungeon parameters for GridRows, GridColumns, and GridOrigin
	InitialBinaryRoom = new BinaryRoom(GridRows, GridColumns, GridOrigin);

	// Queue of rooms that still need to be split
	TQueue<BinaryRoom*> RoomSplitQueue;
	// Array of rooms after they can no longer be split
	TArray<BinaryRoom*> BinaryRooms;
	
	// Add the Initial Binary Room to the array of binary rooms and RoomSplitQueue.
	RoomSplitQueue.Enqueue(InitialBinaryRoom);

	while (!RoomSplitQueue.IsEmpty())
	{
		BinaryRoom* Room;
		RoomSplitQueue.Dequeue(Room);

		if (Room->GetRoomWidth() >= MinRoomSizeX && Room->GetRoomHeight() >= MinRoomSizeY)
		{
			// Randomly split horizontally or vertically
			const auto RandomValue = static_cast<double>(rand()) / RAND_MAX;
			if (RandomValue < 0.5)
			{
				if (Room->GetRoomHeight() >= MinRoomSizeY * 2)
					HorizontalSplit(Room, RoomSplitQueue);
				else if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue);
				else
					BinaryRooms.Add(Room);
			}
			else
			{
				if (Room->GetRoomWidth() >= MinRoomSizeX * 2)
					VerticalSplit(Room, RoomSplitQueue);
				else if (Room->GetRoomHeight() >= MinRoomSizeY * 2)
					HorizontalSplit(Room, RoomSplitQueue);
				else
					BinaryRooms.Add(Room);
			}
		}
	}

	DrawInstancedMesh(BinaryRooms);
}

void UBinarySpacePartitionComponent::DrawInstancedMesh(TArray<BinaryRoom*>& BinaryRoomsArray)
{
	// Iterate through BinaryRooms array.
	for (int Index = 0; Index < BinaryRoomsArray.Num(); Index++)
	{
		// Retrieve a pointer to the current room.
		const BinaryRoom* Room = BinaryRoomsArray[Index];		

		// Iterate through each cell of the room using rows and columns.
		for (int i = RoomTrim; i < Room->GetRoomWidth() - RoomTrim; i++)
		{
			for (int j = RoomTrim; j < Room->GetRoomHeight() - RoomTrim; j++)
			{
				// Calculate the spawn position of the static mesh instance within the room.
				// The position is determined based on the room's origin, mesh width, height, and iteration indices.
				const float SpawnPosX = Room->GetRoomOrigin().X + (i + MeshWidth * i);
				const float SpawnPosY = Room->GetRoomOrigin().Y + (j + MeshHeight * j);

				// Create a vector representing the spawn position.
				FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
				// Define the scale of the static mesh instance.
				FVector Scale = FVector(MeshScale, MeshScale, 1);

				// Add an instance of the static mesh to the grid at the calculated position and scale.
				// The instance is added to the GridMeshInstance object.
				GridMeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);

				// Store the spawn position of the current cell for future reference.
				GridCellPositions.Add(SpawnPosition); 
			}
		}
	}
}

void UBinarySpacePartitionComponent::VerticalSplit(const BinaryRoom* RoomToSplit, TQueue<BinaryRoom*>& RoomsQueue)
{
	UE_LOG(LogTemp, Warning, TEXT("Vertical Split"));
	
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeX, RoomToSplit->GetRoomWidth() - MinRoomSizeX);
	
	const FVector RightOrigin = FVector(RoomToSplit->GetRoomOrigin().X + (RoomTrim + SplitPoint) * MeshWidth , RoomToSplit->GetRoomOrigin().Y, 0);
	
	BinaryRoom* LeftLeaf  = new BinaryRoom(SplitPoint, RoomToSplit->GetRoomHeight(), RoomToSplit->GetRoomOrigin());
	BinaryRoom* RightLeaf = new BinaryRoom(RoomToSplit->GetRoomWidth() - SplitPoint, RoomToSplit->GetRoomHeight(), RightOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}

void UBinarySpacePartitionComponent::HorizontalSplit(const BinaryRoom* RoomToSplit, TQueue<BinaryRoom*>& RoomsQueue)
{
	UE_LOG(LogTemp, Warning, TEXT("Horixontal Split"));
	
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinRoomSizeY, RoomToSplit->GetRoomHeight() - MinRoomSizeY);
	
	const FVector UpOrigin = FVector(RoomToSplit->GetRoomOrigin().X, RoomToSplit->GetRoomOrigin().Y + RoomTrim + SplitPoint * MeshHeight, 0);

	BinaryRoom* LeftLeaf  = new BinaryRoom(RoomToSplit->GetRoomWidth(), SplitPoint, RoomToSplit->GetRoomOrigin());
	BinaryRoom* RightLeaf = new BinaryRoom(RoomToSplit->GetRoomWidth(), RoomToSplit->GetRoomHeight() - SplitPoint, UpOrigin);

	// Add LeftLeaf and RightLeaf to RoomSplitQueue
	RoomsQueue.Enqueue(LeftLeaf);
	RoomsQueue.Enqueue(RightLeaf);
}

// Called every frame
void UBinarySpacePartitionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBinarySpacePartitionComponent::ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance)
{
	MeshInstance->ClearInstances();
	
	UE_LOG(LogTemp, Warning, TEXT("Cleared Mesh Instances"));
}