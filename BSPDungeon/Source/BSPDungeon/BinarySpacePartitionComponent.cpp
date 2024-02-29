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
	InitialBinaryRoom = new BinaryRoom(GridOrigin.X, GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, GridOrigin.Y);
	
	// Add the Initial Binary Room to the array of binary rooms
	BinaryRooms.Add(InitialBinaryRoom);
}


// Called when the game starts
void UBinarySpacePartitionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Get the width and length of the static mesh, and scale by mesh size variable
	MeshWidth  = GridMesh->GetBoundingBox().GetSize().X * MeshScale;
	MeshHeight = GridMesh->GetBoundingBox().GetSize().Y * MeshScale;
	
	// Clear Previous Instances
	ClearMeshInstance(GridMeshInstance);
	
	// Add new static mesh instances for each cell of the grid
	for (int i = 0; i < GridRows; i++)
	{
		for (int j = 0; j < GridColumns; j++)
		{
			const float SpawnPosX = GridOrigin.X + (i + MeshWidth * i);
			const float SpawnPosY = GridOrigin.Y + (j + MeshHeight * j);
			
			FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
			FVector Scale = FVector(MeshScale, MeshScale, 1);
			
			GridMeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);

			GridCellPositions.Add(SpawnPosition); 
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

	Split(InitialBinaryRoom);
}

void UBinarySpacePartitionComponent::Split(BinaryRoom* RoomToSplit)
{
	const auto RandomValue = static_cast<double>(rand()) / RAND_MAX;
	if ( RandomValue < 0.5)
		VerticalSplit(RoomToSplit);
	else
		HorizontalSplit(RoomToSplit);
}

void UBinarySpacePartitionComponent::VerticalSplit(BinaryRoom* RoomToSplit)
{
	UE_LOG(LogTemp, Warning, TEXT("Vertical Split"));

	int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinimumRoomSizeX, GridRows - MinimumRoomSizeX);

	UE_LOG(LogTemp, Warning, TEXT("Min = %d"), MinimumRoomSizeX);
	UE_LOG(LogTemp, Warning, TEXT("Max = %d"), GridRows - MinimumRoomSizeX);
	UE_LOG(LogTemp, Warning, TEXT("Split Point = %d"), SplitPoint);
	

	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(RoomToSplit->GetRoomLeft() + SplitPoint * MeshWidth, RoomToSplit->GetRoomBottom() + GridColumns * MeshHeight, 0), 100, 12, FLinearColor::Red, 100, 1);
	
	BinaryRoom* LeftLeaf = new BinaryRoom(GridOrigin.X, GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, GridOrigin.Y);
	BinaryRoom* RightLeaf = new BinaryRoom(GridOrigin.X, GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, GridOrigin.Y);

	RoomToSplit->SetLeftLeaf(LeftLeaf);
	RoomToSplit->SetRightLeaf(RightLeaf);
	
	LeftLeaf->SetParent(RoomToSplit);
	RightLeaf->SetParent(RoomToSplit);
}

void UBinarySpacePartitionComponent::HorizontalSplit(BinaryRoom* RoomToSplit)
{
	UE_LOG(LogTemp, Warning, TEXT("Horixontal Split"));
	
	int SplitPoint = UKismetMathLibrary::RandomIntegerInRange(MinimumRoomSizeY, GridColumns - MinimumRoomSizeY);

	UE_LOG(LogTemp, Warning, TEXT("Min = %d"), MinimumRoomSizeY);
	UE_LOG(LogTemp, Warning, TEXT("Max = %d"), GridColumns - MinimumRoomSizeY);
	UE_LOG(LogTemp, Warning, TEXT("Split Point = %d"), SplitPoint);
    
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), FVector(RoomToSplit->GetRoomLeft(), RoomToSplit->GetRoomBottom() + SplitPoint * MeshHeight, 0), 100, 12, FLinearColor::Red, 100, 1);
    	
	BinaryRoom* LeftLeaf = new BinaryRoom(GridOrigin.X, GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, GridOrigin.Y);
	BinaryRoom* RightLeaf = new BinaryRoom(GridOrigin.X, GridOrigin.X + GridRows * MeshWidth, GridOrigin.Y + GridColumns * MeshHeight, GridOrigin.Y);
    
    RoomToSplit->SetLeftLeaf(LeftLeaf);
    RoomToSplit->SetRightLeaf(RightLeaf);
    	
	LeftLeaf->SetParent(RoomToSplit);
	RightLeaf->SetParent(RoomToSplit);
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
