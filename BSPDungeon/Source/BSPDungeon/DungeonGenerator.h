// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class FDungeonRoom;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class BSPDUNGEON_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

	// The number of rows used to generate the dungeon.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int Rows = 50;
	// The number of columns used to generate the dungeon.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int Columns = 40;
	// The initial position of this asset in world space at runtime.
	UPROPERTY(VisibleAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	FVector Origin;
	// The amount or rows and columns trimmed from the outer cells of the room.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int RoomTrim = 1;
	// The minimum amount of rows a room can be made from.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int MinRoomSizeX = 4 + RoomTrim;
	// The minimum amount of columns a room can be made from.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int MinRoomSizeY = 6 + RoomTrim;
	// The maximum amount of rooms that can be generated in the dungeon.
	UPROPERTY(EditAnywhere, Category = "Dungeon Variables", meta=(AllowPrivateAccess = "true"))
	int MaxRooms = 15;

	/** INSTANCED MESH VARIABLES **/
	// Adjusts the scale of the mesh we are generating
	UPROPERTY(EditAnywhere, Category = "Floor Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	float FloorMeshScale = 5;
	// Mesh instance of the static mesh we are spawning in
	UPROPERTY(EditDefaultsOnly, Category = "Floor Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* FloorMeshInstance;
	// Variables storing the static mesh we are instancing
	UPROPERTY(EditDefaultsOnly, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	UStaticMesh* FloorMesh;
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BSPSplit();
	void VerticalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue) const;
	void HorizontalSplit(const FDungeonRoom* RoomToSplit, TQueue<FDungeonRoom*>& RoomsQueue) const;
	
	// Clears the mesh instance of all previous mesh instances.
	static void ClearMeshInstance(UHierarchicalInstancedStaticMeshComponent* MeshInstance);
	void DrawInstancedMesh(TArray<FDungeonRoom*>& BinaryRoomsArray);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	static int GetMeshWidth(const UStaticMesh* Mesh, const int MeshScale)  {return Mesh->GetBoundingBox().GetSize().X * MeshScale; }
	static int GetMeshHeight(const UStaticMesh* Mesh, const int MeshScale) {return Mesh->GetBoundingBox().GetSize().Y * MeshScale; }

};


