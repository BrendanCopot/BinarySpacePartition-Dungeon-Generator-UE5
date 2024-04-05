// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonGenerator.h"

#include "BSPAlgorithms.h"
#include "DungeonRoom.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

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

	BSPAlgorithmsReference = new FBSPAlgorithms;
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	// Clear Previous Instances.
	ClearMeshInstance(FloorMeshInstance);
	
	// Recursively split a grid into smaller grids to make up rooms for the dungeon.
	TArray<FDungeonRoom*> DungeonRooms;
	DungeonRooms = BSPAlgorithmsReference->BSPSplit(DungeonRooms, Rows, Columns, RoomTrim, Origin, MaxRooms,
		MinRoomSizeX, MinRoomSizeY, GetMeshWidth(FloorMesh, FloorMeshScale), GetMeshHeight(FloorMesh, FloorMeshScale));

	for (FDungeonRoom*& DungeonRoom : DungeonRooms)
	{
		DungeonRoom->DrawFloorInstancedMesh(GetMeshWidth(FloorMesh, FloorMeshScale), GetMeshHeight(FloorMesh, FloorMeshScale), FloorMeshScale, FloorMeshInstance);
	}
		
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance)
{
	MeshInstance->ClearInstances();
	
	UE_LOG(LogTemp, Warning, TEXT("Cleared Mesh Instances"));
}



