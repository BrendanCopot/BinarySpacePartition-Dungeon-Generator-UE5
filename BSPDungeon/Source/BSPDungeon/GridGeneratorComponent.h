// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GridGeneratorComponent.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BSPDUNGEON_API UGridGeneratorComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Grid Variables
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridWidth = 10;
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridLength = 10;
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	int GridHeight = 1;
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	float GridOffsetX = 0;
	UPROPERTY(EditAnywhere, Category = "Grid Variables", meta=(AllowPrivateAccess = "true"))
	float GridOffsetY = 0;
	
	UPROPERTY(EditAnywhere, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	float CellSize = 5;
	UPROPERTY(EditDefaultsOnly, Category = "Instanced Mesh Variables", meta=(AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* CellFloorMeshInstance;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
