// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

class UBinarySpacePartitionComponent;

UCLASS()
class BSPDUNGEON_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UBinarySpacePartitionComponent* BinarySpacePartitionComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBinarySpacePartitionComponent* GetBinarySpacePartitionComponent() const { return BinarySpacePartitionComponent; }
};


