// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGeneratorComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values for this component's properties
UGridGeneratorComponent::UGridGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
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
}

// Called when the game starts
void UGridGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the width and length of the static mesh, and scale by mesh size variable
	MeshWidth  = GridMesh->GetBoundingBox().GetSize().X * MeshScale;
	MeshLength = GridMesh->GetBoundingBox().GetSize().Y * MeshScale;
	
	// Clear Previous Instances
	ClearMeshInstance(GridMeshInstance);
	
	// Add new static mesh instances for each cell of the grid
	for (int i = 0; i < GridRows; i++)
	{
		for (int j = 0; j < GridColumns; j++)
		{
			const float SpawnPosX = GridOrigin.X + (i + MeshWidth * i);
			const float SpawnPosY = GridOrigin.Y + (j + MeshLength * j);
			
			FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
			FVector Scale = FVector(MeshScale, MeshScale, 1);
			
			GridMeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);

			GridCellPositions.Add(SpawnPosition); 
		}
	}
}

// Called every frame
void UGridGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridGeneratorComponent::ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance)
{
	MeshInstance->ClearInstances();

	UE_LOG(LogTemp, Warning, TEXT("Cleared Mesh Instances"));
}