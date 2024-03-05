// Fill out your copyright notice in the Description page of Project Settings.


#include "BinarySpacePartitionComponent.h"

#include "BinaryRoom.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UBinarySpacePartitionComponent::UBinarySpacePartitionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	// Create new UHierarchicalInstancedStaticMeshComponent that holds the mesh instance used for the floor of the dungeon grid.
	GridMeshInstance = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("GridInstancedMesh"));
	GridMeshInstance->SetupAttachment(Cast<USceneComponent>(this));

	// Set the Origin of the grid
	GridOrigin = this->GetComponentLocation();

	// Dynamically load the Static Mesh used for the floor at construction
	GridMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Art/Debug/SM_GridOutliner"));

	// Safety check ensuring FloorMesh is set before running the next lines of code
	if (GridMesh != nullptr)
	{
		// Set the Mesh Instances static mesh to the static mesh we just loaded
		GridMeshInstance->SetStaticMesh(GridMesh);
	}

	// Create the Initial Binary Room using dungeon parameters for left, right, top, and bottom extents of the room
	InitialBinaryRoom = new BinaryRoom(GridRows, GridColumns, GridOrigin);
	
	// Add the Initial Binary Room to the array of binary rooms and RoomSplitQueue
	BinaryRooms.Add(InitialBinaryRoom);
	RoomSplitQueue.Add(InitialBinaryRoom);
}


// Called when the game starts
void UBinarySpacePartitionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Get the width and height of the static mesh, and scale by MeshScale variable
	MeshWidth  = GridMesh->GetBoundingBox().GetSize().X * MeshScale;
	MeshHeight = GridMesh->GetBoundingBox().GetSize().Y * MeshScale;
	
	// Clear Previous Instances
	ClearMeshInstance(GridMeshInstance);

	Split();
	
	// Add new static mesh instances for each cell of the grid
	for (int32 Index = 0; Index < BinaryRooms.Num(); ++Index)
	{
		// Access array element
		const BinaryRoom* Room = BinaryRooms[Index];
		// Modify Element as needed
		for (int i = 0; i < Room->GetRoomWidth(); i++)
		{
			for (int j = 0; j < Room->GetRoomHeight(); j++)
			{
				const float SpawnPosX = Room->GetRoomOrigin().X + (i + MeshWidth * i);
				const float SpawnPosY = Room->GetRoomOrigin().Y + (j + MeshHeight * j);
			
				FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
				FVector Scale = FVector(MeshScale, MeshScale, 1);
			
				GridMeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);

				GridCellPositions.Add(SpawnPosition); 
			}
		}
	}

	
	// Bottom Left
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), GridOrigin, 100, 12, FLinearColor::Red, 100, 1);
	// Top Left
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(GridOrigin.X, GridOrigin.Y + GridColumns * MeshHeight, 0), 100, 12, FLinearColor::Red, 100, 1);
	// Bottom Right
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y , 0), 100, 12, FLinearColor::Red, 100, 1);
	// Top Right
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, 0), 100, 12, FLinearColor::Red, 100, 1);
}

void UBinarySpacePartitionComponent::Split()
{
	while (!RoomSplitQueue.IsEmpty())
	{
		for (int32 Index = 0; Index < BinaryRooms.Num(); ++Index)
		{
			BinaryRoom* Room = BinaryRooms[Index];

			const auto RandomValue = static_cast<double>(rand()) / RAND_MAX;
			if ( RandomValue < 0.5)
				VerticalSplit(Room);
			else
				HorizontalSplit(Room);
		}
	}
	
}

void UBinarySpacePartitionComponent::VerticalSplit(BinaryRoom* RoomToSplit)
{
	UE_LOG(LogTemp, Warning, TEXT("Vertical Split"));

	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinimumRoomSizeX, RoomToSplit->GetRoomWidth() - MinimumRoomSizeX);

	UE_LOG(LogTemp, Warning, TEXT("Width = %d"), RoomToSplit->GetRoomWidth());
	UE_LOG(LogTemp, Warning, TEXT("Height = %d"), RoomToSplit->GetRoomHeight());
	
	UE_LOG(LogTemp, Warning, TEXT("Min = %d"), MinimumRoomSizeX);
	UE_LOG(LogTemp, Warning, TEXT("Max = %d"), RoomToSplit->GetRoomWidth() - MinimumRoomSizeX);
	UE_LOG(LogTemp, Warning, TEXT("Split Point = %d"), SplitPoint);
	
	const FVector RightOrigin = FVector(RoomToSplit->GetRoomOrigin().X + SplitPoint * MeshWidth , RoomToSplit->GetRoomOrigin().Y, 0);

	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), RoomToSplit->GetRoomOrigin(),150, 12, FLinearColor::Blue, 100, 1);
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), RightOrigin,150, 12, FLinearColor::Blue, 100, 1);
	
	BinaryRoom* LeftLeaf  = new BinaryRoom(SplitPoint, RoomToSplit->GetRoomHeight(), RoomToSplit->GetRoomOrigin());
	BinaryRoom* RightLeaf = new BinaryRoom(RoomToSplit->GetRoomWidth() - SplitPoint, RoomToSplit->GetRoomHeight(), RightOrigin);

	// Remove RoomToSplit if it exists
	BinaryRooms.Remove(RoomToSplit);

	// Add LeftLeaf and RightLeaf if they don't exist in BinaryRooms
	if (!BinaryRooms.Contains(LeftLeaf))
		BinaryRooms.Add(LeftLeaf);
	if (!BinaryRooms.Contains(RightLeaf))
		BinaryRooms.Add(RightLeaf);

	// Set LeftLeaf and RightLeaf as children of RoomToSplit if they are not already
	if (!RoomToSplit->HasLeftLeaf())
		RoomToSplit->SetLeftLeaf(LeftLeaf);
	if (!RoomToSplit->HasRightLeaf())
		RoomToSplit->SetRightLeaf(RightLeaf);

	// Set RoomToSplit as the parent of LeftLeaf and RightLeaf if they don't have one
	if (!LeftLeaf->HasParent())
		LeftLeaf->SetParent(RoomToSplit);
	if (!RightLeaf->HasParent())
		RightLeaf->SetParent(RoomToSplit);

	// Remove RoomToSplit from RoomSplitQueue if it exists
	RoomSplitQueue.Remove(RoomToSplit);
}

void UBinarySpacePartitionComponent::HorizontalSplit(BinaryRoom* RoomToSplit)
{
	UE_LOG(LogTemp, Warning, TEXT("Horixontal Split"));
	
	const int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinimumRoomSizeY, RoomToSplit->GetRoomHeight() - MinimumRoomSizeY);

	UE_LOG(LogTemp, Warning, TEXT("Width = %d"), RoomToSplit->GetRoomWidth());
	UE_LOG(LogTemp, Warning, TEXT("Height = %d"), RoomToSplit->GetRoomHeight());
	
	UE_LOG(LogTemp, Warning, TEXT("Min = %d"), MinimumRoomSizeY);
	UE_LOG(LogTemp, Warning, TEXT("Max = %d"), RoomToSplit->GetRoomHeight() - MinimumRoomSizeY);
	UE_LOG(LogTemp, Warning, TEXT("Split Point = %d"), SplitPoint);

	const FVector UpOrigin = FVector(RoomToSplit->GetRoomOrigin().X, RoomToSplit->GetRoomOrigin().Y + SplitPoint * MeshHeight, 0);

	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), RoomToSplit->GetRoomOrigin(),150, 12, FLinearColor::Blue, 100, 1);
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), UpOrigin,150, 12, FLinearColor::Blue, 100, 1);

	BinaryRoom* LeftLeaf  = new BinaryRoom(SplitPoint, RoomToSplit->GetRoomHeight(), RoomToSplit->GetRoomOrigin());
	BinaryRoom* RightLeaf = new BinaryRoom(RoomToSplit->GetRoomWidth() - SplitPoint, RoomToSplit->GetRoomHeight(), UpOrigin);

	// Remove RoomToSplit if it exists
	BinaryRooms.Remove(RoomToSplit);

	// Add LeftLeaf and RightLeaf if they don't exist in BinaryRooms
	if (!BinaryRooms.Contains(LeftLeaf))
		BinaryRooms.Add(LeftLeaf);
	if (!BinaryRooms.Contains(RightLeaf))
		BinaryRooms.Add(RightLeaf);

	// Set LeftLeaf and RightLeaf as children of RoomToSplit if they are not already
	if (!RoomToSplit->HasLeftLeaf())
		RoomToSplit->SetLeftLeaf(LeftLeaf);
	if (!RoomToSplit->HasRightLeaf())
		RoomToSplit->SetRightLeaf(RightLeaf);

	// Set RoomToSplit as the parent of LeftLeaf and RightLeaf if they don't have one
	if (!LeftLeaf->HasParent())
		LeftLeaf->SetParent(RoomToSplit);
	if (!RightLeaf->HasParent())
		RightLeaf->SetParent(RoomToSplit);

	// Remove RoomToSplit from RoomSplitQueue if it exists
	RoomSplitQueue.Remove(RoomToSplit);
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
