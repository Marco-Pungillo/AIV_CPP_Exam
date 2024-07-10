// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "ExamBaseMovingPlatfrom.generated.h"

UCLASS()
class AIV_CPP_EXAM_API AExamBaseMovingPlatfrom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExamBaseMovingPlatfrom();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PlatformBody;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	#pragma region Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> Positions;
	int32 PositionIndex=1;
	int32 IndexChangerValue = 1;
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;
	UPROPERTY(EditAnywhere)
	float MovementDuration = 1;
	UPROPERTY(EditAnywhere)
	float WaitInPositionTime;
	float WaitInPositionCounter = WaitInPositionTime;
	float MovementTimeAccumulator;
	bool bIsWaiting = true;

	void MovementBehavior(const float DeltaTime);
	#pragma endregion



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
