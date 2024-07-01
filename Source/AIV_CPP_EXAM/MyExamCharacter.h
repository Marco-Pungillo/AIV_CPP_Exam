// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

// Including useful libraries
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"

// Including Components
#include "MyExamMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ExamTelekinesisComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Including Input System
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "MyExamCharacter.generated.h"

//Forward Declaration
class UInputMappingContext;
class UInputAction;

UCLASS()
class AIV_CPP_EXAM_API AMyExamCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyExamCharacter();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UExamTelekinesisComponent* TelekinesisComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CharacterCameraInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraBoomInstance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UWorld* CurrentWorld;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraPitchLimit;


	#pragma region Inputs

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* ExamMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PushForceAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PullForceAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

	void ApplyPushForce(const FInputActionValue& Value);
	void ApplyPullForce(const FInputActionValue& Value);
	void StopForce(const FInputActionValue& Value);

	#pragma endregion
private:

	void SetUpCharacterMesh();
	void SetUpCharacterCamera();
	void SetUpMovementParams();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
