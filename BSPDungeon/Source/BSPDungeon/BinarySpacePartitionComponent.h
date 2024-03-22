// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Containers/CircularQueue.h"
#include "BinarySpacePartitionComponent.generated.h"

class BinaryRoom;
class UGridGeneratorComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BSPDUNGEON_API UBinarySpacePartitionComponent : public USceneComponent
{
	GENERATED_BODY()

	/** GRID VARIABLES **/
	// The number of rows the grid will generate.
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridRows = 30;
	// The number of columns the grid will generate.
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridColumns = 35;
	// The number of layers the grid will generate
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridLayers = 1;
	// The grids distance from the origin point of this asset, along the X axis.
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	float GridOffsetX = 0;
	// The grids distance from the origin point of this asset, along the Y axis.
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	float GridOffsetY = 0;
	// The initial position of this asset in world space at runtime.
	UPROPERTY(VisibleAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	FVector GridOrigin;
	// An array holding the position of each cell in the grid
	UPROPERTY(VisibleAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	TArray<FVector> GridCellPositions;

	/** INSTANCED MESH VARIABLES **/
	// Adjusts the scale of the mesh we are generating
	UPROPERTY(EditAnywhere, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	float MeshScale = 5;
	// Default width of the static mesh
	UPROPERTY(VisibleAnywhere, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	int MeshWidth;
	// Default height of the static mesh
	UPROPERTY(VisibleAnywhere, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	int MeshHeight;
	// Mesh instance of the static mesh we are spawning in
	UPROPERTY(EditDefaultsOnly, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* GridMeshInstance;
	// Variables storing the static mesh we are instancing
	UPROPERTY(EditDefaultsOnly, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	UStaticMesh* GridMesh;
	
	/** BINARY SPACE PARTITION VARIABLES **/
	UPROPERTY(EditAnywhere, Category = "BSP Variables", meta=(AllowPrivateAccess = "true"))
	int RoomTrim = 1;
	UPROPERTY(EditAnywhere, Category = "BSP Variables", meta=(AllowPrivateAccess = "true"))
	int MinRoomSizeX = 4 + RoomTrim;
	UPROPERTY(EditAnywhere, Category = "BSP Variables", meta=(AllowPrivateAccess = "true"))
	int MinRoomSizeY = 6 + RoomTrim;
	UPROPERTY(EditAnywhere, Category = "BSP Variables", meta=(AllowPrivateAccess = "true"))
	int MaxRooms = 500;
	
	BinaryRoom* InitialBinaryRoom;
	
	/** FUNCTIONS **/
	// Clears the mesh instance of all previous mesh instances
	static void ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance);

public:	
	// Sets default values for this component's properties
	UBinarySpacePartitionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void BSPSplit();
	void DrawInstancedMesh(TArray<BinaryRoom*>& BinaryRoomsArray);

	void VerticalSplit(const BinaryRoom* RoomToSplit, TQueue<BinaryRoom*>& RoomsQueue);

	void HorizontalSplit(const BinaryRoom* RoomToSplit, TQueue<BinaryRoom*>& RoomsQueue);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
