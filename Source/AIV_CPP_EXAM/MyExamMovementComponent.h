// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MyExamMovementComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class AIV_CPP_EXAM_API UMyExamMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector GravityOverride{ 0,0,-9.81 };
	UPROPERTY(VisibleAnywhere)
	bool bIsGrounded;


	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

	UFUNCTION(BlueprintCallable)
	void MoveForwardRight(FVector2D InputAxis);
};