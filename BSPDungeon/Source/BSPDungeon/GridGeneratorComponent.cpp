// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGeneratorComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values for this component's properties
UGridGeneratorComponent::UGridGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	CellFloorMeshInstance = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("CellFloorInstancedMesh"));
	CellFloorMeshInstance->SetupAttachment(Cast<USceneComponent>(this));
	
	for (int i = 0; i < GridWidth; i++)
	{
		for (int j = 0; j < GridLength; j++)
		{
			//CellFloorMeshInstance->AddInstance(FTransform(FVector(0, 0, 0)), false);
		}
	}
}


// Called when the game starts
void UGridGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGridGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

