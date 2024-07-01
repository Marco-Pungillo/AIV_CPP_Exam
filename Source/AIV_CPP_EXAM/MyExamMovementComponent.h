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
#pragma region Parameters
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float movementSpeed = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float movementMaxSpeed = 200;
	UPROPERTY(EditAnywhere)
	FVector GravityOverride{ 0,0,-9.81 };
	UPROPERTY(VisibleAnywhere)
	bool bIsGrounded;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector CurrentAccelleration = {0,0,0};

#pragma endregion

	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;

	#pragma region Translation
	bool bCannotMoveForward = false;
	bool bCannotMoveBackward = false;
	bool bCannotMoveRight = false;
	bool bCannotMoveLeft = false;

	UFUNCTION(BlueprintCallable)
	void MoveForwardRight(FVector2D InputAxis);
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Input);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Input);
	UFUNCTION(BlueprintCallable)
	#pragma endregion
	const bool IsFalling();

	#pragma region Rotation
	UFUNCTION(BlueprintCallable)
	void Rotate(FVector2D RotationAxis);

	#pragma endregion



};