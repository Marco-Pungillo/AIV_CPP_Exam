// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "ITelekineticObject.h"
#include "Impulsable.h"

//Utility libraries
#include "Kismet/KismetMathLibrary.h"

#include "ExamTelekinesisComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class AIV_CPP_EXAM_API UExamTelekinesisComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UExamTelekinesisComponent();


#pragma region Components
	
	UPrimitiveComponent* TelekinesisOrigin;
	USceneComponent* ControlledBody;
	UCameraComponent* TelekinesisCamera;
	IITelekineticObject* ControlledTelekineticActor;

#pragma endregion

#pragma region Parameters
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisRange = 200;
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float TelekinesisStrenght = 25;
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float MinControlledBodyOffset;
	UPROPERTY(EditAnywhere, Category = "Telekinesis Parameters")
	float MaxControlledBodyOffset;
	float ControlledBodyOffset; 
#pragma endregion

	UFUNCTION(BlueprintCallable)
	void SetTelekinesisOrigin(UPrimitiveComponent* origin);

#pragma region Hold-Release
	UFUNCTION(BlueprintCallable)
	void ApplyTelekineticHold(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);

	UFUNCTION(BlueprintCallable)
	void StopTelekineticHold();

#pragma endregion

#pragma region Close-Far
	UFUNCTION(BlueprintCallable)
	void TelekineticPush();
	UFUNCTION(BlueprintCallable)
	void TelekineticPull();


#pragma endregion

#pragma region ImpulseAndForces
	UFUNCTION(BlueprintCallable)
	void TelekineticImpulse(UWorld* World, FVector StartPosition, FVector Direction, ECollisionChannel TelekinesisChannel);
	UFUNCTION(BlueprintCallable)
	void TelekineticLaunch();

#pragma endregion


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FHitResult* TelekinesisRay(UWorld* World, FVector StartPosition, FVector EndPosition, ECollisionChannel TelekinesisChannel);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		


};
