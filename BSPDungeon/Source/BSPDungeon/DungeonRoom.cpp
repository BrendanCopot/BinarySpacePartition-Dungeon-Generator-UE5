#include "DungeonRoom.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

FDungeonRoom::FDungeonRoom(int Rows, int Cols, int Trim, FVector Origin)
{
	RoomRows = Rows;
	RoomCols = Cols;
	RoomTrim = Trim;
	RoomOrigin = Origin;
}

FDungeonRoom::~FDungeonRoom()
{
	
}

void FDungeonRoom::DrawFloorInstancedMesh(int MeshWidth, int MeshHeight, int MeshScale, UHierarchicalInstancedStaticMeshComponent* MeshInstance) const
{
	// Iterate through each cell of the room using rows and columns.
	for (int i = RoomTrim; i <= RoomRows - RoomTrim; i++)
	{
		for (int j = RoomTrim; j <= RoomCols - RoomTrim; j++)
		{
			
			// Calculate the spawn position of the static mesh instance within the room.
			// The position is determined based on the room's origin, mesh width, height, and iteration indices.
			const float SpawnPosX = RoomOrigin.X + (i + MeshWidth * i);
			const float SpawnPosY = RoomOrigin.Y + (j + MeshHeight * j);

			// Create a vector representing the spawn position.
			FVector SpawnPosition = FVector(SpawnPosX, SpawnPosY, 0);
			// Define the scale of the static mesh instance.
			FVector Scale = FVector(MeshScale, MeshScale, 1);

			// Add an instance of the static mesh to the grid at the calculated position and scale.
			// The instance is added to the GridMeshInstance object.
			MeshInstance->AddInstance(FTransform(FRotator(0), SpawnPosition, Scale), true);
		}
	}
}
