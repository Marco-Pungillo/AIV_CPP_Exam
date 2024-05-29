// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Including Components
#include "MyExamMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ExamTelekinesisComponent.h"

// Including Input System
#include "InputActionValue.h"
#include "MyExamPawn.generated.h"

//Forward Declaration
class UInputMappingContext;
class UInputAction;

UCLASS()
class AIV_CPP_EXAM_API AMyExamPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyExamPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCapsuleComponent* Capsule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMyExamMovementComponent* MovementComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* PawnCameraInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraBoomInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UExamTelekinesisComponent* TelekinesisComponentInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UWorld* CurrentWorld;

	#pragma region Inputs

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* ExamMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PushForceAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PullForceAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ApplyPushForce(const FInputActionValue& Value);
	void ApplyPullForce(const FInputActionValue& Value);
	void StopForce();

#pragma endregion


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
