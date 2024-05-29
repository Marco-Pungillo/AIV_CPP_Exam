// Fill out your copyright notice in the Description page of Project Settings.


#include "ExamBaseMovingPlatfrom.h"

// Sets default values
AExamBaseMovingPlatfrom::AExamBaseMovingPlatfrom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->PlatformBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformBody"));
	FString MeshPath = "/Game/LevelPrototyping/Meshes/SM_Cube.SM_Cube";
	UStaticMesh * Mesh = LoadObject<UStaticMesh>(nullptr, *MeshPath);
	if (Mesh)
	{
		this->PlatformBody->SetStaticMesh(Mesh);
	}
}

// Called when the game starts or when spawned
void AExamBaseMovingPlatfrom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExamBaseMovingPlatfrom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementBehavior(DeltaTime);
}

void AExamBaseMovingPlatfrom::MovementBehavior(float DeltaTime)
{
	// Wait Status
	if (bIsWaiting)
	{
		WaitInPositionCounter -= DeltaTime;
		if (WaitInPositionCounter <= 0)
		{
			bIsWaiting = false;
		}
	}
	// Movement Status
	else
	{
		if (((this->GetActorLocation() - Positions[PositionIndex]).SizeSquared()) <= AcceptableRadius * AcceptableRadius)
		{
			// Set waiting
			bIsWaiting = true;
			WaitInPositionCounter = WaitInPositionTime;

			// Resetting Movement
			MovementTimeAccumulator = 0;
			UE_LOG(LogTemp, Warning, TEXT("Destination Reached"));

			if (PositionIndex >= Positions.Num() - 1 || ((PositionIndex <= 0)))
			{
				IndexChangerValue *= -1;
			}
			PositionIndex += IndexChangerValue;
		}
		else
		{
			MovementTimeAccumulator += DeltaTime;
			this->SetActorLocation(FMath::Lerp(Positions[PositionIndex - IndexChangerValue], Positions[PositionIndex], MovementTimeAccumulator / MovementDuration));
		}
	}
}